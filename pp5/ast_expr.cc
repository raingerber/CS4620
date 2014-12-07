/* File: ast_expr.cc
 * -----------------
 * Implementation of expression node classes.
 */
#include "ast_expr.h"
#include "ast_type.h"
#include "ast_decl.h"
#include <string.h>

#include "tac.h"        // pp5
#include "errors.h"

// USE FUNCTION POINTERS TO AVOID ALL THIS REPETITION?

bool Expr::isArray() {
    return true;
}

ClassDecl* ArrayAccess::findParentClassDecl(CodeGenerator *generator) {
    //printf("array findParentClassDecl\n");
    //base
    return NULL;
}

ClassDecl* Call::findParentClassDecl(CodeGenerator *generator) {
    //printf("call findParentClassDecl\n");
    return NULL;
}

ClassDecl* FieldAccess::findParentClassDecl(CodeGenerator *generator) {
    //printf("call findParentClassDecl\n");
    return generator->findClassDecl(getName());
}

bool FieldAccess::isInt(CodeGenerator *generator) {
    return declaration != NULL ? declaration->isInt() : false;
}

bool FieldAccess::isBool(CodeGenerator *generator) {
    return declaration != NULL ? declaration->isBool() : false;
}

bool FieldAccess::isString(CodeGenerator *generator) {
    return declaration != NULL ? declaration->isString() : false;
}

/************************************************************************************/
/************************************************************************************/

Location* EqualityExpr::Emit(CodeGenerator *generator, int *count) {

    bool L = false, R = false;
    //Location *lloc, *rloc, *ret;
    char* opStr = op->getTokenString();

    FieldAccess *f1 = dynamic_cast<FieldAccess*>(left);
    FieldAccess *f2 = dynamic_cast<FieldAccess*>(right);
    ArrayAccess *lcheck = dynamic_cast<ArrayAccess*>(left);
    ArrayAccess *rcheck = dynamic_cast<ArrayAccess*>(right);

    if (f1) {
        f1->getFieldDeclaration(generator);
        L = f1->isString(generator);
    }

    if (f2) {
        f2->getFieldDeclaration(generator);
        R = f2->isString(generator);
    }

    L = L | left->isString(generator); // special function will be called for strings
    R = R | right->isString(generator);

    if (L & R) { // for this hw assignment, all expressions are well-formed
        //printf("strings\n");
        return CheckStringEquality(generator, count);
    }

/*    if ((lcheck != NULL) && (rcheck != NULL)) {
        lloc = lcheck->EmitButReturnReference(generator, count);
        rloc = rcheck->EmitButReturnReference(generator, count);
    } else if (lcheck != NULL) {
        lloc = lcheck->EmitButReturnReference(generator, count);
        rloc = right->Emit(generator, count);
    } else {
        lloc = left->Emit(generator, count);
        rloc = right->Emit(generator, count);
    }*/

    Location *lloc = left->Emit(generator, count),
             *rloc = right->Emit(generator, count), *ret;

    if (strcmp(opStr, "!=") == 0) {
        Location *temp0 = generator->GenBinaryOp("==", rloc, lloc);
        ret = generator->GenBinaryOp("==", temp0, generator->GenLoadConstant(false));
    } else {
        ret = generator->GenBinaryOp(opStr, lloc, rloc);
    }

    return ret;

}

Location* EqualityExpr::CheckStringEquality(CodeGenerator *generator, int *count) {
    char* opStr = op->getTokenString();
    Location *lloc = left->Emit(generator, count),
             *rloc = right->Emit(generator, count), *ret, *zero;
    generator->GenPushParam(rloc);
    generator->GenPushParam(lloc);
    ret = generator->GenLCall("_StringEqual", true);
    generator->GenPopParams(8);
    if (strcmp(opStr, "!=") == 0) {
        zero = generator->GenLoadConstant(0);
        return generator->GenBinaryOp("==", ret, zero);
    }
    return ret;
}

