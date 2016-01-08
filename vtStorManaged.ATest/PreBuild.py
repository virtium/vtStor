# Import built-in modules
import argparse
import os
import shutil
import sys
import xml.etree.ElementTree

def Main(arguments, unknownArguments):
    print("=== {0} Pre-Build Start ===".format(arguments.projectName))

    print("Arguments: {0}".format(arguments))
    print("Unknown Arguments: {0}".format(unknownArguments))

    nativePlatformMap = {'x86': 'Win32', 'x64': 'x64'}

    sourceDir = os.path.join(arguments.solutionDir, "{0}{1}".format(nativePlatformMap[arguments.platformName], arguments.configurationName))
    destinationDir = os.path.join(arguments.projectDir, "bin", arguments.platformName, arguments.configurationName)

    appConfigPath = os.path.join(arguments.projectDir, "App.config")
    appConfig = xml.etree.ElementTree.parse(appConfigPath).getroot()

    for nativeDependencies in appConfig.findall('nativeDependencies'):
        for dependency in nativeDependencies.findall('dependency'):
            dependencyFile = "{0}.dll".format(dependency.get('name'))
            sourcePath = os.path.join(sourceDir, dependencyFile)
            destinationPath = os.path.join(destinationDir, dependencyFile)
            print("Copying '{0}' to '{1}'".format(sourcePath, destinationPath))
            shutil.copyfile(sourcePath, destinationPath)

    print("=== {0} Pre-Build End ===".format(arguments.projectName))

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('--configurationName', action="store", dest="configurationName")
    parser.add_argument('--outDir', action="store", dest="outDir")
    parser.add_argument('--platformName', action="store", dest="platformName")
    parser.add_argument('--projectDir', action="store", dest="projectDir")
    parser.add_argument('--projectName', action="store", dest="projectName")
    parser.add_argument('--solutionDir', action="store", dest="solutionDir")
    parser.add_argument('--targetDir', action="store", dest="targetDir")
    arguments, unknownArguments = parser.parse_known_args()
    Main(arguments, unknownArguments)
