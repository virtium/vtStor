import os
import os.path
import shutil
import sys

def CreateRequiredDirectoriesAndCopyFiles( ProjectName, SourceBinDirectory, exportRootDirectory ):
    exportDirectory = os.path.join( exportRootDirectory, "export" )
    projectExportDirectory = os.path.join( exportDirectory, ProjectName )
    projectExportIncDirectory = os.path.join( projectExportDirectory, "inc" )
    projectExportBinDirectory = os.path.join( projectExportDirectory, "bin" )

    if not os.path.exists( exportDirectory ):
        print "\n..Creating " + exportDirectory
        os.makedirs( exportDirectory )

    if not os.path.exists( projectExportDirectory ):
        print "\n..Creating " + projectExportDirectory
        os.makedirs( projectExportDirectory )

    if not os.path.exists( projectExportIncDirectory ):
        print "\n..Creating " + projectExportIncDirectory
        os.makedirs( projectExportIncDirectory )

    if not os.path.exists( projectExportBinDirectory ):
        print "\n..Creating " + projectExportBinDirectory
        os.makedirs( projectExportBinDirectory )

    libFile = os.path.join( sourceBinDirectory, projectName + ".lib" )
    dllFile = os.path.join( sourceBinDirectory, projectName + ".dll" )

    destinationLibFile = os.path.join( projectExportBinDirectory, projectName + ".lib" )
    print "\n..Copying " + libFile + " to " + destinationLibFile
    shutil.copyfile( libFile, destinationLibFile )

    destinationDllFile = os.path.join( projectExportBinDirectory, projectName + ".dll" )
    print "\n..Copying " + dllFile + " to " + destinationDllFile
    shutil.copyfile( dllFile, destinationDllFile )

# Main entry point
if __name__ == "__main__":
    print "\nRunning PostBuildExport..."
    if ( len( sys.argv ) < 4 ):
        print "\n  Not enough information provided."
        exit(1)
    
    projectName = sys.argv[ 1 ]
    sourceBinDirectory = sys.argv[ 2 ]
    exportRootDirectory = sys.argv[ 3 ]
    CreateRequiredDirectoriesAndCopyFiles( projectName, sourceBinDirectory, exportRootDirectory )
