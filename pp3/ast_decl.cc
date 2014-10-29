/* File: ast_decl.cc
 * -----------------
 * Implementation of Decl node classes.
 */
#include "ast_decl.h"
#include "ast_type.h"
#include "ast_stmt.h"
#include <string.h>

/*
Decl::Decl(Identifier *n) : Node(*n->GetLocation())
VarDecl::VarDecl(Identifier *n, Type *t) : Decl(n)
ClassDecl::ClassDecl(Identifier *n, NamedType *ex, List<NamedType*> *imp, List<Decl*> *m) : Decl(n)
InterfaceDecl::InterfaceDecl(Identifier *n, List<Decl*> *m) : Decl(n)
FnDecl::FnDecl(Identifier *n, Type *r, List<VarDecl*> *d) : Decl(n)
void FnDecl::SetFunctionBody(Stmt *b)
*/
         
Decl::Decl(Identifier *n) : Node(*n->GetLocation()) {
    Assert(n != NULL); 
    (id=n)->SetParent(this); 
}

VarDecl::VarDecl(Identifier *n, Type *t) : Decl(n) {
    Assert(n != NULL && t != NULL);
    (type=t)->SetParent(this);
}

ClassDecl::ClassDecl(Identifier *n, NamedType *ex, List<NamedType*> *imp, List<Decl*> *m) : Decl(n) {
    // extends can be NULL, impl & mem may be empty lists but cannot be NULL
    Assert(n != NULL && imp != NULL && m != NULL);     
    extends = ex;
    if (extends) extends->SetParent(this);
    (implements=imp)->SetParentAll(this);
    (members=m)->SetParentAll(this);
}

InterfaceDecl::InterfaceDecl(Identifier *n, List<Decl*> *m) : Decl(n) {
    Assert(n != NULL && m != NULL);
    (members=m)->SetParentAll(this);
}

FnDecl::FnDecl(Identifier *n, Type *r, List<VarDecl*> *d) : Decl(n) {
    Assert(n != NULL && r!= NULL && d != NULL);
    (returnType=r)->SetParent(this);
    (formals=d)->SetParentAll(this);
    body = NULL;
}

void FnDecl::SetFunctionBody(Stmt *b) { 
    (body=b)->SetParent(this);
}

/*******************************************************************************************************************************************************/
/*******************************************************************************************************************************************************/
/*******************************************************************************************************************************************************/

void CheckInParentClass(Decl* childDecl, ClassDecl* parentClass) {
    //printf("Decl: %s, Class: %s\n", childDecl->id->name, parentClass->id->name);
    FnDecl *var1, *var2;
    Decl *dec = parentClass->localTable->Lookup(childDecl->id->name);
/*    if (dec != NULL && (var1 = dynamic_cast<FnDecl*>(childDecl)) != NULL && (var2 = dynamic_cast<FnDecl*>(dec))) {
        if (var1->formals->NumElements() == var2->formals->NumElements()) {
            for (int i = 0; i<var1->formals->NumElements(); i++) {
                if (strcmp(var1->formals->Nth(i)->type->typeName, var2->formals->Nth(i)->type->typeName) != 0) {
                    ReportError::OverrideMismatch(childDecl);
                }
            }
        }*/
    if (dec != NULL) {
        ReportError::DeclConflict(childDecl, dec);
    }
}

void CheckForDeclConflict(Decl *nodeToCheck) {
    Decl* dec;
    Iterator<Decl*> iterator = nodeToCheck->GetParent()->localTable->GetIterator();
    while ((dec = iterator.GetNextValue()) != NULL) {
        if (dec == nodeToCheck) {
            break;
        }
        if (strcmp(dec->getName(), nodeToCheck->getName()) == 0) {
            ReportError::DeclConflict(nodeToCheck, dec);
            break;
        }
    }
}

ClassDecl* FindParentClass(ClassDecl *childNode, char *extendsName) {
    Iterator<Decl*> iterator = childNode->GetParent()->localTable->GetIterator();
    Decl* dec;
    while ((dec = iterator.GetNextValue()) != NULL) {
        if (strcmp(extendsName, dec->getName()) == 0 && dynamic_cast<ClassDecl*>(dec) != NULL) {
            return dynamic_cast<ClassDecl*>(dec);
        }
    }
    return NULL;
}

InterfaceDecl* FindInterface(Decl *childNode, char *extendsName) {
    Iterator<Decl*> iterator = childNode->GetParent()->localTable->GetIterator();
    Decl* dec;
    while ((dec = iterator.GetNextValue()) != NULL) {
        if (strcmp(extendsName, dec->getName()) == 0 && dynamic_cast<InterfaceDecl*>(dec) != NULL) {
            return dynamic_cast<InterfaceDecl*>(dec);
        }
    }
    return NULL;
}

void VarDecl::Check() {
    //printf("vardecl check\n");
    type->Check();
    CheckForDeclConflict(this);
}

void VarDecl::CreateTables() {
    //printf("var\n");
    //type->CreateTables();
    localTable = NULL;
}

/*******************************************************************************************************************************************************/

