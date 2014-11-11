/* File: ast_stmt.cc
 * -----------------
 * Implementation of statement node classes.
 */
#include "ast_stmt.h"
#include "ast_type.h"
#include "ast_decl.h"
#include "ast_expr.h"
#include "scope.h"
#include "errors.h"

void PrintStmt::Check() {
    Type *temp;
    for (int i=0; i<args->NumElements(); i++) {
        temp = args->Nth(i)->getType();
        if (temp && 
            !(temp->IsEquivalentTo(Type::intType) ||
              temp->IsEquivalentTo(Type::boolType) ||
              temp->IsEquivalentTo(Type::stringType)))
            ReportError::PrintArgMismatch(args->Nth(i), i+1, temp);
    }
}

void BreakStmt::Check() {
    if (!isWithinLoop()) {
        ReportError::BreakOutsideLoop(this);
    }
}

void ReturnStmt::Check() {
    FnDecl *parentDecl = FindParentFn();
    if (!expr->getType() || expr->getType()->isNullType()) {
        return;
    }
    if (parentDecl) {
        parentDecl->CompareReturnTypes(this, expr->getType());
    }
}

void ConditionalStmt::Check() {
    test->Check();
    Type *t = test->getType();
    if (t && !t->IsEquivalentTo(Type::boolType)) {
        ReportError::TestNotBoolean(test);
    }
    body->Check();
}

void Program::Check() {
    nodeScope = new Scope();
    decls->DeclareAll(nodeScope);
    decls->CheckAll();

}

void StmtBlock::Check() {
    nodeScope = new Scope();
    decls->DeclareAll(nodeScope);
    decls->CheckAll();
    stmts->CheckAll();
}

void IfStmt::Check() {
    ConditionalStmt::Check();
    if (elseBody) elseBody->Check();
}

Case::Case(Expr *t, List<Stmt*> *s) {
    Assert(t != NULL && s != NULL);
    (test=t)->SetParent(this);
    (stmts=s)->SetParentAll(this);
}

Program::Program(List<Decl*> *d) {
    Assert(d != NULL);
    (decls=d)->SetParentAll(this);
}

StmtBlock::StmtBlock(List<VarDecl*> *d, List<Stmt*> *s) {
    Assert(d != NULL && s != NULL);
    (decls=d)->SetParentAll(this);
    (stmts=s)->SetParentAll(this);
}

ConditionalStmt::ConditionalStmt(Expr *t, Stmt *b) { 
    Assert(t != NULL && b != NULL);
    (test=t)->SetParent(this); 
    (body=b)->SetParent(this);
}

ForStmt::ForStmt(Expr *i, Expr *t, Expr *s, Stmt *b): LoopStmt(t, b) { 
    Assert(i != NULL && t != NULL && s != NULL && b != NULL);
    (init=i)->SetParent(this);
    (step=s)->SetParent(this);
}

IfStmt::IfStmt(Expr *t, Stmt *tb, Stmt *eb): ConditionalStmt(t, tb) { 
    Assert(t != NULL && tb != NULL); // else can be NULL
    elseBody = eb;
    if (elseBody) elseBody->SetParent(this);
}

ReturnStmt::ReturnStmt(yyltype loc, Expr *e) : Stmt(loc) { 
    Assert(e != NULL);
    (expr=e)->SetParent(this);
}
  
PrintStmt::PrintStmt(List<Expr*> *a) {    
    Assert(a != NULL);
    (args=a)->SetParentAll(this);
}


