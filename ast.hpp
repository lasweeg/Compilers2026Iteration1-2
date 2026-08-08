#pragma once
#include <string>
#include "visitor.hpp"

struct program {
    virtual ~program() = default;
    virtual void accept(Visitor* visitor) = 0;
};

struct statements {
    virtual ~statements() = default;
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

struct makeProgram : program {
    statements* programStatements;
    makeProgram(statements* allStatements) :
        programStatements(allStatements) 
    {}

    ~makeProgram() {
        delete programStatements;
    }
    
    void accept(Visitor* visitor) {
        visitor->visit(this);
    }
};

struct emptyStatements : statements {
    
    void accept(Visitor* visitor) {
        visitor->visit(this);
    }
};

struct concatenateStatements : statements {
    statements* previousStatements;
    statement* currentStatement;
    concatenateStatements (statements* prevStatements, statement* curStatement): 
        previousStatements(prevStatements), 
        currentStatement(curStatement) 
    {}

    ~concatenateStatements () {
        delete previousStatements;
        delete currentStatement;
    }

    void accept(Visitor* visitor) {
        visitor->visit(this);
    }
};

struct expressionStatement : statement {
    expression* value;

    expressionStatement(expression* newValue) :
        value(newValue)
    {}

    ~expressionStatement() {
        delete value;
    }
    void accept(Visitor* visitor) {
        visitor->visit(this);
    }
};


struct intdeclareStatement : statement {
    intdeclare* value;

    intdeclareStatement(intdeclare* newValue) :
        value(newValue)
    {}

    ~intdeclareStatement() {
        delete value;
    }
    
    void accept(Visitor* visitor) {
        visitor->visit(this);
    }
};


struct assignmentStatement : statement {
    assignment* value;

    assignmentStatement(assignment* newValue) : 
        value(newValue)
    {}

    ~assignmentStatement() {
        delete value;
    }

    void accept(Visitor* visitor) {
        visitor->visit(this);
    }
};


struct printStatement : statement {
    print* value;

    printStatement(print* newValue) :
        value(newValue)
    {}

    ~printStatement() {
        delete value;
    }

    void accept(Visitor* visitor) {
        visitor->visit(this);
    }
};


struct ifElseExpression : expression {
    comparison* condition;
    statements* trueStatements;
    statements* falseStatements;

    ifElseExpression(comparison* newCondition, statements* newTrueStatements, statements* newFalseStatements) :
        condition(newCondition),
        trueStatements(newTrueStatements), 
        falseStatements(newFalseStatements)
    {}

    ~ifElseExpression() {
        delete condition;
        delete trueStatements;
        delete falseStatements;
    }

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

struct assignInteger : assignment {
    std::string variableName;
    int value;

    assignInteger(std::string newVariableName, int newValue) :
        variableName(newVariableName),
        value(newValue)
    {}

    void accept(Visitor* visitor) {
        visitor->visit(this);
    }
};


struct assignIdentifier : assignment {
    std::string leftVariableName;
    std::string rightVariableName;

    assignIdentifier(std::string newLeftVariableName, std::string newRightVariableName) :
        leftVariableName(newLeftVariableName),
        rightVariableName(newRightVariableName)
    {}

    void accept(Visitor* visitor) {
        visitor->visit(this);
    }
};


struct compareIdentifierWithIdentifier : comparison {
    std::string leftVariableName;
    std::string rightVariableName;

    compareIdentifierWithIdentifier(std::string newLeftVariableName, std::string newRightVariableName) :
        leftVariableName(newLeftVariableName),
        rightVariableName(newRightVariableName)
    {}

    void accept(Visitor* visitor) {
        visitor->visit(this);
    }
};


struct compareIdentifierWithInteger : comparison {
    std::string leftVariableName;
    int rightValue;

    compareIdentifierWithInteger(std::string newLeftVariableName, int newRightValue) :
        leftVariableName(newLeftVariableName),
        rightValue(newRightValue)
    {}

    void accept(Visitor* visitor) {
        visitor->visit(this);
    }
};


struct compareIntegerWithIdentifier : comparison {
    int leftValue;
    std::string rightVariableName;

    compareIntegerWithIdentifier(int newLeftValue, std::string newRightVariableName): 
        leftValue(newLeftValue),
        rightVariableName(newRightVariableName)
    {}

    void accept(Visitor* visitor) {
        visitor->visit(this);
    }
};

struct printIdentifier : print {
    std::string variableName;

    printIdentifier(std::string newVariableName) :
        variableName(newVariableName)
    {}

    void accept(Visitor* visitor) {
        visitor->visit(this);
    }
};


struct printInteger : print {
    int value;

    printInteger(int newValue) :
        value(newValue)
    {}

    void accept(Visitor* visitor) {
        visitor->visit(this);
    }
};