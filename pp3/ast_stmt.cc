/* File: ast_stmt.cc
 * -----------------
 * Implementation of statement node classes.
 */
#include "ast_stmt.h"
#include "ast_type.h"
#include "ast_decl.h"
#include "ast_expr.h"

    /* pp3: here is where the semantic analyzer is kicked off.
     *      The general idea is perform a tree traversal of the
     *      entire program, examining all constructs for compliance
     *      with the semantic rules.  Each node can have its own way of
     *      checking itself, which makes for a great use of inheritance
     *      and polymorphism in the node classes.
     */

Program::Program(List<Decl*> *d) {
    Assert(d != NULL);
    (decls=d)->SetParentAll(this);
}

StmtBlock::StmtBlock(List<VarDecl*> *d, List<Stmt*> *s) {
    Assert(d != NULL && s != NULL);
    (decls=d)->SetParentAll(this);
    (stmts=s)->SetParentAll(this);
}
 
ConditionalStmt::ConditionalStmt(Expr *t, Stmt *b) {        // NOT THIS ONE
    Assert(t != NULL && b != NULL);
    (test=t)->SetParent(this); 
    (body=b)->SetParent(this);
}

ForStmt::ForStmt(Expr *i, Expr *t, Expr *s, Stmt *b): LoopStmt(t, b) { 
    Assert(i != NULL && t != NULL && s != NULL && b != NULL);
    (init=i)->SetParent(this);
    (step=s)->SetParent(this);
} 

WhileStmt::WhileStmt(Expr *t, Stmt *b) : LoopStmt(t, b) {
    Assert (t != NULL && b != NULL);
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

/********************************************************************************************************/

void Program::Check(int scopeLevel, ScopeTracker *tracker) {
    //printf("Program Check\n");

    decls->SetUpAll(scopeLevel, tracker);

    decls->CheckAll(scopeLevel, tracker);
}

void StmtBlock::Check(int scopeLevel, ScopeTracker *tracker) {
    //printf("StmtBlock Check\n");
    decls->CheckAll(scopeLevel, tracker); //+1
    stmts->CheckAll(scopeLevel, tracker); //+1
    tracker->UpdateScope(scopeLevel);
}

void ForStmt::Check(int scopeLevel, ScopeTracker *tracker) {
    //printf("ForStmt Check\n");
    init->Check(scopeLevel, tracker);
    test->Check(scopeLevel, tracker);
    step->Check(scopeLevel, tracker);
    body->Check(scopeLevel+1, tracker); //+1
    tracker->UpdateScope(scopeLevel);
}

void WhileStmt::Check(int scopeLevel, ScopeTracker *tracker) {
    //printf("WhileStmt Check\n");
    test->Check(scopeLevel, tracker);
    body->Check(scopeLevel+1, tracker); //+1
    tracker->UpdateScope(scopeLevel);
}

void IfStmt::Check(int scopeLevel, ScopeTracker *tracker) {
    //printf("IfStmt Check\n");
    test->Check(scopeLevel, tracker);
    body->Check(scopeLevel+1, tracker); //+1
    tracker->UpdateScope(scopeLevel);
    if (elseBody) elseBody->Check(scopeLevel+1, tracker); //+1
    tracker->UpdateScope(scopeLevel);
}

void ReturnStmt::Check(int scopeLevel, ScopeTracker *tracker) {
    //printf("ReturnStmt Check\n");
    expr->Check(scopeLevel, tracker);
}

void PrintStmt::Check(int scopeLevel, ScopeTracker *tracker) {
    //printf("PrintStmt Check\n");
    args->CheckAll(scopeLevel, tracker);
}