void FnDecl::Check() {
    returnType->Check();
    CheckForDeclConflict(this);
    if (formals) {
        int j;
        for (int i=0; i < formals->NumElements(); i++) {
            //printf("fndecl check\n");
            formals->Nth(i)->type->Check();
            for (j = i - 1; j >= 0; j--) {
                if (strcmp(formals->Nth(i)->id->name, formals->Nth(j)->id->name) == 0) {
                    ReportError::DeclConflict(formals->Nth(i), formals->Nth(j)); 
                }
            }
        }
    }
    if (body) {
        body->Check();
    }
}

void FnDecl::CreateTables() {
    localTable = new Hashtable<Decl*>;
    for (int i=0; i < formals->NumElements(); i++) {
        localTable->Enter(formals->Nth(i)->getName(), formals->Nth(i), false);
        formals->Nth(i)->CreateTables();
    }
    //printf("1\n");
    if (body) {
        body->CreateTables();
    }
    //printf("2\n");
}

/*******************************************************************************************************************************************************/

bool FnDecl::CheckFunctionSignatures(FnDecl* otherClass) {
    if (!(strcmp(returnType->typeName, otherClass->returnType->typeName) == 0 && formals->NumElements() == otherClass->formals->NumElements())) {
        ReportError::OverrideMismatch(this);
        return false;
    }
    for (int i = 0; i < formals->NumElements(); i++) {
        if (strcmp(formals->Nth(i)->type->typeName, otherClass->formals->Nth(i)->type->typeName) != 0) {
            ReportError::OverrideMismatch(otherClass);
            return false;
        }
    }
    return true;
}

void ClassDecl::CheckInterfaceDecls(InterfaceDecl* interfaceClass) {
    Decl *dec1, *dec2;
    Iterator<Decl*> iterator = interfaceClass->localTable->GetIterator();
    bool implementsAllOfIt = true;
    while ((dec1 = iterator.GetNextValue()) != NULL) {
        dec2 = this->localTable->Lookup(dec1->id->name);
        if (dec2 != NULL) {
            VarDecl *var1 = dynamic_cast<VarDecl*>(dec1);
            VarDecl *var2 = dynamic_cast<VarDecl*>(dec2);
            if (var1 != NULL && var2 != NULL) {
                if (strcmp(var1->type->typeName, var2->type->typeName) != 0) {
                    ReportError::DeclConflict(var1, var2);
                    implementsAllOfIt = false;
                }
            } else if (dynamic_cast<FnDecl*>(dec1) != NULL && dynamic_cast<FnDecl*>(dec2) != NULL) {
                implementsAllOfIt = implementsAllOfIt && dynamic_cast<FnDecl*>(dec1)->CheckFunctionSignatures(dynamic_cast<FnDecl*>(dec2));
            } else {
                ReportError::DeclConflict(dec2, dec1);
                implementsAllOfIt = false;
            }
        }
        if (!implementsAllOfIt) {
            ReportError::InterfaceNotImplemented(interfaceClass, new NamedType(this->id));
        }
    }
}

void ClassDecl::Check() {
    CheckForDeclConflict(this);
    //List<Decl*> *extendsList = new List<Decl*>;
    if (extends) {
        ClassDecl* parentClass;
        extends->Check(LookingForClass);                                          // could return false here if not found
        parentClass = FindParentClass(this, extends->id->name);
        //printf("Parent Class: %s\n", parentClass->getName());
        if (parentClass != NULL) {
            for (int i = 0; i < members->NumElements(); i++) {                    // could add another function to list.h
                FnDecl *childFn = dynamic_cast<FnDecl*>(members->Nth(i));
                FnDecl *parentFn = dynamic_cast<FnDecl*>(parentClass->localTable->Lookup(members->Nth(i)->getName()));
                if (childFn != NULL && parentFn != NULL) {
                    childFn->CheckFunctionSignatures(parentFn);
                } else {
                    members->Nth(i)->Check();
                    CheckInParentClass(members->Nth(i), parentClass);
                }
            }
        }
    } else {
        members->CheckAll();    
    }
    InterfaceDecl* interfaceClass;
    for (int i=0; i < implements->NumElements(); i++) {
        //printf("loop %i\n",i);
        interfaceClass = FindInterface(this, implements->Nth(i)->id->name);
        if (interfaceClass != NULL) {
            this->CheckInterfaceDecls(interfaceClass);
            //printf("Interface Class %s Exists\n", interfaceClass->id->name);
            //implements->Nth(i)->Check(LookingForInterface);
        } else {
            ReportError::IdentifierNotDeclared(implements->Nth(i)->id, LookingForInterface);
        }
    }
    
}

void ClassDecl::CreateTables() {
    //printf("ClassDecl\n");
    localTable = new Hashtable<Decl*>;
    for (int i=0; i < members->NumElements(); i++) {
        localTable->Enter(members->Nth(i)->getName(), members->Nth(i), false);
        members->Nth(i)->CreateTables();
    }
}

/*******************************************************************************************************************************************************/

void InterfaceDecl::Check() { 
    CheckForDeclConflict(this);
    //members->CheckAll();
}

void InterfaceDecl::CreateTables() {
    localTable = new Hashtable<Decl*>;
    for (int i=0; i < members->NumElements(); i++) {
        localTable->Enter(members->Nth(i)->getName(), members->Nth(i), false);
        CheckForDeclConflict(members->Nth(i));
    }
    for (int i=0; i < members->NumElements(); i++) {
        members->Nth(i)->CreateTables();                                             // PROBLEMATIC BEFORE
    }
}

/*******************************************************************************************************************************************************/
