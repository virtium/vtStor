
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

### Python 
### Project Name: Post Build Copy

from xml.dom import minidom
import fnmatch  # for check extension
import os
import sys
import glob     # for filter
import shutil   # for copy file
###

def CopyFolder( iSource, iDest ):
    if not os.path.exists( iDest ):
        os.makedirs( iDest )
    for item in os.listdir( iSource ):
        s = os.path.join( iSource, item )
        d = os.path.join( iDest, item )
        if os.path.isdir( s ):
            CopyFolder( s, d )
            print("\t+Successful Copy(\"%s\" to \"%s\")" %( s, d ) )
        if os.path.isfile( s ):
            shutil.copyfile( s, d )
            print("\t+Successful Copy(\"%s\" to \"%s\")" %( s, d ) )
                     
def PostBuildCopy( iSource, iDest ):
    try:
        if os.path.isdir( iSource ):   
            print "\n...Copying " + iSource + " ..to.. " + iDest
            basename = os.path.basename( iSource )
            newDest = os.path.join( iDest, basename )
            CopyFolder( iSource, newDest )
        else:
            if not os.path.exists( iDest ):
                os.makedirs( iDest )
            # get filter files and copy to destination.
            for file1 in glob.glob( iSource ):
                print "\n...Copying " + file1 + " ..to.. " + iDest
                shutil.copy2( file1, iDest )
                print("\t+Successful Copy(\"%s\" ..to.. \"%s\")" %( file1, iDest ) )
    except:
        print("\t-Unsuccessful Copy(\"%s\" ..to.. \"%s\")" %( iSource, iDest ) )

def ReplaceString( iString, iOldListString, iNewListString ):
    if( len( iOldListString ) == len( iNewListString ) ):
        for i in range( 0, len( iOldListString ) ):
            iString = iString.replace( iOldListString[ i ], iNewListString[ i ] )
        return iString
    else:
        raise cReplaceStrError("Length of two list strings are not equal is cause error!")

class cReplaceStrError( Exception ):
    def __init__( self, value ):
        self.value = value

# Main function
if __name__ == "__main__":
    print "\nRunning PostBuildCopy..."
    print ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Start >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"
    
    # Check nember of argv from command line
    if( 2 > len( sys.argv ) ):
        print "\nNot enough information provided."
        print "\tPlease check in command line."
        print "\tFirst Argv should be: path of python file."
        print "\tSecond Argv should be: path of xml file that user want to call."
        print "\n----------------------------------------------------------------------------------"
        exit( 1 )

    pathToXml = sys.argv[ 1 ]

    # Check second argv is there a xml file or no?
    if fnmatch.fnmatch( pathToXml, '*.xml' ) == False:
        print "\n\tPlease check second argv in command line. It should be: path of xml file."
        print "\n----------------------------------------------------------------------------------"  
        exit( 1 )

    print "\nConfiguration file path: " + pathToXml

    # Read from xml file
    objects = minidom.parse( pathToXml )
    actions = objects.getElementsByTagName( "Actions" )[ 0 ]
    copies = actions.getElementsByTagName( "Copy" )
    parameterName = objects.getElementsByTagName( "Parameters" )[ 0 ]
    parameterNames = parameterName.getElementsByTagName( "Parameter" )


    if( ( len( sys.argv ) - 2 ) != len( parameterNames ) ):
        print "\nInformation provided is not true."
        print "\tPlease check in command line."
        print ("\tUser declares %r dynamic arguments.")%len( parameterNames )
        for argv in parameterNames:
            print ("\tArgv : %s")%argv.firstChild.data
        print "\n----------------------------------------------------------------------------------"
        exit( 1 )

    # Convert list argv from xml to list string
    strParameterNames = [ ]
    for i in range( 0, parameterNames.length ):
        strParameterNames.append( str( parameterNames[ i ].firstChild.data ) )

    # Get new list parameter
    strParameterValues = [ ]
    for i in range( 2, len( sys.argv ) ):
        strParameterValues.append( sys.argv[ i ] ) 
            
    # Get destinations and sources in every Copy
    for copy in copies:
        # Get a destination from xml
        destination = copy.getElementsByTagName( "Destination" )[ 0 ]
        destinationPath = destination.firstChild.data
        try:
            destinationPath = ReplaceString( destinationPath, strParameterNames, strParameterValues )
        except cReplaceStrError as e:
            print ("Parameter names and parameter values are not match.")
            break
            
        #Get all sources from xml
        listSources = copy.getElementsByTagName( "Source" )
        for sourcePath in listSources:
            try:
                sourcePath = sourcePath.firstChild.data
                try:
                    sourcePath = ReplaceString( sourcePath, strParameterNames, strParameterValues )
                except cReplaceStrError as e:
                    print ("Parameter names and parameter values are not match.")
                    break

                PostBuildCopy( sourcePath, destinationPath )
            except:
                print "Exception a Get Sourse from xml"

    print "\n---------------------------------------- END -------------------------------------"












