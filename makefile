#
#	baut das komplette Scanner Projekt
#


AUTOMATDIR = Automat

BUFFERDIR = Buffer

SYMBOLTABLEDIR = Symboltable

SCANNERDIR = Scanner

SHAREDLIB = sharedlib


all:	automatLib bufferLib symboltableLib scanner  
	@echo "target all"

	

clean:
	rm -rf $(AUTOMATDIR)/lib/*
	rm -rf $(BUFFERDIR)/lib/*
	rm -rf $(SYMBOLTABLEDIR)/lib/*
	rm -rf $(SHAREDLIB)/*
	rm -rf $(SCANNERDIR)/debug/*
	

scanner: 
	$(MAKE) -C $(SCANNERDIR) makeTestScanner

automatLib:
	$(MAKE) -C $(AUTOMATDIR) AutomatLib
	
	
bufferLib:
	$(MAKE) -C $(BUFFERDIR) BufferLib

# scannerLib wird erst fuer den Parser Teil benoetigt	
#scannerLib:
#	$(MAKE) -C $(SCANNERDIR) ScannerLib
	
symboltableLib:
	$(MAKE) -C $(SYMBOLTABLEDIR) SymboltableLib