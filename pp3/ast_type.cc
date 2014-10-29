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
    localTable = NULL;
}

NamedType::NamedType(Identifier *i) : Type(*i->GetLocation()) {
    Assert(i != NULL);
    (id=i)->SetParent(this);
    localTable = NULL;
} 

ArrayType::ArrayType(yyltype loc, Type *et) : Type(loc) {
    Assert(et != NULL);
    (elemType=et)->SetParent(this);
    localTable = NULL;
}

/********************************************************************************************************/

void Type::Check() {
    //printf("Type check %s\n", this->typeName);
}

void NamedType::Check() {  
    //printf("Named Check 1-- %s\n",this->id->name);
    Decl *dec;
    Node *p = this;
    while ((p = p->GetParent()) != NULL) {
        if (p->localTable != NULL) {
            Iterator<Decl*> iterator = p->localTable->GetIterator();
            while ((dec = iterator.GetNextValue()) != NULL) {
                if (strcmp(dec->getName(), this->id->name) == 0 && (dynamic_cast<ClassDecl*>(dec) != NULL || dynamic_cast<InterfaceDecl*>(dec) != NULL)) {
                    return;
                }
            }
        }
    }
    
    ReportError::IdentifierNotDeclared(this->id, LookingForType);
}

void NamedType::Check(reasonT whyNeeded) {
    Decl *dec;
    Node *p = this;
    while ((p = p->GetParent()) != NULL) {
        if (p->localTable != NULL) {
            Iterator<Decl*> iterator = p->localTable->GetIterator();
            while ((dec = iterator.GetNextValue()) != NULL) {
                if (strcmp(dec->getName(), this->id->name) == 0 && dynamic_cast<ClassDecl*>(dec) != NULL) {
                    return;
                }
            }
        }
    }
    //printf("Named Check 2-- %s\n",this->id->name);
    ReportError::IdentifierNotDeclared(this->id, whyNeeded);
}

void ArrayType::Check() {
    //printf("ArrayType check   %s\n", this->elemType->typeName);
    Decl *dec;
    Node *p = this;
    while ((p = p->GetParent()) != NULL) {
        if (p->localTable != NULL) {
            Iterator<Decl*> iterator = p->localTable->GetIterator();
            while ((dec = iterator.GetNextValue()) != NULL) {
                char *var1 = dec->getName();
                char *var2 = this->elemType->typeName;
                if (var1 != NULL && var2 != NULL) {
                    if (strcmp(var1, var2) == 0 && dynamic_cast<ClassDecl*>(dec) != NULL) {
                        return;
                    }
                }
            }
        }
    }
    //new NamedType(this->id)// : Type(*i->GetLocation()) {
    //ReportError::IdentifierNotDeclared(new NamedType(this->id), LookingForType);
}

//Identifier::Identifier(yyltype loc, const char *n) : Node(loc)
//Identifier(yyltype loc, const char *n)
