# <License>
# Copyright 2016 Virtium Technology
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http ://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# </License>

TARGET        = libvtStor.so
# Separate compile options per configuration
ifeq "$(findstring debug,$(MAKECMDGOALS))" "debug"
CXXFLAGS      = -pipe -std=c++14 -fpermissive -g -Wall -D_DEBUG -fPIC
LFLAGS        = -Wl,-O0 -shared -Wl,-soname,$(TARGET)
CFG           = debug
else
CXXFLAGS      = -pipe -std=c++14 -fpermissive -O2 -Wall -W -fPIC
LFLAGS        = -Wl,-O1 -shared -Wl,-soname,$(TARGET)
CFG           = release
endif
# Compiler, tools and options
CXX           = g++
# OS name
OS_NAME       = $(shell sed -n -e '/PRETTY_NAME/ s/^.*=\|"\| .*//gp' /etc/*-release)
# Architecture of chipset
ARCH = $(shell uname -m)

# Define the directories.
DEST_DIR                        = ../bin
OBJECTS_DIR                     = $(DEST_DIR)/vtStor
VTSTOR_INTERNAL_DIR             = Internal
EXTERN_DIR                      = ../Extern
COMMON_DIR                      = ../Common
COMMON_PF_X86X64_DIR            = ../Common/Platform/x86x64
COMMON_PF_X86X64_LINUX_DIR      = ../Common/Platform/x86x64/Linux
STORAGE_UTILITY_DIR             = ../StorageUtility
STORAGE_UTILITY_LINUX_DIR       = ../StorageUtility/Internal/Linux
GENERATEFILES_DIR               = ../GenerateFiles

INC_DIR       =../$(CFG)/inc
LIB_DIR       =../$(CFG)/lib/$(OS_NAME)/$(ARCH)/$(notdir $(shell pwd))/
 
INCPATH       = -I. -I$(EXTERN_DIR) -I$(COMMON_DIR) -I$(COMMON_PF_X86X64_DIR) -I$(COMMON_PF_X86X64_LINUX_DIR) -I$(STORAGE_UTILITY_DIR) -I$(STORAGE_UTILITY_LINUX_DIR) -I$(VTSTOR_INTERNAL_DIR) -I$(DEST_DIR)
LINK          = g++
LIBS          = $(SUBLIBS) -ludev -luuid
DEL_FILE      = rm -f
DEL_DIR       = rmdir
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

# Files
VPATH         = SOURCES_DIR: . $(STORAGE_UTILITY_DIR) $(STORAGE_UTILITY_LINUX_DIR) $(VTSTOR_INTERNAL_DIR)
SOURCES       = ProtocolEssense.cpp \
    DriveManager.cpp \
    Drive.cpp \
    CommandDescriptor.cpp \
    BufferFormatter.cpp \
    Buffer.cpp \
    Scsi.cpp \
    Ata.cpp \
    Device.cpp \
    StorageUtility.cpp \
    DriveEnumerateDecorator.cpp \
    DriveEnumerator.cpp \
    Overlapped.cpp \
	

OBJECTS       = $(patsubst %.cpp, $(OBJECTS_DIR)/%.o, ${SOURCES})
DEPS          = $(patsubst %.cpp, $(OBJECTS_DIR)/%.d, ${SOURCES})

.PHONY : all debug clean install
debug: all
all: generateFiles compile Makefile  $(DEST_DIR)/$(TARGET)

generateFiles:
	# output file                                                                           Templated file                                          xml file
	python $(GENERATEFILES_DIR)/GenerateFiles.py $(COMMON_DIR)/ErrorCodes.h                 $(GENERATEFILES_DIR)/ErrorCodesTemplate.h               $(GENERATEFILES_DIR)/ErrorCodes.xml
	python $(GENERATEFILES_DIR)/GenerateFiles.py $(COMMON_DIR)/ScanForHardwareChanges.h     $(GENERATEFILES_DIR)/ScanForHardwareChangesTemplate.h 	$(GENERATEFILES_DIR)/ScanForHardwareChanges.xml
	python $(GENERATEFILES_DIR)/GenerateFiles.py $(COMMON_DIR)/BusType.h                    $(GENERATEFILES_DIR)/BusTypeTemplate.h                  $(GENERATEFILES_DIR)/BusType.xml
	python $(GENERATEFILES_DIR)/GenerateFiles.py $(COMMON_DIR)/DeviceDataType.h             $(GENERATEFILES_DIR)/DeviceDataTypeTemplate.h           $(GENERATEFILES_DIR)/DeviceDataType.xml
	
compile: $(OBJECTS)

$(OBJECTS_DIR)/%.o: %.cpp
	@$(CHK_DIR_EXISTS) $(OBJECTS_DIR) || $(MKDIR) $(OBJECTS_DIR)
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

$(OBJECTS_DIR)/%.d: %.cpp
	@echo Generating dependencies for $<
	@set -e ; $(CXX) -MM -MP $(INCPATH) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,$(OBJECTS_DIR)\/\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$
	
# Build rules
$(DEST_DIR)/$(TARGET): $(OBJECTS) $(SUBLIBS) $(OBJCOMP)
	@$(CHK_DIR_EXISTS) $(DEST_DIR) || $(MKDIR) $(DEST_DIR)
	-$(DEL_FILE) $(DEST_DIR)/$(TARGET)
	$(LINK) $(LFLAGS) -o $(DEST_DIR)/$(TARGET) $(OBJECTS) $(LIBS) $(OBJCOMP)
	@$(CHK_DIR_EXISTS) $(INC_DIR) || $(MKDIR) $(INC_DIR)
	@$(CHK_DIR_EXISTS) $(LIB_DIR) || $(MKDIR) $(LIB_DIR)
	cp -f $(DEST_DIR)/$(TARGET) $(LIB_DIR)
	rsync -avm --include='*.h' -f 'hide,! */' --exclude 'Windows*' --exclude 'Internal*' $(EXTERN_DIR) $(INC_DIR)
	rsync -avm --include='*.h' -f 'hide,! */' --exclude 'Windows*' --exclude 'Internal*' $(COMMON_DIR) $(INC_DIR)
	rsync -avm --include='*.h' -f 'hide,! */' --exclude 'Windows*' --exclude 'Internal*' $(STORAGE_UTILITY_DIR) $(INC_DIR)
	rsync -avm --include='*.h' -f 'hide,! */' --exclude 'Windows*' --exclude 'Internal*' . $(INC_DIR)/$(notdir $(shell pwd))
	
install: all
	cp $(DEST_DIR)/$(TARGET) /usr/lib
clean: 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core
	$(CCADMIN)
	-$(DEL_DIR) $(OBJECTS_DIR)

