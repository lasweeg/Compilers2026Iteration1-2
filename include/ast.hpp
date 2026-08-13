#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "visitor.hpp"


struct program {
    virtual ~program() = default;
    virtual void accept(Visitor* visitor) = 0;
};

struct statement {
    virtual ~statement() = default;
    virtual void accept(Visitor* visitor) = 0;
};

struct expression {
    virtual ~expression() = default;
    virtual void accept(Visitor* visitor) = 0;
};

struct intdeclare {
    virtual ~intdeclare() = default;
    virtual void accept(Visitor* visitor) = 0;
};

struct assignment {
    virtual ~assignment() = default;
    virtual void accept(Visitor* visitor) = 0;
};

struct comparison {
    virtual ~comparison() = default;
    virtual void accept(Visitor* visitor) = 0;
};

struct print {
    virtual ~print() = default;
    virtual void accept(Visitor* visitor) = 0;
};

struct arithmeticExpression {
    virtual ~arithmeticExpression() = default;
    virtual void accept(Visitor* visitor) = 0;
};


struct statements {
    std::vector<std::unique_ptr<statement>> values;

    void add(std::unique_ptr<statement> value) {
        values.push_back(std::move(value));
    }

    void accept(Visitor* visitor) {
        visitor->visit(this);
    }
};


struct makeProgram : program {
    std::unique_ptr<statements> programStatements;

    makeProgram(std::unique_ptr<statements> allStatements) :
        programStatements(std::move(allStatements))
    {}

    void accept(Visitor* visitor) {
        visitor->visit(this);
    }
};


struct expressionStatement : statement {
    std::unique_ptr<expression> value;

    expressionStatement(std::unique_ptr<expression> newValue) :
        value(std::move(newValue))
    {}

    void accept(Visitor* visitor) {
        visitor->visit(this);
    }
};


struct intdeclareStatement : statement {
    std::unique_ptr<intdeclare> value;

    intdeclareStatement(std::unique_ptr<intdeclare> newValue) :
        value(std::move(newValue))
    {}

    void accept(Visitor* visitor) {
        visitor->visit(this);
    }
};


struct assignmentStatement : statement {
    std::unique_ptr<assignment> value;

    assignmentStatement(std::unique_ptr<assignment> newValue) :
        value(std::move(newValue))
    {}

    void accept(Visitor* visitor) {
        visitor->visit(this);
    }
};


struct printStatement : statement {
    std::unique_ptr<print> value;

    printStatement(std::unique_ptr<print> newValue) :
        value(std::move(newValue))
    {}

    void accept(Visitor* visitor) {
        visitor->visit(this);
    }
};


struct ifElseExpression : expression {
    std::unique_ptr<comparison> condition;
    std::unique_ptr<statements> trueStatements;
    std::unique_ptr<statements> falseStatements;

    ifElseExpression(
        std::unique_ptr<comparison> newCondition,
        std::unique_ptr<statements> newTrueStatements,
        std::unique_ptr<statements> newFalseStatements
    ) :
        condition(std::move(newCondition)),
        trueStatements(std::move(newTrueStatements)),
        falseStatements(std::move(newFalseStatements))
    {}

    void accept(Visitor* visitor) {
        visitor->visit(this);
    }
};


struct declareInteger : intdeclare {
    std::string variableName;

    declareInteger(std::string newVariableName) :
        variableName(newVariableName)
    {}

    void accept(Visitor* visitor) {
        visitor->visit(this);
    }
};


struct assignValue : assignment {
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


struct compareValues : comparison {
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


struct printValue : print {
    std::unique_ptr<arithmeticExpression> value;

    printValue(std::unique_ptr<arithmeticExpression> newValue) :
        value(std::move(newValue))
    {}

    void accept(Visitor* visitor) {
        visitor->visit(this);
    }
};


struct integerValue : arithmeticExpression {
    int value;

    integerValue(int newValue) :
        value(newValue)
    {}

    void accept(Visitor* visitor) {
        visitor->visit(this);
    }
};


struct variableValue : arithmeticExpression {
    std::string variableName;

    variableValue(std::string newVariableName) :
        variableName(newVariableName)
    {}

    void accept(Visitor* visitor) {
        visitor->visit(this);
    }
};


struct addValues : arithmeticExpression {
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


struct subtractValues : arithmeticExpression {
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


struct multiplyValues : arithmeticExpression {
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


struct divideValues : arithmeticExpression {
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
