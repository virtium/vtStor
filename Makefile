# Directory of projects
vtStor_DIR              = ./vtStor
vtStorAtaProtocol_DIR   = ./vtStorAtaProtocol
vtStorScsiProtocol_DIR  = ./vtStorScsiProtocol
vtStorAta_DIR           = ./vtStorAta
vtStorScsi_DIR          = ./vtStorScsi

# Project names
vtStor                  = vtStor
vtStorAtaProtocol       = vtStorAtaProtocol
vtStorScsiProtocol      = vtStorScsiProtocol
vtStorAta               = vtStorAta
vtStorScsi              = vtStorScsi

ALL_PROJECTS = $(vtStor) $(vtStorAtaProtocol) $(vtStorScsiProtocol) $(vtStorAta) $(vtStorScsi)

# Build all projects
all: $(ALL_PROJECTS)

$(vtStor):
	$(MAKE) -C $(vtStor_DIR) all
        
$(vtStorAtaProtocol): $(vtStor)
	$(MAKE) -C $(vtStorAtaProtocol_DIR) all
        
$(vtStorScsiProtocol): $(vtStor)
	$(MAKE) -C $(vtStorScsiProtocol_DIR) all
        
$(vtStorAta): $(vtStor) $(vtStorAtaProtocol)
	$(MAKE) -C $(vtStorAta_DIR) all
        
$(vtStorScsi): $(vtStor) $(vtStorScsiProtocol)
	$(MAKE) -C $(vtStorScsi_DIR) all
        
debug: debug$(vtStor) debug$(vtStorAtaProtocol) debug$(vtStorScsiProtocol) debug$(vtStorAta) debug$(vtStorScsi)

debug$(vtStor):
	$(MAKE) -C $(vtStor_DIR) debug
        
debug$(vtStorAtaProtocol): $(vtStor)
	$(MAKE) -C $(vtStorAtaProtocol_DIR) debug
        
debug$(vtStorScsiProtocol): $(vtStor)
	$(MAKE) -C $(vtStorScsiProtocol_DIR) debug
        
debug$(vtStorAta): $(vtStor) $(vtStorAtaProtocol)
	$(MAKE) -C $(vtStorAta_DIR) debug
        
debug$(vtStorScsi): $(vtStor) $(vtStorScsiProtocol)
	$(MAKE) -C $(vtStorScsi_DIR) debug
	
install: install$(vtStor) install$(vtStorAtaProtocol) install$(vtStorScsiProtocol) install$(vtStorAta) install$(vtStorScsi)
install$(vtStor):
	$(MAKE) -C $(vtStor_DIR) install
        
install$(vtStorAtaProtocol): $(vtStor)
	$(MAKE) -C $(vtStorAtaProtocol_DIR) install
        
install$(vtStorScsiProtocol): $(vtStor)
	$(MAKE) -C $(vtStorScsiProtocol_DIR) install
        
install$(vtStorAta): $(vtStor) $(vtStorAtaProtocol)
	$(MAKE) -C $(vtStorAta_DIR) install
        
install$(vtStorScsi): $(vtStor) $(vtStorScsiProtocol)
	$(MAKE) -C $(vtStorScsi_DIR) install
	
clean: 
	cd $(vtStor_DIR); make clean
	cd $(vtStorAtaProtocol_DIR); make clean
	cd $(vtStorScsiProtocol_DIR); make clean
	cd $(vtStorAta_DIR); make clean
	cd $(vtStorScsi_DIR); make clean
	
.PHONY: all debug clean install $(ALL_PROJECTS)