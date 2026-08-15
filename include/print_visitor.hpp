#pragma once

#include <fstream>
#include <memory>
#include <stdexcept>
#include <string>

#include "ast.hpp"


struct PrintVisitor : Visitor {
    std::ofstream output;
    int depth;

    PrintVisitor(const std::string& fileName) :
        output(fileName),
        depth(0)
    {
        if (!output) {
            throw std::runtime_error("Cannot open AST output file: " + fileName);
        }
    }


    void printIndent() {
        for (int i = 0; i < depth; i++) {
            output << "  ";
        }
    }


    void visit(program* node) {
        printIndent();
        output << "program\n";

        depth++;
        node->programStatements.accept(this);
        depth--;
    }


    void visit(statements* node) {
        printIndent();
        output << "statements\n";

        depth++;

        for (const std::unique_ptr<statement>& currentStatement : node->values) {
            currentStatement->accept(this);
        }

        depth--;
    }


    void visit(expressionStatement* node) {
        printIndent();
        output << "expressionStatement\n";

        depth++;
        node->value->accept(this);
        depth--;
    }


    void visit(intdeclareStatement* node) {
        printIndent();
        output << "intdeclareStatement\n";

        depth++;
        node->value->accept(this);
        depth--;
    }


    void visit(assignmentStatement* node) {
        printIndent();
        output << "assignmentStatement\n";

        depth++;
        node->value->accept(this);
        depth--;
    }


    void visit(printStatement* node) {
        printIndent();
        output << "printStatement\n";

        depth++;
        node->value->accept(this);
        depth--;
    }


    void visit(ifElseExpression* node) {
        printIndent();
        output << "ifElseExpression\n";

        depth++;

        printIndent();
        output << "condition\n";

        depth++;
        node->condition->accept(this);
        depth--;

        printIndent();
        output << "trueStatements\n";

        depth++;
        node->trueStatements.accept(this);
        depth--;

        printIndent();
        output << "falseStatements\n";

        depth++;
        node->falseStatements.accept(this);
        depth--;

        depth--;
    }


    void visit(declareInteger* node) {
        printIndent();
        output << "declareInteger: " << node->variableName << "\n";
    }


    void visit(assignValue* node) {
        printIndent();
        output << "assignValue: " << node->variableName << "\n";

        depth++;
        node->value->accept(this);
        depth--;
    }


    void visit(compareValues* node) {
        printIndent();
        output << "compareValues\n";

        depth++;
        node->leftValue->accept(this);
        node->rightValue->accept(this);
        depth--;
    }


    void visit(printValue* node) {
        printIndent();
        output << "printValue\n";

        depth++;
        node->value->accept(this);
        depth--;
    }


    void visit(integerValue* node) {
        printIndent();
        output << "integerValue: " << node->value << "\n";
    }


    void visit(variableValue* node) {
        printIndent();
        output << "variableValue: " << node->variableName << "\n";
    }


    void visit(addValues* node) {
        printIndent();
        output << "addValues\n";

        depth++;
        node->leftValue->accept(this);
        node->rightValue->accept(this);
        depth--;
    }


    void visit(subtractValues* node) {
        printIndent();
        output << "subtractValues\n";

        depth++;
        node->leftValue->accept(this);
        node->rightValue->accept(this);
        depth--;
    }


    void visit(multiplyValues* node) {
        printIndent();
        output << "multiplyValues\n";

        depth++;
        node->leftValue->accept(this);
        node->rightValue->accept(this);
        depth--;
    }


    void visit(divideValues* node) {
        printIndent();
        output << "divideValues\n";

        depth++;
        node->leftValue->accept(this);
        node->rightValue->accept(this);
        depth--;
    }
};
