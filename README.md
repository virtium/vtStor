# vtStor

## Introduction
The vtStor libraries are a collection of libraries based on C++11. The source code is released under the Apache License, which allows anyone to use, modify and distribute the libraries for free. The libraries are platform independent libraries.

The vtStor libraries are a set of libraries to allow easy access and communication to storage devices. The libraries are the good choice for anyone who looking for a cross-platform libraries to do stuff with storage devices.

The vtStor libraries also have C++/CLI libraries to support for .NET framework. By default, the targeted framework is compatible with .NET Framework 4.

## Architecture
The vtStor libraries have following main components:
- The vtStor is the core library. The vtStor is in charge of scanning and managing storage devices. Each storage device is encapsulated to a drive. It also contains all framework interfaces such as: IDriveEnumerator, IProtocol, ICommandHandler
- The vtStorAta is a extended library. It is used to access and communicate with ATA storage device. The vtStorAta has a class called AtaCommmandExtensions that contains all functions to send a ATA command.
- The vtStorScsi is same as the vtStorAta, but it is used for SCSI commands.

## Release Structure
Each library package is structured as:

```
#!shell

   |-- LibraryName
        |-- lib
             |-- *.so *.lib *.dll
        |-- inc
             |-- *.h
```


## Sample Code
Sample code include 2 parts:

- __dependencies__ contains vtStor libraries such as vtStor, vtStorAta, vtStorScsi.
- __< Sample_project >__ contains sample code such as DriveIdentifier project. 

```
#!shell

	|-- < SampleCode >
		|-- dependencies
			|-- vtStor
			|-- vtStorAta
		|-- < Sample_project >
			|-- main.cpp
			|-- makefile
```


## Windows
### Environment
- Windows 7/10
- Visual Studio 2013/2015

### Build
On the solution:

- Select the Solutions Configurations and Solution Platforms. 
- Under menu Build, select Build Solution
- When the build completes, all libraries are in a folder $SolutionsPlatform$SolutionConfiguration

## Ubuntu
### Environment
- Ubuntu 14.04 64 bit
- Some packages must be installed before compiling sample code:
	+ GCC 4.9
	+ libusb-1.0-0-dev
	+ libudev-dev

Install GCC 4.9 with commands

```
#!shell

sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt-get update
sudo apt-get install gcc-4.9 g++-4.9
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.9 60 --slave /usr/bin/g++ g++ /usr/bin/g++-4.9
```

Install libusb-1.0-0-dev and libudev-dev with commands

```
#!shell

sudo apt-get update
sudo apt-get install libusb-1.0-0-dev
sudo apt-get install libudev-dev
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/include/libudev.h
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/include/libusb-1.0/libusb.h
```

### Build
- In this case: sample code is __DriveIdentifier__ and the current directory is <pre>/home/<user\>/SampleCode/DriveIdentifier/</pre>
- Use __root__ permission.
- Use makefile to build.

Command:
```
#!shell
sudo make clean all
```
Run:
```
#!shell
cd bin
export LD_LIBRARY_PATH=.
```
./DriveIdentifier</pre>
Or another build:
```
#!shell
sudo make clean install
```
Run:
```
#!shell
cd bin
./DriveIdentifier
```
After built successfully, it looks like:
```
#!shell
	|-- SampleCode
		|-- dependencies
			|-- vtStor
			|-- vtStorAta
		|-- DriveIdentifier
			|-- main.cpp
			|-- makefile
			|-- bin
				|-- DriveIdentifier
				|-- libvtStor.so
				|-- libvtStorAta.so
				|-- libvtStorAtaProtocol.so
				|-- object
```
### How To Use
-  __DriveIdentifier__ is the sample project read idenfitier of drives attaching into Ubuntu OS by SATA cables. First, you need import the vtStor library (libvtStor.so) and vtStorAta library (libvtStorAta.so, libvtStorAtaProtocol.so).
  	+ libvtStor.so: detect all ATA drives from class __vtStor::IDriveManager__, tell to vtStor know detect ATA drives from __RegisterDriveEnumerator__ function, perform __EnumerateDrives__ function to enumerate drives and we can get all drives from function __GetDrives()__.
	+ libvtStorAta.so: construct a ATA command from __vtStor::Ata::cAtaCommandExtensions__ with issue command to be define such as __IssueCommand_IdentifyDevice__ function.
	+ libvtStorAtaProtocol.so: helps us determine which command set to use.
	
- Note:
    - If error libudev.so.0 , please command <pre>sudo ln -sf /lib/$(arch)-linux-gnu/libudev.so.1 /lib/$(arch)-linux-gnu/libudev.so.0</pre>
    - Using "sudo" cmd to get permission to run this app.
