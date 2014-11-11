/* File: ast_decl.cc
 * -----------------
 * Implementation of Decl node classes.
 */
#include "ast_decl.h"
#include "ast_type.h"
#include "ast_stmt.h"
#include "scope.h"
#include "errors.h"

#include "ast_expr.h" // matt

bool ClassDecl::isChildOf(Decl *d) {
    Decl *d1;
    if (extends) {
        if (extends->GetId()->isEqual(d->GetId())) {
            return true;
        } else {
            d1 = extends->GetDeclForType();
            if (d1 && isChildOf(d1)) {
                return true;
            }
        }
    }
    for (int i=0; i<implements->NumElements(); i++) {
        if (d->GetId()->isEqual(implements->Nth(i)->GetId())) {
            return true;
        } else {
            d1 = implements->Nth(i)->GetDeclForType();
            if (d1 && isChildOf(d1)) {
                return true;
            } 
        }
    }
    return false;
}

bool InterfaceDecl::isChildOf(Decl *d) {
    return false;
}

void FnDecl::CompareReturnTypes(ReturnStmt *rStmt, Type *testType) {
    if (!testType->IsEquivalentTo(returnType)) {
        ReportError::ReturnMismatch(rStmt, testType, returnType);
    }
}

VarDecl* ClassDecl::getClassVar(Identifier *memberId) { // matt
    return dynamic_cast<VarDecl*>(nodeScope->Lookup(memberId));
}

FnDecl* ClassDecl::getClassFn(Identifier *memberId) { // matt
    FnDecl *fnDecl = dynamic_cast<FnDecl*>(nodeScope->Lookup(memberId));
    if (!fnDecl && extends) {
        Decl *typeDecl = extends->GetDeclForType();
        return typeDecl->getClassFn(memberId);
    }
    return dynamic_cast<FnDecl*>(nodeScope->Lookup(memberId));
}

FnDecl* InterfaceDecl::getClassFn(Identifier *memberId) { // matt
    return dynamic_cast<FnDecl*>(nodeScope->Lookup(memberId));
}

Decl::Decl(Identifier *n) : Node(*n->GetLocation()) {
    Assert(n != NULL);
    (id=n)->SetParent(this);
}

bool Decl::ConflictsWithPrevious(Decl *prev) {
    ReportError::DeclConflict(this, prev);
    return true;
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
    cType = new NamedType(n);
    cType->SetParent(this);
    convImp = NULL;
}

void VarDecl::Check() {
    type->Check();
    //id->Check();
}

void ClassDecl::Check() {
    PrepareScope();
    members->CheckAll();
    if (extends && !dynamic_cast<ClassDecl*>(extends->GetDeclForType())) {
        ReportError::IdentifierNotDeclared(extends->GetId(), LookingForClass);
    }
    for (int i = 0; i < implements->NumElements(); i++) {
        NamedType *in = implements->Nth(i);
        if (!in->IsInterface()) {
            ReportError::IdentifierNotDeclared(in->GetId(), LookingForInterface);
            implements->RemoveAt(i--);
        }
    }
    if (convImp) {
        for (int i=0; i<convImp->NumElements(); i++) {
            if (!convImp->Nth(i)->compareAgainstChild(this)) {
                ReportError::InterfaceNotImplemented(this, new NamedType(implements->Nth(i)->GetId()));
            }
        }
    }
}

// ensure the class implements the full interfaces (returns false if it's not implemented)
bool InterfaceDecl::compareAgainstChild(ClassDecl* childDecl) {
    int x = 0;
    FnDecl *interfaceFn, *classFn, *d = NULL;
    Hashtable<int*> *memLeaker = new Hashtable<int*>();
    for (int i=0; i<members->NumElements(); i++) {
        interfaceFn = dynamic_cast<FnDecl*>(members->Nth(i));
        if (!interfaceFn) continue; 
        for (int j=0; j<childDecl->members->NumElements(); j++) {
            d = dynamic_cast<FnDecl*>(childDecl->members->Nth(j));
            if (d && members->Nth(i)->GetId()->isEqual(d->GetId())) {
                if (interfaceFn->MatchesPrototype(d)) {
                    memLeaker->Enter(interfaceFn->GetId()->GetName(), new int(1), true);
                }
            }
        }
    }
    return members->NumElements() == memLeaker->NumEntries();
}

