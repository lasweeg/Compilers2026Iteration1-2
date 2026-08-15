#include <iostream>
#include <stdexcept>
#include <string>

#include "interpreter.hpp"
#include "parser.hpp"
#include "print_visitor.hpp"


void yy::parser::error(const std::string& message)
{
    std::cerr << "Syntax error: " << message << '\n';
}


int main()
{
    program root;
    int result = 0;

    try {
        yy::parser parser(root);
        result = parser.parse();
    }
    catch (const std::runtime_error& error) {
        std::cerr << "Lexer error: " << error.what() << '\n';
        return 1;
    }

    if (result != 0) {
        return result;
    }

    std::cout << "AST successfully created\n";

    try {
        PrintVisitor printVisitor("build/ast.txt");
        root.accept(&printVisitor);

        Interpreter interpreter;
        root.accept(&interpreter);
    }
    catch (const std::runtime_error& error) {
        std::cerr << "Interpreter error: " << error.what() << '\n';
        return 1;
    }

    return 0;
}
