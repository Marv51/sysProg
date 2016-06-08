Dokumentation "systemnahes Programmieren" Teil 2: Der Parser
==============================================================

*Ein Projekt von Dennis Kühnen, Marius Wirtherle und Marvin Rühe*

Grammatik
---------

```
PROG ::= DECLS STATEMENTS
DECLS ::= DECL ; DECLS | ε
DECL ::= int ARRAY identifier
ARRAY ::= [ integer ] | ε
STATEMENTS ::= STATEMENT ; STATEMENTS | ε
STATEMENT ::= identifier INDEX := EXP | write( EXP ) | read ( identifier INDEX) 
              | {STATEMENTS} | if ( EXP ) STATEMENT else STATEMENT 
              | while ( EXP ) STATEMENT
EXP ::= EXP2 OP_EXP
EXP2 ::= ( EXP ) | identifier INDEX | integer | - EXP2 | ! EXP2
INDEX ::= [ EXP ] | ε
OP_EXP ::= OP EXP | ε
OP ::= + | - | * | / | < | > | = | <:> | &
```
Die Regeln für den Typecheck und das generieren des Codes waren als Pseudo-Code in der Aufgabenstellung enthalten.

Parser
------
### Anforderung
Der Parser überprüft die Syntax und Semantik der Token aus dem Scanner (Teil 1) und erzeugt daraus Pseudo-Assembler Code.
Dies wird in 3 Schritten ausgeführt:
1. Parse: überprüft ob der Quellcode den Regeln der Grammatik entspricht.
2. TypeCheck: Überprüft Logik des Programms.
3. MakeCode: Generiert den Assembler Code.

Das wird in der Main Methode dann so aufgerufen:
```
// Teil 1 - Siehe Dokumentation Teil 1
Scanner* scanner = new Scanner(input);

// Teil 2
auto parser = new Parser(scanner, output);
  // Schritt 1: Strukturbaum bauen
Node* root = parser->parse();

  // Schritt 2: TypeCheck
parser->typeCheck(root);

  // Schritt 3: Code generieren
parser->makeCode(root);
```

### Fehlerbehandlung
Sowohl beim Strukturbaum erstellen, als auch beim TypeCheck wird ein Fehler direkt auf der Konsole ausgegeben und der Programm ablauf mit `exit(1)` beendet.


### Implementierung
Der Konstruktor der Parser Klasse erhält das Scanner Objekt und den Pfad zur Ausgabe des Assembler Codes als `char*`.

Die Klasse Parser enthält folgende öffentliche Methoden:

1.  `Node* parse()`
2.  `Node* parse[NodeType]()`
3.  `void  typeCheck(Node*)`
4.  `void  makeCode(Node*)`


zu 1.) Die Methode `Node* parse()` startet das Parsen, indem sie die Methode `Node* parseProg()` aufruft und ihren Rückgabewert zurück gibt. Dadurch wird nach und nach rekursiv ein Baum aufgebaut. Der Wurzel Knoten wird von dieser Methode zurückgegeben

zu 2.) Die Methoden `Node* parse[NodeType]()` rufen sich gegenseitig auf und Bauen so die Baumstruktur der Nodes auf, indem für jeden Knoten durch die Methode `Node* createNode(NodeType)` ein Node Objekt erzeugt wird. Für die Struktur wird die `void addNode(Node*)` Methode der Node Klasse verwendet. Wenn ein Token geparst wird rufen sie außerdem die Methode `Node* match(InfoType)` auf. Fehler werden ausgegeben und das Programm mit `exit(1)` beendet.

zu 3.) Die Methode `void typeCheck(Node*)` funktioniert Rekursiv, indem sie sich immer wieder selbst aufruft mit der nächsten Node im Strukturbaum und prüft dabei auf Fehler im geparsten Programmcode. Dazu wird den Nodes ein Wert aus dem Enum CheckType zugeordnet. Die Möglichen Werte dieses Enums sind: `emptyType, intType, intArrayType, arrayType, noType, errorType, opPlus, opMinus, opMult, opDiv, opLess, opGreater, opEqual, opUnequal, opAnd`. Fehler werden ausgegeben und das Programm mit `exit(1)` beendet.

