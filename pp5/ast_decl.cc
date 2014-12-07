/* File: ast_decl.cc
 * -----------------
 * Implementation of Decl node classes.
 */
#include "ast_decl.h"
#include "ast_type.h"
#include "ast_stmt.h"
                 
#include "codegen.h" // pp5
#include <string.h>
#include "tac.h"

class Location;

int FnDecl::findParameterOffset(char *name) {
    for (int i = 0; i < formals->NumElements(); i++) {
        if (strcmp(name, formals->Nth(i)->getName()) == 0) {
            return i;
        }
    }
    return -1; // if not found
}

VarDecl* FnDecl::findFormal(char *name) {
    for (int i = 0; i < formals->NumElements(); i++) {
        if (strcmp(name, formals->Nth(i)->getName()) == 0) return formals->Nth(i);
    }
    return NULL;
}

VarDecl* FnDecl::findVarDecl(char *name) {
    if (body) {
        return body->findVarDecl(name);
    }
    return NULL;
}

Location* VarDecl::Emit(CodeGenerator *generator, int *count) {
    if (!tacLoc) {
        if (dynamic_cast<Program*>(GetParent()) == NULL) {
            tacLoc = generator->GenLocalVar(getName());
        } else {
            tacLoc = generator->GenGlobalVar(getName(), this);
        }
    }
    return tacLoc;
}

Location* FnDecl::Emit(CodeGenerator *generator, int *count) {

    generator->ResetTempNumber();
    
    if (dynamic_cast<Program*>(GetParent()) != NULL) {
        generator->storeGlobalFnDecl(this);
    }

    int vars = 0; // NO LONGER NECESSARY, THE WHOLE "COUNT" SCHEME HAS BEEN DISCONTINUED
    BeginFunc *beginFunc;
    ClassDecl *parentClass = dynamic_cast<ClassDecl*>(GetParent());
    if (parentClass != NULL) {
        char labelName[100];
        sprintf(labelName, "%s.%s", parentClass->getName(), getName());
        generator->GenLabel(labelName);
    } else {
        generator->GenLabel(getName());
    }
    beginFunc = generator->GenBeginFunc();

    List<Location*> *declareList = new List<Location*>;

    for (int i = 0; i < formals->NumElements(); i++) {
    }

    body->Emit(generator, &vars);

    beginFunc->SetFrameSize(4 * generator->GetTempNumber());
    generator->ResetTempNumber();
    generator->GenEndFunc();

    return NULL;
}

void ClassDecl::FindMethodLabels(CodeGenerator *generator) {

    if (methodLabelsFound) {
        return;
    }

    Decl *decl;

    char *className;
    char *methodName;
    char *labelName;

    parentClasses = new List<ClassDecl*>;
    List<const char*> *classNames = new List<const char*>;
    // later used to find vtable offsets when calling functions
    methodNames = new List<const char*>;
    methodLabels = new List<const char*>;

    ClassDecl *classDecl = this;
    VarDecl *v;
    // find classes this one extends (with this class at list[0])
    parentClasses->Append(this);
    while (classDecl->extends) {
        classDecl = generator->findClassDecl(classDecl->extends->getName());
        parentClasses->Append(classDecl);
    }

    // add parent functions in reverse order (parent -> child -> child ... -> this)
    for (int i = parentClasses->NumElements() - 1; i >= 0; i--) {
        //printf("%i\n",i);
        appendLabelNames(parentClasses->Nth(i), classNames, methodNames);
        for (int j = 0; j < parentClasses->Nth(i)->members->NumElements(); j++) {
            v = dynamic_cast<VarDecl*>(parentClasses->Nth(i)->members->Nth(j));
            if (v) varList->Append(v);
        }
    }

/*    for (int i = 0; i < varList->NumElements(); i++) { // for checking that the vardecls are correct
        printf("var decl     %s\n", varList->Nth(i)->getName());
    }
    printf("\n");*/

    //appendLabelNames(this, classNames, methodNames);

    // create the list that will generate the vtable and be used to offset into the vtable
    // (methodLabels)
    for (int i = 0; i < classNames->NumElements(); i++) {
        labelName = new char[100];
        sprintf(labelName, "%s.%s", classNames->Nth(i), methodNames->Nth(i));
        methodLabels->Append(labelName);
    }

    methodLabelsFound = true;

}

