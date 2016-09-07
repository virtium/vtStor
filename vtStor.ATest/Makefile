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

# Separate compile options per configuration
ifeq "$(findstring debug,$(MAKECMDGOALS))" "debug"
CXXFLAGS      = -pipe -std=c++14 -fpermissive -g -Wall -D_DEBUG -fPIC
LFLAGS        = -Wl,-O0
CFG           = debug
else
CXXFLAGS      = -pipe -std=c++14 -fpermissive -O2 -Wall -W -fPIC
LFLAGS        = -Wl,-O1
CFG           = release
endif
# Compiler, tools and options
CXX           = g++
# Define the directories.
DEST_DIR                        = ../bin
OBJECTS_DIR                     = $(DEST_DIR)/vtStorATest
LIBRARY_DIR			= ../bin
HEADER_DIR                      = ..
EXTERN_DIR                      = $(HEADER_DIR)/Extern
COMMON_DIR                      = $(HEADER_DIR)/Common
COMMON_PF_X86X64_DIR            = $(HEADER_DIR)/Common/Platform/x86x64
COMMON_PF_X86X64_LINUX_DIR      = $(HEADER_DIR)/Common/Platform/x86x64/Linux
VTSTOR_DIR                      = $(HEADER_DIR)/vtStor
STORAGEUTILITY_DIR              = $(HEADER_DIR)/StorageUtility

VTSTORATA_DIR                   = $(HEADER_DIR)/vtStorAta
VTSTORATAPROTOCOL_DIR           = $(HEADER_DIR)/vtStorAtaProtocol
VTSTORATAPROTOCOL_PF_LINUX_DIR  = $(HEADER_DIR)/vtStorAtaProtocol/Platform/Linux  
VTSTORSCSI_DIR                  = $(HEADER_DIR)/vtStorScsi 
VTSTORSCSIPROTOCOL_DIR          = $(HEADER_DIR)/vtStorScsiProtocol
VTSTORSCSIPROTOCOL_PF_LINUX_DIR = $(HEADER_DIR)/vtStorScsiProtocol/Platform/Linux 

INCPATH       = -I. -I$(EXTERN_DIR) -I$(COMMON_DIR) -I$(COMMON_PF_X86X64_DIR) -I$(COMMON_PF_X86X64_LINUX_DIR) -I$(STORAGEUTILITY_DIR) -I$(VTSTOR_DIR) -I$(DEST_DIR) \
                -I$(VTSTORATA_DIR) -I$(VTSTORATAPROTOCOL_DIR) -I$(VTSTORATAPROTOCOL_PF_LINUX_DIR) -I$(VTSTORSCSI_DIR) -I$(VTSTORSCSIPROTOCOL_DIR) -I$(VTSTORSCSIPROTOCOL_PF_LINUX_DIR)
LINK          = g++
LIBS          = $(SUBLIBS) -L$(LIBRARY_DIR)/ -lvtStor -lvtStorAtaProtocol -lvtStorAta -lvtStorScsiProtocol -lvtStorScsi -ludev
DEL_FILE      = rm -rf
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p



# Files
VPATH         = SOURCES_DIR: .
SOURCES       = main.cpp
OBJECTS       = $(patsubst %.cpp, $(OBJECTS_DIR)/%.o, ${SOURCES})
DEPS          = $(patsubst %.cpp, $(OBJECTS_DIR)/%.d, ${SOURCES})
TARGET        = $(DEST_DIR)/vtStor.ATest

.PHONY: all clean debug install

all: inform Makefile  $(TARGET)
debug: inform Makefile  $(TARGET)
inform:
ifneq ($(CFG),release)
ifneq ($(CFG),debug)
	@echo "Invalid configuration "$(CFG)" specified."
	@echo "You must specify a configuration when running make, e.g."
	@echo  "make CFG=debug"
	@echo  
	@echo  "Possible choices for configuration are 'release' and 'debug'"
	@exit 1
endif
endif
	@echo "Configuration "$(CFG)
	@echo "------------------------"	
	
$(OBJECTS_DIR)/%.o: %.cpp
	@$(CHK_DIR_EXISTS) $(OBJECTS_DIR) || $(MKDIR) $(OBJECTS_DIR)
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

$(OBJECTS_DIR)/%.d: %.cpp
	@echo Generating dependencies for $<
	@set -e ; $(CXX) -MM -MP $(INCPATH) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,$(OBJECTS_DIR)\/\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

install: all
	cp $(DEST_DIR)/*.so /usr/lib
	cp $(TARGET) /bin
# Build rules
$(TARGET): $(OBJECTS) | inform
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)
	
clean: 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core