Location* CompoundExpr::Emit(CodeGenerator *generator, int *count) {

    char* opStr = op->getTokenString();

    Location *ret = NULL,
             *lloc = left ? left->Emit(generator, count) : NULL,
             *rloc = right->Emit(generator, count),
             *temp0, *temp1;

    if (strcmp(opStr, ">") == 0) {

        //*count = (*count) + 1;
        ret = generator->GenBinaryOp("<", rloc, lloc);

    } else if (strcmp(opStr, ">=") == 0) {

        //*count = (*count) + 3;
        temp0 = generator->GenBinaryOp("<", rloc, lloc);
        temp1 = generator->GenBinaryOp("==", rloc, lloc);
        ret = generator->GenBinaryOp("||", temp0, temp1);

    } else if (strcmp(opStr, "<=") == 0) {

        //*count = (*count) + 3;
        temp0 = generator->GenBinaryOp("<", lloc, rloc);
        temp1 = generator->GenBinaryOp("==", lloc, rloc);
        ret = generator->GenBinaryOp("||", temp0, temp1);
        //ret = lessThanOrEqualTo(generator, count, lloc, rloc);
    } else if (left == NULL) {

        if (strcmp(opStr, "!") == 0) {

            //*count = (*count) + 2;
            temp0 = generator->GenLoadConstant(false);
            ret = generator->GenBinaryOp("==", rloc, temp0);

        } else if (strcmp(opStr, "-") == 0) {

            //*count = (*count) + 2;
            temp0 = generator->GenLoadConstant(0);
            ret = generator->GenBinaryOp("-", temp0, rloc);

        }
    } else {

        //*count = (*count) + 1;
        ret = generator->GenBinaryOp(opStr, lloc, rloc);

    }
    return ret;
}

Location* IntConstant::Emit(CodeGenerator *generator, int *count) {
    //*count = (*count) + 1;
    return generator->GenLoadConstant(value);
}

Location* BoolConstant::Emit(CodeGenerator *generator, int *count) {
    //*count = (*count) + 1;
    return generator->GenLoadConstant(value ? 1 : 0);
}

Location* StringConstant::Emit(CodeGenerator *generator, int *count) {
    //*count = (*count) + 1;
    //printf("string constant: %s\n", value);
    return generator->GenLoadConstant(value);
}

Location* NullConstant::Emit(CodeGenerator *generator, int *count) {
    //*count = (*count) + 1;
    return generator->GenLoadConstant(0);
}

Location* ReadIntegerExpr::Emit(CodeGenerator *generator, int *count) {
    //*count = (*count) + 1;
    return generator->GenBuiltInCall(ReadInteger);
}

Location* ReadLineExpr::Emit(CodeGenerator *generator, int *count) {
    //*count = (*count) + 1;
    return generator->GenBuiltInCall(ReadLine);
}

/************************************************************************************/
/************************************************************************************/

Location* NewArrayExpr::Emit(CodeGenerator *generator, int *count) {

    Location *sizeLoc, *one1, *ztest, *errorMsg;

    char* label = generator->NewLabel();
    sizeLoc = size->Emit(generator, count);

    one1 = generator->GenLoadConstant(1);
    ztest = generator->GenBinaryOp("<", sizeLoc, one1);
    generator->GenIfZ(ztest, label);
    errorMsg = generator->GenLoadConstant(err_arr_bad_size);
    generator->GenBuiltInCall(PrintString, errorMsg);
    generator->GenBuiltInCall(Halt);

    generator->GenLabel(label);

    Location *one2, *arrayBytes, *four, *memSize, *ptr, *ret;

    one2 = generator->GenLoadConstant(1);
    arrayBytes = generator->GenBinaryOp("+", one2, sizeLoc);
    four = generator->GenLoadConstant(4);
    memSize = generator->GenBinaryOp("*", arrayBytes, four);
    ptr = generator->GenBuiltInCall(Alloc, memSize);
    generator->GenStore(ptr, sizeLoc);
    return generator->GenBinaryOp("+", ptr, four);

}

