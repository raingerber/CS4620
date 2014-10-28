/* File: ast.cc
 * ------------
 */

#include "ast.h"
#include "ast_type.h"
#include "ast_decl.h"
#include <string.h> // strdup
#include <stdio.h>  // printf

#include "hashtable.h"

#include <string>

class VarDecl;

ScopeTracker::ScopeTracker()
{
	currentScope = 0;
    h = new Hashtable<Hashtable<Node*>*>;
    h->Enter("0", new Hashtable<Node*>, true);

    extendsTable = new Hashtable<Hashtable<Decl*>*>;
    interfaceTable = new Hashtable<Hashtable<Decl*>*>;
    typeTable = new Hashtable<Type*>;
}

void ScopeTracker::UpdateScope(int scope) {

	char scopeStr[20];

	if (scope < currentScope) {
		sprintf(scopeStr, "%d", currentScope);
		h->Remove(scopeStr, h->Lookup(scopeStr));
	} else if (currentScope < scope) {
		sprintf(scopeStr, "%d", scope);
		h->Enter(scopeStr, new Hashtable<Node*>, true);
	}
	currentScope = scope;
	//printf("SCOPE = %i\n", currentScope);
}

void ScopeTracker::addType(char *key, Type *type) {
	typeTable->Enter(key, type, true);
}

void ScopeTracker::addDecl(char *key, Node *node) {
	
}

/******************************************************************************************************************
													AST_DECL
******************************************************************************************************************/

void ScopeTracker::CheckForDeclConflict(int scope, char *key, Node *node) {

	UpdateScope(scope);
	char scopeStr[20];
	sprintf(scopeStr, "%d", currentScope);
	Node *currentNode = h->Lookup(scopeStr)->Lookup(key);

	if (currentNode == NULL) {
		h->Lookup(scopeStr)->Enter(key, node, true);
	} else {
		ReportError::DeclConflict(dynamic_cast<Decl*>(node), dynamic_cast<Decl*>(currentNode));
	}

}

void ScopeTracker::CheckForDeclConflict(int scope, char *key, Node *node, char *parentName) {

	UpdateScope(scope);
	char scopeStr[20];
	sprintf(scopeStr, "%d", currentScope);
	Node *existingNode = h->Lookup(scopeStr)->Lookup(key);

	if (existingNode != NULL) {
		ReportError::DeclConflict(dynamic_cast<Decl*>(node), dynamic_cast<Decl*>(existingNode));
		return;
	} else {
		//printf("parent name %s\n", parentName);
		Hashtable<Decl*> *parent = this->extendsTable->Lookup(parentName);
		if (parent != NULL) {
			//printf("null\n");
			if (parent->Lookup(key) != NULL) {
				ReportError::DeclConflict(dynamic_cast<Decl*>(node), parent->Lookup(key));
			}
		}
		return;
	}
	h->Lookup(scopeStr)->Enter(key, node, true);

}

void ScopeTracker::IdentifierCheck(int scope, char *key, Node *node, reasonT whyNeeded) {

	UpdateScope(scope);

	char scopeStr[20];
	Node *currentNode = NULL;
	int i = currentScope;

	while (i >= 0 && currentNode == NULL) {						// check the scope and all sub-scopes to see if the identifier has been declared
		sprintf(scopeStr, "%d", i);
		currentNode = h->Lookup(scopeStr)->Lookup(key);
		i--;
	}

	if (currentNode == NULL) {
		ReportError::IdentifierNotDeclared(dynamic_cast<Identifier*>(node), whyNeeded);
	}

}

/******************************************************************************************************************
											ORIGINAL NODE + IDENTIFIER DEFINITIONS
******************************************************************************************************************/

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

void Identifier::Check(int scopeLevel, ScopeTracker *tracker) {
	tracker->IdentifierCheck(scopeLevel, this->name, this, LookingForVariable);
}

void Identifier::CheckNamedType(int scopeLevel, ScopeTracker *tracker) {
	tracker->IdentifierCheck(scopeLevel, this->name, this, LookingForInterface);
}

void Identifier::CheckExtends(int scopeLevel, ScopeTracker *tracker) {
	tracker->IdentifierCheck(scopeLevel, this->name, this, LookingForClass);
}

//typedef enum {LookingForType, LookingForClass, LookingForInterface, LookingForVariable, LookingForFunction} reasonT;