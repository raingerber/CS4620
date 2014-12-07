/* File: ast_expr.h
 * ----------------
 * The Expr class and its subclasses are used to represent
 * expressions in the parse tree.  For each expression in the
 * language (add, call, New, etc.) there is a corresponding
 * node class for that construct. 
 *
 * pp5: You will need to extend the Expr classes to implement 
 * code generation for expressions.
 */


#ifndef _H_ast_expr
#define _H_ast_expr

#include "ast.h"
#include "ast_stmt.h"
#include "list.h"

#include "ast_type.h"
#include "codegen.h" // pp5 builtin

class NamedType; // for new
class Type; // for NewArray

class CodeGenerator;
class FnDecl;

class Expr : public Stmt 
{
  public:
    Expr(yyltype loc) : Stmt(loc) {}
    Expr() : Stmt() {}
    
    virtual bool isInt(CodeGenerator *generator) { return false; }
    virtual bool isBool(CodeGenerator *generator) { return false; }
    virtual bool isString(CodeGenerator *generator) { return false; }

    virtual int getNum() { return 0; }
    bool isArray();

    virtual ClassDecl* findParentClassDecl(CodeGenerator *generator) { return NULL; }
    virtual bool IsThis() { return false; }
    //bool isArray() { return true; }

};

/* This node type is used for those places where an expression is optional.
 * We could use a NULL pointer, but then it adds a lot of checking for
 * NULL. By using a valid, but no-op, node, we save that trouble */
class EmptyExpr : public Expr
{
  public:
};

class IntConstant : public Expr 
{
  protected:
    int value;
  
  public:
    IntConstant(yyltype loc, int val);
    bool isInt(CodeGenerator *generator) { return true; }
    Location* Emit(CodeGenerator *generator, int *count);

    int getNum() { return value; }
};

class DoubleConstant : public Expr 
{
  protected:
    double value;
    
  public:
    DoubleConstant(yyltype loc, double val);
};

class BoolConstant : public Expr 
{
  protected:
    bool value;
    
  public:
    BoolConstant(yyltype loc, bool val);
    bool isBool(CodeGenerator *generator) { return true; }
    Location* Emit(CodeGenerator *generator, int *count);
};

class StringConstant : public Expr 
{ 
  protected:
    char *value;
    
  public:
    StringConstant(yyltype loc, const char *val);
    bool isString(CodeGenerator *generator) { return true; }
    Location* Emit(CodeGenerator *generator, int *count);
};

class NullConstant: public Expr 
{
  public: 
    NullConstant(yyltype loc) : Expr(loc) {}
    Location* Emit(CodeGenerator *generator, int *count);
};

class Operator : public Node 
{
  protected:
    char tokenString[4];
    
  public:
    Operator(yyltype loc, const char *tok);
    char* getTokenString() { return tokenString; }
    friend std::ostream& operator<<(std::ostream& out, Operator *o) { return out << o->tokenString; }
 };
 
class CompoundExpr : public Expr
{
  protected:
    Operator *op;
    Expr *left, *right; // left will be NULL if unary
    
  public:
    CompoundExpr(Expr *lhs, Operator *op, Expr *rhs); // for binary
    CompoundExpr(Operator *op, Expr *rhs);             // for unary
    Location* Emit(CodeGenerator *generator, int *count);
};


class ArithmeticExpr : public CompoundExpr 
{
  public:
    ArithmeticExpr(Expr *lhs, Operator *op, Expr *rhs) : CompoundExpr(lhs,op,rhs) {}
    ArithmeticExpr(Operator *op, Expr *rhs) : CompoundExpr(op,rhs) {}
    bool isInt(CodeGenerator *generator) { return true; }
};

class RelationalExpr : public CompoundExpr 
{
  public:
    RelationalExpr(Expr *lhs, Operator *op, Expr *rhs) : CompoundExpr(lhs,op,rhs) {}
    bool isBool(CodeGenerator *generator) { return true; }
};

class EqualityExpr : public CompoundExpr 
{
  public:
    EqualityExpr(Expr *lhs, Operator *op, Expr *rhs) : CompoundExpr(lhs,op,rhs) {}
    const char *GetPrintNameForNode() { return "EqualityExpr"; }
    Location* Emit(CodeGenerator *generator, int *count); // needed for dereferencing strings
    bool isBool(CodeGenerator *generator) { return true; }
    Location* CheckStringEquality(CodeGenerator *generator, int *count);
};

class LogicalExpr : public CompoundExpr 
{
  public:
    LogicalExpr(Expr *lhs, Operator *op, Expr *rhs) : CompoundExpr(lhs,op,rhs) {}
    LogicalExpr(Operator *op, Expr *rhs) : CompoundExpr(op,rhs) {}
    const char *GetPrintNameForNode() { return "LogicalExpr"; }
    bool isBool(CodeGenerator *generator) { return true; }
};

class AssignExpr : public CompoundExpr 
{
  public:
    AssignExpr(Expr *lhs, Operator *op, Expr *rhs) : CompoundExpr(lhs,op,rhs) {}
    const char *GetPrintNameForNode() { return "AssignExpr"; }
    Location* Emit(CodeGenerator *generator, int *count);
};

class LValue : public Expr 
{
  public:
    LValue(yyltype loc) : Expr(loc) {}
};

