#<License>
#Copyright 2016 Virtium Technology
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

TARGET        = libvtStorAta.so
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
LIBRARY_DIR                        = ../$(CFG)/lib/$(OS_NAME)/$(ARCH)
VTSTOR_LIB_DIR                     = $(LIBRARY_DIR)/vtStor
VTSTOR_ATA_LIB_DIR                 = $(LIBRARY_DIR)/vtStorAta

DEST_DIR                        = ../bin
OBJECTS_DIR                     = $(DEST_DIR)/vtStorAta
EXTERN_DIR                      = ../Extern
COMMON_DIR                      = ../Common
COMMON_PF_X86X64_DIR            = ../Common/Platform/x86x64
COMMON_PF_X86X64_LINUX_DIR      = ../Common/Platform/x86x64/Linux
VTSTOR_DIR                      = ../vtStor
VTSTOR_INTERNAL_DIR             = ../vtStor/Internal
VTSTOR_ATA_INTERNAL_DIR             = Internal
STORAGEUTILITY_DIR              = ../StorageUtility
STORAGEUTILITY_LINUX_DIR        = ../StorageUtility/Internal/Linux
VTSTORATAPROTOCOL_DIR           = ../vtStorAtaProtocol
VTSTORATAPROTOCOL_PF_LINUX_DIR  = ../vtStorAtaProtocol/Platform/Linux

INC_DIR       =../$(CFG)/inc
LIB_DIR       =../$(CFG)/lib/$(OS_NAME)/$(ARCH)/$(notdir $(shell pwd))/

INCPATH       = -I. -I$(EXTERN_DIR) -I$(COMMON_DIR) -I$(COMMON_PF_X86X64_DIR) -I$(COMMON_PF_X86X64_LINUX_DIR) -I$(STORAGEUTILITY_DIR) -I$(STORAGEUTILITY_LINUX_DIR) -I$(VTSTOR_DIR) -I$(DEST_DIR) \
                -I$(VTSTORATAPROTOCOL_DIR) -I$(VTSTORATAPROTOCOL_PF_LINUX_DIR) -I$(VTSTOR_INTERNAL_DIR) -I$(VTSTOR_ATA_INTERNAL_DIR)
LINK          = g++
LIBS          = $(SUBLIBS) -L$(VTSTOR_LIB_DIR)/ -lvtStor -L$(VTSTOR_ATA_LIB_DIR)/ -lvtStorAtaProtocol -ludev -luuid
DEL_FILE      = rm -f
DEL_DIR       = rmdir
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

# Files
VPATH         = SOURCES_DIR: . $(VTSTOR_ATA_INTERNAL_DIR)
SOURCES       = DriveEnumeratorAta.cpp \
		DriveAta.cpp \
		CommandHandlerAta.cpp \
		CommandDescriptorAta.cpp \
		AtaCommandExtensions.cpp \
		TrimBufferFormatter.cpp \
		AsynIoCommandExtensions.cpp \
		CommandHandlerAsynIo.cpp
		

OBJECTS       = $(patsubst %.cpp, $(OBJECTS_DIR)/%.o, ${SOURCES})
DEPS          = $(patsubst %.cpp, $(OBJECTS_DIR)/%.d, ${SOURCES})

.PHONY : all debug clean install
debug: all
all: compile Makefile  $(DEST_DIR)/$(TARGET)

	
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
	-$(DEL_FILE) $(DEST_DIR)/$(TARGET)
	$(LINK) $(LFLAGS) -o $(DEST_DIR)/$(TARGET) $(OBJECTS) $(LIBS) $(OBJCOMP)
	@$(CHK_DIR_EXISTS) $(INC_DIR) || $(MKDIR) $(INC_DIR)
	@$(CHK_DIR_EXISTS) $(LIB_DIR) || $(MKDIR) $(LIB_DIR)
	cp -f $(DEST_DIR)/$(TARGET) $(LIB_DIR)
	rsync -avm --include='*.h' -f 'hide,! */' --exclude 'Windows*' --exclude 'Internal*' . $(INC_DIR)/$(notdir $(shell pwd))

install: all
	cp $(DEST_DIR)/$(TARGET) /usr/lib
	
clean: 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core
	$(CCADMIN)
	-$(DEL_DIR) $(OBJECTS_DIR)
