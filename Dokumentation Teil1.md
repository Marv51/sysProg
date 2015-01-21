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

### Anforderung
Der Scanner baut die einzelnen Teile zusammen und steuert den Datenaustausch.
Der Scanner bekommt im Konstruktor den Pfad einer Eingabedatei. Diese Datei wird mit jedem aufruf von nextToken um ein Token ausgelesen und dieses Token zurückgegeben.

###public
Der Scanner hat die Methode `bool nextToken(Token* t)` und die Methode `Information* getInfo(uint16_t key)`

Die Methode `nextToken` ließt solange Zeichen aus dem Buffer bis ein Token zusammengebaut werden kann. Und Verknüpft dieses Token dann mit der Symboltabelle. Wenn man am Ende der Datei ist und also kein Token mehr gebaut werden kann, wird false zurückgegeben.

Die Methode `getInfo` gibt zu einem übergebenen Schlüssel die entsprechende Information aus der Symboltabelle zurück.

### Implementierung
Im Konstruktor des Scanners wird ein neuer Buffer mit dem Übergebenen Dateipfad hergestellt, außerdem wird ein neuer Automat und eine neue Symboltabelle erstellt.
Solange das eingegebene Token noch leer ist, und kein Kommentar, wird nach dem nächsten Token gesucht:
Es wird immer ein Zeichen aus dem Buffer geladen, dieses Zeichen wird in einer Liste gespeichert, dann wird es in den Automaten gegeben. 
Die Liste wird weiter unten dokumentiert.

Das wird solange getan bis der Buffer zurückgibt, dass er kein weiteres Zeichen möchte. 
Dann wird der letzten Finale Zustand des Automaten im Token gespeichert. Und so viele Zeichen wieder zurück gesprungen werden wie seit dem letzten Finalen Zustand in den Automaten gegeben wurden.
Danach wird im Token die Zeile und Spalte die der Automat gezählt hat gespeichert.
Jetzt wird noch  mit Hilfe der privaten Methode `makeInfo(Token* t)` das Token in die Symboltabelle eingefügt.
Am Ende zurückgegeben wird, ob der Buffer noch weitere Zeichen hat.

Die Methode `getInfo` ruft einfach nur den Methode `getInfo`  der Symboltabelle mit dem Übergebenen Schlüssel  auf und gibt deren Resultat zurück.

### Die Methode `makeInfo`
Wandelt den TokenTyp im Token ein einen InfoTyp um. State::Number wird zu InfoTyp::Integer State::Identifier wird zu InfoTyp::Identifier, State::Fehler wird zu InfoTyp::Fehler, und die Zustände die ein Zeichen sind werden zu InfoTyp::Sign.

Mit der newInfo Methode der Symboltabelle wird jetzt der Inhalt des Tokens und dessen InfoTyp gespeichert und zurück wird ein Key gegeben mit dem man später wieder auf die Information zugreifen kann. 
Zur Kontrolle wird dann überprüft ob der Wert des Tokens ungleich -1 ist, dass würde eine Bereichsüberschreitung hinweisen., dann wird der Typ auf Fehler gesetzt.

Abschließend wird noch der Key im Token gespeichert.

### Die Liste
Idee: Um Buchstaben bequem in einer Liste speichern zu können, von deren Ende man Buchstaben auch wieder entfernen kann. , haben wir unsere Liste gebaut. Das macht natürlich nur Sinn wenn man weiß, dass wir keine fertigen Datenstrukturen verwenden dürfen.

Die Öffentlichen Methoden unserer Liste sind:
1. `void push(char ch)`
2. `char pop()`
3. `char* getString()`
4. `bool isEmpty()`
5. `void clear()`

Die Liste ist eigentlich nicht als Liste implementiert, sondern als automatisch wachsendes Array.

Mit `push` wird an die Stelle des internen Zählers ein neues Zeichen geschreiben. Der Zähler wird um eins erhöht und an die Stelle an der, der Zähler dann steht wird `\0`eingefügt. Probleme gibt es nur wenn das aktuelle Array nicht groß genug ist:
in diesem Fall wird doppelt so viel Speicher wie das Array im Moment belegt angefordert und der Inhalt des aktuellen Arrays in das neue Array kopiert. Dann wird das alte Array gelöscht und durch das neue Array ersetzt.

Die Methode `pop()` gibt das letzte Zeichen zurück und überschreibt seine Position vorher mit `\0`. Die Liste schrumpft nicht wieder.

Die Methode `getString` gibt einfach einen Pointer auf das erste Element zurück, da wir immer am Ende des benutzenBereichs des Arrays ein `\0` einfügen. `isEmpty()` ist ebenfalls trivial wir verwenden einen internen Zähler der einfach mit 0 verglichen wird.
`clear` setzt den internen Zähler wieder auf 0 und fügt an der ersten Stelle im Array ein `\0` ein.

Im Konstruktor wird eine leere Liste angelegt mit Platz für 8 Zeichen.
Im Destruktor wird der Speicherplatz der Liste immer wieder freigegeben.


Token
-----
Der Quelltext der vom Buffer eingelesen wird, soll im Scanner in Tokens aufgespalten werden. Diese Tokens haben Zeilen un Spalten Information, sowie einen Typen, einen Inhalt und einen Key. Mit dem Key kann man dann die Information die mit diesem Token verbunden ist in der Symboltabelle abrufen.

Für Zeile und Spalte gibt es Getter und Setter (`int getZeile(), int getSpalte(), void setZeile(int Zeile), void setSpalte(int Spalte)`).
Für TokenTyp und Key ebenso (`State getTokenTyp(), void setTokenTyp(State t), void setKey(uint16_t key) und uint16_t getKey()`)

Der Inhalt wird in einer Liste gespeichert, diese Liste wird im Konstruktor angelegt und ist über die content Variable öffentlich Zugänglich. Die Methode `char* getContent()` liefert die Liste als Zeichenkette zurück.

Zusätzlich hat ein Token noch die Methode `const char* getTokenTypeString()` das den aktuellen TokenTyp als Zeichenkettte für die Ausgabe zurückgibt. Ein TokenTyp ist ein enum, und kann damit in ein Integer umgewandelt werden. Dieser Wird als Index für ein Array mit den Namen der TokenTypen verwendet und der String zurückgegeben.
