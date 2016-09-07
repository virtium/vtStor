# Compiler, tools and options
CXX           = g++
CXXFLAGS      = -pipe -std=c++14 -fpermissive -O2 -Wall -W -fPIC

# Define the directories.
DEST_DIR                        = bin
OBJECTS_DIR                     = $(DEST_DIR)/object

# Path of vtStor libraries
VTSTOR_LIBRARY_DIR          = ../Dependencies/lib/Ubuntu/x86_64/vtStor
VTSTOR_ATA_LIBRARY_DIR      = ../Dependencies/lib/Ubuntu/x86_64/vtStorAta
VTSTOR_SCSI_LIBRARY_DIR     = ../Dependencies/lib/Ubuntu/x86_64/vtStorScsi

# Include paths of vtStor module
VTSTOR_INC_DIR                  = ../Dependencies/inc
EXTERN_DIR                      = $(VTSTOR_INC_DIR)/Extern
COMMON_DIR                      = $(VTSTOR_INC_DIR)/Common
COMMON_PF_X86X64_DIR            = $(VTSTOR_INC_DIR)/Common/Platform/x86x64
COMMON_PF_X86X64_LINUX_DIR      = $(VTSTOR_INC_DIR)/Common/Platform/x86x64/Linux
VTSTOR_DIR                      = $(VTSTOR_INC_DIR)/vtStor
VTSTOR_ATA_PROTOCOL_DIR         = $(VTSTOR_INC_DIR)/vtStorAtaProtocol
VTSTOR_ATA_PROTOCOL_LINUX_DIR   = $(VTSTOR_INC_DIR)/vtStorAtaProtocol/Platform/Linux
VTSTOR_ATA_DIR                  = $(VTSTOR_INC_DIR)/vtStorAta
VTSTOR_SCSI_PROTOCOL_DIR        = $(VTSTOR_INC_DIR)/vtStorScsiProtocol
VTSTOR_SCSI_PROTOCOL_LINUX_DIR  = $(VTSTOR_INC_DIR)/vtStorScsiProtocol/Platform/Linux
VTSTOR_SCSI_DIR                 = $(VTSTOR_INC_DIR)/vtStorScsi
STORAGE_UTILITY_DIR             = $(VTSTOR_INC_DIR)/StorageUtility

# Define include paths of vtStor module
INCPATH       = -I. -I$(VTSTOR_INC_DIR) -I$(COMMON_DIR) -I$(EXTERN_DIR) -I$(VTSTOR_DIR) -I$(COMMON_PF_X86X64_DIR) -I$(COMMON_PF_X86X64_LINUX_DIR) -I$(STORAGE_UTILITY_DIR)  -I$(VTSTOR_ATA_DIR)  -I$(VTSTOR_ATA_PROTOCOL_DIR)  -I$(VTSTOR_ATA_PROTOCOL_LINUX_DIR) -I$(VTSTOR_SCSI_DIR) -I$(VTSTOR_SCSI_PROTOCOL_DIR) -I$(VTSTOR_SCSI_PROTOCOL_LINUX_DIR)\

# Define include paths of other module
#INCPATH	     += Include paths

LINK          = g++
LFLAGS        = -Wl,-O1
DEL_FILE      = rm -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

# Link vtStor module
LIBS          = -L$(VTSTOR_LIBRARY_DIR) -lvtStor -ludev

# Link vtStorAta module
LIBS          += -L$(VTSTOR_ATA_LIBRARY_DIR) -lvtStorAta -lvtStorAtaProtocol

# Link vtStorScsi module
LIBS          += -L$(VTSTOR_SCSI_LIBRARY_DIR) -lvtStorScsi -lvtStorScsiProtocol

# Link other modules
#LIBS          += a another module

# Files
VPATH         = SOURCES_DIR: .
SOURCES       = ../main.cpp
OBJECTS       = $(patsubst %.cpp, $(OBJECTS_DIR)/%.o, ${SOURCES})

TARGET        = $(DEST_DIR)/SampleCode

.PHONY : all debug clean install

all: directories compile Makefile  $(TARGET)

# Create the target directory (if needed)	
directories:
	@$(CHK_DIR_EXISTS) $(OBJECTS_DIR) || $(MKDIR) $(OBJECTS_DIR)
	cp -a $(VTSTOR_LIBRARY_DIR)/. $(DEST_DIR)
	cp -a $(VTSTOR_ATA_LIBRARY_DIR)/. $(DEST_DIR)
	cp -a $(VTSTOR_SCSI_LIBRARY_DIR)/. $(DEST_DIR)
	
compile: $(OBJECTS)

$(OBJECTS_DIR)/%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

# Build rules
$(TARGET): $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

install: all
	cp $(DEST_DIR)/*.so /usr/lib
clean: 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core
