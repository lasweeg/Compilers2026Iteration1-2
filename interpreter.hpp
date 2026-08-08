#pragma once

#include <iostream>
#include <map>
#include <stdexcept>
#include <string>

#include "ast.hpp"


struct Interpreter : Visitor {
    std::map<std::string, int> variables;
    bool comparisonResult;

    Interpreter()
        : comparisonResult(false)
    {
    }


    int getVariable(std::string name) {
        if (variables.count(name) == 0) {
            throw std::runtime_error("Variable is not declared: " + name);
        }

        return variables[name];
    }


    void setVariable(std::string name, int value) {
        if (variables.count(name) == 0) {
            throw std::runtime_error("Variable is not declared: " + name);
        }

        variables[name] = value;
    }


    void visit(makeProgram* node) {
        node->programStatements->accept(this);
    }


    void visit(emptyStatements* node) {
    }


    void visit(concatenateStatements* node) {
        node->previousStatements->accept(this);

        node->currentStatement->accept(this);
    }


    void visit(expressionStatement* node) {
        node->value->accept(this);
    }


    void visit(intdeclareStatement* node) {
        node->value->accept(this);
    }


    void visit(assignmentStatement* node) {
        node->value->accept(this);
    }


    void visit(printStatement* node) {
        node->value->accept(this);
    }


    void visit(ifElseExpression* node) {
        node->condition->accept(this);

        if (comparisonResult) {
            node->trueStatements->accept(this);
        } else {
            node->falseStatements->accept(this);
        }
    }


    void visit(declareInteger* node) {
        if (variables.count(node->variableName) != 0) {
            throw std::runtime_error("Variable is already declared: " + node->variableName);
        }

        variables[node->variableName] = 0;
    }


    void visit(assignInteger* node) {
        setVariable(node->variableName, node->value);
    }


    void visit(assignIdentifier* node) {
        int value = getVariable(node-> rightVariableName);

        setVariable(node->leftVariableName, value);
    }


    void visit(compareIdentifierWithIdentifier* node) {
        int leftValue = getVariable(node->leftVariableName);

        int rightValue = getVariable(node->rightVariableName);

        comparisonResult = false;

        if (leftValue == rightValue) {
            comparisonResult = true;
        }
    }


    void visit(compareIdentifierWithInteger* node) {
        int leftValue = getVariable(node->leftVariableName);

        comparisonResult = false;

        if (leftValue == node->rightValue) {
            comparisonResult = true;
        }
    }


    void visit(compareIntegerWithIdentifier* node) {
        int rightValue = getVariable(node->rightVariableName);

        comparisonResult = false;

        if (node->leftValue == rightValue) {
            comparisonResult = true;
        }
    }


    void visit(printIdentifier* node) {
        std::cout << getVariable(node->variableName) << '\n';
    }


    void visit(printInteger* node) {
        std::cout << node->value << '\n';
    }
};
