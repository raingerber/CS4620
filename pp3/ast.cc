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

void Identifier::CreateTables() {
	//printf("create Id table\n");
	localTable = NULL;
}

void Identifier::Check() {
	//printf("Normal Identifier Check\n");
}

void Identifier::Check(reasonT whyNeeded) { 						// DOES NOT ACCOUNT FOR THE TYPE OF THE DECLARATION

	Decl *dec;
	Node *p = this;
	while ((p = p->GetParent()) != NULL) {
		Iterator<Decl*> iterator = p->localTable->GetIterator();
	    while ((dec = iterator.GetNextValue()) != NULL) {
	        if (strcmp(dec->getName(), this->name) == 0) {
	        	return;
	        }
	    }	
	}
	ReportError::IdentifierNotDeclared(this, whyNeeded);
}

/*void Identifier::Check(int scopeLevel, ScopeTracker *tracker) {
	tracker->IdentifierCheck(scopeLevel, this->name, this, LookingForVariable);
}

void Identifier::CheckNamedType(int scopeLevel, ScopeTracker *tracker) {
	tracker->IdentifierCheck(scopeLevel, this->name, this, LookingForInterface);
}

void Identifier::CheckExtends(int scopeLevel, ScopeTracker *tracker) {
	tracker->IdentifierCheck(scopeLevel, this->name, this, LookingForClass);
}*/