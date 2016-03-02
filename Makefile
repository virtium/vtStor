# Directory of projects
StorageUtility_DIR      = ./StorageUtility
vtStor_DIR              = ./vtStor
vtStorAtaProtocol_DIR   = ./vtStorAtaProtocol
vtStorScsiProtocol_DIR  = ./vtStorScsiProtocol
vtStorAta_DIR           = ./vtStorAta
vtStorScsi_DIR          = ./vtStorScsi
vtStor.ATest_DIR        = ./vtStor.ATest

# Project names
StorageUtility          = StorageUtility
vtStor                  = vtStor
vtStorAtaProtocol       = vtStorAtaProtocol
vtStorScsiProtocol      = vtStorScsiProtocol
vtStorAta               = vtStorAta
vtStorScsi              = vtStorScsi
vtStor.ATest            = vtStor.ATest

ALL_PROJECTS = $(StorageUtility) $(vtStor) $(vtStorAtaProtocol) $(vtStorScsiProtocol) $(vtStorAta) $(vtStorScsi) $(vtStor.ATest)

# Build all projects
.PHONY: all $(ALL_PROJECTS)
all: $(ALL_PROJECTS)

$(StorageUtility):
	cd $(StorageUtility_DIR); make all

$(vtStor): $(StorageUtility)
	cd $(vtStor_DIR); make all
        
$(vtStorAtaProtocol): $(StorageUtility) $(vtStor)
	cd $(vtStorAtaProtocol_DIR); make all
        
$(vtStorScsiProtocol): $(StorageUtility) $(vtStor)
	cd $(vtStorScsiProtocol_DIR); make all
        
$(vtStorAta): $(vtStorAtaProtocol)
	cd $(vtStorAta_DIR); make all
        
$(vtStorScsi): $(vtStorScsiProtocol)
	cd $(vtStorScsi_DIR); make all
        
$(vtStor.ATest): $(vtStorAta) $(vtStorScsi)
	cd $(vtStor.ATest_DIR); make all

clean: 
	cd $(StorageUtility_DIR); make clean
	cd $(vtStor_DIR); make clean
	cd $(vtStorAtaProtocol_DIR); make clean
	cd $(vtStorScsiProtocol_DIR); make clean
	cd $(vtStorAta_DIR); make clean
	cd $(vtStorScsi_DIR); make clean
	cd $(vtStor.ATest_DIR); make clean