void InterfaceDecl::Check() {
    PrepareScope();
    members->CheckAll();
}

void FnDecl::Check() {
    returnType->Check();
    if (body) {
        nodeScope = new Scope();
        formals->DeclareAll(nodeScope);
        formals->CheckAll();
        body->Check();
    }
}

// This is not done very cleanly. I should sit down and sort this out. Right now
// I was using the copy-in strategy from the old compiler, but I think the link to
// parent may be the better way now.
Scope *ClassDecl::PrepareScope()
{
    if (nodeScope) {
        return nodeScope;
    }
    nodeScope = new Scope();  
    if (extends) {
        ClassDecl *ext = dynamic_cast<ClassDecl*>(parent->FindDecl(extends->GetId())); 
        if (ext) {
            //printf("EXTENDS CLASS\n");
            nodeScope->CopyFromScope(ext->PrepareScope(), this);
        }
    }
    convImp = new List<InterfaceDecl*>;
    for (int i = 0; i < implements->NumElements(); i++) {
        NamedType *in = implements->Nth(i);
        InterfaceDecl *id = dynamic_cast<InterfaceDecl*>(in->FindDecl(in->GetId()));
        if (id) {
            nodeScope->CopyFromScope(id->PrepareScope(), NULL);
            convImp->Append(id);
	  }
    }
    members->DeclareAll(nodeScope);
    return nodeScope;
}

InterfaceDecl::InterfaceDecl(Identifier *n, List<Decl*> *m) : Decl(n) {
    Assert(n != NULL && m != NULL);
    (members=m)->SetParentAll(this);
}
  
Scope *InterfaceDecl::PrepareScope() {
    if (nodeScope) return nodeScope;
    nodeScope = new Scope();  
    members->DeclareAll(nodeScope);
    return nodeScope;
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

bool FnDecl::ConflictsWithPrevious(Decl *prev) {
 // special case error for method override
    if (IsMethodDecl() && prev->IsMethodDecl() && parent != prev->GetParent()) { 
        if (!MatchesPrototype(dynamic_cast<FnDecl*>(prev))) {
            ReportError::OverrideMismatch(this);
            return true;
        }
        return false;
    }
    ReportError::DeclConflict(this, prev);
    return true;
}

bool FnDecl::IsMethodDecl() 
  { return dynamic_cast<ClassDecl*>(parent) != NULL || dynamic_cast<InterfaceDecl*>(parent) != NULL; }

bool FnDecl::MatchesPrototype(FnDecl *other) {
    if (!returnType->IsEquivalentTo(other->returnType)) return false;
    if (formals->NumElements() != other->formals->NumElements())
        return false;
    for (int i = 0; i < formals->NumElements(); i++)
        if (!formals->Nth(i)->GetDeclaredType()->IsEquivalentTo(other->formals->Nth(i)->GetDeclaredType()))
            return false;
    return true;
}

void FnDecl::CheckActualsAgainstFormals(Identifier *field, List<Expr*> *actuals) {
    Type *t1, *t2;
    if (formals->NumElements() != actuals->NumElements()) {
        ReportError::NumArgsMismatch(field, formals->NumElements(), actuals->NumElements());
        return;
    }
    for (int i = 0; i < actuals->NumElements(); i++) {
        t1 = actuals->Nth(i)->getType();
        t2 = formals->Nth(i)->GetDeclaredType();
        if (t1 && t2 && !t1->isNullType() && !t1->IsEquivalentTo(t2)) {
            ReportError::ArgMismatch(actuals->Nth(i), i+1, t1, t2);
        }
    }
}

