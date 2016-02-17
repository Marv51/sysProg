Dokumentation "systemnahes Programmieren" Teil 2: Der Parser
==============================================================
Parser
------
### Anforderung
Der Parser überprüft die Syntax und Semantik der Token aus dem Scanner (Teil 1) und erzeugt daraus Pseudo-Assembler Code.
Dies wird in 3 Schritten ausgeführt: 
1. Parse: überprüft ob der Quellcode den Regeln der Grammatik entspricht.
2. TypeCheck: Überprüft Logik des Programms.
3. MakeCode: Generiert den Assembler Code.

### Implementierung
Der Konstruktor der Parser Klasse erhält das Scanner Objekt und den Pfad zur Ausgabe als `char*`.

Die Klasse Parser enthält folgende öffentliche Methoden:

1.  `Node* match(InfoType)`
2.  `void nextToken()`
3.  `Node* parse()`
4.  `Node* parse[NodeType]()`
5.  `Node* createNode(NodeType)`
6.  `void error()`
7.  `void typeCheck(Node*)`
8.  `void errorTypeCheck(char* message, Token*)`
9.  `void makeCode(Node*)`

zu 1.) Die Methode `Node* match(InfoType)` wird aufgerufen, wenn ein Token geparst wird. Sie ruft die Methode `Node* createNode(NodeType::LEAF)` auf, weist dem erstellten Node die nötigen Werte zu und ruft dann die Methode `void nextToken()` auf.

zu 2.) Die Methode `void nextToken()` holt das nächste Token vom Scanner.

zu 3.) Die Methode `Node* parse()` startet das Parsen, indem sie die Methode `Node* parseProg()` aufruft und ihren Rückgabewert zurück gibt.

zu 4.) Die Methoden `Node* parse[NodeType]()` rufen sich gegenseitig auf und Bauen so die Baumstruktur der Nodes auf, indem für jeden Knoten durch die Methode `Node* createNode(NodeType)` ein Node Objekt erzeugt wird. Für die Struktur wird die `void addNode(Node*)` Methode der Node Klasse verwendet. Wenn ein Token geparst wird rufen sie außerdem die Methode `Node* match(InfoType)` auf. Fehler werden mit der Methode `void error()` ausgegeben.

zu 5.) Die Methode `Node* createNode(NodeType)` erstellt ein Neues Node Objekt mit dem angegebenen NodeType und gibt es zurück. Sie wird von den `Node* parse[NodeType]()` Methoden verwendet.

zu 6.) Die Methode `void error()` erzeugt eine Fehlermeldung (`stderr`) mit Angabe von Token, Zeile und Spalte und beendet das Programm (`exit(1);`).

zu 7.) Die Methode `void typeCheck(Node*)` funktioniert Rekursiv, indem sie sich immer wieder selbst aufruft mit der nächsten Node im Strukturbaum und prüft dabei auf Fehler im geparsten Programmcode. Dazu wird den Nodes ein Wert aus dem Enum CheckType zugeordnet. Die Möglichen Werte dieses Enums sind: `emptyType, intType, intArrayType, arrayType, noType, errorType, opPlus, opMinus, opMult, opDiv, opLess, opGreater, opEqual, opUnequal, opAnd`. Fehler werden mit der Methode `void errorTypeCheck(char* message, Token*)` ausgegeben.

zu 8.) Die Methode`void errorTypeCheck(char* message, Token*)` erzeugt eine Fehlermeldung (`stderr`) mit Angabe von Zeile, Spalte, und `message` und beendet das Programm (`exit(1);`).

zu 9.) Die Methode `void makeCode(Node*)` funktioniert Rekursiv, indem sie sich immer wieder selbst aufruft mit dem nächsten Node im Strukturbaum und erzeugt dabei den Assembler ähnlichen Code und schreibt ihn in die im Konstruktor spezifizierte Datei.

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
3.  `void print(uint16_t level)`
4.  `NodeType getType()`
5.  `Node* getNode(uint16_t index)`
6.  `CheckType getCheckType()`
7.  `void setCheckType(CheckType)`
8.  `uint16_t getSubnodesCount()`
9.  `uint16_t getKey()`
10. `Token* getToken()`
11. `void setToken(Token*)`

zu 1.) Die Methode `void addNode(Node*)` hängt den übergebenen Node an dieses Node an, indem es zur Liste `subnodes` hinzugefügt wird.

zu 2.) Die Methode `void setKey(uint16_t key, char* lexem)` setzt den Information Key und zu debugging Zwecken das Lexem des zugehöringen Tokens (wird in der `void print(uint16_t level)` Methode benötigt).

zu 3.) Die Methode `void print(uint16_t level)` gibt den Strukturbaum auf der Konsole aus. Sie funktioniert Rekursiv(?). Dies wird nur zu Debugging Zwecken benötigt. Das Argument `uint16_t level` wird zur Formatierung der Ausgabe verwendet.

zu 4.) Die Methode `NodeType getType()` gibt den NodeType des Node Objekts zurück.

zu 5.) Die Methode `Node* getNode(uint16_t index)` gibt den angehängten Node mit dem angegebenen Index zurück. Dieser Index muss kleiner 7 sein.

zu 6.) Die Methode `CheckType getCheckType()` gibt den CheckType des Node Objekts zurück.

zu 7.) Die Methode `void setCheckType(CheckType)` setzt den CheckType des Node Objekts auf den angegebenen Wert.

zu 8.) Die Methode `uint16_t getSubnodesCount()` liefert die Anzahl der angehängten Nodes zurück.

zu 9.) Die Methode `uint16_t getKey()` liefert den Information Key des Node Objekts zurück.

zu 10.) Die Methode `Token* getToken()` liefert den Token des Node Objekts zurück.

zu 11.) Die Methode `void setToken(Token*)` setzt den Token des Node Objekts auf den angegebenen Wert.


Verwendung des Compilers
------

### ParserTest

Durch Aufrufargumente werden die Ein- und Ausgabedateien eingelesen und gespeichert als `char*`. Es wird ein neuer Scanner erzeugt mit der Eingabedatei als Konstruktor Argument. Es wird ein neuer Parser mit dem Scanner und der Ausgabedatei als Konstruktor Argumente erzeugt. Auf dem Parser wird die Methode `Node* parse()` aufgerufen und der Rückgabewert wird gespeichert. Auf dem Parser werden nacheinander die Methoden `void checkType(Node*)` und `void makeCode(Node*)` mit dem Rückgabewert des `Node* parse()` Aufrufs als Argumente. Anschliessend ist der Pseudo-Assembler in der Ausgabedatei zu finden.