zu 4.) Die Methode `void makeCode(Node*)` funktioniert rekursiv, indem sie sich immer wieder selbst aufruft mit dem nächsten Node im Strukturbaum und erzeugt dabei den Assembler ähnlichen Code und schreibt ihn in die im Konstruktor spezifizierte Datei.

Node
------

### Anforderungen
Node-Objekte bilden den Struktur-Baum der in der Parse-Methode erstellt wird. Dieser Baum wird dann in typeCheck und makeCode rekursiv abgearbeitet.

###Implementierung

Eine Node hat einen Typen aus der Grammatik, den NodeType: `PROG, DECLS, DECL, ARRAY, STATEMENT, STATEMENTS, EXP, EXP2, INDEX, OP_EXP, OP, LEAF`

Während dem TypeCheck wird den Nodes ein weiterer Typ zugeordnet, der CheckType: `emptyType, intType, intArrayType, arrayType, noType, errorType, opPlus, opMinus, opMult, opDiv, opLess, opGreater, opEqual, opUnequal, opAnd`


Der Konstruktor der Klasse Node bekommt den NodeType übergeben und speichert ihn und setzt den CheckType auf `emptyType`.

Die Klasse Node hat folgende öffentliche Methoden:

1.  `void addNode(Node*)`
2.  `void setKey(uint16_t key, char* lexem)`
3.  `NodeType getType()`
4.  `Node* getNode(uint16_t index)`
5.  `CheckType getCheckType()`
6.  `void setCheckType(CheckType)`
7.  `uint16_t getSubnodesCount()`
8.  `uint16_t getKey()`
9. `Token* getToken()`
10. `void setToken(Token*)`

zu 1.) Die Methode `void addNode(Node*)` hängt den übergebenen Node an dieses Node an, indem es zur Liste `subnodes` hinzugefügt wird.

zu 2.) Die Methode `void setKey(uint16_t key, char* lexem)` setzt den Information Key und zu debugging Zwecken das Lexem des zugehöringen Tokens.

zu 3.) Die Methode `NodeType getType()` gibt den NodeType des Node Objekts zurück.

zu 4.) Die Methode `Node* getNode(uint16_t index)` gibt den angehängten Node mit dem angegebenen Index zurück. Dieser Index muss kleiner 7 sein.

zu 5.) Die Methode `CheckType getCheckType()` gibt den CheckType des Node Objekts zurück.

zu 6.) Die Methode `void setCheckType(CheckType)` setzt den CheckType des Node Objekts auf den angegebenen Wert.

zu 7.) Die Methode `uint16_t getSubnodesCount()` liefert die Anzahl der angehängten Nodes zurück.

zu 8.) Die Methode `uint16_t getKey()` liefert den Information Key des Node Objekts zurück.

zu 9.) Die Methode `Token* getToken()` liefert den Token des Node Objekts zurück.

zu 10.) Die Methode `void setToken(Token*)` setzt den Token des Node Objekts auf den angegebenen Wert.


Verwendung des Compilers
------

### ParserTest

Durch Aufrufargumente werden die Ein- und Ausgabedateien eingelesen und gespeichert als `char*`. Es wird ein neuer Scanner erzeugt mit der Eingabedatei als Konstruktor Argument. Es wird ein neuer Parser mit dem Scanner und der Ausgabedatei als Konstruktor Argumente erzeugt. Auf dem Parser wird die Methode `Node* parse()` aufgerufen und der Rückgabewert wird gespeichert. Auf dem Parser werden nacheinander die Methoden `void checkType(Node*)` und `void makeCode(Node*)` mit dem Rückgabewert des `Node* parse()` Aufrufs als Argumente. Anschliessend ist der Pseudo-Assembler in der Ausgabedatei zu finden.

Ein Beispielaufruf wäre also zum Bespiel:
```
./ParserTest in.txt out.txt
```
