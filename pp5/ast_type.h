/* File: ast_type.h
 * ----------------
 * In our parse tree, Type nodes are used to represent and
 * store type information. The base Type class is used
 * for built-in types, the NamedType for classes and interfaces,
 * and the ArrayType for arrays of other types.  
 *
 * pp5: You will need to extend the Type classes to implement
 * code generation for types.
 */
 
#ifndef _H_ast_type
#define _H_ast_type

#include "ast.h"
#include "list.h"
#include <iostream>

#include <string.h>

class Type : public Node 
{
  protected:
    char *typeName;

  public:
    static Type *intType, *doubleType, *boolType, *voidType,
                *nullType, *stringType, *errorType;

    Type(yyltype loc) : Node(loc) {}
    Type(const char *str);
    
    virtual void PrintToStream(std::ostream& out) { out << typeName; }
    friend std::ostream& operator<<(std::ostream& out, Type *t) { t->PrintToStream(out); return out; }
    virtual bool IsEquivalentTo(Type *other) { return this == other; }

    virtual bool isInt() { return typeName ? !strcmp(typeName, "int") : false; }
    virtual bool isBool() { return typeName ? !strcmp(typeName, "bool") : false; }
    virtual bool isString() { return typeName ? !strcmp(typeName, "string") : false; }
    virtual bool isArray() { return false; }

    virtual char* getName() { //printf("%s\n",typeName);
    return typeName; }

};

class NamedType : public Type 
{
  protected:
    Identifier *id;
    
  public:
    NamedType(Identifier *i);

    void PrintToStream(std::ostream& out) { out << id; }

    char* getName() { //printf("%s\n",id->getName());
    return id->getName(); }

};

class ArrayType : public Type 
{
  protected:
    Type *elemType;

  public:
    ArrayType(yyltype loc, Type *elemType);
    
    void PrintToStream(std::ostream& out) { out << elemType << "[]"; }

    bool isInt() { 
      //if (elemType->isInt()) printf("it's another int\n");
      return elemType->isInt(); }
    bool isBool() { return elemType->isBool(); }
    bool isString() { return elemType->isString(); }
    bool isArray() { return true; }

    char* getName() { //printf("%s\n",elemType->getName());
    return elemType->getName(); }

};

 
#endif
