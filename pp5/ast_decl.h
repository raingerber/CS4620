/* File: ast_decl.h
 * ----------------
 * In our parse tree, Decl nodes are used to represent and
 * manage declarations. There are 4 subclasses of the base class,
 * specialized for declarations of variables, functions, classes,
 * and interfaces.
 *
 * pp5: You will need to extend the Decl classes to implement 
 * code generation for declarations.
 */

#ifndef _H_ast_decl
#define _H_ast_decl

#include "ast.h"
#include "list.h"

#include "ast_type.h" // pp5
#include "hashtable.h"
#include "string.h"

//class Type;
//class NamedType;
class Identifier;
class Stmt;

class CodeGenerator; // pp5

class Decl : public Node 
{
  protected:
    Identifier *id;
    Location *locc = NULL;
  
  public:
    Decl(Identifier *name);
    char *getName() { return id->getName(); }
    friend std::ostream& operator<<(std::ostream& out, Decl *d) { return out << d->id; }

    virtual bool isInt() { return false; }
    virtual bool isBool() { return false; }
    virtual bool isString() { return false; }
    virtual bool isArray() { return false; }

    //Location* getLocation() { return location; }

};

class VarDecl : public Decl 
{
  protected:
    Type *type;
    
  public:
    VarDecl(Identifier *name, Type *type);
    Location* Emit(CodeGenerator *generator, int *count);
    Location* Emit(CodeGenerator *generator, int *count, int value);

    bool isInt() { return type->isInt(); }
    bool isBool() { return type->isBool(); }
    bool isString() { return type->isString(); }
    bool isArray() { return type->isArray(); }

    char* getTypeName() { return type->getName(); }

};

class ClassDecl : public Decl 
{
  protected:
    
    NamedType *extends;
    List<NamedType*> *implements;
    List<ClassDecl*> *parentClasses;
    List<VarDecl*> *variables;
    bool variableListReady;
    bool methodLabelsFound;

  public:
    List<Decl*> *members;
    List<const char*> *methodNames; // used for vtable
    List<VarDecl*> *varList; // used for instance variables
    List<const char*> *methodLabels;
    ClassDecl(Identifier *name, NamedType *extends, 
      List<NamedType*> *implements, List<Decl*> *members);
    Location* Emit(CodeGenerator *generator, int *count);
    void appendLabelNames(ClassDecl *classDecl,
                          List<const char*> *classNames,
                          List<const char*> *methodNames);
    Decl* getDeclFromClass(CodeGenerator *generator, char *name);
    void FindMethodLabels(CodeGenerator *generator);
    int getVarOffset(CodeGenerator *generator, char *name);

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
    int findParameterOffset(char *name);
    
    VarDecl* findFormal(char *name);
    VarDecl* findVarDecl(char *name);
    Location* Emit(CodeGenerator *generator, int *count);

    bool isInt() { return returnType->isInt(); }
    bool isBool() { return returnType->isBool(); }
    bool isString() { return returnType->isString(); }
    bool isArray() { return returnType->isArray(); }

    bool hasReturn() { 
        if (strcmp("void", returnType->getName()) == 0) {
          //printf("return type %s\n", returnType->getName());
          return false;
        }
        //printf("true return type %s\n", returnType->getName());
        return true;
      }

};

class InterfaceDecl : public Decl 
{
  protected:
    List<Decl*> *members;
    
  public:
    InterfaceDecl(Identifier *name, List<Decl*> *members);
    Location* Emit(CodeGenerator *generator, int *count);
};

#endif
