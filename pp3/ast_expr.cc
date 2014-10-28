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
}

DoubleConstant::DoubleConstant(yyltype loc, double val) : Expr(loc) {
    value = val;
}

BoolConstant::BoolConstant(yyltype loc, bool val) : Expr(loc) {
    value = val;
}
 
StringConstant::StringConstant(yyltype loc, const char *val) : Expr(loc) {
    Assert(val != NULL);
    value = strdup(val);
}

Operator::Operator(yyltype loc, const char *tok) : Node(loc) {
    Assert(tok != NULL);
    strncpy(tokenString, tok, sizeof(tokenString));
}

CompoundExpr::CompoundExpr(Expr *l, Operator *o, Expr *r) 
  : Expr(Join(l->GetLocation(), r->GetLocation())) {
    Assert(l != NULL && o != NULL && r != NULL);
    (op=o)->SetParent(this);
    (left=l)->SetParent(this); 
    (right=r)->SetParent(this);
}

CompoundExpr::CompoundExpr(Operator *o, Expr *r) 
  : Expr(Join(o->GetLocation(), r->GetLocation())) {
    Assert(o != NULL && r != NULL);
    left = NULL; 
    (op=o)->SetParent(this);
    (right=r)->SetParent(this);
}

ArrayAccess::ArrayAccess(yyltype loc, Expr *b, Expr *s) : LValue(loc) {
    (base=b)->SetParent(this); 
    (subscript=s)->SetParent(this);
}
 
FieldAccess::FieldAccess(Expr *b, Identifier *f) 
  : LValue(b? Join(b->GetLocation(), f->GetLocation()) : *f->GetLocation()) {
    Assert(f != NULL); // b can be be NULL (just means no explicit base)
    base = b; 
    if (base) base->SetParent(this); 
    (field=f)->SetParent(this);
}

Call::Call(yyltype loc, Expr *b, Identifier *f, List<Expr*> *a) : Expr(loc)  {
    Assert(f != NULL && a != NULL); // b can be be NULL (just means no explicit base)
    base = b;
    if (base) base->SetParent(this);
    (field=f)->SetParent(this);
    (actuals=a)->SetParentAll(this);
}

NewExpr::NewExpr(yyltype loc, NamedType *c) : Expr(loc) { 
  Assert(c != NULL);
  (cType=c)->SetParent(this);
}

NewArrayExpr::NewArrayExpr(yyltype loc, Expr *sz, Type *et) : Expr(loc) {
    Assert(sz != NULL && et != NULL);
    (size=sz)->SetParent(this); 
    (elemType=et)->SetParent(this);
}

/********************************************************************************************************/

void IntConstant::Check(int scopeLevel, ScopeTracker *tracker) { 
    //printf("IntConstant\n");
}

void DoubleConstant::Check(int scopeLevel, ScopeTracker *tracker) { 
    //printf("DoubleConstant\n");
}

void BoolConstant::Check(int scopeLevel, ScopeTracker *tracker) { 
    //printf("BoolConstant\n");
}

void StringConstant::Check(int scopeLevel, ScopeTracker *tracker) { 
    //printf("StringConstant\n");
}

void Operator::Check(int scopeLevel, ScopeTracker *tracker) { 
    //printf("Operator\n");
}

void CompoundExpr::Check(int scopeLevel, ScopeTracker *tracker) {
    //printf("CompoundExpr Check\n");
    if (left) left->Check(scopeLevel, tracker);
    op->Check(scopeLevel, tracker);
    if (right) right->Check(scopeLevel, tracker);
}

void ArrayAccess::Check(int scopeLevel, ScopeTracker *tracker) {
    //printf("ArrayAccess Check\n");
    base->Check(scopeLevel, tracker);
    subscript->Check(scopeLevel, tracker);
}

void FieldAccess::Check(int scopeLevel, ScopeTracker *tracker) {
    //printf("FieldAccess Check\n");
    if (base) base->Check(scopeLevel, tracker);
    field->Check(scopeLevel, tracker);
}

void Call::Check(int scopeLevel, ScopeTracker *tracker) {
    //printf("Call Check\n");
    if (base) base->Check(scopeLevel, tracker);
    field->Check(scopeLevel, tracker);
    actuals->CheckAll(scopeLevel, tracker);
}

void NewExpr::Check(int scopeLevel, ScopeTracker *tracker) {
    //printf("NewExpr Check\n");
    cType->Check(scopeLevel, tracker);
}

void NewArrayExpr::Check(int scopeLevel, ScopeTracker *tracker) {
    //printf("NewArrayExpr Check\n");
    size->Check(scopeLevel, tracker);
    elemType->Check(scopeLevel, tracker);
}

       
