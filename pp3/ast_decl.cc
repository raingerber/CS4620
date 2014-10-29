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
    Decl *d = parentClass->localTable->Lookup(childDecl->id->name);
    if (d == NULL) {
        return;
    } else {
        ReportError::DeclConflict(childDecl, d);
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

void VarDecl::Check() {
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
    CheckForDeclConflict(this);
    if (formals) {
        int j;
        for (int i=0; i < formals->NumElements(); i++) {
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
    body->CreateTables();
    //printf("2\n");
}

/*******************************************************************************************************************************************************/

void ClassDecl::Check() {
    CheckForDeclConflict(this);
    //List<Decl*> *extendsList = new List<Decl*>;
    if (extends) {
        extends->Check(LookingForClass);                                        // could return false here if not found
        ClassDecl* parentClass = FindParentClass(this, extends->id->name);
        if (parentClass != NULL) {
            for (int i=0; i < members->NumElements(); i++) {                    // could add another function to list.h
                members->Nth(i)->Check();
                CheckInParentClass(members->Nth(i), parentClass);
            }
        } else {
            members->CheckAll();
        }
    }
    for (int i=0; i < implements->NumElements(); i++) {

        //implements->Nth(i)->Check(LookingForInterface);

    }
    members->CheckAll();
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
        //members->Nth(i)->CreateTables();
    }
}

/*******************************************************************************************************************************************************/






/*
void VarDecl::Check(int scopeLevel, ScopeTracker *tracker, char *parentName) { 
    //printf("VarDecl Check\n");
    type->Check(scopeLevel, tracker);
    tracker->CheckForDeclConflict(scopeLevel, this->id->name, this, parentName);
}

void FnDecl::Check(int scopeLevel, ScopeTracker *tracker, char *parentName) { 
    //printf("FnDecl Check With Parent Name\n");
    returnType->Check(scopeLevel, tracker);
    tracker->CheckForDeclConflict(scopeLevel, id->name, this);
    if (formals->NumElements()==0) {
        tracker->UpdateScope(scopeLevel+1);
    } else {
        formals->CheckAll(scopeLevel+1, tracker, parentName);
    }
    if (body) body->Check(scopeLevel+2, tracker);
    tracker->UpdateScope(scopeLevel);
}*/





/*void ClassDecl::Check(int scopeLevel, ScopeTracker *tracker) {  // everything is collapsing, trying to make it somehow work last minute with terrible nested for loops
    //printf("ClassDecl Check\n");
    
    tracker->CheckForDeclConflict(scopeLevel, id->name, this);
    if (extends) {
        if (tracker->extendsTable->Lookup(this->id->name)==NULL) {
            ReportError::IdentifierNotDeclared(this->id, LookingForClass);
        }
        //extends->CheckExtends(scopeLevel, tracker);
    }

    //implements->CheckAll(scopeLevel, tracker);
    for (int i=0; i<implements->NumElements(); i++) {
        Hashtable<Decl*> *table = tracker->interfaceTable->Lookup(implements->Nth(i)->id->name);
        if (table == NULL) {
            i = 2000;
        } else {
            for (int j=0; j<members->NumElements(); j++) {
                Decl *d = table->Lookup(members->Nth(j)->id->name);
                if (d == NULL) {
                    //ReportError::OverrideMismatch(this);
                    ReportError::InterfaceNotImplemented(this, new Type(implements->Nth(i)->id->name)); 
                    j = 2000;
                }
            }
        }
    }

    if (extends) {
        //members->CheckAll(scopeLevel+1, tracker, extends->id->name);
    } else {
        members->CheckAll(scopeLevel+1, tracker);
    }
    tracker->UpdateScope(scopeLevel);

}*/
