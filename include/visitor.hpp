#pragma once

struct makeProgram;
struct statements;

struct expressionStatement;
struct intdeclareStatement;
struct assignmentStatement;
struct printStatement;

struct ifElseExpression;
struct declareInteger;
struct assignValue;
struct compareValues;
struct printValue;

struct integerValue;
struct variableValue;
struct addValues;
struct subtractValues;
struct multiplyValues;
struct divideValues;


struct Visitor {
    virtual ~Visitor() = default;

    virtual void visit(makeProgram* node) = 0;
    virtual void visit(statements* node) = 0;

    virtual void visit(expressionStatement* node) = 0;
    virtual void visit(intdeclareStatement* node) = 0;
    virtual void visit(assignmentStatement* node) = 0;
    virtual void visit(printStatement* node) = 0;

    virtual void visit(ifElseExpression* node) = 0;
    virtual void visit(declareInteger* node) = 0;
    virtual void visit(assignValue* node) = 0;
    virtual void visit(compareValues* node) = 0;
    virtual void visit(printValue* node) = 0;

    virtual void visit(integerValue* node) = 0;
    virtual void visit(variableValue* node) = 0;
    virtual void visit(addValues* node) = 0;
    virtual void visit(subtractValues* node) = 0;
    virtual void visit(multiplyValues* node) = 0;
    virtual void visit(divideValues* node) = 0;
};
