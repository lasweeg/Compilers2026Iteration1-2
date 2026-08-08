#pragma once

#include <fstream>
#include <string>

#include "ast.hpp"


struct PrintVisitor : Visitor {
    std::ofstream output;
    int depth;

    PrintVisitor(std::string fileName)
        : output(fileName),
          depth(0)
    {
    }

    void printIndent() {
        for (int i = 0; i < depth; i++) {
            output << "  ";
        }
    }


    void visit(makeProgram* node) {
        printIndent();
        output << "makeProgram\n";

        depth++;
        node->programStatements->accept(this);
        depth--;
    }


    void visit(emptyStatements* node) {
        printIndent();
        output << "emptyStatements\n";
    }


    void visit(concatenateStatements* node) {
        printIndent();
        output << "concatenateStatements\n";

        depth++;

        node->previousStatements->accept(this);
        node->currentStatement->accept(this);

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
        node->trueStatements->accept(this);
        depth--;

        printIndent();
        output << "falseStatements\n";

        depth++;
        node->falseStatements->accept(this);
        depth--;

        depth--;
    }


    void visit(declareInteger* node) {
        printIndent();
        output << "declareInteger: " << node->variableName << "\n";
    }


    void visit(assignInteger* node) {
        printIndent();
        output << "assignInteger: " << node->variableName << " = " << node->value << "\n";
    }


    void visit(assignIdentifier* node) {
        printIndent();
        output << "assignIdentifier: " << node->leftVariableName << " = " << node->rightVariableName << "\n";
    }


    void visit(compareIdentifierWithIdentifier* node) {
        printIndent();
        output << "compareIdentifierWithIdentifier: " << node->leftVariableName << " == " << node->rightVariableName << "\n";
    }


    void visit(compareIdentifierWithInteger* node) {
        printIndent();
        output << "compareIdentifierWithInteger: " << node->leftVariableName << " == " << node->rightValue << "\n";
    }


    void visit(compareIntegerWithIdentifier* node) {
        printIndent();
        output << "compareIntegerWithIdentifier: " << node->leftValue << " == " << node->rightVariableName << "\n";
    }


    void visit(printIdentifier* node) {
        printIndent();
        output << "printIdentifier: " << node->variableName << "\n";
    }


    void visit(printInteger* node) {
        printIndent();
        output << "printInteger: " << node->value << "\n";
    }
};
