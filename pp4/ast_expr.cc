/* File: ast_expr.cc
 * -----------------
 * Implementation of expression node classes. 
 */
#include "ast_expr.h"
#include "ast_type.h"
#include "ast_decl.h"
#include <string.h>

#include "errors.h"

Type* NewExpr::getType() {
  return cType;
}

void NewExpr::Check() {
    Decl *d;
    if (!cType->GetDeclForType()) {
        ReportError::IdentifierNotDeclared(cType->GetId(), LookingForClass);
        StoreExprError();
    }
    d = cType->GetDeclForType();
    if (d && !d->IsClassDecl()) {
        ReportError::IdentifierNotDeclared(cType->GetId(), LookingForClass);
        StoreExprError();
    }
}

void NewArrayExpr::Check() {
    if (!size->getType()->IsEquivalentTo(Type::intType)) {
        if (!StoreExprError())
        ReportError::NewArraySizeNotInteger(size);
    }
    elemType->Check();
}

void Call::Check() {
    FnDecl *fnDecl = NULL;
    Type *baseType = NULL;
    NamedType *namedType = NULL;
    for (int i=0; i<actuals->NumElements(); i++) {
        actuals->Nth(i)->Check();
    }
    if (base) {
        base->Check();
        baseType = base->getType();
        if (baseType) {
            //printf("null\n");
            baseType->print();
            namedType = dynamic_cast<NamedType*>(baseType);
            if (!namedType) {
                if (!(baseType->IsArrayType() && field->isLengthId())) {
                    ReportError::FieldNotFoundInBase(field, baseType);
                }
            } else {
                Decl *typeDecl = namedType->GetDeclForType();
                if (typeDecl) {
                    fnDecl = typeDecl->getClassFn(field);
                }
            }
        }
    } else {
        fnDecl = dynamic_cast<FnDecl*>(field->Check(LookingForFunction));
    }
    if (fnDecl) {
        fnDecl->CheckActualsAgainstFormals(field, actuals);
    } else if (base) {
        Type *t = base->getType();
        if (!(t->IsArrayType() && field->isLengthId()) &&
            (!t->IsNamedType() || dynamic_cast<NamedType*>(t)->GetDeclForType())) {
                ReportError::FieldNotFoundInBase(field, t);
            
        }
    }
}


Type* Call::getType() {
    Type *baseType = NULL;
    NamedType *namedType = NULL;
    ClassDecl *classDecl = NULL;
    FnDecl *fnDecl = NULL;
    if (base) {
        baseType = base->getType();
        if (!baseType) {
            //printf("1\n");
            return NULL;
        }
        //printf("2\n");
        baseType->print();
        namedType = dynamic_cast<NamedType*>(baseType);
        if (!namedType) {
            if (!(baseType->IsArrayType() && field->isLengthId())) {
                ReportError::FieldNotFoundInBase(field, baseType);
            }
        } else {
            //printf("3\n");
            classDecl = dynamic_cast<ClassDecl*>(namedType->GetDeclForType());
            if (classDecl) {
                fnDecl = classDecl->getClassFn(field);
                if (fnDecl) {
                    return fnDecl->GetDeclaredType();
                } else {
                    if (true) {
                        ReportError::FieldNotFoundInBase(field, base->getType());
                    }
                }
            }
        }
    } else {
        fnDecl = dynamic_cast<FnDecl*>(FindDecl(field));
        if (fnDecl) {
            //printf("6\n");
            return fnDecl->GetDeclaredType();
        }
    }
    return NULL;
}

void FieldAccess::Check() {
    //printf("field check\n");
    if (!base) {
        field->getType();
        field->Check(LookingForVariable);
    } else {
        Type *baseType = NULL;
        ClassDecl *classDecl = NULL;
        NamedType *namedType = NULL;
        VarDecl *varDecl = NULL;
        base->Check();
        baseType = base->getType();
        if (!baseType) {
            return;
        }
        namedType = dynamic_cast<NamedType*>(baseType);
        if (!namedType) {
            //if (!StoreExprError()) {
            if (true) {
                ReportError::FieldNotFoundInBase(field, baseType);
                StoreExprError();
                return;
            }
        }
        classDecl = dynamic_cast<ClassDecl*>(namedType->GetDeclForType());
        if (!classDecl) {
            return;
        }
        varDecl = classDecl->getClassVar(field);
        if (!varDecl) {
            if (true) {
                ReportError::FieldNotFoundInBase(field, base->getType());
                StoreExprError();
            }
        } else {
            ClassDecl *classierDecl = FindParentClass();
            if (!classierDecl || !classDecl->hasSameId(classierDecl->GetId())) {
                if (true) {
                    ReportError::InaccessibleField(field, base->getType());
                    StoreExprError();
                }
            }
        }
    }
}

