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

zu 1.) Die Methode match() wird aufgerufen, wenn ein Token geparst wird. Sie ruft die Methode `Node* createNode(NodeType::LEAF)` auf, weist dem erstellten Node die nötigen Werte zu und ruft dann die Methode `void nextToken()` auf.

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
