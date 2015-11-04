# /*
# <License>
# Copyright 2015 Virtium Technology
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# http ://www.apache.org/licenses/LICENSE-2.0
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# </License>
# */

import os
import shutil
import subprocess

X86                         = "Win32"
X64                         = "x64"
RELEASE_NAME                = "Release"
MS_BUILD                    = "MsBuild"
CONFIGURATION_BUILD_TYPE    = "/p:Configuration={0}".format( RELEASE_NAME )
BUILD_PLATFORM_X86          = "/p:Platform={0}".format( X86 )
BUILD_PLATFORM_X64          = "/p:Platform={0}".format( X64 )
REBUILD_DEFAULT             = "/t:rebuild"

projectName                 = "vtStor"
RELEASE_LOCAL_DIR_X86       = "./{0}{1}".format( X86, RELEASE_NAME )
RELEASE_LOCAL_DIR_X64       = "./{0}{1}".format( X64, RELEASE_NAME )
ARCHIVE_TEMP                = "ArchiveTemp"
ARCHIVE_TEMP_PATH           = "./{0}/".format( ARCHIVE_TEMP )

REMOVE_EXTENSION_SET = { 'lib', 'pdb' }

def _Build( iBuildPlatform ) :
    status = subprocess.call( [ MS_BUILD, CONFIGURATION_BUILD_TYPE, iBuildPlatform, REBUILD_DEFAULT ] )
    if 0 != status :
        print "\nBuild failed for {0} {1}".format( RELEASE_NAME, X86 )
        return False
    return True

def _CopyRequiredFiles( iConfiguration ) :
    if X86 == iConfiguration :
        shutil.copytree( RELEASE_LOCAL_DIR_X86, ARCHIVE_TEMP_PATH + projectName + "/{0}/".format( iConfiguration ) )
    elif X64 == iConfiguration :
        shutil.copytree( RELEASE_LOCAL_DIR_X64, ARCHIVE_TEMP_PATH + projectName + "/{0}/".format( iConfiguration ) )

def _BuildAndCopyAllRequiredFiles() :
    # Build via following orders:
    if False == _Build( BUILD_PLATFORM_X86 ) :
        exit( 1 )
    _CopyRequiredFiles( X86 )
    if False == _Build( BUILD_PLATFORM_X64 ) :
        exit( 1 )
    _CopyRequiredFiles( X64 )

def _CreateTempDirArchive() :
    if ( True == os.path.exists( ARCHIVE_TEMP_PATH ) ):
        shutil.rmtree( ARCHIVE_TEMP_PATH, ignore_errors=True )
    os.makedirs( ARCHIVE_TEMP_PATH )
    os.makedirs( ARCHIVE_TEMP_PATH + projectName )

def _DoArchiveAndRemoveTempDirs() :
    archiveFilename = projectName + "_Release.7z"
    if ( True == os.path.exists( archiveFilename ) ):
        os.remove( archiveFilename )

    status = subprocess.call( [ "7z", "a", "-t7z", archiveFilename, ARCHIVE_TEMP_PATH + projectName ] )
    if ( 0 != status ):
        print "\nFailed to archive " + archiveFilename
        return False

    shutil.rmtree( ARCHIVE_TEMP_PATH, ignore_errors = True )
    return True

def _CleanUpRelease() :
    _CleanupFiles( X86 )
    _CleanupFiles( X64 )

def _CleanupFiles( iConfiguration ) :
    if X86 == iConfiguration or X64 == iConfiguration :
        _Prune( "/{0}/{1}/{2}".format( ARCHIVE_TEMP, projectName, iConfiguration ) )

def _Prune( iDirPath ) :
    curDir = os.getcwd()
    fullPath = curDir + iDirPath
    os.chdir( fullPath )
    files = os.listdir( fullPath )
    for file in files :
        for removeExtenstion in REMOVE_EXTENSION_SET :
            if (True == os.path.isfile( file )) and (True == file.endswith( removeExtenstion )) :
                os.remove( file )
    os.chdir( curDir )

# Main entry point
if __name__ == "__main__":
    # Step 1: Create temporary directory archive
    _CreateTempDirArchive()

    # Step 2: Build the project
    _BuildAndCopyAllRequiredFiles()

    # Step 3: Clean up release
    _CleanUpRelease()

    # Step 4: Archive result and remove temporary thing
    if True == _DoArchiveAndRemoveTempDirs() :
        print "\nBUILD COMPLETE"
    else :
        print "\nBUILD FAIL"
        exit( 1 )