#
#	baut das komplette Projekt
#


AUTOMATDIR = Automat

BUFFERDIR = Buffer

SYMBOLTABLEDIR = Symboltable

SCANNERDIR = Scanner

SHAREDLIB = sharedlib

PARSERDIR = Parser


all: automatLib bufferLib symboltableLib scannerLib parser  
	@echo "target all"

	

clean:
	rm -rf $(AUTOMATDIR)/lib/*
	rm -rf $(BUFFERDIR)/lib/*
	rm -rf $(SYMBOLTABLEDIR)/lib/*
	rm -rf $(SCANNERDIR)/lib/*
	rm -rf $(SHAREDLIB)/*
	rm -rf $(SCANNERDIR)/debug/*
	rm -rf $(PARSERDIR)/debug/*
	

scanner: 
	$(MAKE) -C $(SCANNERDIR) makeTestScanner
	
parser:
	$(MAKE) -C $(PARSERDIR) makeParserTest

automatLib:
	$(MAKE) -C $(AUTOMATDIR) AutomatLib
	
	
bufferLib:
	$(MAKE) -C $(BUFFERDIR) BufferLib

# scannerLib wird erst fuer den Parser Teil benoetigt	
scannerLib:
	$(MAKE) -C $(SCANNERDIR) ScannerLib
	
symboltableLib:
	$(MAKE) -C $(SYMBOLTABLEDIR) SymboltableLib