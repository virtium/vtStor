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

import datetime
import os
import subprocess
import time

class cAssemblyInfoBuilder() :
    # These version will be managed by developers (the build number and revision will be generated automatically)
    MAJOR_VERSION = "1"
    MINOR_VERSION = "0"

    VERSION_PATCH_TOOL_PATH     = "Build\\VersionPatch.exe"

    # [/options]
    NO_VERSION_RESOURCE_KEY     = "/va"
    PRODUCT_VERSION_KEY         = "/pv"
    
    STRING_KEY                  = "/s"
    FILE_DESCRIPTION_STRING     = "FileDescription"
    PRODUCTION_NAME_STRING      = "ProductName"
    COPYRIGHT_STRING            = "copyright"
    
    # Default values
    COPYRIGHT_DEFAULT           = "Copyright (c) 2015"
    
    s_ProductVersion = None
    
    @staticmethod
    def Initialize() :
        cAssemblyInfoBuilder.s_ProductVersion = cAssemblyInfoBuilder.GenerateProductVersion()

    @staticmethod
    def Build( iDllFilePath ) :
        if None == cAssemblyInfoBuilder.s_ProductVersion:
            raise Exception("cAssemblyInfoBuilder.Initialize has not performed yet")

        dllFileName = os.path.basename( iDllFilePath )
        productName = os.path.splitext( dllFileName )[0] # Get dll filename without extension
    
        status = subprocess.call( [ cAssemblyInfoBuilder.VERSION_PATCH_TOOL_PATH,
                                    iDllFilePath, cAssemblyInfoBuilder.s_ProductVersion,
                                    cAssemblyInfoBuilder.PRODUCT_VERSION_KEY, cAssemblyInfoBuilder.s_ProductVersion,
                                    cAssemblyInfoBuilder.STRING_KEY, cAssemblyInfoBuilder.FILE_DESCRIPTION_STRING, productName,
                                    cAssemblyInfoBuilder.STRING_KEY, cAssemblyInfoBuilder.PRODUCTION_NAME_STRING, productName,
                                    cAssemblyInfoBuilder.STRING_KEY, cAssemblyInfoBuilder.COPYRIGHT_STRING, cAssemblyInfoBuilder.COPYRIGHT_DEFAULT,
                                    cAssemblyInfoBuilder.NO_VERSION_RESOURCE_KEY ] )
        if 0 != status :
            print "\Path build failed for {0} {1}".format( iDllFilePath, cAssemblyInfoBuilder.s_ProductVersion )
            return False
        return True
    
    @staticmethod
    def GenerateProductVersion() :
        [ buildNumber, revision ] = cAssemblyInfoBuilder.AutoGenerateBuildNumberAndRevision()
        
        # format assembly version MajorVersion.MinorVersion.BuildNumber.Revision
        return "{0}.{1}.{2}.{3}".format( cAssemblyInfoBuilder.MAJOR_VERSION, cAssemblyInfoBuilder.MINOR_VERSION, buildNumber, revision )
    
    @staticmethod
    def AutoGenerateBuildNumberAndRevision() :
        timeTuple       = datetime.datetime.now().timetuple()
        dateTimeNumber  = long(time.mktime(timeTuple))
    
        # Build number is the 16 first bit of dateTimeNumber
        buildNumber = ( dateTimeNumber & 0xffff0000 ) >> 16
        
        # Revision is the 16 last bit of dateTimeNumber
        revision    = dateTimeNumber & 0xffff
        return [ buildNumber, revision ]
