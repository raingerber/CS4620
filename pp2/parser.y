/* File: parser.y
 * --------------
 * Yacc input file to generate the parser for the compiler.
 *
 * pp2: your job is to write a parser that will construct the parse tree
 *      and if no parse errors were found, print it.  The parser should 
 *      accept the language as described in specification, and as augmented 
 *      in the pp2 handout.
 */

%{

/* Just like lex, the text within this first region delimited by %{ and %}
 * is assumed to be C/C++ code and will be copied verbatim to the y.tab.c
 * file ahead of the definitions of the yyparse() function. Add other header
 * file inclusions or C++ variable declarations/prototypes that are needed
 * by your code here.
 */
#include "scanner.h" // for yylex
#include "parser.h"
#include "errors.h"

void yyerror(const char *msg); // standard error-handling routine

%}

/* The section before the first %% is the Definitions section of the yacc
 * input file. Here is where you declare tokens and types, add precedence
 * and associativity options, and so on.
 */
 
/* yylval 
 * ------
 * Here we define the type of the yylval global variable that is used by
 * the scanner to store attibute information about the token just scanned
 * and thus communicate that information to the parser. 
 *
 * pp2: You will need to add new fields to this union as you add different 
 *      attributes to your non-terminal symbols.
 */
 
%union {
    int integerConstant;
    bool boolConstant;
    char *stringConstant;
    double doubleConstant;
    char identifier[MaxIdentLen+1]; // +1 for terminating null
    Decl *decl;
    VarDecl *var;
    FnDecl *fDecl;
    Type *type;
    Stmt *stmt;
    List<Stmt*> *stmtList;
    List<VarDecl*> *varList;
    List<Decl*> *declList;
    
    
    /* ast_stmt */
    Program *program;
    StmtBlock *stmtBlock;
    ConditionalStmt *conditionalStmt;
    ForStmt *forStmt;
    WhileStmt *whileStmt;
    IfStmt *ifStmt;
    BreakStmt *breakStmt;
    ReturnStmt *returnStmt;
    PrintStmt *printStmt;
    /* ast_decl */
    ClassDecl *classDecl;
    InterfaceDecl *interfaceDecl;
    /* ast_expr */
    BoolConstant *boolConst;
    
    EmptyExpr *emptyExpr;
    /* ast_type */
    
    /*stopped categorizing*/
    Expr *expr;
    List<Expr*> *exprList;
    Call *call;
    LValue *lvalue;
    NamedType *namedType;
    List<NamedType*> *namedTypeList;
    
    PostfixExpr *postfixExpr;
    /*
    SwitchStmt *switchStmt;
    Case *switchCase;
    DefaultStmt *defaultStmt;
    */
}

/************************************** TOKENS **************************************/
%token   T_Void T_Bool T_Int T_Double T_String T_Class 
%token   T_Dims                                                   //T_LessEqual T_GreaterEqual T_Equal T_NotEqual 
%token   T_Null T_Extends T_This T_Interface T_Implements         //T_And T_Or
%token   T_While T_For T_If T_Return T_Break                      //T_Else 
%token   T_New T_NewArray T_Print T_ReadInteger T_ReadLine
/************************************************************************************/
%token   <identifier> T_Identifier
%token   <stringConstant> T_StringConstant 
%token   <integerConstant> T_IntConstant
%token   <doubleConstant> T_DoubleConstant
%token   <boolConstant> T_BoolConstant
/************************************************************************************/

/* STILL NEEDS THE UNARY OPERATOR */

%nonassoc  '='
%left      T_Or
%left      T_And
%nonassoc  T_Equal T_NotEqual
%nonassoc  '<' T_LessEqual '>' T_GreaterEqual
%left      '+' '-'  
%left      '*' '/' '%'
%left      '!' UNARY T_PostIncrement T_PostDecrement
%left      '[' '.'
%left      IFBLOCKDONE
%left      T_Else

