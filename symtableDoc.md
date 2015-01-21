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


Information
------

Anforderung: Die Klasse `Information` dient zum speichern der Informationen in der Symboltabelle. Sie speichert das Lexem, den Key in der Symboltabelle, ihren `InfoTyp` und ihren Wert für Zahlen.

## Public

Der Konstruktor der Klasse erwartet als Parameter das Lexem der Information und den Key. Diese werden abgespeichert und alle anderen Attribute werden auf ihre Standartwerte gesetzt.

`char* getLexem()`: Liefert das Lexem der Information zurück.

`void setLexem(char* lex)`: Ändert das Lexem zu dem Wert des Parameters.

`bool compareLexem(char* lex)`: Liefert true zurück, wenn das übergebene Lexem das gleiche ist wie das gespeicherte.

`Information* getNextInfo()`: Liefert das Attribut `nextInfo` zurück.

`void setNextInfo(Information* info)`: Ändert das Attribut nextInfo zu dem Wert des Parameters.

`uint16_t getKey()`: Liefert den Key der Information zurück.

`int getValue()`: Liefert den Inhalt des Tokens als Integer konvertiert zurück. Beim ersten Aufruf wird dieser Berechnet. Wenn eine Berechsüberschreitung (x < 0 oder x > `INT_MAX`) vorliegt, dann wird der Wert -1 zurückgegeben.

`InfoTyp getType()`: Liefert den Typ der Information als `InfoTyp`-enum zurück.

`void setType(InfoTyp t)`: Ändert den Wert des Typs der Information.

## Attribute

`InfoTyp type`: Der Typ der Information: (Standartwert Unknown)

`enum class InfoTyp{
	Unknown,
	Sign,
	Integer,
	Identifier,
	iftyp,
	whiletyp,
	elsetyp,
	inttyp,
	writetyp,
	readtyp,
	Fehler
};`

`char* lexem`: Das Lexem der Information.

`Information* nextInfo`: Bei doppeltem Hashwert in der Symboltabelle wird hiermit die Linked List realisiert. (Standartwert NULL)

`uint16_t key`: Der Key der Information in der Symboltabelle.

`int value`: Das Lexem als Integer. (Standartwert -1)
