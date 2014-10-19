sysProg
=======
Das Projekt wurde in 4 Teilprojekte aufgeteilt:
* Automat
* Buffer
* Symboltabelle

* Scanner
	

Jedes Teilprojekt hat die Verzeichnisstruktur:
* debug		enthaelt Objektfiles zum Testen
* lib		enthaelt Objektfiles zum Erstellen der shared library des Teilprojekts
* src		enthaelt den Source-Code

jedes Teilprojekt enthaelt ein eigenes Makefile und eine eigene Main-Klasse, um die Funktionalitaet zu testen.
	
Level: ohne Makefile Kenntnisse	
Im Makefile im Teilprojekt Automat sind alle Schritte zum Compilieren und Linken ausfuehrlich aufgelistet.


Level: wenig Makefile-Kenntnisse
Im Makefile im Teilprojekt Buffer werden die benoetigten Verzeichnisse ueber Variablen definiert.


Level: gute Makefile-Kenntnisse
Im Makefile im Teilprojekt Symboltabelle und Scanner wird auch die Liste der Abhaengigkeiten ueber Variablen deklariert

Aufbau des Makefiles:

	Definition der Variablen
	Targets zum Bauen des Tests
	Targets zum Erstellen der shared library
	
Das Makefile im obersten Projekt-Verzeichnis loescht alle shared libraries und erstellt alle neu.

In der View "Make Targets" erscheinen die Targets der einzelnen Makefiles, die dann mit einem Doppelklick ausgefuehrt werden können.

Aufbau der Targets

	# 	 target: dependencies
	# 	 [tab] system_command
	#
	#
	# Compilation commands:
	#    classA.o: classA.cpp
	#    [tab] g++ -c classA.cpp -o classA.o
	#
	#    classB.o: classB.cpp
	#    [tab] g++ -c classB.cpp -o classB.o
	#
	#
	# Link command:
	#    my_program: classA.o classB.o
	#    [tab] c++ classA.o classB.o -o my_program
	#	
	# options:
	#		-c			Kompilieren ohne zu linken. 
	#		-g 			debugging infos erzeugen
	#		-o file     object-file file erzeugen 
	#
	#       -fPIC		position independant code wichtig für shared library

Zum Ausfuehren der Programme muss der LD_LIBRARY_PATH noch folgendermaßen gesetzt werden:
m Eclipse workspace unter 

	Project --> Properties --> Run / Debug Settings --> Environment --> Select --> LD_LIBRARY_PATH --> ok

den Eintrag LD_LIBRARY_PATH auswählen --> edit
den Pfad zum Verzeichnis der shared library an das Ende anhängen, trennen mit ;


http://www.sethi.org/classes/cet375/lab_notes/lab_04_makefile_and_compilation.html

http://mrbook.org/tutorials/make/
