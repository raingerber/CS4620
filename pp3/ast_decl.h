/* File: ast_decl.h
 * ----------------
 * In our parse tree, Decl nodes are used to represent and
 * manage declarations. There are 4 subclasses of the base class,
 * specialized for declarations of variables, functions, classes,
 * and interfaces.
 *
 * pp3: You will need to extend the Decl classes to implement 
 * semantic processing including detection of declaration conflicts 
 * and managing scoping issues.
 */

#ifndef _H_ast_decl
#define _H_ast_decl

#include "ast.h"
//#include "list.h"

class Type;
class NamedType;
class Identifier;
class Stmt;

class Decl : public Node 
{
  protected:
    
  
  public:
    Identifier *id;
    Decl(Identifier *name);
    friend std::ostream& operator<<(std::ostream& out, Decl *d) { return out << d->id; }

    virtual void Check(int scopeLevel, ScopeTracker *tracker) {}
    virtual void Check(int scopeLevel, ScopeTracker *tracker, char *parentName) {}

    virtual void SetUp(int scopeLevel, ScopeTracker *tracker) { }

};

class VarDecl : public Decl 
{
  protected:
    Type *type;
    
  public:
    VarDecl(Identifier *name, Type *type);
    void Check(int scopeLevel, ScopeTracker *tracker);
    void Check(int scopeLevel, ScopeTracker *tracker, char *parentName);

/*    void SetUp(int scopeLevel, ScopeTracker *tracker);
*/};

class ClassDecl : public Decl 
{
  protected:
    List<Decl*> *members;
    NamedType *extends;
    List<NamedType*> *implements;

  public:
    ClassDecl(Identifier *name, NamedType *extends, List<NamedType*> *implements, List<Decl*> *members);
    void Check(int scopeLevel, ScopeTracker *tracker);

    void SetUp(int scopeLevel, ScopeTracker *tracker);
};

class InterfaceDecl : public Decl 
{
  protected:
    List<Decl*> *members;
    
  public:
    InterfaceDecl(Identifier *name, List<Decl*> *members);
    void Check(int scopeLevel, ScopeTracker *tracker);

    void SetUp(int scopeLevel, ScopeTracker *tracker);
};

class FnDecl : public Decl 
{
  protected:
    List<VarDecl*> *formals;
    Type *returnType;
    Stmt *body;
    
  public:
    FnDecl(Identifier *name, Type *returnType, List<VarDecl*> *formals);
    void SetFunctionBody(Stmt *b);
    void Check(int scopeLevel, ScopeTracker *tracker);
    void Check(int scopeLevel, ScopeTracker *tracker, char *parentName);

/*    void SetUp(int scopeLevel, ScopeTracker *tracker);
*/};

#endif
