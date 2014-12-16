Dokumentation "systemnahes Programmieren" Teil 1: Der Scanner
==============================================================
Buffer
------
Anforderung: Der Buffer wird zum einlesen von Dateien in unser Programm verwendet. Er verwendet die systemnahe Funktion open um Dateien von der Festplatte zu lesen. Um die Aufgabe zusätzlich kompliziert zu machen verwenden wir das Flag "O_Direct". 

### public
Der Konstruktor der Buffer-Klasse erwartet einen char* auf den Pfad an dem sich die Datei die gelesen werden soll befindet. 

Der Buffer hat drei öffentliche Methoden: 

1. `char getChar()`  
2. `void ungetChar()` 
3. `bool hasCharLeft()` 

zu 1. ) Die Methode `getChar` liefert das nächste Zeichen der Datei zurück. Wenn man also zwei mal hintereinander `getChar()` aufruft werden die ersten beiden Zeichen einer Datei zurückgegeben. 

zu 2. ) Die Methode `ungetChar` setzt die Position in der Datei von der wir aktuell lesen um ein Zeichen zurück. Vorsicht: Das bedeutet, wenn man `getChar(); ungetChar(); getChar()` aufruft wird zwei mal das selbe Zeichen gelesen. 

zu 3. ) Die Methode `bool hasCharLeft();` Überprüft ob das Zeichen das mit dem nächsten `getChar()` gelesen werden würde das Ende der Datei ist, dass bedeutet die Methode überprüft ob es noch weitere Zeichen in der Datei gibt, die wir noch nicht gelesen haben. 

### Implementierung
Der Datei Zugriff nutzt `read` und `O_DIRECT`, die drei entscheidenden Zeilen sind: 

    fileHandle = open(input_path, O_RDONLY | O_DIRECT); // um die Datei zu öffnen 
    posix_memalign((void**) &current_buffer, 512, 512); // um Speicher zu reservieren  
    read(fileHandle, current_buffer, 512); // um einen Block zu lesen 

Mit diesen drei Zeilen können wir jeder Zeit einen Block aus der Datei lesen. 

Intern wird der Buffer in zwei Teile aufgeteilt: `current_buffer` und `prev_buffer` Anfangs wird der `current_buffer` mit 512 Zeichen aus der Datei gefüllt und der Positionsindex `position` steht auf 0. 

Wenn jetzt `getChar` aufgerufen wird, wird position um eins erhöht und die Stelle im `current_buffer` zurückgegeben an der Position vorher stand.  
Mit der Methode `ungetChar()` wird einfach `position` um eins verringert. 

Die Methode `hasCharLeft()`, ruft einfach `getChar()` auf, schaut ob das nächste Zeichen ein Dateiende-Zeichen ist (`\0`) und ruft dann `ungetChar()` auf um die Position wiederherzustellen. 

Die beiden schwierigen Fälle sind: Wenn man am Ende eines Blockes angekommen ist muss mehr aus der Datei nachgeladen werden und wenn man über die Blockgrenzen hinweg `ungetChar()` aufruft. 

Zum ersten Fall wenn mehr Daten gebraucht werden (d.h. das 513 Zeichen aus einem Block), dann müssen neue Daten aus der Datei gelesen werden, dass machen wir so: 

Der Inhalt des `current_buffer` wird in den `prev_buffer` verschoben. Das ist sehr einfach, weil nur die Pointer auf die Speicherstellen getauscht werden müssen. Dann wird wie schon am Anfang in `current_buffer` ein neuer Block der Datei eingelesen. Die Position wird auf 0 gesetzt. 

Wenn also direkt nachdem wir neue Daten gelesen haben ein `ungetChar()` kommt steht die `position` auf -1. Unsere `getChar()` Methode gibt wenn `position < 0` ist das Zeichen aus dem `prev_buffer` zurück an der Stelle `511+postion`. Also wenn `position = ` ist, wird `prev_buffer[511-1]` zurückgegeben. 

### Fehlerbehandlung

In der Klasse Buffer können Fehler auftreten.

Automat
------
Wenn man dem Automaten ein Zeichen übergibt, ändert er seinen internen Zustand und zählt Zeilen und Spalten.
### public
Es wird ein enum mit allen Zuständen die der Automat einnehmen kann definiert, `State`

    enum State {
    	Undefined,
    	Start,
    	Number,
    	Identifier,
    	KleinerAls,
    	GeschweifteKlammerAuf,
    	GeschweifteKlammerZu,
    	VorwaertsSchraegstrich,
    	EckigeKlammerAuf,
    	EckigeKlammerZu,
    	UndZeichen,
    	GroesserAls,
    	Stern,
    	Ausrufezeichen,
    	RundeKlammerAuf,
    	RundeKlammerZu,
    	IstGleichZeichen,
    	Minus,
    	Plus,
    	Doppelpunkt,
    	DoppelpunktIstGleich,
    	Semikolon,
    	KleinerDoppelpunkt,
    	kleinerDoppelpunktGroesser,
    	SchraegStrichStern,
    	SchraegstrichSternStern,
    	SchraegstrichSternSternSchraegstrich,
    	Fehler
    };

Seine öffentlichen Methoden sind:

1. `State getlastFinalState();`
2. `int getStepsSinceLastFinalState();`
3. `bool testChar(char c)`
4. `int getZeile();`
5. `int getSpalte();`
6. `void clean();`
7. `void spalteZurueck();`

zu 1.) Gibt den letzten finalen Zustand des Automaten zurück. Wenn noch kein Finaler Zustand erreicht wurde wird der Zustand `Start` zurückgegeben.

zu 2.) Gibt die Zeichen die getestet (`testChar()`) wurden seit dem letzten finalen Zustand des Automaten zurück.

zu 3.) Die wichtigste Methode des Automaten: Sie führe die Übergänge der Zustände mit einem eingegeben Zeichen aus. Außerdem sorgt Sie dafür, dass Zeile und Spalte gezählt wurden.

zu 4. und 5.) Geben die Zeile und Spalte vom Anfang des Tokens zurück. (Ein neues Token beginnt wenn der Automat im Start Zustand ist und ein Zeichen getestet werden soll.

zu 6.) Die Methode wird wahrscheinlich entfernt.

zu 7.) Wenn wir ein Zeichen mehr eingelesen haben als wir sollten, kann man hiermit den Spalten-Zähler wieder zurücksetzen. Warum brauchen wir diese Methode?

### Implementierung
Unser Automat basiert auf einer großen Übergangsmatrix (28x256), die aus die aus dem aktuellen Zustand und einem bliebigen char einen Folgezustand zurückgibt.
Anfangs sind alle Übergänge mit Undefined als Folgezustand definiert, außer den Übergängen die bewusst im Konstruktor gesetzt wurden.
Ein zweites Array finalStates ordnet jedem Zustand zu, ob dieser ein finaler Zustand ist.

Mit dieser Information kann man jetzt für jedes Zeichen das man testet der Übergang Undefined ist, oder ob es einen Folgezustand gibt.
Wenn der Übergang Undefined ist, wird false zurückgegeben, dies ist dann das Ende des Tokens. Ist der Folgezustand aber nicht undefined, wird der Aktuelle Zustand verändert und true zurückgegeben.

Scanner
-------
Der Scanner hat die Methode nextToken und die Methode ?

Die Methode Next Token ließt solange Zeichen aus dem Buffer bis ein Token zusammengebaut werden kann. Und Verknüpft dieses Token dann mit der Symboltabelle.
