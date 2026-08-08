#include <iostream>
#include "parser.hpp"
#include "print_visitor.hpp"
#include "interpreter.hpp"

program* root = nullptr;

void yy::parser::error(const std::string& message)
{
    std::cerr << "Syntax error: " << message << '\n';
}

int main()
{
    yy::parser parser;
    int result = parser.parse();

    if (result == 0) {
        std::cout << "AST successfully created\n";

        PrintVisitor printVisitor("ast.txt");
        root->accept(&printVisitor);

        try {
            Interpreter interpreter;
            root->accept(&interpreter);
        }
        catch (const std::runtime_error& error) {
            std::cerr << "Interpreter error: " << error.what() << '\n';

            delete root;
            return 1;
        }
    }

    delete root;
    return result;
}
