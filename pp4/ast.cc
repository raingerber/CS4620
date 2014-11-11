/* File: ast.cc
 * ------------
 */

#include "ast.h"
#include "ast_type.h"
#include "ast_decl.h"
#include <string.h> // strdup
#include <stdio.h>  // printf
#include "errors.h"
#include "scope.h"

#include "ast_stmt.h"    // matt
class LoopStmt;          // matt
#include "ast_expr.h"    // matt

Node::Node(yyltype loc) {
    location = new yyltype(loc);
    parent = NULL;
    nodeScope = NULL;
    messedUp = false;
}

Node::Node() {
    location = NULL;
    parent = NULL;
    nodeScope = NULL;
    messedUp = false;
}

bool Node::StoreExprError() {
    Node *temp = dynamic_cast<Expr*>(this->parent);
    if (temp) {
        while (dynamic_cast<Expr*>(temp->parent) != NULL) {
            temp = dynamic_cast<Expr*>(temp->parent);
        }
    } else {
        temp = dynamic_cast<Expr*>(this);
    }
    if (!temp || dynamic_cast<Call*>(temp) != NULL) {
        return false;
    }
    if (temp->errorFlagged()) {
        return true;
    } else {
        temp->setErrorFlag();
        return false;
    }
}

bool Node::inSamePosition(Node *compNode) {
    yyltype *compLoc = compNode->GetLocation();
    return (location->first_line == compLoc->first_line && location->first_column == compLoc->first_column);
}

ClassDecl* Node::FindParentClass() {
    Node *current = this;
    ClassDecl *classDecl;
    while (current->parent != NULL) {
        current = current->parent;
        classDecl = dynamic_cast<ClassDecl*>(current);
        if (classDecl) {
            return classDecl;
        }
    }
    return NULL;
}

FnDecl* Node::FindParentFn() {
    Node *current = this;
    FnDecl *fnDecl;
    while (current->parent != NULL) {
        current = current->parent;
        fnDecl = dynamic_cast<FnDecl*>(current);
        if (fnDecl) {
            return fnDecl;
        }
    }
    return NULL;
}

bool Node::isWithinLoop() {
    Node *current = this;
    LoopStmt *loopStmt;
    while (current->parent != NULL) {
        current = current->parent;
        loopStmt = dynamic_cast<LoopStmt*>(current);
        if (loopStmt) {
            return true;
        }
    }
    return false; 
}

Decl *Node::FindDecl(Identifier *idToFind, lookup l) {
    Decl *mine;
    if (!nodeScope) PrepareScope();
    if (nodeScope && (mine = nodeScope->Lookup(idToFind)))
        return mine;
    if (l == kDeep && parent)
        return parent->FindDecl(idToFind, l);
    return NULL;
}
	 
Identifier::Identifier(yyltype loc, const char *n) : Node(loc) {
    name = strdup(n);
    cached = NULL;
} 

void Identifier::Check() {
}

//classes, interfaces, functions, variables
Decl* Identifier::Check(reasonT whyNeeded) {
    //printf("id check\n");
    Decl *d = FindDecl(this);
    if (!d) {
        StoreExprError();
        ReportError::IdentifierNotDeclared(this, whyNeeded);
        return NULL;
    }
    if (whyNeeded == LookingForFunction && !d->IsFnDecl()) {
        StoreExprError();
        ReportError::IdentifierNotDeclared(this, whyNeeded);
        return NULL;
    }
    if (whyNeeded == LookingForVariable && !d->IsVarDecl()) {
        StoreExprError();
        ReportError::IdentifierNotDeclared(this, whyNeeded);
        return NULL;
    }
/*    if ((whyNeeded == LookingForClass || whyNeeded == LookingForInterface)) {
        ReportError::IdentifierNotDeclared(this, whyNeeded);
    } */
    cached = d;
    return cached;
}

Type* Identifier::getType() {
    //printf("identifier get type\n");
    Decl *d = FindDecl(this);
    if (d) {
        return d->GetDeclaredType();
    }
    return NULL;
}
