%{
#include <stdlib.h>
#include <stdio.h>
int yyerror(char *s);
int yylex(void);
%}

%union {
    char* str;
    char chr;
    int integer;
}

%error-verbose
%token AND_OP
%token OR_OP
%token NOT_OP
%token EQ_OP
%token LT_EQ_OP
%token GT_EQ_OP
%token GT_OP
%token LT_OP
%token NE_EQ_OP
%token PLUS_OP
%token MINUS_OP
%token DIV_OP
%token MOD_OP
%token MULT_OP
%token ASSIGN_OP
%token DEFINE_OP
%token ANGLE_OP
%token TILDA_OP
%token CHAR_KEY
%token ORD_KEY
%token PRED_KEY
%token SUCC_KEY
%token FORWARD_KEY
%token PROD_KEY
%token VAR_KEY
%token REF_KEY
%token BEGIN_KEY
%token END_KEY
%token TYPE_KEY
%token RECORD_KEY
%token ARRAY_KEY
%token IF_KEY
%token THEN_KEY
%token ELSE_IF_KEY
%token ELSE_KEY
%token WHILE_KEY
%token DO_KEY
%token REPEAT_KEY
%token UNTIL_KEY
%token FOR_KEY
%token TO_KEY
%token DOWN_TO_KEY
%token STOP_KEY
%token RETURN_KEY
%token READ_KEY
%token WRITE_KEY
%token CONST_KEY
%token DOT
%token SEMI_COL
%token OPEN_PAR
%token CLOSE_PAR
%token COL
%token OPEN_SQ
%token CLOSE_SQ
%token COMMA
%token IDENTIFIER


%left AND_OP OR_OP
%right NOT_OP
%nonassoc EQ_OP LT_EQ_OP GT_EQ_OP GT_OP LT_OP NE_EQ_OP
%left PLUS_OP MINUS_OP
%left DIV_OP MOD_OP MULT_OP
%right UMINUS_OP

%start program

%%
program: progHead block DOT
    ;

progHead: optConstDecl
    | optTypeDecl
    | optVarDecl
    | procedureDecl
    | functionDecl
    ;

optConstDecl: constDecls
    | 
    ;

constDecls: CONST_KEY constDecls
    | CONST_KEY constDecl
    ;

constDecl: identifier ASSIGN_OP expression
    ;

procedureDecl: procedureSig FORWARD_KEY SEMI_COL
    | procedureSig body SEMI_COL
    ;

procedureSig: PROD_KEY identifier OPEN_PAR formalParameters CLOSE_PAR SEMI_COL
    ;

functionDecl: functionSig FORWARD_KEY SEMI_COL
    | functionSig body SEMI_COL
    ;

functionSig: FUNC_KEY identifier OPEN_PAR formalParameters CLOSE_PAR COL type SEMI_COL
    ;

formalParameters: formalParameters SEMI_COL formalParameter
    |
    ;

formalParameter: optVar identifierList COL type
    ;

optVar: VAR_KEY
    | REF_KEY
    ;

body: optConstDecl
    | optTypeDecl
    | optVarDecl
    | block
    ;

block: BEGIN_KEY statementList END_KEY
    ;

optTypeDecl: typeDecls
    |
    ;

typeDecls: TYPE_KEY typeDecls
    | TYPE_KEY typeDecl
    ;

typeDecl: identifier ASSIGN_OP type SEMI_COL
    ;

type: simpleType
    | recordType
    | arrayType
    ;

simpleType: identifier
    ;

recordType: RECORD_KEY optRecordTypeParams END_KEY
    ;

optRecordTypeParams: recordTypeParams
    |
    ;

recordTypeParams: recordTypeParams
    | recordTypeParam
    ;

recordTypeParam: identifierList COL type SEMI_COL
    ;

arrayType: ARRAY_KEY OPEN_SQ expression COL expression CLOSE_SQ of type
    ;

identifierList: identifierList COMMA
    | identifier
    ;

identifier: IDENTIFIER
    ;

optVarDecl: varDecls
    |
    ;

varDecls: VAR_KEY varDecls
    | VAR_KEY varDecl
    ;

varDecl: identifierList COL type SEMI_COL
    ;

statementList: statementList SEMI_COL
    | statement
    ;

statement: assignment
    | ifStatement
    | whileStatement
    | repeatStatement
    | forStatement
    | stopStatement
    | returnStatement
    | readStatement
    | writeStatement
    | procedureCall
    | nullStatement
    ;

assignment: lvalue DEFINE_OP expression
    ;

ifStatement: IF_KEY expression THEN_KEY statementList optElsifs optElse END_KEY
    ;

optElsifs: elseIfStatements
    |
    ;

elseIfStatements: elseIfStatements
    : elseIfStatement
    ;

elseIfStatement: ELSE_IF_KEY expression THEN_KEY statementList
    ;

optElse: elseStatement
    |
    ;

elseStatement: ELSE_KEY statementList
    ;

whileStatement: WHILE_KEY expression DO_KEY statementList END_KEY
    ;

repeatStatement: REPEAT_KEY statementList UNTIL_KEY expression
    ;

forStatement: FOR_KEY identifier DEFINE_OP expression optTo expression DO_KEY statementList END_KEY
    ;

optTo: TO_KEY
    | DOWN_TO_KEY
    ;

stopStatement: STOP_KEY
    ;

returnStatement: RETURN_KEY optExpression
    ;

readStatement: READ_KEY OPEN_PAR lvalueList CLOSE_PAR
    ;

writeStatement: WRITE_KEY OPEN_PAR expressionList CLOSE_PAR
    ;

procedureCall: identifier OPEN_PAR optExpressionList CLOSE_PAR

nullStatement:
    ;

optExpressionList: expressionList
    |
    ;

expressionList: expressionList COMMA
    | expression
    ;

optExpression: expression
    |
    ;

expression: expression OR_OP expression
    | expression AND_OP expression
    | expression ASSIGN_OP expression
    | expression ANGLE_OP expression
    | expression LT_EQ_OP expression
    | expression GT_EQ_OP expression
    | expression LT_OP expression
    | expression GT_OP expression
    | expression PLUS_OP expression
    | expression MINUS_OP expression
    | expression MULT_OP expression
    | expression DIV_OP expression
    | expression MOD_OP expression
    | TILDA_OP expression
    | MINUS_OP expression %pred UMINUS_OP
    | OPEN_PAR expression CLOSE_PAR
    | identifier OPEN_PAR optExpressionList CLOSE_PAR
    | CHAR_KEY OPEN_PAR expression CLOSE_PAR
    | ORD_KEY OPEN_PAR expression CLOSE_PAR
    | PRED_KEY OPEN_PAR expression CLOSE_PAR
    | SUCC_KEY OPEN_PAR expression CLOSE_PAR
    | lvalue
    ;

lvalueList: lvalueList COMMA
    | lvalue
    ;

lvalue: lvalue DOT identifier
    | lvalue OPEN_SQ expression CLOSE_SQ
    | identifier
    ;

%%

int yyerror(char* s){
    extern int yylineno;
    extern int yycolno;
    extern char* yytext;
    printf("ERROR: Incorrect value \"%s\" on line %d column %d\n", yytext, yylineno, yycolno);
    exit(1);
}