//%token T_SwitchStmt T_CaseStmt T_Default
/*********************** Non-terminal types ********************/
%type <declList>  DeclList                         ProtoLsBegin ProtoList FieldList
%type <decl>      Decl                             Field
%type <type>      Type 
%type <var>       Variable VarDecl
%type <varList>   Formals FormalList VarDecls      
%type <fDecl>     FnDecl FnHeader                  Prototype
%type <stmtList>  StmtList                         StmtListRpt       
// SwitchBlock SwitchCases SwitchBody MaybeBreak
%type <stmt>      StmtBlock                        
/*
%type <switchStmt>          SwitchStmt
%type <switchCase>          SwitchCase
%type <defaultStmt>         DefaultStmt*/
/***************************************************************/
%type <stmt>                Stmt ElseStmt          
%type <breakStmt>           BreakStmt
%type <ifStmt>              IfStmt
%type <returnStmt>          ReturnStmt
%type <printStmt>           PrintStmt
%type <forStmt>             ForStmt
%type <whileStmt>           WhileStmt
%type <classDecl>           ClassDecl
%type <interfaceDecl>       InterfaceDecl
%type <exprList>            ExprList Actuals
%type <expr>                Expr PossExpr Constant
%type <call>                Call
%type <lvalue>              LValue
%type <namedType>           ExtClause
%type <namedTypeList>       ImpClause IdList
/***************************************************************/
%%
Program   :    DeclList            { 
                                      @1; 
                                      /* pp2: The @1 is needed to convince 
                                       * yacc to set up yylloc. You can remove 
                                       * it once you have other uses of @n*/
                                      Program *program = new Program($1);
                                      // if no errors, advance to next phase
                                      if (ReportError::NumErrors() == 0) 
                                          program->Print(0);
                                    }
;

DeclList  :    DeclList Decl        { ($$ = $1)->Append($2); }
          |    Decl                 { ($$ = new List<Decl*>)->Append($1); }
;

Decl      :    VarDecl              { $$ = $1; }
          |    FnDecl               { $$ = $1; }
          |    ClassDecl            { $$ = $1; }
          |    InterfaceDecl        { $$ = $1; } 
;

VarDecl   :    Variable ';'         { $$ = $1; }
; 

Variable  :    Type T_Identifier    { $$ = new VarDecl(new Identifier(@2, $2), $1); }
;

Type      :    T_Int                { $$ = Type::intType; }
          |    T_Double             { $$ = Type::doubleType; }
          |    T_Bool               { $$ = Type::boolType; }
          |    T_String             { $$ = Type::stringType; }
          |    T_Identifier         { $$ = new NamedType(new Identifier(@1,$1)); }
          |    Type T_Dims          { $$ = new ArrayType(Join(@1, @2), $1); }
;

FnDecl    :    FnHeader StmtBlock   { ($$ = $1)->SetFunctionBody($2); }
;

FnHeader  :    Type T_Identifier '(' Formals ')'      { $$ = new FnDecl(new Identifier(@2, $2), $1, $4); }
          |    T_Void T_Identifier '(' Formals ')'    { $$ = new FnDecl(new Identifier(@2, $2), Type::voidType, $4); }
;

Formals   :    FormalList                 { $$ = $1; }
          |    /* empty */                { $$ = new List<VarDecl*>; }
;

FormalList:    FormalList ',' Variable    { ($$ = $1)->Append($3); }
          |    Variable                   { ($$ = new List<VarDecl*>)->Append($1); }
;

StmtBlock :    '{' VarDecls StmtList '}'  { $$ = new StmtBlock($2, $3); } 
;


VarDecls  :    VarDecls VarDecl           { ($$ = $1)->Append($2); }
          |    /* empty*/                 { $$ = new List<VarDecl*>; }
;

/******************    MY WORK STARTS HERE   ***************************/
// SwitchStmt SwitchCase DefaultStmt
// SwitchBlock SwitchCases SwitchBlock MaybeBreak
/*
SwitchStmt   : T_SwitchStmt Expr ':' SwitchBlock                     { $$ = new SwitchStmt($2, $4); }                    // switchstmt 
;

SwitchBlock   : SwitchCases DefaultStmt                              { (($$ = new List<Stmt*>)->Append($1))->Append($2); }
;

SwitchCases  : SwitchCase                                            { $$ = $1; }
             | SwitchCases SwitchCase                                { ($$ = $1)->Append($2) }
;

SwitchCase   : T_CaseStmt T_IntConstant ':' SwitchBody               { $$ = new SwitchCase(new IntConstant(@2, $2), $4); }
;

DefaultStmt  : T_Default ':' SwitchBody                              { ($$ = new DefaultStmt($3); }*/
//             | /* empty */                                           { ($$ = new DefaultStmt(new List<Stmt*>); };

//SwitchBody   : StmtList MaybeBreak                                   { (($$ = new List<Stmt*>)->Append($1))->Append($2); }  
//             | /* empty */                                           { $$ = new List<Stmt*>; };

//MaybeBreak   : BreakStmt ';'                                         { ($$ = new List<Stmt*>)->Append($1); }
//             | /* empty */                                           { $$ = new List<Stmt*>; };

/*********************************************************************************************************************** switch block over */

StmtList    : StmtListRpt                           { $$ = $1; }
            | /* empty */                           { $$ = new List<Stmt*>; }