Location* ArrayAccess::EmitButReturnReference(CodeGenerator *generator, int *count) {

    Location *i, *zero, *lessThanZero, *maxSize, 
             *lessThanMax, *outOfBounds, *equality, *ztest, *errorMsg;

    char* label = generator->NewLabel();

    i = subscript->Emit(generator, count);

    zero = generator->GenLoadConstant(0);
    lessThanZero = generator->GenBinaryOp("<", i, zero);
    maxSize = generator->GenLoad(base->Emit(generator, count), -4);
    lessThanMax = generator->GenBinaryOp("<", i, maxSize);
    equality = generator->GenBinaryOp("==", lessThanMax, zero);
    ztest = generator->GenBinaryOp("||", lessThanZero, equality);

    generator->GenIfZ(ztest, label);
    errorMsg = generator->GenLoadConstant(err_arr_out_of_bounds);
    generator->GenBuiltInCall(PrintString, errorMsg);
    generator->GenBuiltInCall(Halt);
    
    generator->GenLabel(label);
    Location *four, *off, *index;
    four = generator->GenLoadConstant(4);
    off = generator->GenBinaryOp("*", four, i);

    return generator->GenBinaryOp("+", base->Emit(generator, count), off);

}

Location* ArrayAccess::Emit(CodeGenerator *generator, int *count) {
    return generator->GenLoad(EmitButReturnReference(generator, count));
}

Decl* FieldAccess::getFieldDeclaration(CodeGenerator *generator) {

    if (declaration) return declaration;
    
    Node *node = this;
    Decl *testDecl = NULL;
    FnDecl *fnDecl = NULL;
    VarDecl *varDecl = NULL;
    ClassDecl *classDecl = NULL;
    char *name = field->getName();

    while (node) {

        varDecl = node->findVarDecl(name);

        if (varDecl) { setIsLocal(); declaration = varDecl; return declaration; }

        fnDecl = dynamic_cast<FnDecl*>(node);

        if ((fnDecl != NULL)) { // & (dynamic_cast<This*>(base) == NULL)
            varDecl = fnDecl->findFormal(field->getName());
            if (varDecl) {
                offset = fnDecl->findParameterOffset(field->getName());
                //printf("-----param %s has offset %i\n", field->getName(), offset);
                declaration = varDecl;
                if (dynamic_cast<This*>(base) == NULL) {
                    //printf("is param: %s\n", getName());
                    setIsParam();
                    //generator->OffsetToFirstLocal;
                    tacLoc = new Location(fpRelative, 8 + (4 * offset), field->getName());
                    return declaration;
                }
            }
        }

        node = node->GetParent();

    }

    classDecl = this->getParentClass();

    if (classDecl) {            
        testDecl = classDecl->getDeclFromClass(generator, getName());
        if (testDecl) { 
            //printf("-----------is class var %s\n", getName());
            setIsClassVar(); 
            declaration = testDecl; 
            return declaration; 
        }
    }

    // CHECK IF IT'S A GLOBAL
    varDecl = dynamic_cast<VarDecl*>(generator->findGlobal(field->getName()));
    if (varDecl) { declaration = varDecl; setIsGlobal(); return declaration; }

    return declaration;

}

Location* AssignExpr::Emit(CodeGenerator *generator, int *count) {

    Location *lloc, *rloc;

    FieldAccess *f1 = dynamic_cast<FieldAccess*>(left);
    FieldAccess *f2 = dynamic_cast<FieldAccess*>(right);

    ArrayAccess *lcheck = dynamic_cast<ArrayAccess*>(left);

    NewArrayExpr *arrayExpr = dynamic_cast<NewArrayExpr*>(right);

    ClassDecl *classDecl;
    Location *thisLoc = new Location(fpRelative, 4, "this");

    bool assigningToClassVar = false;

    if (f1) {
        f1->getFieldDeclaration(generator);
        if (f1->isClassVar()) {
            assigningToClassVar = true;
        }
    } 

    if (f2) {
        f2->getFieldDeclaration(generator);
        if (f2->isParam()) {
            //printf("b\n");  
        } else if (f2->isClassVar()) {
            //printf("b2\n"); 
        } 
    }

    rloc = right->Emit(generator, count);

    if (assigningToClassVar) {
/*        int instOff = f1->getParentClass()->getVarOffset(generator, f1->getName());
        lloc = new Location(fpRelative, 4, "this");
        generator->GenStore(lloc, rloc, 4 * instOff);*/
    } else if (lcheck) {
        lloc = lcheck->EmitButReturnReference(generator, count);
        generator->GenStore(lloc, rloc);
    } else {
        lloc = left->Emit(generator, count);
        generator->GenAssign(lloc, rloc);
    }
    return lloc;

}

