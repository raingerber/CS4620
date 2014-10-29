/* File: ast_expr.cc
 * -----------------
 * Implementation of expression node classes.
 */
#include "ast_expr.h"
#include "ast_type.h"
#include "ast_decl.h"
#include <string.h>



IntConstant::IntConstant(yyltype loc, int val) : Expr(loc) {
    value = val;
    localTable = NULL;
}
 
DoubleConstant::DoubleConstant(yyltype loc, double val) : Expr(loc) {
    value = val; 
    localTable = NULL;
}

BoolConstant::BoolConstant(yyltype loc, bool val) : Expr(loc) {
    value = val;
    localTable = NULL;
}
 
StringConstant::StringConstant(yyltype loc, const char *val) : Expr(loc) {
    Assert(val != NULL);
    value = strdup(val);
    localTable = NULL;
}

Operator::Operator(yyltype loc, const char *tok) : Node(loc) {
    Assert(tok != NULL);
    strncpy(tokenString, tok, sizeof(tokenString));
    localTable = NULL;
}

CompoundExpr::CompoundExpr(Expr *l, Operator *o, Expr *r) 
  : Expr(Join(l->GetLocation(), r->GetLocation())) {
    Assert(l != NULL && o != NULL && r != NULL);
    (op=o)->SetParent(this);
    (left=l)->SetParent(this); 
    (right=r)->SetParent(this);
    localTable = NULL;
}

CompoundExpr::CompoundExpr(Operator *o, Expr *r) 
  : Expr(Join(o->GetLocation(), r->GetLocation())) {
    Assert(o != NULL && r != NULL);
    left = NULL; 
    (op=o)->SetParent(this);
    (right=r)->SetParent(this);
    localTable = NULL;
}

ArrayAccess::ArrayAccess(yyltype loc, Expr *b, Expr *s) : LValue(loc) {
    (base=b)->SetParent(this); 
    (subscript=s)->SetParent(this);
    localTable = NULL;
}
 
FieldAccess::FieldAccess(Expr *b, Identifier *f) 
  : LValue(b? Join(b->GetLocation(), f->GetLocation()) : *f->GetLocation()) {
    Assert(f != NULL); // b can be be NULL (just means no explicit base)
    base = b; 
    if (base) base->SetParent(this);  
    (field=f)->SetParent(this);
    localTable = NULL;
}

Call::Call(yyltype loc, Expr *b, Identifier *f, List<Expr*> *a) : Expr(loc)  {
    Assert(f != NULL && a != NULL); // b can be be NULL (just means no explicit base)
    base = b;
    if (base) base->SetParent(this);
    (field=f)->SetParent(this);
    (actuals=a)->SetParentAll(this);
    localTable = NULL;
}

NewExpr::NewExpr(yyltype loc, NamedType *c) : Expr(loc) { 
    Assert(c != NULL);
    (cType=c)->SetParent(this);
    localTable = NULL;
}

NewArrayExpr::NewArrayExpr(yyltype loc, Expr *sz, Type *et) : Expr(loc) {
    Assert(sz != NULL && et != NULL);
    (size=sz)->SetParent(this); 
    (elemType=et)->SetParent(this);
    localTable = NULL;
}

/********************************************************************************************************/

void IntConstant::Check() {
    //printf("IntConstant\n");
}

void DoubleConstant::Check() {
    //printf("DoubleConstant\n");
}

void BoolConstant::Check() {
    //printf("BoolConstant\n");
}

void StringConstant::Check() {
    //printf("StringConstant\n");
}

void Operator::Check() {
    //printf("Operator\n");
}

void CompoundExpr::Check() {
    //printf("CompoundExpr Check\n");
    if (left) left->Check();
    op->Check();
    if (right) right->Check();
}

void ArrayAccess::Check() {
    //printf("ArrayAccess Check\n");
    base->Check();
    subscript->Check();
}

void FieldAccess::Check() {
    //printf("FieldAccess Check\n");
    if (base) base->Check();
    //field->Check();
    Decl *dec, *p;

    if (base == NULL) { // find 

    } else { // find the identifier
/*        p = this;
        while ((p = p->GetParent()) != NULL) {
            if (p->localTable != NULL) {
                Iterator<Decl*> iterator = p->localTable->GetIterator();
                while ((dec = iterator.GetNextValue()) != NULL) {
                    if (strcmp(dec->getName(), this->id->name) == 0) {
                        printf("YAHOO YAHOO YAHOO : %s\n", this->id->name);
                    }
                }
            }
        }*/
    }
}
    //printf("Named Check 1-- %s\n",this->id->name);
/*    Decl *dec;
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
    }*/

void Call::Check() {
    //printf("Call Check\n");
    if (base) base->Check();
    field->Check();
    actuals->CheckAll();
}

void NewExpr::Check() {
    //printf("NewExpr Check\n");
    cType->Check();
}

void NewArrayExpr::Check() {
    //printf("NewArrayExpr Check\n");
    size->Check();
    elemType->Check();
}

       