class This : public Expr 
{
  public:
    This(yyltype loc) : Expr(loc) {}
    Location* Emit(CodeGenerator *generator, int *count);
    bool IsThis() { return true; }
};

/* Note that field access is used both for qualified names
 * base.field and just field without qualification. We don't
 * know for sure whether there is an implicit "this." in
 * front until later on, so we use one node type for either
 * and sort it out later. */
class FieldAccess : public LValue 
{
  protected:
    Expr *base;	// will be NULL if no explicit base
    Identifier *field;
    bool _local, _param, _global, _classvar;
    Decl *declaration = NULL;

  public:

    int offset;

    FieldAccess(Expr *base, Identifier *field); //ok to pass NULL base
    Location* Emit(CodeGenerator *generator, int *count);
    Location* EmitHelper(CodeGenerator *generator, int *count);
    //bool storeDecl(CodeGenerator *generator); 
    bool isInt(CodeGenerator *generator);
    bool isBool(CodeGenerator *generator);
    bool isString(CodeGenerator *generator);

    char* getName() { return field->getName(); }

    Decl* getFieldDeclaration(CodeGenerator *generator);

    ClassDecl* findParentClassDecl(CodeGenerator *generator);

    void setIsClassVar() { _classvar = true; _local = false; _param = false; _global = false; }
    bool isClassVar() { return _classvar; }
    void setIsLocal() { _classvar = false; _local = true; _param = false; _global = false; }
    bool isLocal() { return _local; }
    void setIsParam() { _classvar = false; _local = false; _param = true; _global = false; }
    bool isParam() { return _param; }
    void setIsGlobal()  { _classvar = false; _local = false; _param = false; _global = true; }
    bool isGlobal() { return _global; }

};

class ArrayAccess : public LValue 
{
  protected:
    Expr *base, *subscript;
    Decl *declaration = NULL;
    
  public:
    ArrayAccess(yyltype loc, Expr *base, Expr *subscript);
    Location* Emit(CodeGenerator *generator, int *count);
    Location* EmitButReturnReference(CodeGenerator *generator, int *count);

    bool isInt(CodeGenerator *generator) { 
      return base->isInt(generator); 
    }
    bool isBool(CodeGenerator *generator) { 
      return base->isBool(generator); 
    }
    bool isString(CodeGenerator *generator) { 
      getFieldDeclaration(generator);
      if (declaration) return declaration->isString();
      return false;
      //return base->isString(generator); 
    }

    bool isStringArray(CodeGenerator *generator) {
      return true;
    }

    ClassDecl* findParentClassDecl(CodeGenerator *generator);

    // MAKE THIS BETTER IF IT ACTUALLY WORKS TO HELP CHECK STRING EQUALITY
    Decl* getFieldDeclaration(CodeGenerator *generator) {
      if (declaration) return declaration;
      FieldAccess *fieldAccess = dynamic_cast<FieldAccess*>(base);
      if (fieldAccess) {
        declaration = fieldAccess->getFieldDeclaration(generator);
      }
      return declaration;  
    }
    
    //bool isArray() { return true; }

};

/* Like field access, call is used both for qualified base.field()
 * and unqualified field().  We won't figure out until later
 * whether we need implicit "this." so we use one node type for either
 * and sort it out later. */
class Call : public Expr 
{
  protected:
    Expr *base;	// will be NULL if no explicit base
    Identifier *field;
    List<Expr*> *actuals;
    FnDecl *parentFn = NULL;
    FnDecl *theFnDecl = NULL;
    
  public:
    Call(yyltype loc, Expr *base, Identifier *field, List<Expr*> *args);
    Location* Emit(CodeGenerator *generator, int *count);

    bool isArrayLengthCall();

    ClassDecl* findParentClassDecl(CodeGenerator *generator);

    bool isInt(CodeGenerator *generator);
    bool isBool(CodeGenerator *generator);
    bool isString(CodeGenerator *generator);

    FnDecl* getFnDcel(CodeGenerator *generator);

};

class NewExpr : public Expr
{
  protected:
    NamedType *cType;

    NamedType *currentType;
    ClassDecl *parentClass;
    
  public:
    NewExpr(yyltype loc, NamedType *clsType);
    Location* Emit(CodeGenerator *generator, int *count);

    NamedType* getCurrentNamedType() { return currentType; }
    void setCurrentNamedType(NamedType *nt) { currentType = nt; }

};

class NewArrayExpr : public Expr
{
  protected:
    Expr *size;
    Type *elemType;
    
  public:
    NewArrayExpr(yyltype loc, Expr *sizeExpr, Type *elemType);
    Location* Emit(CodeGenerator *generator, int *count);

    bool isInt(CodeGenerator *generator) { return elemType->isInt(); }
    bool isBool(CodeGenerator *generator) { return elemType->isBool(); }
    bool isString(CodeGenerator *generator) { return elemType->isString(); }

};

class ReadIntegerExpr : public Expr
{
  public:
    ReadIntegerExpr(yyltype loc) : Expr(loc) {}
    Location* Emit(CodeGenerator *generator, int *count);
    bool isInt(CodeGenerator *generator) { return true; }
};

class ReadLineExpr : public Expr
{
  public:
    ReadLineExpr(yyltype loc) : Expr (loc) {}
    Location* Emit(CodeGenerator *generator, int *count);
    bool isString(CodeGenerator *generator) { return true; }
};

    
#endif