Location* FieldAccess::Emit(CodeGenerator *generator, int *count) {
    
    Expr *expr = NULL;
    Location *loc = NULL;

    getFieldDeclaration(generator);

    if (dynamic_cast<This*>(base) != NULL) {
        if (isClassVar()) { // use ThisPtr ?
            int instOff = getParentClass()->getVarOffset(generator, field->getName());
            //printf("offset for %s %i\n", field->getName(), instOff);
            return generator->GenLoad(new Location(fpRelative, 0, "this"), 4*(instOff));
        }
    }

    if (base) {

        char *tempName;
        // CALLING VARIABLE THAT BELONGS TO AN OBJECT OR ARRAY
        ArrayAccess *arrayAccess = dynamic_cast<ArrayAccess*>(base);
        FieldAccess *baseField = dynamic_cast<FieldAccess*>(base);

        VarDecl *varDecl;
        ClassDecl *classDecl;
        Location *locc;

        if (arrayAccess) {
            varDecl = dynamic_cast<VarDecl*>(arrayAccess->getFieldDeclaration(generator));
            tempName = varDecl->getName();
            locc = arrayAccess->Emit(generator, count);
        } else if (baseField) {
            varDecl = dynamic_cast<VarDecl*>(baseField->getFieldDeclaration(generator));
            tempName = baseField->getName();
            locc = varDecl->Emit(generator, count);
        }
        if (varDecl) classDecl = generator->findClassDecl(varDecl->getTypeName());
        if (classDecl) {
            int instOff = classDecl->getVarOffset(generator, tempName);
            return generator->GenLoad(locc, 4 * (instOff + 1));
        }

    } else { // NO BASE

        if (isLocal()) {
            //printf("get local %s with offset %i\n", getName(), offset);
            return declaration->Emit(generator, count);
        }
        if (isParam()) {
            //printf("get param %s with offset %i\n", getName(), offset);
            return new Location(fpRelative, 4 + (4 * offset), field->getName());
        }
        if (isGlobal()) {
            //printf("get global %s with offset %i\n", getName(), offset);
            return declaration->Emit(generator, count);
        }
        if (isClassVar()) {
            int instOff = getParentClass()->getVarOffset(generator, field->getName());
            //printf("offset for %s %i\n", field->getName(), instOff);
            return generator->GenLoad(new Location(fpRelative, 0, "this"), 4 * (instOff)); // +1 (skip vtable pointer)
            //return generator->GenLoad(generator->ThisPtr, 4 * instOff);
        }

    }

    return loc;
}

FnDecl* Call::getFnDcel(CodeGenerator *generator) {
    if (theFnDecl) return theFnDecl;
    FnDecl *fnDecl;
    VarDecl *varDecl;
    ClassDecl *classDecl;
    FieldAccess *baseField;
    if (base) {
        baseField = dynamic_cast<FieldAccess*>(base);
        if (!baseField) return NULL;
        varDecl = dynamic_cast<VarDecl*>(baseField->getFieldDeclaration(generator));
        if (!varDecl) return NULL;
        classDecl = generator->findClassDecl(varDecl->getTypeName());
        if (!classDecl) return NULL;
        fnDecl = dynamic_cast<FnDecl*>(classDecl->getDeclFromClass(generator, field->getName()));
        if (!fnDecl) return NULL;
        theFnDecl = fnDecl;
        return theFnDecl;
    } else {
        classDecl = field->getParentClass();
        if (classDecl) {
            FnDecl *fnDecl = dynamic_cast<FnDecl*>(classDecl->getDeclFromClass(generator, field->getName()));
            if (fnDecl) {
                theFnDecl = fnDecl;
                return theFnDecl;
            }
        }
        fnDecl = generator->findGlobalFnDecl(field);
        if (fnDecl) {
            theFnDecl = fnDecl;
            return theFnDecl;
        }
    }
    return NULL;
}

// you should break up these unwieldy swamps of code and make some helper functions

