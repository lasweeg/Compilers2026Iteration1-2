#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "visitor.hpp"


class statement {
public:
    virtual ~statement() {}
    virtual void accept(Visitor* visitor) = 0;
};

class expression {
public:
    virtual ~expression() {}
    virtual void accept(Visitor* visitor) = 0;
};

class intdeclare {
public:
    virtual ~intdeclare() {}
    virtual void accept(Visitor* visitor) = 0;
};

class assignment {
public:
    virtual ~assignment() {}
    virtual void accept(Visitor* visitor) = 0;
};

class comparison {
public:
    virtual ~comparison() {}
    virtual void accept(Visitor* visitor) = 0;
};

class print {
public:
    virtual ~print() {}
    virtual void accept(Visitor* visitor) = 0;
};

class arithmeticExpression {
public:
    virtual ~arithmeticExpression() {}
    virtual void accept(Visitor* visitor) = 0;
};


class statements {
public:
    std::vector<std::unique_ptr<statement>> values;

    void add(std::unique_ptr<statement> value) {
        values.push_back(std::move(value));
    }

    void accept(Visitor* visitor) {
        visitor->visit(this);
    }
};


class program {
public:
    statements programStatements;

    void accept(Visitor* visitor) {
        visitor->visit(this);
    }
};


class expressionStatement : public statement {
public:
    std::unique_ptr<expression> value;

    expressionStatement(std::unique_ptr<expression> newValue) :
        value(std::move(newValue))
    {}

    void accept(Visitor* visitor) {
        visitor->visit(this);
    }
};


class intdeclareStatement : public statement {
public:
    std::unique_ptr<intdeclare> value;

    intdeclareStatement(std::unique_ptr<intdeclare> newValue) :
        value(std::move(newValue))
    {}

    void accept(Visitor* visitor) {
        visitor->visit(this);
    }
};


class assignmentStatement : public statement {
public:
    std::unique_ptr<assignment> value;

    assignmentStatement(std::unique_ptr<assignment> newValue) :
        value(std::move(newValue))
    {}

    void accept(Visitor* visitor) {
        visitor->visit(this);
    }
};


class printStatement : public statement {
public:
    std::unique_ptr<print> value;

    printStatement(std::unique_ptr<print> newValue) :
        value(std::move(newValue))
    {}

    void accept(Visitor* visitor) {
        visitor->visit(this);
    }
};


class ifElseExpression : public expression {
public:
    std::unique_ptr<comparison> condition;
    statements trueStatements;
    statements falseStatements;

    ifElseExpression(
        std::unique_ptr<comparison> newCondition,
        statements newTrueStatements,
        statements newFalseStatements
    ) :
        condition(std::move(newCondition)),
        trueStatements(std::move(newTrueStatements)),
        falseStatements(std::move(newFalseStatements))
    {}

    void accept(Visitor* visitor) {
        visitor->visit(this);
    }
};


class declareInteger : public intdeclare {
public:
    std::string variableName;

    declareInteger(std::string newVariableName) :
        variableName(newVariableName)
    {}

    void accept(Visitor* visitor) {
        visitor->visit(this);
    }
};


class assignValue : public assignment {
public:
    std::string variableName;
    std::unique_ptr<arithmeticExpression> value;

    assignValue(
        std::string newVariableName,
        std::unique_ptr<arithmeticExpression> newValue
    ) :
        variableName(newVariableName),
        value(std::move(newValue))
    {}

    void accept(Visitor* visitor) {
        visitor->visit(this);
    }
};


class compareValues : public comparison {
public:
    std::unique_ptr<arithmeticExpression> leftValue;
    std::unique_ptr<arithmeticExpression> rightValue;

    compareValues(
        std::unique_ptr<arithmeticExpression> newLeftValue,
        std::unique_ptr<arithmeticExpression> newRightValue
    ) :
        leftValue(std::move(newLeftValue)),
        rightValue(std::move(newRightValue))
    {}

    void accept(Visitor* visitor) {
        visitor->visit(this);
    }
};


class printValue : public print {
public:
    std::unique_ptr<arithmeticExpression> value;

    printValue(std::unique_ptr<arithmeticExpression> newValue) :
        value(std::move(newValue))
    {}

    void accept(Visitor* visitor) {
        visitor->visit(this);
    }
};


class integerValue : public arithmeticExpression {
public:
    int value;

    integerValue(int newValue) :
        value(newValue)
    {}

    void accept(Visitor* visitor) {
        visitor->visit(this);
    }
};


class variableValue : public arithmeticExpression {
public:
    std::string variableName;

    variableValue(std::string newVariableName) :
        variableName(newVariableName)
    {}

    void accept(Visitor* visitor) {
        visitor->visit(this);
    }
};


class addValues : public arithmeticExpression {
public:
    std::unique_ptr<arithmeticExpression> leftValue;
    std::unique_ptr<arithmeticExpression> rightValue;

    addValues(
        std::unique_ptr<arithmeticExpression> newLeftValue,
        std::unique_ptr<arithmeticExpression> newRightValue
    ) :
        leftValue(std::move(newLeftValue)),
        rightValue(std::move(newRightValue))
    {}

    void accept(Visitor* visitor) {
        visitor->visit(this);
    }
};


class subtractValues : public arithmeticExpression {
public:
    std::unique_ptr<arithmeticExpression> leftValue;
    std::unique_ptr<arithmeticExpression> rightValue;

    subtractValues(
        std::unique_ptr<arithmeticExpression> newLeftValue,
        std::unique_ptr<arithmeticExpression> newRightValue
    ) :
        leftValue(std::move(newLeftValue)),
        rightValue(std::move(newRightValue))
    {}

    void accept(Visitor* visitor) {
        visitor->visit(this);
    }
};


class multiplyValues : public arithmeticExpression {
public:
    std::unique_ptr<arithmeticExpression> leftValue;
    std::unique_ptr<arithmeticExpression> rightValue;

    multiplyValues(
        std::unique_ptr<arithmeticExpression> newLeftValue,
        std::unique_ptr<arithmeticExpression> newRightValue
    ) :
        leftValue(std::move(newLeftValue)),
        rightValue(std::move(newRightValue))
    {}

    void accept(Visitor* visitor) {
        visitor->visit(this);
    }
};


class divideValues : public arithmeticExpression {
public:
    std::unique_ptr<arithmeticExpression> leftValue;
    std::unique_ptr<arithmeticExpression> rightValue;

    divideValues(
        std::unique_ptr<arithmeticExpression> newLeftValue,
        std::unique_ptr<arithmeticExpression> newRightValue
    ) :
        leftValue(std::move(newLeftValue)),
        rightValue(std::move(newRightValue))
    {}

    void accept(Visitor* visitor) {
        visitor->visit(this);
    }
};
