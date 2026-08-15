#pragma once

class program;
class statements;

class expressionStatement;
class intdeclareStatement;
class assignmentStatement;
class printStatement;

class ifElseExpression;
class declareInteger;
class assignValue;
class compareValues;
class printValue;

class integerValue;
class variableValue;
class addValues;
class subtractValues;
class multiplyValues;
class divideValues;


class Visitor {
public:
    virtual ~Visitor() = default;

    virtual void visit(program* node) = 0;
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
