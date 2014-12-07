/* File: ast_stmt.cc
 * -----------------
 * Implementation of statement node classes.
 */
#include "ast_stmt.h"
#include "ast_type.h"
#include "ast_decl.h"
#include "ast_expr.h"

#include "codegen.h"
#include "errors.h"
#include <string.h>

Program::Program(List<Decl*> *d) {
    Assert(d != NULL);
    (decls=d)->SetParentAll(this);
}

void Program::Check() {
}

/****************************************************************************/
/****************************************************************************/

void Program::Emit() {

    int count = 0; // no longer used
    CodeGenerator *generator = new CodeGenerator();
    generator->setProgramPtr(this);
    
    Decl *tempDecl, *mainDecl = NULL;

    //decls->EmitAll(generator, &count);

/*    for (int i = 0; i < decls->NumElements(); i++) {
        tempDecl = decls->Nth(i);
        if (strcmp(tempDecl->getName(), "main") == 0) {
            //printf("main\n");
            mainDecl = tempDecl;
        } else {
            tempDecl->Emit(generator, &count);
        }
    }*/

    for (int i = 0; i < decls->NumElements(); i++) {
        tempDecl = decls->Nth(i);
        tempDecl->Emit(generator, &count);
        if (strcmp(tempDecl->getName(), "main") == 0) {
            mainDecl = tempDecl;
        }
    }

/*    if (strcmp(getName(), "main") == 0) {
        generator->setMainHasBeenDefined(true);    
    }*/

    //if (generator->getMainHasBeenDefined()) {
    // TEMPORARY LOOP REPLACE IT LATER
        
    //generator->DoFinalCodeGen(); return;

    if (mainDecl) {
        //mainDecl->Emit(generator, &count);
        generator->DoFinalCodeGen();
    } else {
        ReportError::NoMainFound();
    }
    
}

ClassDecl* Program::findClassDecl(char *searchName) {
    Decl *decl = NULL;
    ClassDecl *classDecl = NULL;
    for (int i = 0; i < decls->NumElements(); i++) {
        decl = decls->Nth(i);
        //printf("%s %s\n", searchName, decl->getName());
        if (strcmp(searchName, decl->getName()) == 0) {
            classDecl = dynamic_cast<ClassDecl*>(decl);
            if (classDecl) return classDecl;
        }
    }
    return NULL;
}

FnDecl* Program::findFnDecl(char *searchName) {
    Decl *decl = NULL;
    FnDecl *fnDecl = NULL;
    for (int i = 0; i < decls->NumElements(); i++) {
        decl = decls->Nth(i);
        if (strcmp(searchName, decl->getName()) == 0) {
            fnDecl = dynamic_cast<FnDecl*>(decl);
            if (fnDecl) return fnDecl;
        }
    }
    return NULL;  
}

Location* StmtBlock::Emit(CodeGenerator *generator, int *count) {
    decls->EmitAll(generator, count);
    stmts->EmitAll(generator, count);
/*    Call *call;
    List<Call*> *callStmts = new List<Call*>;
    for (int i = 0; i < stmts->NumElements(); i++) {
        call = dynamic_cast<Call*>(stmts->Nth(i));
        if (call) {
            callStmts->Append(call);
        } else {
            stmts->Nth(i)->Emit(generator, count);
        }
        
    }
    callStmts->EmitAll(generator, count);*/
    return NULL;
}

Location* ReturnStmt::Emit(CodeGenerator *generator, int *count) {
    Location *loc = expr->Emit(generator, count);
    generator->GenReturn(loc);
    //generator->resetSpaceForLocals();
    return NULL;
}

//condense it with polymorphism
BuiltIn getBuiltIn(CodeGenerator *generator, Location *loc, Expr *arg) {
    if (arg) {
        if (arg->isInt(generator))     return PrintInt;
        if (arg->isBool(generator))    return PrintBool;
        if (arg->isString(generator))  return PrintString;
    }
    return Null;
}

Location* PrintStmt::Emit(CodeGenerator *generator, int *count) {
    Expr *arg;
    for (int i = 0; i < args->NumElements(); i++) {
        arg = args->Nth(i);
        Location *loc = arg->Emit(generator, count);
        BuiltIn builtIn = getBuiltIn(generator, loc, arg);
        if (builtIn != Null) generator->GenBuiltInCall(builtIn, loc);
        else {
            printf("NULL print\n");
        }
    }
    return NULL;
}

Location* IfStmt::Emit(CodeGenerator *generator, int *count) {
    char* lab1 = generator->NewLabel(), *lab2;
    Location *testLoc = test->Emit(generator, count);
    generator->GenIfZ(testLoc, lab1);
    body->Emit(generator, count);
    if (elseBody) {
        lab2 = generator->NewLabel();
        generator->GenGoto(lab2);
    }
    generator->GenLabel(lab1);
    if (elseBody) {
        elseBody->Emit(generator, count);  
        generator->GenLabel(lab2);
    }
    return NULL;
}

Location* ForStmt::Emit(CodeGenerator *generator, int *count) {
    char* lab1 = generator->NewLabel();
    char* lab2 = generator->NewLabel();
    generator->setCurrentBreakLabel(lab2);
    if (init) init->Emit(generator, count);
    generator->GenLabel(lab1);
    Location *testLoc = test->Emit(generator, count);
    generator->GenIfZ(testLoc, lab2);
    body->Emit(generator, count);
    if (step) step->Emit(generator, count);
    generator->GenGoto(lab1);
    generator->GenLabel(lab2);
    return NULL;
}

Location* WhileStmt::Emit(CodeGenerator *generator, int *count) {
    char* lab1 = generator->NewLabel();
    char* lab2 = generator->NewLabel();
    generator->setCurrentBreakLabel(lab2);
    generator->GenLabel(lab1);
    Location *testLoc = test->Emit(generator, count);
    generator->GenIfZ(testLoc, lab2);
    body->Emit(generator, count);
    generator->GenGoto(lab1);
    generator->GenLabel(lab2);
    return NULL;
}

Location* BreakStmt::Emit(CodeGenerator *generator, int *count) {
    generator->GenGoto(generator->getCurrentBreakLabel());
    return NULL;
}

VarDecl* StmtBlock::findVarDecl(char *name) {
    Decl *decl;
    VarDecl *varDecl;
    for (int i = 0; i < decls->NumElements(); i++) {
        varDecl = decls->Nth(i);
        if (strcmp(name, varDecl->getName()) == 0) return varDecl;
    }
    // MIGHT NEED TO SEARCH RECURSIVELY (wait, no, that would be climbing back up the tree)
    return NULL;
}

/****************************************************************************/
/****************************************************************************/

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