;

StmtListRpt : StmtListRpt Stmt                      { ($$ = $1)->Append($2); }
            | Stmt                                  { ($$ = new List<Stmt*>)->Append($1); }
;
ExprList  : Expr                                    { ($$ = new List<Expr*>)->Append($1); }
          | ExprList ',' Expr                       { ($$ = $1)->Append($3); }
;

Stmt      : Expr ';'                                { $$ = $1; }
          | IfStmt                                  { $$ = $1; }
          | WhileStmt                               { $$ = $1; }
          | ForStmt                                 { $$ = $1; }
          | BreakStmt                               { $$ = $1; }
          | ReturnStmt                              { $$ = $1; }
          | PrintStmt                               { $$ = $1; }
          | StmtBlock                               { $$ = $1; }
;

StmtList    : StmtListRpt                           { $$ = $1; }
            | /* empty */                           { $$ = new List<Stmt*>; }
;

StmtListRpt : StmtListRpt Stmt                      { ($$ = $1)->Append($2); }
            | Stmt                                  { ($$ = new List<Stmt*>)->Append($1); }
;

Constant   : T_IntConstant                          { $$ = new IntConstant(@1, $1); }
           | T_DoubleConstant                       { $$ = new DoubleConstant(@1, $1); }
           | T_BoolConstant                         { $$ = new BoolConstant(@1, $1); }
           | T_StringConstant                       { $$ = new StringConstant(@1, $1); }
           | T_Null                                 { $$ = new NullConstant(@1); }
;

IfStmt     : T_If '(' Expr ')' Stmt ElseStmt        { $$ = new IfStmt($3, $5, $6); } 
;

ElseStmt   : T_Else Stmt                            { $$ = $2; } 
           | /* empty */     %prec IFBLOCKDONE      { $$ = NULL; }
;

WhileStmt  : T_While '(' Expr ')' Stmt              { $$ = new WhileStmt($3, $5); }
;

ForStmt    : T_For '(' PossExpr ';' Expr ';' PossExpr ')' Stmt { $$ = new ForStmt($3, $5, $7, $9); }
;

ReturnStmt : T_Return PossExpr ';'                  { $$ = new ReturnStmt(@1, $2);  }
;

BreakStmt : T_Break ';'                             { $$ = new BreakStmt(@1); } 
;

PrintStmt : T_Print '(' ExprList ')' ';'            { $$ = new PrintStmt($3);  }
;

PossExpr  : Expr                                    { $$ = $1; }
          | /* empty */                             { $$ = new EmptyExpr(); }
;

Call      : T_Identifier '(' Actuals ')'            { $$ = new Call(@1, NULL, new Identifier(@1, $1), $3); }
          | Expr '.' T_Identifier '(' Actuals ')'   { $$ = new Call(@1, $1, new Identifier(@3, $3), $5); }
;

LValue    : Expr '.' T_Identifier                   { $$ = new FieldAccess($1, new Identifier(@3, $3)); }
          | Expr '[' Expr ']'                       { $$ = new ArrayAccess(@1, $1, $3); }
          | T_Identifier                            { $$ = new FieldAccess(NULL, new Identifier(@1, $1)); }
;

