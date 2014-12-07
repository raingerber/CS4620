/* File: ast.cc
 * ------------
 */

#include "ast.h"
#include "ast_type.h"
#include "ast_decl.h"
#include <string.h> // strdup
#include <stdio.h>  // printf

Node::Node(yyltype loc) {
    location = new yyltype(loc);
    parent = NULL;
}

Node::Node() {
    location = NULL;
    parent = NULL;
}
	 
Identifier::Identifier(yyltype loc, const char *n) : Node(loc) {
    name = strdup(n);
} 

/*FnDecl* Node::getParentFn() {
    Node *node = this;
    FnDecl *fnDecl;
    while (node != NULL) {
        fnDecl = dynamic_cast<FnDecl*>(node);
        if (fnDecl) return fnDecl;
        node = node->GetParent();
    }
    return NULL;
}
*/
ClassDecl* Node::getParentClass() {
    Node *node = this;
    ClassDecl *classDecl;
    while (node != NULL) {
        classDecl = dynamic_cast<ClassDecl*>(node);
        if (classDecl) return classDecl;
        node = node->GetParent();
    }
    return NULL;
}
