

SRCDIR = src
OBJDIR = debug

BINDIR = debug

LIBDIR = lib


SHAREDLIB = ../sharedlib

## hier alle Object Files eintragen
## darauf achten, dass letzte Zeile ohne "\" eingetragen wird

OBJS = $(OBJDIR)/Scanner.o \
	$(OBJDIR)/TestScanner.o \
	$(OBJDIR)/Token.o \
	$(OBJDIR)/myListe.o

#$(OBJDIR)/xx1.o \
#$(OBJDIR)/xxn.o

OBJSFORSCANNERLIB =  \
	$(LIBDIR)/Scanner.o  \
	$(LIBDIR)/Token.o \
	$(LIBDIR)/myListe.o
	


# Variante mit wenig Makefile-Kenntnissen
 
# linken der Object-files under shared libraries

makeTestScanner: $(OBJDIR)/Token.o $(OBJDIR)/Scanner.o $(OBJDIR)/TestScanner.o $(OBJDIR)/myListe.o
	g++ -Wall -Wextra -pedantic -std=c++11 -g $(OBJDIR)/Token.o $(OBJDIR)/Scanner.o $(OBJDIR)/TestScanner.o $(OBJDIR)/myListe.o  -L../sharedlib  -lAutomat  -lBuffer -lSymboltable -o $(BINDIR)/ScannerTest
#	
#	
#	
## compilieren der source-files
$(OBJDIR)/Token.o :  $(SRCDIR)/Token.cpp 
	@echo "g++ $*.cpp"
	g++ -Wall -Wextra -pedantic -std=c++11 -g  -c -Wall  -o $(OBJDIR)/Token.o  $(SRCDIR)/Token.cpp
	
$(OBJDIR)/myListe.o :  $(SRCDIR)/myListe.cpp 
	@echo "g++ $*.cpp"
	g++ -Wall -Wextra -pedantic -std=c++11 -g  -c -Wall  -o $(OBJDIR)/myListe.o  $(SRCDIR)/myListe.cpp

$(OBJDIR)/Scanner.o :  $(SRCDIR)/Scanner.cpp 
	@echo "g++ $*.cpp"
	g++ -Wall -Wextra -pedantic -std=c++11 -g  -c -Wall  -o $(OBJDIR)/Scanner.o  $(SRCDIR)/Scanner.cpp

$(OBJDIR)/TestScanner.o :  $(SRCDIR)/TestScanner.cpp 
	@echo "g++ $*.cpp"
	g++ -Wall -Wextra -pedantic -std=c++11 -g  -c -Wall  -o $(OBJDIR)/TestScanner.o  $(SRCDIR)/TestScanner.cpp
		


#Variante  mit guten Kenntnissen
#makeTestScanner: $(OBJS)
#	g++ -g $^ -L../sharedlib  -lAutomat  -lBuffer -lSymboltable -o $(BINDIR)/ScannerTest
	
	
	
# $^ liste der abhaengigkeiten


#$(OBJDIR)/%.o :  $(SRCDIR)/%.cpp 
#	@echo "g++ $*.cpp"
#	g++ -g  -c -Wall  -o $@  $<

# 
# $@ name des object files
# $< erste abhaengigkeit


# loeschen aller files im verzeichnis $(OBJDIR) und $(LIBDIR) und neu bauen

cleanScanner:
	rm -rf $(OBJDIR)/*
	rm -rf $(LIBDIR)/*
#	$(MAKE) makeTestScanner
	
	
	
## erstellen der shared library

# erst wichtig fuer den Parser Teil
#
ScannerLib:$(OBJSFORSCANNERLIB)
		g++ -shared  -o $(SHAREDLIB)/libScanner.so $^ 
#
#	
$(LIBDIR)/%.o :  $(SRCDIR)/%.cpp 
	@mkdir -p `dirname $(OBJDIR)/$*.o`
	@echo "g++ -Wall -Wextra -pedantic -std=c++11 $*.cpp"
	g++ -Wall -Wextra -pedantic -std=c++11 -g  -c -fPIC  -o $@  $<

	