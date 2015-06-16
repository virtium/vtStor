import glob
import os
import os.path
import shutil
import sys

LONG_PATH_PREFIX = u"\\\\?\\"

# Copy all dll files from source directory to destination directory
def CopyAllFilesInSourceToDestination( iSourcePath, iDestinationPaths, iFilter = "*" ):
    fileList = glob.glob( iSourcePath + iFilter )
    for filePath in fileList :
        if True == os.path.isdir( filePath ) :
            CopyAllFilesInSourceToDestination( filePath + "/", iDestinationPaths, iFilter )
        elif ( os.path.splitext( filePath )[ 1 ] == ".dll" ) :
            CopyFileToDestination( filePath, iDestinationPaths )

def CopyFileToDestination( iFilePath, iDestinationPath ):
    print "Copying file: " + iFilePath + " to " + iDestinationPath
    shutil.copy( LONG_PATH_PREFIX + os.path.abspath(iFilePath), LONG_PATH_PREFIX + os.path.abspath(iDestinationPath) )

# Main entry point
if __name__ == "__main__":
    print "\nRunning PostBuild..."
    if ( len( sys.argv ) < 3 ):
        print "\n  Not enough information provided."
        exit(1)

    exportDirectory = sys.argv[ 1 ]
    destinationDirectory = sys.argv[ 2 ]
    CopyAllFilesInSourceToDestination( exportDirectory, destinationDirectory )
