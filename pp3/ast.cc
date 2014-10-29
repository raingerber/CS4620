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
	//printf("Normal Identifier Check %s\n", this->name);
	Decl *dec;
	Node *p = this;
	while ((p = p->GetParent()) != NULL) {
		if (p->localTable != NULL) {
			Iterator<Decl*> iterator = p->localTable->GetIterator();
		    while ((dec = iterator.GetNextValue()) != NULL) {
		        if (strcmp(dec->getName(), this->name) == 0) {
		        	return;
		        }
		    }	
		}
	}
	ReportError::IdentifierNotDeclared(this, LookingForVariable);
}

void Identifier::Check(reasonT whyNeeded) { 						// DOES NOT ACCOUNT FOR THE TYPE OF THE DECLARATION
	//printf("id check\n")
	Decl *dec;
	Node *p = this;
	while ((p = p->GetParent()) != NULL) {
		if (p->localTable != NULL) {
			Iterator<Decl*> iterator = p->localTable->GetIterator();
		    while ((dec = iterator.GetNextValue()) != NULL) {
		        if (strcmp(dec->getName(), this->name) == 0) {
		        	return;
		        }
		    }
		}
	}
	ReportError::IdentifierNotDeclared(this, whyNeeded);
}
