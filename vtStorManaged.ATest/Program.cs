/*
<License>
Copyright 2015 Virtium Technology

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http ://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
</License>
*/

using vtStor.Ata.Managed;
using vtStor.Managed;
using vtStor.Protocol.Managed;
using vtStor.Scsi.Managed;

namespace vtStorManaged.ATest
{
    class Program
    {
        static void Main(string[] args)
        {
            uint driveCount;
            eErrorCode errorCode;
            string path = System.AppDomain.CurrentDomain.BaseDirectory;
            ILoadRunTimeDll vtStorDll = new cLoadRunTimeDll("vtStor.dll");
            ILoadRunTimeDll vtStorAtaDll = new cLoadRunTimeDll("vtStorAta.dll");
            ILoadRunTimeDll vtStorScsiDll = new cLoadRunTimeDll("vtStorScsi.dll");
            ILoadRunTimeDll vtStorAtaProtocolDll = new cLoadRunTimeDll("vtStorAtaProtocol.dll");
            ILoadRunTimeDll vtStorScsiProtocolDll = new cLoadRunTimeDll("vtStorScsiProtocol.dll");
            IRunTimeDll vtStorModule = vtStorDll.Load();
            IRunTimeDll vtStorAtaModule = vtStorAtaDll.Load();
            IRunTimeDll vtStorScsiModule = vtStorScsiDll.Load();
            IRunTimeDll vtStorAtaProtocolModule = vtStorAtaProtocolDll.Load();
            IRunTimeDll vtStorScsiProtocolModule = vtStorScsiProtocolDll.Load();

            cDriveManagerInterface driveManager = new cDriveManagerInterface(vtStorModule);

            // Register drive enumerators
            driveManager.RegisterDriveEnumerator(new cDriveEnumeratorAta(vtStorAtaModule));
            driveManager.RegisterDriveEnumerator(new cDriveEnumeratorScsi(vtStorScsiModule));

            // Enumerate drives
            errorCode = driveManager.EnumerateDrives(vtStor.Managed.eScanForHardwareChanges.Yes);
            if (eErrorCode.None == errorCode)
            {
                System.Console.WriteLine("Enumerate drive successfully!!!");

                // Retrieve number of enumerate drives
                driveCount = driveManager.GetDriveCount();
                System.Console.WriteLine("Drive count: " + driveCount);

                cProtocolInterface protocol = null;
                cCommandHandlerInterface commandHandler = null;

                if (0 < driveCount)
                {
                    cBufferInterface buffer = new cBufferInterface(vtStorModule, 512);
                    cDriveInterface drive = driveManager.GetDrive(0);   //!!! Warning: be careful with value 0 in GetDrive(0)
                    string devicePath = drive.GetDevicePath();

                    if (eBusType.Ata == drive.GetBusType())
                    {
                        protocol = new cProtocolAtaPassThrough(vtStorAtaProtocolModule);
                        commandHandler = new cCommandHandlerAta(vtStorAtaModule, protocol);

                        // Register command handler to drive
                        drive.RegisterCommandHandler(0, commandHandler);

                        cAtaCommandExtensions ataCommandExtensions = new cAtaCommandExtensions(vtStorAtaModule);

                        errorCode = ataCommandExtensions.IssueCommand_IdentifyDevice(drive, 0, buffer);
                    }
                    else if (eBusType.Scsi == drive.GetBusType())
                    {
                        protocol = new cProtocolScsiPassThrough(vtStorScsiProtocolModule);
                        commandHandler = new cCommandHandlerScsi(vtStorScsiModule, protocol);

                        // Register command handler to drive
                        drive.RegisterCommandHandler(0, commandHandler);

                        cScsiCommandExtensions scsiCommandExtensions = new cScsiCommandExtensions(vtStorScsiModule);

                        errorCode = scsiCommandExtensions.IssueCommand_AtaIdentifyDevice(drive, 0, buffer);
                    }

                    if (eErrorCode.None == errorCode)
                    {
                        System.Console.WriteLine("IssueCommand_IdentifyDevice on drive 0 successfully!!!");
                        for (uint i = 0; i < 512; i++)
                        {
                            if (i % 16 == 15)
                                System.Console.WriteLine((buffer.GetByteAt(i)).ToString("X2"));
                            else
                                System.Console.Write("{0} ", (buffer.GetByteAt(i)).ToString("X2"));
                        }
                    }
                    else
                    {
                        System.Console.WriteLine("IssueCommand_IdentifyDevice failed!!!");
                    }
                    System.Console.ReadKey();
                }
            }
            else
            {
                System.Console.WriteLine("Enumerate drive failed!!!");
            }
        }
    }
}
