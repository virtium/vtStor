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

using Microsoft.VisualStudio.TestTools.UnitTesting;
using vtStor.Managed;

namespace vtStorManaged.Test
{
    [TestClass]
    public class vtStorManagedTest
    {
        [TestMethod]
        public void Enumeration()
        {
            Enumerate();
        }

        private void Enumerate()
        {
            cDriveManagerInterface driveManager;
            cDriveEnumeratorInterface driveEnumerator;
            eErrorCode errorCode;
            ILoadRunTimeDll vtStorUnifiedDll = new cLoadRunTimeDll("vtStorUnified.dll");
            IRunTimeDll vtStorUnifiedModule = vtStorUnifiedDll.Load();

            // Create an instance for DriveManager
            driveManager = new cDriveManagerInterface(vtStorUnifiedModule);

            // Create an instance for DriveEnumeratorAta
            driveEnumerator = new cDriveEnumerator(vtStorUnifiedModule);
            driveEnumerator = new cDriveEnumeratorAta(vtStorUnifiedModule, driveEnumerator);

            // Register drive enumerator Ata
            driveManager.RegisterDriveEnumerator(driveEnumerator);

            // Enumerate drives
            errorCode = driveManager.EnumerateDrives(eScanForHardwareChanges.Yes);
        }
    }
}
