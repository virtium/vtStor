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

namespace vtStorManaged.ATest
{
    class Program
    {
        static void Main(string[] args)
        {
            const uint commandTypeAta = 1;

            cDriveManagerInterface driveManager;
            cDriveEnumeratorInterface driveEnumeratorAta;
            uint driveCount;
            eErrorCode errorCode;

            // Create an instance for DriveManager
            driveManager = new cDriveManagerInterface();

            // Create an instance for DriveEnumeratorAta
            driveEnumeratorAta = new cDriveEnumeratorAta();

            // Set default command handler command type for Ata
            cAta.SetDefaultCommandHandlerCommandType(commandTypeAta);

            // Register drive enumerator Ata
            driveManager.RegisterDriveEnumerator(driveEnumeratorAta);

            // Enumerate drives
            errorCode = driveManager.EnumerateDrives();
            if (eErrorCode.None == errorCode)
            {
                System.Console.WriteLine("Enumerate drive successfully!!!");

                // Retrieve number of enumerate drives
                driveCount = driveManager.GetDriveCount();
                System.Console.WriteLine("Drive count: " + driveCount);

                if (0 < driveCount)
                {
                    cBufferInterface buffer = new cBufferInterface(512);
                    cDriveInterface drive = driveManager.GetDrive(0);
                    errorCode = cDriveAtaCommandExtensions.IssueCommand_IdentifyDevice(drive, commandTypeAta, buffer);
                    if (eErrorCode.None == errorCode)
                    {
                        System.Console.WriteLine("IssueCommand_IdentifyDevice on drive 0 successfully!!!");
                    }
                    else
                    {
                        System.Console.WriteLine("IssueCommand_IdentifyDevice failed!!!");
                    }
                }
            }
            else
            {
                System.Console.WriteLine("Enumerate drive failed!!!");
            }
        }
    }
}
