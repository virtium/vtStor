/*
<License>
Copyright 2016 Virtium Technology

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
using vtStor.AsynIo.Managed;
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
            ILoadRunTimeDll vtStorUnifiedDll = new cLoadRunTimeDll("vtStorUnified.dll");
            IRunTimeDll vtStorUnifiedModule = vtStorUnifiedDll.Load();

            cDriveManagerInterface driveManager = new cDriveManagerInterface(vtStorUnifiedModule);

            // Register drive enumerators
            cDriveEnumeratorInterface enumerateDecorator = new cDriveEnumerator(vtStorUnifiedModule);
            driveManager.RegisterDriveEnumerator(new cDriveEnumeratorScsi(vtStorUnifiedModule, new cDriveEnumeratorAta(vtStorUnifiedModule, enumerateDecorator)));

            // Enumerate drives
            errorCode = driveManager.EnumerateDrives(vtStor.Managed.eScanForHardwareChanges.Yes);
            if (eErrorCode.None == errorCode)
            {
                System.Console.WriteLine("Enumerate drive successfully!!!");

                // Retrieve number of enumerate drives
                driveCount = driveManager.GetDriveCount();
                System.Console.WriteLine("Drive count: " + driveCount);

                cProtocolInterface protocol, protocolAsynIo = null;
                cCommandHandlerInterface commandHandler, commandHandlerAsynIo = null;

                if (0 < driveCount)
                {
                    cBufferInterface buffer = new cBufferInterface(vtStorUnifiedModule, 512);
                    cDriveInterface drive = driveManager.GetDrive(0);   //!!! Warning: be careful with value 0 in GetDrive(0)
                    string devicePath = drive.GetDriveProperties().DevicePath;
                    uint physicalDiskNumber = drive.GetDriveProperties().PhysicalDiskNumber;

                    if (eBusType.Ata == drive.GetBusType())
                    {
                        protocol = new cProtocolAtaPassThrough(vtStorUnifiedModule);
                        commandHandler = new cCommandHandlerAta(vtStorUnifiedModule, protocol);

                        protocolAsynIo = new cProtocolAsynIo(vtStorUnifiedModule);
                        commandHandlerAsynIo = new cCommandHandlerAsynIo(vtStorUnifiedModule, protocolAsynIo);

                        // Register command handler to drive
                        drive.RegisterCommandHandler(0, commandHandler);
                        drive.RegisterCommandHandler(256, commandHandlerAsynIo);

                        cAtaCommandExtensions ataCommandExtensions = new cAtaCommandExtensions(vtStorUnifiedModule);
                        cAsynIoCommandExtensions asynIoCommandExtensions = new cAsynIoCommandExtensions(vtStorUnifiedModule);

                        errorCode = ataCommandExtensions.IssueCommand_IdentifyDevice(drive, 0, buffer);

                        // Issue asynIo commands
                        //cOverlapped overlapped = new cOverlapped(vtStorUnifiedModule);
                        //errorCode = asynIoCommandExtensions.IssueCommand_ReadAsynIo(drive, 256, buffer, 1, 0, overlapped);
                    }
                    else if (eBusType.Scsi == drive.GetBusType())
                    {
                        protocol = new cProtocolScsiPassThrough(vtStorUnifiedModule);
                        commandHandler = new cCommandHandlerScsi(vtStorUnifiedModule, protocol);

                        protocolAsynIo = new cProtocolAsynIo(vtStorUnifiedModule);
                        commandHandlerAsynIo = new cCommandHandlerAsynIo(vtStorUnifiedModule, protocolAsynIo);

                        // Register command handler to drive
                        drive.RegisterCommandHandler(0, commandHandler);
                        drive.RegisterCommandHandler(256, commandHandlerAsynIo);

                        cScsiCommandExtensions scsiCommandExtensions = new cScsiCommandExtensions(vtStorUnifiedModule);
                        cAsynIoCommandExtensions asynIoCommandExtensions = new cAsynIoCommandExtensions(vtStorUnifiedModule);

                        errorCode = scsiCommandExtensions.IssueCommand_AtaIdentifyDevice(drive, 0, buffer);

                        // Issue asynIo commands
                        //cOverlapped overlapped = new cOverlapped(vtStorUnifiedModule);
                        //errorCode = asynIoCommandExtensions.IssueCommand_ReadAsynIo(drive, 256, buffer, 1, 100, overlapped);
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