Location* Call::Emit(CodeGenerator *generator, int *count) {
    int index = 0;
    FnDecl *fnDecl = NULL;
    VarDecl *varDecl = NULL;
    ClassDecl *classDecl = NULL;
    FieldAccess *baseField = dynamic_cast<FieldAccess*>(base);
    ArrayAccess *arrayAccess = NULL;
    Location *loc = NULL, *loc1 = NULL, *param = NULL;
    bool hasReturn; // does the function being called return a value?
    for (int i = actuals->NumElements() -1; i >= 0; i--) { // PUSH PARAMETERS
        arrayAccess = dynamic_cast<ArrayAccess*>(actuals->Nth(i));
        generator->GenPushParam(actuals->Nth(i)->Emit(generator, count));
    }
    // CALLING A CLASS FUNCTION FROM WITHIN A CLASS; OR A REGULAR GLOBAL FUNCTION
    if ((base == NULL) | (dynamic_cast<This*>(base) != NULL)) {
        char buffer[100];
        classDecl = getParentClass(); // IF IT'S CALLED IN A CLASS
        if (classDecl) {
            fnDecl = dynamic_cast<FnDecl*>(classDecl->getDeclFromClass(generator, field->getName()));
            if (fnDecl) {
                sprintf(buffer, "%s.%s\n", fnDecl->getParentClass()->getName(), field->getName());
            }
        }
        if (fnDecl == NULL) {       // GLOBAL FUNCTIONS
            fnDecl = generator->findGlobalFnDecl(field);
            sprintf(buffer, "%s\n", field->getName());
        } // printf("name is %s\n", buffer);
        if (fnDecl) { // GET THE RETURN VALUE
            hasReturn = fnDecl->hasReturn();
            loc = generator->GenLCall(buffer, hasReturn);
            if (loc) {
                if (actuals->NumElements() > 0) {
                    generator->GenPopParams(4 * actuals->NumElements());
                }
            }
            return loc;
        }
    } else if (base) {   // CLASS.CALL()
        if (isArrayLengthCall()) { // IF IT'S AN ARRAY LENGTH CHECK
            Location *arraySize = generator->GenLoad(base->Emit(generator, count), -4);
            return arraySize;
        }

        arrayAccess = dynamic_cast<ArrayAccess*>(base);

        if (arrayAccess) { // REDUNDANT IF ELSE BLOCK (easy to fix, just no superclass for the call)
            varDecl = dynamic_cast<VarDecl*>(arrayAccess->getFieldDeclaration(generator));
        } else if (baseField) {
            varDecl = dynamic_cast<VarDecl*>(baseField->getFieldDeclaration(generator));
        }

        if (varDecl) { // THEN GET THE CLASS
            //printf("%s\n ",varDecl->getTypeName());
            classDecl = generator->findClassDecl(varDecl->getTypeName());
        }
        if (classDecl) { // 
            fnDecl = dynamic_cast<FnDecl*>(classDecl->getDeclFromClass(generator, field->getName()));
            //if (fnDecl)printf("array sssss: %s\n", varDecl->getTypeName());
            if (fnDecl) {
                hasReturn = fnDecl->hasReturn();
            }
            for (; index < classDecl->methodNames->NumElements(); index++) {
                if (strcmp(classDecl->methodNames->Nth(index), field->getName()) == 0) break;
            }
            bool tog = true;
            if (baseField) {
                if (baseField->isParam()) {
                    loc1 = new Location(fpRelative, 8 + (4 * baseField->offset), field->getName());
                    generator->GenPushParam(loc1);
                    param = generator->GenLoad(loc1, 4 * index);
                    tog = false;//printf("%s\n ",varDecl->getTypeName());
                }
            }
            if (arrayAccess) {

                loc1 = arrayAccess->Emit(generator, count);
                param = generator->GenLoad(loc1, 4 * index);
                generator->GenPushParam(loc1);
            } else if (tog) {
                
                loc1 = generator->GenLoad(varDecl->Emit(generator, count));
                param = generator->GenLoad(loc1, 4 * index);
                generator->GenPushParam(varDecl->Emit(generator, count));
            }

            loc = generator->GenACall(param, hasReturn);
            generator->GenPopParams(4 * (actuals->NumElements() + 1)); // +1 for "this" param
        }
    }
    return loc;
}