/* LValue '=' Expr  -- got rid of it because Expr = LValue for either side */
Expr      : T_This                                  { $$ = new This(@1); }
          | LValue T_PostIncrement                    { $$ = new PostfixExpr($1, new Operator(@1, "++")); }                  // POSTFIX EXPRESSIONS
          | LValue T_PostDecrement                    { $$ = new PostfixExpr($1, new Operator(@1, "--")); }          
          | Call                                    { $$ = $1; }
          | LValue                                  { $$ = $1; }
          | Constant                                { $$ = $1; }
	  | '(' Expr ')'                            { $$ = $2; }
	  | T_ReadInteger '(' ')'                   { $$ = new ReadIntegerExpr(@1); }
          | T_ReadLine '(' ')'                      { $$ = new ReadLineExpr(@1); }
          | T_New '(' T_Identifier ')'              { $$ = new NewExpr(@1, new NamedType(new Identifier(@3, $3))); }
          | T_NewArray '(' Expr ',' Type ')'        { $$ = new NewArrayExpr(@1, $3, $5); }
	  | Expr '=' Expr                           { $$ = new AssignExpr($1, new Operator(@2, "="), $3); }
          | Expr '+' Expr                           { $$ = new ArithmeticExpr($1, new Operator(@2, "+"), $3); }
          | Expr '-' Expr                           { $$ = new ArithmeticExpr($1, new Operator(@2, "-"), $3); }
          | Expr '*' Expr                           { $$ = new ArithmeticExpr($1, new Operator(@2, "*"), $3); }
          | Expr '/' Expr                           { $$ = new ArithmeticExpr($1, new Operator(@2, "/"), $3); }
          | Expr '%' Expr                           { $$ = new ArithmeticExpr($1, new Operator(@2, "%"), $3); }
          | Expr '<' Expr                           { $$ = new RelationalExpr($1, new Operator(@2, "<"), $3); }
          | Expr T_LessEqual Expr                   { $$ = new RelationalExpr($1, new Operator(@2, "<="), $3); }
          | Expr '>' Expr                           { $$ = new RelationalExpr($1, new Operator(@2, ">"), $3); }
          | Expr T_GreaterEqual Expr                { $$ = new RelationalExpr($1, new Operator(@2, ">="), $3); }
          | Expr T_Equal Expr                       { $$ = new EqualityExpr($1, new Operator(@2, "=="), $3); }
          | Expr T_NotEqual Expr                    { $$ = new EqualityExpr($1, new Operator(@2, "!="), $3); }
          | Expr T_And Expr                         { $$ = new LogicalExpr($1, new Operator(@2, "&&"), $3); }
          | Expr T_Or Expr                          { $$ = new LogicalExpr($1, new Operator(@2, "||"), $3); }
          | '-' Expr               %prec UNARY      { $$ = new LogicalExpr(new Operator(@1, "-"), $2); }
          | '!' Expr                                { $$ = new LogicalExpr(new Operator(@1, "!"), $2); }
;

Actuals   : /* empty */                             { $$ = new List<Expr*>; }
          | ExprList                                { $$ = $1; }
;

ExprList  : Expr                                    { ($$ = new List<Expr*>)->Append($1); }
          | ExprList ',' Expr                       { ($$ = $1)->Append($3); }
;

ClassDecl : T_Class T_Identifier ExtClause ImpClause '{' FieldList '}' { ($$ = new ClassDecl(new Identifier(@2, $2), $3, $4, $6));   }
;

ExtClause : /* empty */                             { $$ = NULL; }
          | T_Extends T_Identifier                  { $$ = new NamedType(new Identifier(@2, $2)); }
;

ImpClause : /* empty */                             { $$ = new List<NamedType*>; }
          | T_Implements IdList                     { $$ = $2; }
;

IdList    : T_Identifier                            { ($$ = new List<NamedType*>)->Append(new NamedType(new Identifier(@1, $1))); }
          | IdList ',' T_Identifier                { ($$ = $1)->Append(new NamedType(new Identifier(@3, $3))); }
;

Field     : VarDecl                                 { $$ = $1; }
          | FnDecl                                  { $$ = $1; }
;

FieldList : /* empty */                             { $$ = new List<Decl*>; }
          | FieldList Field                         { ($$ = $1)->Append($2); }
;

InterfaceDecl : T_Interface T_Identifier '{' ProtoLsBegin '}' { $$ = new InterfaceDecl(new Identifier(@2, $2), $4); }
;

Prototype     : Type T_Identifier '(' Formals ')' ';'         { $$ = new FnDecl(new Identifier(@2, $2), $1, $4); }
              | T_Void T_Identifier '(' Formals ')' ';'       { $$ = new FnDecl(new Identifier(@2, $2), Type::voidType, $4); }
;

ProtoLsBegin  : /* empty */                                   { $$ = new List<Decl*>; }  // SHOULD BE VarDecl*
              | ProtoList                                     { $$ = $1; }
;

ProtoList      : Prototype                                    { ($$ = new List<Decl*>)->Append($1); }  // SHOULD BE VarDecl*
               | ProtoList Prototype                          { ($$ = $1)->Append($2); }
;

%%

/* The closing %% above marks the end of the Rules section and the beginning
 * of the User Subroutines section. All text from here to the end of the
 * file is copied verbatim to the end of the generated y.tab.c file.
 * This section is where you put definitions of helper functions.
 */

/* Function: InitParser
 * --------------------
 * This function will be called before any calls to yyparse().  It is designed
 * to give you an opportunity to do anything that must be done to initialize
 * the parser (set global variables, configure starting state, etc.). One
 * thing it already does for you is assign the value of the global variable
 * yydebug that controls whether yacc prints debugging information about
 * parser actions (shift/reduce) and contents of state stack during parser.
 * If set to false, no information is printed. Setting it to true will give
 * you a running trail that might be helpful when debugging your parser.
 * Please be sure the variable is set to false when submitting your final
 * version.
 */
void InitParser()
{
   PrintDebug("parser", "Initializing parser");
   yydebug = false;
}
