Dokumentation "systemnahmes Programmieren" Teil 1: Der Scanner
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


 
