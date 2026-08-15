%language "c++"
%define api.value.type variant
%define api.token.constructor
%parse-param { program& root }

%code requires {
    #include <memory>
    #include <string>
    #include "ast.hpp"
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
%token PLUS "+"
%token MINUS "-"
%token MULTIPLY "*"
%token DIVIDE "/"
%token INT "int"
%token PRINT "print"
%token DECLARE "declare"
%token <std::string> ID
%token <int> INTEGER

%left PLUS MINUS
%left MULTIPLY DIVIDE

%type <statements> statements
%type <std::unique_ptr<statement>> statement
%type <std::unique_ptr<expression>> expression
%type <std::unique_ptr<intdeclare>> intdeclare
%type <std::unique_ptr<assignment>> assignment
%type <std::unique_ptr<comparison>> comparison
%type <std::unique_ptr<print>> print
%type <std::unique_ptr<arithmeticExpression>> arithmetic

%start program

%%

program:
    MAIN LBRACE statements RBRACE
    {
        root.programStatements = std::move($3);
    }
;

statements:
    %empty
    {
        $$ = ::statements();
    }
    |
    statements statement
    {
        $1.add(std::move($2));
        $$ = std::move($1);
    }
;

statement:
    expression
    {
        $$ = std::make_unique<expressionStatement>(std::move($1));
    }
    |
    intdeclare
    {
        $$ = std::make_unique<intdeclareStatement>(std::move($1));
    }
    |
    assignment
    {
        $$ = std::make_unique<assignmentStatement>(std::move($1));
    }
    |
    print
    {
        $$ = std::make_unique<printStatement>(std::move($1));
    }
;

expression:
    IF LX comparison RX
    LBRACE statements RBRACE
    ELSE
    LBRACE statements RBRACE
    {
        $$ = std::make_unique<ifElseExpression>(
            std::move($3),
            std::move($6),
            std::move($10)
        );
    }
;

intdeclare:
    DECLARE ID INT
    {
        $$ = std::make_unique<declareInteger>($2);
    }
;

assignment:
    ID ASSIGN arithmetic
    {
        $$ = std::make_unique<assignValue>($1, std::move($3));
    }
;

comparison:
    arithmetic EQ arithmetic
    {
        $$ = std::make_unique<compareValues>(
            std::move($1),
            std::move($3)
        );
    }
;

print:
    PRINT LX arithmetic RX
    {
        $$ = std::make_unique<printValue>(std::move($3));
    }
;

arithmetic:
    INTEGER
    {
        $$ = std::make_unique<integerValue>($1);
    }
    |
    ID
    {
        $$ = std::make_unique<variableValue>($1);
    }
    |
    arithmetic PLUS arithmetic
    {
        $$ = std::make_unique<addValues>(
            std::move($1),
            std::move($3)
        );
    }
    |
    arithmetic MINUS arithmetic
    {
        $$ = std::make_unique<subtractValues>(
            std::move($1),
            std::move($3)
        );
    }
    |
    arithmetic MULTIPLY arithmetic
    {
        $$ = std::make_unique<multiplyValues>(
            std::move($1),
            std::move($3)
        );
    }
    |
    arithmetic DIVIDE arithmetic
    {
        $$ = std::make_unique<divideValues>(
            std::move($1),
            std::move($3)
        );
    }
    |
    LX arithmetic RX
    {
        $$ = std::move($2);
    }
;

%%