bool Call::isInt(CodeGenerator *generator) {
    if (isArrayLengthCall()) return true;
    FnDecl *fnDecl = getFnDcel(generator);
    return fnDecl ? fnDecl->isInt() : false;
}

bool Call::isBool(CodeGenerator *generator) {
    FnDecl *fnDecl = getFnDcel(generator);
    return fnDecl ? fnDecl->isBool() : false;
}

bool Call::isString(CodeGenerator *generator) {
    FnDecl *fnDecl = getFnDcel(generator);
    return fnDecl ? fnDecl->isString() : false;
}

Location* This::Emit(CodeGenerator *generator, int *count) {
    //printf("THIS\n");
    return new Location(fpRelative, 4, "this");
}

Location* NewExpr::Emit(CodeGenerator *generator, int *count) {
    currentType = cType;
    parentClass = generator->findClassDecl(cType->getName());
    Location *label, *memSize, *ptr;
    int num = parentClass->varList->NumElements();
    memSize = generator->GenLoadConstant(4 * (num + 1));
    ptr = generator->GenBuiltInCall(Alloc, memSize);
    label = generator->GenLoadLabel(cType->getName());
    generator->GenStore(ptr, label);
    return ptr;
}

bool Call::isArrayLengthCall() {
    return (base && (base->isArray()) && (strcmp(field->getName(), "length") == 0));
}

/************************************************************************************/
/************************************************************************************/

IntConstant::IntConstant(yyltype loc, int val) : Expr(loc) {
    value = val;
}

DoubleConstant::DoubleConstant(yyltype loc, double val) : Expr(loc) {
    value = val;
}

BoolConstant::BoolConstant(yyltype loc, bool val) : Expr(loc) {
    value = val;
}

StringConstant::StringConstant(yyltype loc, const char *val) : Expr(loc) {
    Assert(val != NULL);
    value = strdup(val);
}

Operator::Operator(yyltype loc, const char *tok) : Node(loc) {
    Assert(tok != NULL);
    strncpy(tokenString, tok, sizeof(tokenString));
}
CompoundExpr::CompoundExpr(Expr *l, Operator *o, Expr *r) 
  : Expr(Join(l->GetLocation(), r->GetLocation())) {
    Assert(l != NULL && o != NULL && r != NULL);
    (op=o)->SetParent(this);
    (left=l)->SetParent(this); 
    (right=r)->SetParent(this);
}

CompoundExpr::CompoundExpr(Operator *o, Expr *r) 
  : Expr(Join(o->GetLocation(), r->GetLocation())) {
    Assert(o != NULL && r != NULL);
    left = NULL; 
    (op=o)->SetParent(this);
    (right=r)->SetParent(this);
}
   
  
ArrayAccess::ArrayAccess(yyltype loc, Expr *b, Expr *s) : LValue(loc) {
    (base=b)->SetParent(this); 
    (subscript=s)->SetParent(this);
}
     
FieldAccess::FieldAccess(Expr *b, Identifier *f) 
  : LValue(b? Join(b->GetLocation(), f->GetLocation()) : *f->GetLocation()) {
    Assert(f != NULL); // b can be be NULL (just means no explicit base)
    base = b; 
    if (base) base->SetParent(this); 
    (field=f)->SetParent(this);
}


Call::Call(yyltype loc, Expr *b, Identifier *f, List<Expr*> *a) : Expr(loc)  {
    Assert(f != NULL && a != NULL); // b can be be NULL (just means no explicit base)
    base = b;
    if (base) base->SetParent(this);
    (field=f)->SetParent(this);
    (actuals=a)->SetParentAll(this);
}
 
NewExpr::NewExpr(yyltype loc, NamedType *c) : Expr(loc) { 
  Assert(c != NULL);
  (cType=c)->SetParent(this);
}


NewArrayExpr::NewArrayExpr(yyltype loc, Expr *sz, Type *et) : Expr(loc) {
    Assert(sz != NULL && et != NULL);
    (size=sz)->SetParent(this); 
    (elemType=et)->SetParent(this);
}

       
