

SRCDIR = src
OBJDIR = debug

BINDIR = debug

LIBDIR = lib


SHAREDLIB = ../sharedlib

## hier alle Object Files eintragen
## darauf achten, dass letzte Zeile ohne "\" eingetragen wird

OBJS = $(OBJDIR)/Node.o \
	$(OBJDIR)/ParserTest.o \
	$(OBJDIR)/Parser.o

#$(OBJDIR)/xx1.o \
#$(OBJDIR)/xxn.o

OBJSFORPARSERLIB = $(LIBDIR)/Node.o \
				$(LIBDIR)/Parser.o



makeParserTest: $(OBJS)
	g++ -g $^ -L../sharedlib -lScanner  -lAutomat  -lBuffer -lSymboltable -o $(BINDIR)/ParserTest
	
	
	
# $^ liste der abhaengigkeiten


$(OBJDIR)/%.o: $(SRCDIR)/%.cpp 
	@echo "g++ -Wall -Wextra -pedantic -std=c++11 $*.cpp"
	g++ -Wall -Wextra -pedantic -std=c++11 -g  -c -Wall  -o $@  $<

 
 #$@ name des object files
 #$< erste abhaengigkeit


# loeschen aller files im verzeichnis $(OBJDIR) und $(LIBDIR) und neu bauen

cleanParser:
	rm -rf $(OBJDIR)/*
	rm -rf $(LIBDIR)/*
#	$(MAKE) makeTestScanner
	
	
	
## erstellen der shared library

# erst wichtig fuer den Parser Teil
#
#ScannerLib:$(OBJSFORSCANNERLIB)
#		g++ -shared  -o $(SHAREDLIB)/libScanner.so $^ 
#
#	
#$(LIBDIR)/%.o :  $(SRCDIR)/%.cpp 
##	@mkdir -p `dirname $(OBJDIR)/$*.o`
#	@echo "g++ $*.cpp"
#	g++ -g  -c -fPIC  -o $@  $<

	