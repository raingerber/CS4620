/* File: ast_type.cc
 * -----------------
 * Implementation of type node classes.
 */
#include "ast_type.h"
#include "ast_decl.h"
#include <string.h> 

 
/* Class constants
 * ---------------
 * These are public constants for the built-in base types (int, double, etc.)
 * They can be accessed with the syntax Type::intType. This allows you to
 * directly access them and share the built-in types where needed rather that
 * creates lots of copies.
 */
 
Type *Type::intType    = new Type("int");
Type *Type::doubleType = new Type("double");
Type *Type::voidType   = new Type("void");
Type *Type::boolType   = new Type("bool");
Type *Type::nullType   = new Type("null");
Type *Type::stringType = new Type("string");
Type *Type::errorType  = new Type("error"); 

Type::Type(const char *n) {
    Assert(n);
    typeName = strdup(n);
    //printf("%s\n",typeName);
}

NamedType::NamedType(Identifier *i) : Type(*i->GetLocation()) {
    Assert(i != NULL);
    (id=i)->SetParent(this);
} 

ArrayType::ArrayType(yyltype loc, Type *et) : Type(loc) {
    Assert(et != NULL);
    (elemType=et)->SetParent(this); 
}

/********************************************************************************************************/

void Type::Check(ScopeTracker *tracker) {
/*    printf("Type Check\n");
    if (this->typeName==NULL) {
        ReportError::IdentifierNotDeclared(dynamic_cast<Identifier*>(this), LookingForType);
        return;
    }
    if ( !( (strcmp(this->typeName, "string")==0) || (strcmp(this->typeName, "double")==0)  || (strcmp(this->typeName, "bool")==0) || (strcmp(this->typeName, "int")==0))) {
        printf("puppy\n");
    }*/
}

void NamedType::Check(int scopeLevel, ScopeTracker *tracker) {
    //printf("NamedType Check\n");
    id->CheckNamedType(scopeLevel, tracker);
}

void NamedType::CheckExtends(int scopeLevel, ScopeTracker *tracker) {
    //printf("NamedType Check\n");
    id->CheckExtends(scopeLevel, tracker);
}

void ArrayType::Check(int scopeLevel, ScopeTracker *tracker) {
	//printf("ArrayType Check\n");
	elemType->Check(tracker);
}



