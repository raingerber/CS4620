/* File: ast_decl.cc
 * -----------------
 * Implementation of Decl node classes.
 */
#include "ast_decl.h"
#include "ast_type.h"
#include "ast_stmt.h"
        
         
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

/******************************************************************************************************************/

void VarDecl::Check(int scopeLevel, ScopeTracker *tracker) { 
    //printf("VarDecl Check\n");
    type->Check(tracker);
    tracker->CheckForDeclConflict(scopeLevel, id->name, this);
}


void ClassDecl::SetUp(int scopeLevel, ScopeTracker *tracker) {
    tracker->extendsTable->Enter(id->name, new Hashtable<Decl*>, true);
    for (int i=0; i<members->NumElements(); i++) {
        tracker->extendsTable->Lookup(id->name)->Enter(members->Nth(i)->id->name, members->Nth(i), true);
    }
}
/*void VarDecl::SetUp(int scopeLevel, ScopeTracker *tracker) {
}
void FnDecl::SetUp(int scopeLevel, ScopeTracker *tracker) {
}*/
void InterfaceDecl::SetUp(int scopeLevel, ScopeTracker *tracker) {
    tracker->interfaceTable->Enter(id->name, new Hashtable<Decl*>, true);
    for (int i=0; i<members->NumElements(); i++) {
        tracker->interfaceTable->Lookup(id->name)->Enter(members->Nth(i)->id->name, members->Nth(i), true);
    }
}

void FnDecl::Check(int scopeLevel, ScopeTracker *tracker) { 
    //printf("FnDecl Check\n");
    tracker->CheckForDeclConflict(scopeLevel, id->name, this);
    if (formals->NumElements()==0) {    // also in ClassDecl, helps prevent NULL entries in the hashtable
        tracker->UpdateScope(scopeLevel+1);
    } else {
        formals->CheckAll(scopeLevel+1, tracker);
    }
    if (body) body->Check(scopeLevel+2, tracker);
    tracker->UpdateScope(scopeLevel);
}

void VarDecl::Check(int scopeLevel, ScopeTracker *tracker, char *parentName) { 
    //printf("VarDecl Check\n");
    type->Check(tracker);
    tracker->CheckForDeclConflict(scopeLevel, this->id->name, this, parentName);
}

void FnDecl::Check(int scopeLevel, ScopeTracker *tracker, char *parentName) { 
    //printf("FnDecl Check With Parent Name\n");
    returnType->Check(tracker);
    tracker->CheckForDeclConflict(scopeLevel, id->name, this);
    if (formals->NumElements()==0) {
        tracker->UpdateScope(scopeLevel+1);
    } else {
        formals->CheckAll(scopeLevel+1, tracker, parentName);
    }
    if (body) body->Check(scopeLevel+2, tracker);
    tracker->UpdateScope(scopeLevel);
}

void ClassDecl::Check(int scopeLevel, ScopeTracker *tracker) {  // everything is collapsing, trying to make it somehow work last minute with terrible nested for loops
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
        members->CheckAll(scopeLevel+1, tracker, extends->id->name);
    } else {
        members->CheckAll(scopeLevel+1, tracker);
    }
    tracker->UpdateScope(scopeLevel);

/*    tracker->extendsTable->Enter(id->name, new Hashtable<Decl*>, true);
    for (int i=0; i<members->NumElements(); i++) {
        tracker->extendsTable->Lookup(id->name)->Enter(members->Nth(i)->id->name, members->Nth(i), true);
    }*/

}

void InterfaceDecl::Check(int scopeLevel, ScopeTracker *tracker) { 
    //printf("InterfaceDecl Check\n");
    tracker->CheckForDeclConflict(scopeLevel, id->name, this);
    members->CheckAll(scopeLevel+1, tracker);
    tracker->UpdateScope(scopeLevel);
}