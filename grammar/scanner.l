%option noyywrap

%{
#include <stdexcept>
#include <string>
#include "parser.hpp"
#define YY_DECL yy::parser::symbol_type yylex()
%}

%%

"if"        { return yy::parser::make_IF(); }
"else"      { return yy::parser::make_ELSE(); }
"main"      { return yy::parser::make_MAIN(); }
"int"       { return yy::parser::make_INT(); }
"print"     { return yy::parser::make_PRINT(); }
"declare"   { return yy::parser::make_DECLARE(); }

"=="        { return yy::parser::make_EQ(); }
"="         { return yy::parser::make_ASSIGN(); }
"+"         { return yy::parser::make_PLUS(); }
"-"         { return yy::parser::make_MINUS(); }
"*"         { return yy::parser::make_MULTIPLY(); }
"/"         { return yy::parser::make_DIVIDE(); }

"("         { return yy::parser::make_LX(); }
")"         { return yy::parser::make_RX(); }
"{"         { return yy::parser::make_LBRACE(); }
"}"         { return yy::parser::make_RBRACE(); }

[a-zA-Z_][a-zA-Z0-9_]* {
    return yy::parser::make_ID(
        std::string(yytext, yyleng)
    );
}

[0-9]+ {
    return yy::parser::make_INTEGER(
        std::stoi(std::string(yytext, yyleng))
    );
}

[ \t\r\n]+  { }

<<EOF>>     { return yy::parser::make_YYEOF(); }

. {
    throw std::runtime_error(
        "Unknown character: " + std::string(yytext, yyleng)
    );
}

%%
