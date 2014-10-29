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
/*
Program::Program(List<Decl*> *d)
StmtBlock::StmtBlock(List<VarDecl*> *d, List<Stmt*> *s)
ConditionalStmt::ConditionalStmt(Expr *t, Stmt *b)
ForStmt::ForStmt(Expr *i, Expr *t, Expr *s, Stmt *b): LoopStmt(t, b)
WhileStmt::WhileStmt(Expr *t, Stmt *b) : LoopStmt(t, b)
IfStmt::IfStmt(Expr *t, Stmt *tb, Stmt *eb): ConditionalStmt(t, tb)
ReturnStmt::ReturnStmt(yyltype loc, Expr *e) : Stmt(loc)
PrintStmt::PrintStmt(List<Expr*> *a)  
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

void Program::CreateTables() {
    //printf("program create tables\n");
    //void CreateTables(Hashtable<Node*> &parentTable);
    localTable = new Hashtable<Decl*>;
    for (int i = 0; i < decls->NumElements(); i++) {
        decls->Nth(i)->CreateTables();
        localTable->Enter(decls->Nth(i)->getName(), decls->Nth(i), false);
    }
}
 
void StmtBlock::CreateTables() {
    //printf("stmt block table\n");
    localTable = new Hashtable<Decl*>;
    for (int i = 0; i < decls->NumElements(); i++) {
        decls->Nth(i)->CreateTables();
        localTable->Enter(decls->Nth(i)->getName(), decls->Nth(i), false);
    }
    for (int i = 0; i < stmts->NumElements(); i++) {
        stmts->Nth(i)->CreateTables();
    }
}

void LoopStmt::CreateTables() {
    //printf("Loop table\n");
    body->CreateTables();
}

void IfStmt::CreateTables() {
    //printf("if stmt table\n");
    body->CreateTables();
    if (elseBody) {
        elseBody->CreateTables();
    }
}

/********************************************************************************************************/

void Program::Check() {
    //printf("Program Check\n");
    //decls->SetUpAll(scopeLevel, tracker);
    //printf("\nProgram Check (%i):\n", decls->NumElements());
    decls->CheckAll();
}

void StmtBlock::Check() {
    //printf("StmtBlock Check\n");
    decls->CheckAll();
    stmts->CheckAll();
}

void ForStmt::Check() {
    //printf("ForStmt Check\n");
    init->Check();
    test->Check();
    step->Check();
    body->Check();
}

void WhileStmt::Check() {
    //printf("WhileStmt Check\n");
    test->Check();
    body->Check();
}

void IfStmt::Check() {
    //printf("IfStmt Check\n");
    test->Check();
    body->Check();
    if (elseBody) elseBody->Check();
}

void ReturnStmt::Check() {
    //printf("ReturnStmt Check\n");
    expr->Check();
}

void PrintStmt::Check() {
    //printf("PrintStmt Check\n");
    args->CheckAll();
}

void BreakStmt::Check() {
}

