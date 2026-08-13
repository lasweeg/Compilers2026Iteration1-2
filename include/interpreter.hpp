#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>

#include "ast.hpp"


struct Interpreter : Visitor {
    std::map<std::string, int> variables;
    bool comparisonResult;
    int arithmeticResult;
    int conditionalDepth;

    Interpreter() :
        comparisonResult(false),
        arithmeticResult(0),
        conditionalDepth(0)
    {}


    int getVariable(const std::string& name) {
        if (variables.count(name) == 0) {
            throw std::runtime_error("Variable is not declared: " + name);
        }

        return variables[name];
    }


    void setVariable(const std::string& name, int value) {
        if (variables.count(name) == 0) {
            throw std::runtime_error("Variable is not declared: " + name);
        }

        variables[name] = value;
    }


    void visit(makeProgram* node) {
        node->programStatements->accept(this);
    }


    void visit(statements* node) {
        for (const std::unique_ptr<statement>& currentStatement : node->values) {
            currentStatement->accept(this);
        }
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

        conditionalDepth++;

        if (comparisonResult) {
            node->trueStatements->accept(this);
        } else {
            node->falseStatements->accept(this);
        }

        conditionalDepth--;
    }


    void visit(declareInteger* node) {
        if (conditionalDepth != 0) {
            throw std::runtime_error("Variables cannot be declared inside if/else: " + node->variableName);
        }

        if (variables.count(node->variableName) != 0) {
            throw std::runtime_error("Variable is already declared: " + node->variableName);
        }

        variables[node->variableName] = 0;
    }


    void visit(assignValue* node) {
        node->value->accept(this);

        setVariable(node->variableName, arithmeticResult);
    }


    void visit(compareValues* node) {
        node->leftValue->accept(this);
        int leftValue = arithmeticResult;

        node->rightValue->accept(this);
        int rightValue = arithmeticResult;

        comparisonResult = false;

        if (leftValue == rightValue) {
            comparisonResult = true;
        }
    }


    void visit(printValue* node) {
        node->value->accept(this);

        std::cout << arithmeticResult << '\n';
    }


    void visit(integerValue* node) {
        arithmeticResult = node->value;
    }


    void visit(variableValue* node) {
        arithmeticResult = getVariable(node->variableName);
    }


    void visit(addValues* node) {
        node->leftValue->accept(this);
        int leftValue = arithmeticResult;

        node->rightValue->accept(this);
        int rightValue = arithmeticResult;

        arithmeticResult = leftValue + rightValue;
    }


    void visit(subtractValues* node) {
        node->leftValue->accept(this);
        int leftValue = arithmeticResult;

        node->rightValue->accept(this);
        int rightValue = arithmeticResult;

        arithmeticResult = leftValue - rightValue;
    }


    void visit(multiplyValues* node) {
        node->leftValue->accept(this);
        int leftValue = arithmeticResult;

        node->rightValue->accept(this);
        int rightValue = arithmeticResult;

        arithmeticResult = leftValue * rightValue;
    }


    void visit(divideValues* node) {
        node->leftValue->accept(this);
        int leftValue = arithmeticResult;

        node->rightValue->accept(this);
        int rightValue = arithmeticResult;

        if (rightValue == 0) {
            throw std::runtime_error("Division by zero");
        }

        arithmeticResult = leftValue / rightValue;
    }
};