Type* FieldAccess::getType() {
    return field->getType();
}

void ArrayAccess::Check() {
    if (!base->getType()->IsArrayType()) {
        if (!StoreExprError())
        ReportError::BracketsOnNonArray(base);
    }
    if (!subscript->getType()->IsEquivalentTo(Type::intType)) {
        if (!StoreExprError())
        ReportError::SubscriptNotInteger(subscript);
    }
}

void LValue::Check() {
    //printf("lvalue check\n");
    /*void Identifier::Check() {
        cached = FindDecl(this);
        if (!cached)
            ReportError::IdentifierNotDeclared(this, LookingForFunction);
    }*/

}

void This::Check() {
    if (!FindParentClass()) {
        if (!StoreExprError())
        ReportError::ThisOutsideClassScope(this);
    }
}

void CompoundExpr::Check() {
    if (left) {
        left->Check();
    } else {
        if (op->isUnaryNot()) {
            if (!right->getType()->IsEquivalentTo(Type::boolType)) {
                if (!StoreExprError()) {
                    ReportError::IncompatibleOperand(op, right->getType());
                }
            }
        }
        else if (op->isUnaryMinus()) {

        }
    }
    right->Check();
    if (left) {
        Type *t1 = left->getType();
        Type *t2 = right->getType();
        if (t1 == NULL || t2 == NULL) {
            return;
        }
        if (t1->IsNamedType() && t2->IsNamedType()) {
            Decl *d1 = dynamic_cast<NamedType*>(t1)->GetDeclForType();
            Decl *d2 = dynamic_cast<NamedType*>(t2)->GetDeclForType();
            if ((dynamic_cast<AssignExpr*>(this) != NULL) && d1 && d2) {
                if (d2->isChildOf(d1)) {
                    return;
                }
            }
            if ((dynamic_cast<EqualityExpr*>(this) != NULL) && d1 && d2) {
                if (d1->isChildOf(d2) || d2->isChildOf(d1)) {
                    return;
                }
            }
        }
        if (!t1->IsEquivalentTo(t2) && !StoreExprError() &&
// can assign or compare against null (but shouldn't it be Type::nullType?)
!((dynamic_cast<EqualityExpr*>(this) != NULL || dynamic_cast<AssignExpr*>(this) != NULL) 
                && t2->isNullType())) {
            //if (dynamic_cast<AssignExpr*>(this) || ) {
                StoreExprError();
                ReportError::IncompatibleOperands(op, left->getType(), right->getType());
            
        }
        t1->print();
        t2->print();
    }
}

Type* CompoundExpr::getType() {
    if (dynamic_cast<EqualityExpr*>(this) != NULL) {
        return Type::boolType;
    }
    if (dynamic_cast<RelationalExpr*>(this) != NULL) {
        return Type::boolType;
    }
    if (dynamic_cast<LogicalExpr*>(this) != NULL) {
        return Type::boolType;
    }
    if (left) {
        return left->getType();
    }
    return right->getType();
}

Type* ArrayAccess::getType() {
    Expr *temp = base;
    FieldAccess *fieldAccess = dynamic_cast<FieldAccess*>(base);
    if (fieldAccess != NULL) {
        VarDecl *varDecl = dynamic_cast<VarDecl*>(fieldAccess->getFieldDecl());
        if (varDecl != NULL) {
            ArrayType *arrayType = dynamic_cast<ArrayType*>(varDecl->GetDeclaredType());
            if (arrayType) {
                return arrayType->getType();
            }
        }
    }
    return NULL;
}

/******************************************************************************************************/

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

       
