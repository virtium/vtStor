#<License>
#Copyright 2015 Virtium Technology
#
#Licensed under the Apache License, Version 2.0 (the "License");
#you may not use this file except in compliance with the License.
#You may obtain a copy of the License at
#
#http ://www.apache.org/licenses/LICENSE-2.0
#
#Unless required by applicable law or agreed to in writing, software
#distributed under the License is distributed on an "AS IS" BASIS,
#WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#See the License for the specific language governing permissions and
#limitations under the License.
#</License>

import sys
import xml.etree.ElementTree as ElementTree

class cXmlGenerator():
    Start_Prefix_Tag            = "<$Prefix>"
    End_Prefix_Tag              = "</Prefix$>"
    Start_Suffix_Tag            = "<$Suffix>"
    End_Suffix_Tag              = "</Suffix$>"
    Replace_Tag                 = "<%Replace%>"

    def __init__( self, iOutputFile, iTemplatedFile, iInputFile ) :
        self.m_InputFile        = iInputFile
        self.m_TemplatedFile    = iTemplatedFile
        self.m_OutputFile       = iOutputFile

    def SubTag( self, iText, iStartTag, iEndTag ) :
        startIndex  = iText.find(iStartTag) + len(iStartTag)
        endIndex    = iText.find(iEndTag)
        return iText[ startIndex : endIndex ]

    def GetPrefixText( self, iFullText ) :
        return self.SubTag( iFullText, cXmlGenerator.Start_Prefix_Tag, cXmlGenerator.End_Prefix_Tag )

    def GetSuffixText( self, iFullText ) :
        return self.SubTag( iFullText, cXmlGenerator.Start_Suffix_Tag, cXmlGenerator.End_Suffix_Tag )

    def RemoveText( self, iFullText, iText ):
        iFullText = iFullText.replace( iText, "", 1 )
        return iFullText

    def GetPrefixTag( self, iPrefixContent ) :
        return cXmlGenerator.Start_Prefix_Tag + iPrefixContent + cXmlGenerator.End_Prefix_Tag

    def GetSuffixTag( self, iSuffixContent ) :
        return cXmlGenerator.Start_Suffix_Tag + iSuffixContent + cXmlGenerator.End_Suffix_Tag

    def RemovePrefixTag( self, iFullText, iTagContent ):
        return self.RemoveText( iFullText, self.GetPrefixTag( iTagContent ) )

    def RemoveSuffixTag( self, iFullText, iTagContent ):
        return self.RemoveText( iFullText, self.GetSuffixTag( iTagContent ) )

    def GetIndentAlign( self, iText ):
        replaceIndex    = iText.find( cXmlGenerator.Replace_Tag )
        length          = replaceIndex - iText.rfind( "\n", 0, replaceIndex ) - 1
        strSpace        = ""

        for i in range ( 0, length ) :
            strSpace += ' '
        return strSpace

    def ReadFileContent( self ):
        with open( self.m_TemplatedFile, 'r' ) as f :
            self.m_TemplatedText = f.read()
            f.close()

    def ReadXmlFile( self ) :
        outputText  = ""
        strSpace    = " ";
        strEqual    = "=";
        strNewLine  = "\n";

        tree        = ElementTree.parse( self.m_InputFile )
        root        = tree.getroot()
        listValue   = root.findall( "WordPairs/WordPair" );
        strLine     = ""
        for obj in listValue :
            strLine     = self.m_IndentAlign
            if "" != self.m_PrefixText :
                strLine += self.m_PrefixText + strSpace
            strLine += obj.get( "Name" ) + strSpace + strEqual + strSpace + obj.get( "Value" ) + self.m_SuffixText + strNewLine;
            outputText += strLine

        return outputText

    def GenerateFiles(self):
        self.ReadFileContent()
        self.m_PrefixText       = self.GetPrefixText( self.m_TemplatedText )
        self.m_SuffixText       = self.GetSuffixText( self.m_TemplatedText )
        self.m_IndentAlign      = self.GetIndentAlign( self.m_TemplatedText )
        self.m_OutputText       = self.ReadXmlFile()

        self.m_TemplatedText    = self.RemovePrefixTag( self.m_TemplatedText, self.m_PrefixText )
        self.m_TemplatedText    = self.RemoveSuffixTag( self.m_TemplatedText, self.m_SuffixText )
        self.m_TemplatedText    = self.m_TemplatedText.replace( self.m_IndentAlign + cXmlGenerator.Replace_Tag, self.m_OutputText, 1 )

        with open( self.m_OutputFile, 'w' ) as f:
            f.write( self.m_TemplatedText )
            f.close()

if __name__ == "__main__":

    ##############################################################
    # argv[1] : C header output file path
    # argv[1] : template header input file path
    # argv[1] : xml file which declares generated information
    ##############################################################

    generator = cXmlGenerator( sys.argv[1], sys.argv[2], sys.argv[3] )
    generator.GenerateFiles()
    exit( 0 )
