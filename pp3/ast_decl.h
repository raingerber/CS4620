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

class Type;
class NamedType;
class Identifier;
class Stmt;
class InterfaceDecl;

class Decl : public Node 
{
  protected:
    
  public:
    Identifier *id;
    Decl(Identifier *name);
    friend std::ostream& operator<<(std::ostream& out, Decl *d) { return out << d->id; }

    char* getName() {
      return id->name;
    }

    virtual void Check() {printf("default gal\n");}
    //virtual void Check() {printf("default decl table\n");}
};

class VarDecl : public Decl 
{
  protected:

    
  public:
    Type *type;
    VarDecl(Identifier *name, Type *type);

    void Check();
    void CreateTables();

};

class ClassDecl : public Decl 
{
  protected:
    List<Decl*> *members;
    NamedType *extends;
    List<NamedType*> *implements;

  public:
    ClassDecl(Identifier *name, NamedType *extends, List<NamedType*> *implements, List<Decl*> *members);

    void Check();
    void CheckInterfaceDecls(InterfaceDecl* interfaceClass);
    void CreateTables();

};

class InterfaceDecl : public Decl 
{
  protected:
    List<Decl*> *members;
    
  public:
    InterfaceDecl(Identifier *name, List<Decl*> *members);
    void CheckInterfaceDecls(ClassDecl *classDecl);
    void Check();
    void CreateTables();

};

class FnDecl : public Decl 
{
  protected:
    
    Type *returnType;
    Stmt *body;
    
  public:
    List<VarDecl*> *formals;
    FnDecl(Identifier *name, Type *returnType, List<VarDecl*> *formals);
    void SetFunctionBody(Stmt *b);
    bool CheckFunctionSignatures(FnDecl* otherClass);

    void Check();
    void CreateTables();

};

#endif