Location* ClassDecl::Emit(CodeGenerator *generator, int *count) {

    FindMethodLabels(generator);

    //printf("emitting %s\n", getName());
    // emit the decls within the class (except not vardecls)
    for (int i = 0; i < members->NumElements(); i++) {
        if (dynamic_cast<VarDecl*>(members->Nth(i)) == NULL) {
            members->Nth(i)->Emit(generator, count); 
        } else {

        }
    }
    //printf("emitting %s\n", getName());

    generator->GenVTable(getName(), methodLabels);

    return NULL;

}
// OKAY, THESE METHODS ARE GETTING CRAZY
// BELOW, IT'S PARTLY BECAUSE THE LIST IMPLEMENTATION IS NOT EXACTLY WHAT'S NEEDED
// (DOESN'T SEEM TO ALLOW FOR EASY OVERWRITING, FOR EXAMPLE)
// AND THE DOUBLE LOOP WITH THE FLAG IS JUST A HEADACHE
// could probably use the hashmap with iterator? that would automatically overwrite
// overloaded functions

void ClassDecl::appendLabelNames(ClassDecl *classDecl,
                                 List<const char*> *classNames,
                                 List<const char*> *methodNames) {

    bool flag = true;
    Decl *decl;
    char *className;
    char *methodName;
    char *labelName;
    for (int i = 0; i < classDecl->members->NumElements(); i++) {
        decl = classDecl->members->Nth(i);
        if (dynamic_cast<FnDecl*>(decl) != NULL) {
            className = new char[100];
            methodName = new char[100];
            sprintf(className, "%s", classDecl->getName());
            sprintf(methodName, "%s", decl->getName());
            for (int j = 0; j < methodNames->NumElements(); j++) {
                if (strcmp(methodName, methodNames->Nth(j)) == 0) {
                    classNames->RemoveAt(j);
                    methodNames->RemoveAt(j);
                    if (j < classNames->NumElements()) {
                        classNames->InsertAt(className, j);
                        methodNames->InsertAt(methodName, j);
                    } else {
                        classNames->Append(className);
                        methodNames->Append(methodName);
                    }
                    flag = false;
                }
            }
            if (flag) {
                classNames->Append(className);
                methodNames->Append(methodName);
            }
            flag = true;
        }
    }
}

Decl* ClassDecl::getDeclFromClass(CodeGenerator *generator, char *name) {
    ClassDecl *classDecl = this;
    while (classDecl) {
        for (int i = 0; i < classDecl->members->NumElements(); i++) {
            if (strcmp(name, classDecl->members->Nth(i)->getName()) == 0) {
                return classDecl->members->Nth(i);
            }
        }
        if (classDecl->extends) {
            classDecl = generator->findClassDecl(extends->getName());
        } else {
            classDecl = NULL;
        }
    }
    return NULL;
}

int ClassDecl::getVarOffset(CodeGenerator *generator, char *name) {
    //printf("nothing there %s\n",name);
    FindMethodLabels(generator);
    // used for instance variables
    //printf("nothing there %i\n", varList->NumElements());
    for (int i = 0; i < varList->NumElements(); i++) {
        //printf("test %s against %s\n", name, varList->Nth(i)->getName());
        if (strcmp(name, varList->Nth(i)->getName()) == 0) {
            return i;
        }
    }
    return -1;
}

Location* InterfaceDecl::Emit(CodeGenerator *generator, int *count) {
    return NULL;
}

/****************************************************************************/
/****************************************************************************/

Decl::Decl(Identifier *n) : Node(*n->GetLocation()) {
    Assert(n != NULL);
    (id=n)->SetParent(this);
}


VarDecl::VarDecl(Identifier *n, Type *t) : Decl(n) {
    Assert(n != NULL && t != NULL);
    (type=t)->SetParent(this);
}
  
ClassDecl::ClassDecl(Identifier *n, NamedType *ex, List<NamedType*> *imp, List<Decl*> *m) : Decl(n) {
    // extends can be NULL, impl & mem may be empty lists but cannot be NULL
    Assert(n != NULL && imp != NULL && m != NULL);     
    variables = new List<VarDecl*>;
    varList = new List<VarDecl*>;
    variableListReady = false;
    methodLabelsFound = false;
    extends = ex;
    if (extends) extends->SetParent(this);
    (implements=imp)->SetParentAll(this);
    (members=m)->SetParentAll(this);
}


InterfaceDecl::InterfaceDecl(Identifier *n, List<Decl*> *m) : Decl(n) {
    Assert(n != NULL && m != NULL);
    (members=m)->SetParentAll(this);
}

	
FnDecl::FnDecl(Identifier *n, Type *r, List<VarDecl*> *d) : Decl(n) {
    Assert(n != NULL && r!= NULL && d != NULL);
    (returnType=r)->SetParent(this);
    (formals=d)->SetParentAll(this);
    body = NULL;
}

void FnDecl::SetFunctionBody(Stmt *b) { 
    (body=b)->SetParent(this);
}



