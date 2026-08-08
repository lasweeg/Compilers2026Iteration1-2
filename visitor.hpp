#pragma once

struct makeProgram;
struct emptyStatements;
struct concatenateStatements;

struct expressionStatement;
struct intdeclareStatement;
struct assignmentStatement;
struct printStatement;

struct ifElseExpression;
struct declareInteger;

struct assignInteger;
struct assignIdentifier;

struct compareIdentifierWithIdentifier;
struct compareIdentifierWithInteger;
struct compareIntegerWithIdentifier;

struct printIdentifier;
struct printInteger;


struct Visitor {
    virtual ~Visitor() = default;

    virtual void visit(makeProgram* node) = 0;
    virtual void visit(emptyStatements* node) = 0;
    virtual void visit(concatenateStatements* node) = 0;

    virtual void visit(expressionStatement* node) = 0;
    virtual void visit(intdeclareStatement* node) = 0;
    virtual void visit(assignmentStatement* node) = 0;
    virtual void visit(printStatement* node) = 0;

    virtual void visit(ifElseExpression* node) = 0;
    virtual void visit(declareInteger* node) = 0;

    virtual void visit(assignInteger* node) = 0;
    virtual void visit(assignIdentifier* node) = 0;

    virtual void visit(compareIdentifierWithIdentifier* node) = 0;
    virtual void visit(compareIdentifierWithInteger* node) = 0;
    virtual void visit(compareIntegerWithIdentifier* node) = 0;

    virtual void visit(printIdentifier* node) = 0;
    virtual void visit(printInteger* node) = 0;
};