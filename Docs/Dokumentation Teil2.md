Dokumentation "systemnahes Programmieren" Teil 2: Der Parser
==============================================================
Parser
------

### public
Der Konstruktor der Parser Klasse erhält das Scanner Objekt und eine char\*, die den Pfad zur Ausgabe (\*.code) Datei enthält.

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

zu 4.) Die Methoden `Node* parse[NodeType]()` rufen sich gegenseitig auf und Bauen so die Baumstruktur der Nodes auf, indem für jeden Knoten durch die Methode `Node* createNode(NodeType)` ein Node Objekt erzeugt wird. Für die Struktur wird die `void addNode(Node*)` Methode der Node Klasse verwendet. Wenn ein Token geparst wird rufen sie außerdem die Methode `Node* match(InfoType)` auf.

zu 5.) Die Methode `Node* createNode(NodeType)` erstellt ein Neues Node Objekt mit dem angegebenen NodeType und gibt es zurück. Sie wird von den `Node* parse[NodeType]()` Methoden verwendet.

zu 6.) Die Methode `void error()` erzeugt eine Fehlermeldung (stderr) mit Angabe von Token, Zeile und Spalte und beendet das Programm (exit(1);).

### Implementierung

### Fehlerbehandlung

Node
------

### public

### Implementierung

### Fehlerbehandlung

Verwendung von Scanner und Parser
------

### ParserTest
