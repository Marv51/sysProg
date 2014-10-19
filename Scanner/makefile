

SRCDIR = src
OBJDIR = debug

BINDIR = debug

LIBDIR = lib


SHAREDLIB = ../sharedlib

## hier alle Object Files eintragen
## darauf achten, dass letzte Zeile ohne "\" eingetragen wird

OBJS = $(OBJDIR)/Scanner.o \
	$(OBJDIR)/TestScanner.o

#$(OBJDIR)/xx1.o \
#$(OBJDIR)/xxn.o

OBJSFORSCANNERLIB =  \
	$(LIBDIR)/Scanner.o
	


# Variante mit wenig Makefile-Kenntnissen
 
# linken der Object-files under shared libraries
#makeTestScanner: $(OBJDIR)/Scanner.o $(OBJDIR)/TestScanner.o
#	g++ -g $(OBJDIR)/Scanner.o $(OBJDIR)/TestScanner.o -L../sharedlib  -lAutomat  -lBuffer -lSymboltable -o $(BINDIR)/ScannerTest
#	
#	
#	
## compilieren der source-files
#$(OBJDIR)/Scanner.o :  $(SRCDIR)/Scanner.cpp 
#	@echo "g++ $*.cpp"
#	g++ -g  -c -Wall  -o $(OBJDIR)/Scanner.o  $(SRCDIR)/Scanner.cpp
#
#$(OBJDIR)/TestScanner.o :  $(SRCDIR)/TestScanner.cpp 
#	@echo "g++ $*.cpp"
#	g++ -g  -c -Wall  -o $(OBJDIR)/TestScanner.o  $(SRCDIR)/TestScanner.cpp
#



#Variante  mit guten Kenntnissen
makeTestScanner: $(OBJS)
	g++ -g $^ -L../sharedlib  -lAutomat  -lBuffer -lSymboltable -o $(BINDIR)/ScannerTest
	
	
	
# $^ liste der abhaengigkeiten


$(OBJDIR)/%.o :  $(SRCDIR)/%.cpp 
	@echo "g++ $*.cpp"
	g++ -g  -c -Wall  -o $@  $<

# 
# $@ name des object files
# $< erste abhaengigkeit


# loeschen aller files im verzeichnis $(OBJDIR) und $(LIBDIR) und neu bauen

cleanScanner:
	rm -rf $(OBJDIR)/*
	$(MAKE) makeTestScanner
	
	
	
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

	