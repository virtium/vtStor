# /*
# <License>
# Copyright 2016 Virtium Technology
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
RELEASE_DIR                 = "/{0}/".format( RELEASE_NAME )
LIB_DIR                     = "/{0}/{1}/".format( "lib","Windows" )
DLL_DIR                     = "/{0}/".format( "dll" )
INCLUDE_DIR                 = "/{0}/".format( "inc" )
EXCLUDE_DIR_NAMES           = { "Internal", "SampleCode", "GenerateFiles" } 

MS_BUILD                    = "MSBuild"

CONFIGURATION_BUILD_TYPE_SET    = { "/p:Configuration={0}".format( RELEASE_NAME ) } 

BUILD_PLATFORM_X86          = "/p:Platform={0}".format( X86 )
BUILD_PLATFORM_X64          = "/p:Platform={0}".format( X64 )
REBUILD_DEFAULT             = "/t:rebuild"

projectName                 = "vtStor"
PROJECTDIR                  = "vtStor_Release"
RELEASE_LOCAL_DIR_X86       = "./{0}{1}".format( X86, RELEASE_NAME )
RELEASE_LOCAL_DIR_X64       = "./{0}{1}".format( X64, RELEASE_NAME )
ARCHIVE_TEMP                = "ArchiveTemp"
ARCHIVE_TEMP_PATH           = "./{0}/".format( ARCHIVE_TEMP )

REMOVE_EXTENSION_SET = { 'exe', 'pdb' }

def Build( iBuildPlatform ) :
    for config in CONFIGURATION_BUILD_TYPE_SET:
        status = subprocess.call( [ MS_BUILD, config, iBuildPlatform, REBUILD_DEFAULT ] )
        if 0 != status :
            print "\nBuild failed for {0} {1}".format( config, iBuildPlatform )
            return False
    return True

def CopyRequireFilesForAllModes ( iConfiguration ) :
    CopyLibsAndDlls( iConfiguration, RELEASE_NAME )

def CopyLibsAndDlls( iConfiguration, iBuildType ) :
    sourceDir = "./{0}{1}".format( iConfiguration, iBuildType )
    for file in os.listdir( sourceDir ) :            
        if file.endswith( ".dll" ) or file.endswith( ".lib" ):
            destDir = ARCHIVE_TEMP_PATH + PROJECTDIR + LIB_DIR + "/{0}/".format( iConfiguration )
            CopyAFileToADir( sourceDir, file, destDir)

def CopyAFileToADir( iSourceDir, iFile, iDestDir) :
    if not os.path.exists( iDestDir ) :
        os.makedirs(iDestDir )
    shutil.copy2( os.path.join( iSourceDir, iFile ),  iDestDir )

def BuildAndCopyAllRequiredFiles() :
    # Build via following orders:
    if False == Build( BUILD_PLATFORM_X86 ) :
        exit( 1 )
    CopyRequireFilesForAllModes( X86 )
    if False == Build( BUILD_PLATFORM_X64 ) :
        exit( 1 )
    CopyRequireFilesForAllModes( X64 )

def CreateTempDirArchive() :
    if ( True == os.path.exists( ARCHIVE_TEMP_PATH ) ):
        shutil.rmtree( ARCHIVE_TEMP_PATH, ignore_errors=True )
    os.makedirs( ARCHIVE_TEMP_PATH )
    os.makedirs( ARCHIVE_TEMP_PATH + PROJECTDIR )

def DoArchiveAndRemoveTempDirs() :
    archiveFilename = projectName + "_Release.7z"
    if ( True == os.path.exists( archiveFilename ) ):
        os.remove( archiveFilename )

    status = subprocess.call( [ "7z", "a", "-t7z", archiveFilename, ARCHIVE_TEMP_PATH + PROJECTDIR ] )
    if ( 0 != status ):
        print "\nFailed to archive " + archiveFilename
        return False

    shutil.rmtree( ARCHIVE_TEMP_PATH, ignore_errors = True )
    return True

def CleanUpRelease() :
    CleanupFiles( X86 )
    CleanupFiles( X64 )

def CleanupFiles( iConfiguration ) :
    if X86 == iConfiguration or X64 == iConfiguration :
        Prune( "/{0}/{1}/{2}/{3}".format( ARCHIVE_TEMP, PROJECTDIR, LIB_DIR, iConfiguration ) )

def Prune( iDirPath ) :
    curDir = os.getcwd()
    fullPath = curDir + iDirPath
    os.chdir( fullPath )
    files = os.listdir( fullPath )
    for file in files :
        for removeExtenstion in REMOVE_EXTENSION_SET :
            if (True == os.path.isfile( file )) and (True == file.endswith( removeExtenstion )) :
                os.remove( file )
    os.chdir( curDir )

def BuildTreeOfHeaderFiles() :
    for path, subdirs, files in os.walk(os.getcwd()):
        for file in files:
            if file.endswith(".h") :
                CopyHeaderFile( os.path.join(path, file) )
    destDir = ARCHIVE_TEMP_PATH + PROJECTDIR + INCLUDE_DIR
    srcDir = "./{0}/".format( "inc" )
    if not os.path.exists( destDir ) :
        os.makedirs( destDir )
    for item in os.listdir( srcDir ):
        s = os.path.join( srcDir, item )
        d = os.path.join( destDir, item )
        if os.path.isdir(s):
            shutil.copytree( s, d, False, None )
        else:
            shutil.copy2( s, d )
    shutil.rmtree( srcDir )

def CopyHeaderFile( iFilePath ) :
    currentDir = os.path.relpath( os.path.dirname( iFilePath ), os.getcwd() )
    if False == CheckExcludeDirectories( currentDir ) :
        return
    destDir = os.path.join( os.getcwd(), "inc", os.path.relpath( os.path.dirname( iFilePath ), os.getcwd() ) );
    if not os.path.exists( destDir ) :
        os.makedirs( destDir )
    shutil.copy2( iFilePath,  destDir )

def CheckExcludeDirectories( iFilePath ) :
    for eachname in EXCLUDE_DIR_NAMES :
        if( iFilePath.find( eachname ) != -1 ) :
            return False
    return True
    
# Main entry point
if __name__ == "__main__":
    # Step 0: Create temporary directory archive
    CreateTempDirArchive()
    
    # Step 1: Copy header files
    BuildTreeOfHeaderFiles()
    
    # Step 2: Build the project
    BuildAndCopyAllRequiredFiles()

    # Step 3: Clean up release
    CleanUpRelease()

    # Step 4: Archive result and remove temporary thing
    if True == DoArchiveAndRemoveTempDirs() :
        print "\nBUILD COMPLETE"
    else :
        print "\nBUILD FAIL"
        exit( 1 )