%language "c++"
%define api.value.type variant
%define api.token.constructor

%code requires {
    #include <string>
    #include "ast.hpp"

    extern program* root;
}
%code provides {
    yy::parser::symbol_type yylex();
}

%token IF "if"
%token ELSE "else"
%token MAIN "main"
%token LX "("
%token RX ")"
%token LBRACE "{"
%token RBRACE "}"
%token ASSIGN "="
%token EQ "=="
%token INT "int"
%token PRINT "print"
%token DECLARE "declare" 
%token <std::string> ID
%token <int> INTEGER

%type <program*> program
%type <statements*> statements
%type <statement*> statement
%type <expression*> expression
%type <intdeclare*> intdeclare
%type <assignment*> assignment
%type <comparison*> comparison
%type <print*> print

%start program

%%

program: 
    MAIN LBRACE statements RBRACE 
    {
        $$ = new makeProgram($3);
        root = $$;
    }

statements:
    %empty
    {
        $$ = new emptyStatements();
    }
    |
    statements statement
    {
        $$ = new concatenateStatements($1, $2);
    }
;

statement:
    expression
    {
        $$ = new expressionStatement($1);
    }
    |
    intdeclare
    {
        $$ = new intdeclareStatement($1);
    }
    |
    assignment
    {
        $$ = new assignmentStatement($1);
    }
    | 
    print
    {
        $$ = new printStatement($1);
    }
;

expression:
    IF LX comparison RX
    LBRACE statements RBRACE
    ELSE
    LBRACE statements RBRACE
    {
        $$ = new ifElseExpression($3, $6, $10);
    }
;

intdeclare:
    DECLARE ID INT
    {
        $$ = new declareInteger($2);
    }
;

assignment:
    ID ASSIGN INTEGER
    {
        $$ = new assignInteger($1, $3);
    }
    | 
    ID ASSIGN ID
    {
        $$ = new assignIdentifier($1, $3);
    }
;

comparison:
    ID EQ ID
    {
        $$ = new compareIdentifierWithIdentifier($1, $3);
    }
    | 
    ID EQ INTEGER
    {
        $$ = new compareIdentifierWithInteger($1, $3);
    }
    |
    INTEGER EQ ID
    {
        $$ = new compareIntegerWithIdentifier($1, $3);
    }
;

print:
    PRINT LX ID RX
    {
        $$ = new printIdentifier($3);
    }
    | 
    PRINT LX INTEGER RX
    {
        $$ = new printInteger($3);
    }
;


%%