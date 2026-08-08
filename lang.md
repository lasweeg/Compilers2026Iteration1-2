program := MAIN LBRACE statements RBRACE
statements := EMPTY | statements statement
statement := expression | intdeclate | assignment | print
expression := IF LX comparison RX LBRACE statements RBRACE ELSE LBRACE statements RBRACE
intdeclare := DECLARE ID INT
assignment := ID ASSIGN ID
comparison := ID EQ ID
print := PRINT LX ID RX