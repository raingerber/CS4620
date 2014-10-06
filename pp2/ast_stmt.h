/* File: ast_stmt.h
 * ----------------
 * The Stmt class and its subclasses are used to represent
 * statements in the parse tree.  For each statment in the
 * language (for, if, return, etc.) there is a corresponding
 * node class for that construct. 
 *
 * pp2: You will need to add new expression and statement node c
 * classes for the additional grammar elements (Switch/Postfix)
 */


#ifndef _H_ast_stmt
#define _H_ast_stmt

#include "list.h"
#include "ast.h"

class Decl;
class VarDecl;
class Expr;

//////////////////////////////////////////////////////////////////////////
/*
class Node 
{
  protected:
    yyltype *location;
    Node *parent;

  public:
    Node(yyltype loc);
    Node();
    
    yyltype *GetLocation()   { return location; }
    void SetParent(Node *p)  { parent = p; }
    Node *GetParent()        { return parent; }

    virtual const char *GetPrintNameForNode() = 0;
    
    // Print() is deliberately _not_ virtual
    // subclasses should override PrintChildren() instead
    void Print(int indentLevel, const char *label = NULL); 
    virtual void PrintChildren(int indentLevel)  {}
};


class Switch : public Stmt
{
  
};
*/
//////////////////////////////////////////////////////////////////////////

class Program : public Node
{
  protected:
     List<Decl*> *decls;
     
  public:
     Program(List<Decl*> *declList);
     const char *GetPrintNameForNode() { return "Program"; }
     void PrintChildren(int indentLevel);
};

class Stmt : public Node
{
  public:
     Stmt() : Node() {}
     Stmt(yyltype loc) : Node(loc) {}
};

class StmtBlock : public Stmt 
{
  protected:
    List<VarDecl*> *decls;
    List<Stmt*> *stmts;
    
  public:
    StmtBlock(List<VarDecl*> *variableDeclarations, List<Stmt*> *statements);
    const char *GetPrintNameForNode() { return "StmtBlock"; }
    void PrintChildren(int indentLevel);
};

class ConditionalStmt : public Stmt
{
  protected:
    Expr *test;
    Stmt *body;
  
  public:
    ConditionalStmt(Expr *testExpr, Stmt *body);
};

//////////////////////////////////////////////////////////////////////////////////////////// SWITCH STATEMENT

class SwitchStmt : public ConditionalStmt
{
  public:
    SwitchStmt(Expr *test, Stmt *body);
    const char *GetPrintNameForNode() { return "SwitchStmt"; }
    void PrintChildren(int indentLevel);
};

class Case : public ConditionalStmt
{
  public:
    Case(Expr *test, Stmt *body);
    const char *GetPrintNameForNode() { return "Case"; }
    void PrintChildren(int indentLevel);
};

class DefaultStmt : public Stmt
{
  protected:
    List<Stmt*> *stmts;
  public:
    DefaultStmt(List<Stmt*> *statements);
    const char *GetPrintNameForNode() { return "DefaultStmt"; }
    void PrintChildren(int indentLevel);
};

////////////////////////////////////////////////////////////////////////////////////////////

class LoopStmt : public ConditionalStmt 
{
  public:
    LoopStmt(Expr *testExpr, Stmt *body)
            : ConditionalStmt(testExpr, body) {}
};

class ForStmt : public LoopStmt 
{
  protected:
    Expr *init, *step;
  
  public:
    ForStmt(Expr *init, Expr *test, Expr *step, Stmt *body);
    const char *GetPrintNameForNode() { return "ForStmt"; }
    void PrintChildren(int indentLevel);
};

class WhileStmt : public LoopStmt 
{
  public:
    WhileStmt(Expr *test, Stmt *body) : LoopStmt(test, body) {}
    const char *GetPrintNameForNode() { return "WhileStmt"; }
    void PrintChildren(int indentLevel);
};

class IfStmt : public ConditionalStmt 
{
  protected:
    Stmt *elseBody;
  
  public:
    IfStmt(Expr *test, Stmt *thenBody, Stmt *elseBody);
    const char *GetPrintNameForNode() { return "IfStmt"; }
    void PrintChildren(int indentLevel);
};

class BreakStmt : public Stmt 
{
  public:
    BreakStmt(yyltype loc) : Stmt(loc) {}
    const char *GetPrintNameForNode() { return "BreakStmt"; }
};

class ReturnStmt : public Stmt  
{
  protected:
    Expr *expr;
  
  public:
    ReturnStmt(yyltype loc, Expr *expr);
    const char *GetPrintNameForNode() { return "ReturnStmt"; }
    void PrintChildren(int indentLevel);
};

class PrintStmt : public Stmt
{
  protected:
    List<Expr*> *args;
    
  public:
    PrintStmt(List<Expr*> *arguments);
    const char *GetPrintNameForNode() { return "PrintStmt"; }
    void PrintChildren(int indentLevel);
};


#endif
