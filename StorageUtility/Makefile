# Compiler and tool definitions shared by all build targets 
CC       = gcc
CXX      = g++
CFLAGS   = -pipe -O2 -fPIC -Wall -W 
CXXFLAGS = -pipe -std=c++14 -O2 -fPIC -Wall -W 

# Define the directories.
DEST_DIR                       = ../Debug
OBJECTS_DIR                     = $(DEST_DIR)/StorageUtility
EXTERN_DIR                      = ../Extern
COMMON_DIR                      = ../Common
COMMON_PF_X86X64_DIR            = ../Common/Platform/x86x64
COMMON_PF_X86X64_LINUX_DIR      = ../Common/Platform/x86x64/Linux
VTSTOR_PF_LINUX_DIR             = ../vtStor/Platform/Linux
STORAGEUTILITY_LINUX_DIR        = ../StorageUtility/Linux 
GENERATEFILES_DIR               = ../GenerateFiles

INCPATH  = -I. -I$(EXTERN_DIR) -I$(COMMON_DIR) -I$(COMMON_PF_X86X64_DIR) -I$(COMMON_PF_X86X64_LINUX_DIR) -I$(VTSTOR_PF_LINUX_DIR) -I$(STORAGEUTILITY_LINUX_DIR)
DEL_FILE      = rm -f
CHK_DIR_EXISTS = test -d
MKDIR   = mkdir -p
	
# Target: libStorageUtility
VPATH         = SOURCES_DIR: $(STORAGEUTILITY_LINUX_DIR)
SOURCES = Scsi.cpp \
	  Ata.cpp \
	  Device.cpp \
	  StorageUtility.cpp
	
OBJECTS = $(patsubst %.cpp, $(OBJECTS_DIR)/%.o, ${SOURCES})

TARGET  = libStorageUtility.a
		
all: generateFiles directories compile Makefile $(DEST_DIR)/libStorageUtility
	
generateFiles:
	# output file                                                                           Templated file                                          xml file
	python $(GENERATEFILES_DIR)/GenerateFiles.py $(COMMON_DIR)/ErrorCodes.h                 $(GENERATEFILES_DIR)/ErrorCodesTemplate.h               $(GENERATEFILES_DIR)/ErrorCodes.xml
	python $(GENERATEFILES_DIR)/GenerateFiles.py $(COMMON_DIR)/ScanForHardwareChanges.h     $(GENERATEFILES_DIR)/ScanForHardwareChangesTemplate.h 	$(GENERATEFILES_DIR)/ScanForHardwareChanges.xml
	python $(GENERATEFILES_DIR)/GenerateFiles.py $(COMMON_DIR)/BusType.h                    $(GENERATEFILES_DIR)/BusTypeTemplate.h                  $(GENERATEFILES_DIR)/BusType.xml
	python $(GENERATEFILES_DIR)/GenerateFiles.py $(COMMON_DIR)/DeviceDataType.h             $(GENERATEFILES_DIR)/DeviceDataTypeTemplate.h           $(GENERATEFILES_DIR)/DeviceDataType.xml

# Create the target directory (if needed)	
directories:
	@$(CHK_DIR_EXISTS) $(DEST_DIR) || $(MKDIR) $(DEST_DIR)
	@$(CHK_DIR_EXISTS) $(OBJECTS_DIR) || $(MKDIR) $(OBJECTS_DIR)

compile: $(OBJECTS)

$(OBJECTS_DIR)/%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

# Link or archive
$(DEST_DIR)/libStorageUtility:  $(OBJECTS) $(OBJCOMP) 
	-$(DEL_FILE) $(DEST_DIR)/libStorageUtility.a
	ar rcs $(DEST_DIR)/libStorageUtility.a $(OBJECTS)
	
# Clean target deletes all generated files
clean:
	$(DEL_FILE) \
		$(OBJECTS_DIR)/libStorageUtility \
		$(OBJECTS_DIR)/Ata.o \
		$(OBJECTS_DIR)/Scsi.o
	$(CCADMIN)
	rm -f -r $(DEST_DIR)

