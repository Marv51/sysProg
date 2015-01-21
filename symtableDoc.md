Symboltable
------
Anforderung: Die Symboltabelle speichert die Informationen in einer Hashtabelle. Bei doppelten Hashwerten wird eine Linked List angelegt. Um auf die Informationen zuzugreifen wird ein Key benötigt, welcher in einer dynamischen Liste gespeichert wird.

### public
Der Konstruktor der Symboltable-Klasse erwartet keine Parameter. Er initialisiert die ürsprüngliche größe der Keyliste und die größe der Hashmap und er reserviert den Speicher für beide.

Der Buffer hat drei öffentliche Methoden: 

1. `Information* getInfo(uint16_t key)`  
2. `uint16_t newInfo(char* lexem, InfoTyp t)` 
3. `uint16_t hash(char* ch)` 

zu 1. ) Die Methode `getInfo()` erwartet als Parameter den Key der Information, welche als `Information*` zurückgegeben werden soll. Wenn die Information nicht existiert wird `NULL` zurückgegeben.

zu 2. ) Die Methode `newInfo()` erwartet als Parameter das Lexem als `char*` und den Typ der Information Infotyp-enum(-> siehe Information-Dokumentation). Sie gibt den Key der zum Lexem gehörigen Information als `uint16_t` zurück. Wenn die entsprechende Information schon existiert dann wird sie nicht neu angelegt, sondern lediglich der Key zurückgegeben.

zu 3. ) Der Hashwert der Informationen wird hier mithilfe des Lexems berechnet indem die einzelnen Zeichen als `(uint16_t)` gecastet addiert werden und danach modulo der Hashmap-Größe. Als Parameter wird das Lexem als `char*` erwartet und als Rückgabewert erfolgt der Hashwert als `uint16_t`.

### Private Methoden und Attribute

`void keySizeBigger()`: Diese Methode wird immer dann aufgerufen, wenn eine neue Information angelegt wurde. Sie inkrementiert das Attribut `keysize`. Wenn die `keys`-Liste voll ist verdoppelt sie deren Größe und reserviert neuen Speicher.

`void initSymbols()`: Diese Methode wird vom Konstruktor der Symboltable aufgerufen und erzeugt Informationen für alle Schlüsselwörter der Sprache (if, else, while, int, read, write).

Als Speicher der Keys und der Informationen dienen die Arrays `Information** informations` und `int* keys`. Das Attribut `memsize` legt die Größe der Hashmap `informations` fest und `keysizemax` die momentane Größe des Speichers des `keys` Arrays. Das Attribut `keysize` zählt die tatsächliche Größe des `keys` Arrays mit.

### Fehlerbehandlung

In der Klasse Symboltable können Fehler auftreten.
