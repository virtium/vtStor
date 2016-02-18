# Compiler, tools and options
CC            = gcc
CXX           = g++
CFLAGS        = -pipe -O2 -Wall -W -fPIC 
CXXFLAGS      = -pipe -std=c++14 -fpermissive -O2 -Wall -W -fPIC 

# Define the directories.
DEST_DIR                        = ../Debug
OBJECTS_DIR                     = $(DEST_DIR)/vtStorAta
EXTERN_DIR                      = ../Extern
COMMON_DIR                      = ../Common
COMMON_PF_X86X64_DIR            = ../Common/Platform/x86x64
COMMON_PF_X86X64_LINUX_DIR      = ../Common/Platform/x86x64/Linux
VTSTOR_DIR                      = ../vtStor
VTSTOR_PF_LINUX_DIR             = ../vtStor/Platform/Linux
STORAGEUTILITY_DIR              = ../StorageUtility
STORAGEUTILITY_LINUX_DIR        = ../StorageUtility/Linux 
VTSTORATA_DIR                   = ../vtStorAta
VTSTORATA_PF_LINUX_DIR          = ../vtStorAta/Platform/Linux
VTSTORATAPROTOCOL_DIR           = ../vtStorAtaProtocol
VTSTORATAPROTOCOL_PF_LINUX_DIR  = ../vtStorAtaProtocol/Platform/Linux  

INCPATH       = -I. -I$(EXTERN_DIR) -I$(COMMON_DIR) -I$(COMMON_PF_X86X64_DIR) -I$(COMMON_PF_X86X64_LINUX_DIR) -I$(STORAGEUTILITY_DIR) -I$(STORAGEUTILITY_LINUX_DIR) -I$(VTSTOR_DIR) -I$(VTSTOR_PF_LINUX_DIR) -I$(DEST_DIR) \
                -I$(VTSTORATA_DIR) -I$(VTSTORATA_PF_LINUX_DIR) -I$(VTSTORATAPROTOCOL_DIR) -I$(VTSTORATAPROTOCOL_PF_LINUX_DIR) 
LINK          = g++
LFLAGS        = -Wl,-O1 -shared -Wl,-soname,libvtStorAta.so.1
LIBS          = $(SUBLIBS) -ludev -L$(DEST_DIR)/ -lStorageUtility -lvtStor -lvtStorAtaProtocol 
DEL_FILE      = rm -f
DEL_DIR       = rmdir
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

# Files
VPATH         = SOURCES_DIR: .
SOURCES       = DriveEnumeratorAta.cpp \
		DriveAta.cpp \
		CommandHandlerAta.cpp \
		CommandDescriptorAta.cpp \
		AtaCommandExtensionscpp.cpp \
		TrimBufferFormatter.cpp 

OBJECTS       = $(patsubst %.cpp, $(OBJECTS_DIR)/%.o, ${SOURCES})
        
TARGET        = libvtStorAta.so.1.0.0
TARGET0       = libvtStorAta.so
TARGET1       = libvtStorAta.so.1
TARGET2       = libvtStorAta.so.1.0

all: directories compile Makefile  $(DEST_DIR)/$(TARGET)

# Create the target directory (if needed)	
directories:
	@$(CHK_DIR_EXISTS) $(OBJECTS_DIR) || $(MKDIR) $(OBJECTS_DIR)
	
compile: $(OBJECTS)

$(OBJECTS_DIR)/%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

# Build rules
$(DEST_DIR)/$(TARGET): $(DEST_DIR)/libStorageUtility.a $(OBJECTS) $(SUBLIBS) $(OBJCOMP)  
	-$(DEL_FILE) $(DEST_DIR)/$(TARGET) $(DEST_DIR)/$(TARGET0) $(DEST_DIR)/$(TARGET1) $(DEST_DIR)/$(TARGET2)
	$(LINK) $(LFLAGS) -o $(DEST_DIR)/$(TARGET) $(OBJECTS) $(LIBS) $(OBJCOMP)
	-ln -s $(DEST_DIR)/$(TARGET) $(DEST_DIR)/$(TARGET0)
	-ln -s $(DEST_DIR)/$(TARGET) $(DEST_DIR)/$(TARGET1)
	-ln -s $(DEST_DIR)/$(TARGET) $(DEST_DIR)/$(TARGET2)
    
clean: 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core
	$(CCADMIN)
	-$(DEL_DIR) $(OBJECTS_DIR)
