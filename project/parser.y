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

%token <integer> INTEGER
%token <str> OCTAL
%token <str> HEX
%token <str> STRING
%token <chr> CHAR
%token <str> KEYWORD
%token <str> IDENTIFIER
%token <str> OPERATOR

%start program

%%
program: progHead block DOT_OP
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

constDecls: constDecls
    | constDecl
    ;

constDecl: CONST_KEY identifier ASSIGN_OP expression
    ;

procedureDecl: PROD_KEY identifier OPEN_PAR formalParameters CLOSE_PAR SEMI_COL FORWARD_KEY SEMI_COL
    | PROD_KEY identifier OPEN_PAR formalParameters CLOSE_PAR SEMI_COL body SEMI_COL
    ;

functionDecl: FUNC_KEY identifier OPEN_PAR formalParameters CLOSE_PAR COL type SEMI_COL FORWARD_KEY SEMI_COL
    | FUNC_KEY identifier OPEN_PAR formalParameters CLOSE_PAR COL type SEMI_COL body SEMI_COL
    ;

formalParameters: formalParameters SEMI_COL formalParameter
    |
    ;

formalParameter: optVar identifierList COL type
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
    | typeDecl
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

optVarDecl: varDecl
    |
    ;

varDecls: VAR_KEY varDecls
    | varDecl
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
    | MINUS_OP expression
    | OPEN_PAR expression CLOSE_PAR
    | identifier OPEN_PAR optExpressionList CLOSE_PAR
    | CHAR_KEY OPEN_PAR expression CLOSE_PAR
    | ORD_KEY OPEN_PAR expression CLOSE_PAR
    | PRED_KEY OPEN_PAR expression CLOSE_PAR
    | SUCC_KEY OPEN_PAR expression CLOSE_PAR
    | lvalue
    ;

optLvalueList: lvalueList 
    |
    ;

lvalueList: lvalueList COMMA
    | lvalue
    ;

lvalue: identifier optLvalueParams
    ;

optLvalueParams: lvalueParams
    |
    ;

lvalueParams: lvalueParams
    | lvalueParam
    ;

lvalueParam: DOT_OP identifier
    | OPEN_SQ expression CLOSE_SQ
    ;

%%

int yyerror(char* s){
    extern int yylineno;
    extern int yycolno;
    extern char* yytext;
    printf("ERROR: Incorrect value \"%s\" on line %d column %d\n", yytext, yylineno, yycolno);
    exit(1);
}