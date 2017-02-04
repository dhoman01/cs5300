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
%token ARRAY_KEY
%token BEGIN_KEY
%token CHR_KEY
%token CONST_KEY
%token DO_KEY
%token DOWN_TO_KEY
%token ELSE_KEY
%token ELSE_IF_KEY
%token END_KEY
%token FOR_KEY
%token FORWARD_KEY
%token FUNCTION_KEY
%token IF_KEY
%token OF_KEY
%token ORD_KEY
%token PRED_KEY
%token PROCEDURE_KEY
%token READ_KEY
%token RECORD_KEY
%token REF_KEY
%token REPEAT_KEY
%token RETURN_KEY
%token STOP_KEY
%token SUCC_KEY
%token THEN_KEY
%token TO_KEY
%token TYPE_KEY
%token UNTIL_KEY
%token VAR_KEY
%token WHILE_KEY
%token WRITE_KEY
%token AND_OP
%token ASSIGN_OP
%token DIV_OP
%token EQ_OP
%token GT_OP
%token GT_EQ_OP
%token LT_OP
%token LT_EQ_OP
%token MINUS_OP
%token MOD_OP
%token MULT_OP
%token NOT_EQ_OP
%token NOT_OP
%token OR_OP
%token PLUS_OP
%token CLOSE_PAR
%token CLOSE_SQ
%token COL
%token COMMA
%token DOT
%token OPEN_PAR
%token OPEN_SQ
%token SEMI_COL
%token IDENTIFIER
%token INT_CONST
%token CHR_CONST
%token STRING_CONST


%left AND_OP OR_OP
%right NOT_OP
%nonassoc EQ_OP LT_EQ_OP GT_EQ_OP GT_OP LT_OP NOT_EQ_OP
%left PLUS_OP MINUS_OP
%left DIV_OP MOD_OP MULT_OP
%right UMINUS_OP

%type<str> IDENTIFIER

%start program

%%
program: progHead block DOT { printf("Found program\n"); }
    ;

progHead: optConstDecl
    | optTypeDecl
    | optVarDecl
    | optProcFuncs
    ;

optConstDecl: CONST_KEY constDecls
    | 
    ;

constDecls: constDecls constDecl
    | constDecl
    ;

constDecl: identifier EQ_OP expression SEMI_COL { printf("Found const declaration\n"); }
    ;

optProcFuncs: optProcFuncs procedureDecl
    | optProcFuncs functionDecl
    |
    ;

procedureDecl: procedureSig FORWARD_KEY SEMI_COL { printf("Found procedure declaration\n"); }
    | procedureSig body SEMI_COL { printf("Found procedure declaration\n"); }
    ;

procedureSig: PROCEDURE_KEY identifier OPEN_PAR formalParameters CLOSE_PAR SEMI_COL
    ;

functionDecl: functionSig FORWARD_KEY SEMI_COL { printf("Found function declaration\n"); }
    | functionSig body SEMI_COL { printf("Found function declaration\n"); }
    ;

functionSig: FUNCTION_KEY identifier OPEN_PAR formalParameters CLOSE_PAR COL type SEMI_COL
    ;

formalParameters: formalParameters SEMI_COL
    | formalParameter
    ;

formalParameter: optVar identifierList COL type
    ;

optVar: VAR_KEY
    | REF_KEY
    |
    ;

body: optConstDecl
    | optTypeDecl
    | optVarDecl
    | block
    ;

block: BEGIN_KEY statementList END_KEY { printf("Found block declaration\n"); }
    ;

optTypeDecl: TYPE_KEY typeDecls
    |
    ;

typeDecls: typeDecls typeDecl
    | typeDecl
    ;

typeDecl: identifier EQ_OP type SEMI_COL  { printf("Found type declaration\n"); }
    ;

type: simpleType  { printf("Found simple type declaration\n"); }
    | recordType  { printf("Found record type declaration\n"); }
    | arrayType   { printf("Found array type declaration\n"); }
    ;

simpleType: identifier
    ;

recordType: RECORD_KEY fields END_KEY
    ;

fields: fields field
    |
    ;
field: identifierList COL type SEMI_COL
    ;

arrayType: ARRAY_KEY OPEN_SQ expression COL expression CLOSE_SQ OF_KEY type
    ;

identifierList: identifierList COMMA identifier
    | identifier
    ;

identifier: IDENTIFIER { printf("Found an identifier: %s\n", $1); }
    ;

optVarDecl: VAR_KEY varDecls
    |
    ;

varDecls: varDecls varDecl
    | varDecl
    ;

varDecl: identifierList COL type SEMI_COL { printf("Found var declaration\n"); }
    ;

statementList: statementList SEMI_COL statement
    | statement
    ;

statement: assignment   { printf("Found assignment statement\n"); }
    | ifStatement       { printf("Found if statement\n"); }
    | whileStatement    { printf("Found while statement\n"); }
    | repeatStatement   { printf("Found repeat statement\n"); }
    | forStatement      { printf("Found for statement\n"); }
    | stopStatement     { printf("Found stop statement\n"); }
    | returnStatement   { printf("Found return statement\n"); }
    | readStatement     { printf("Found read statement\n"); }
    | writeStatement    { printf("Found write statement\n"); }
    | procedureCall     { printf("Found procedure callstatement\n"); }
    | nullStatement     { printf("Found null statement\n"); }
    ;

assignment: lvalue ASSIGN_OP expression
    ;

ifStatement: IF_KEY expression thenStatement elseIfStatements elseStatement END_KEY
    ;

elseIfStatements: elseIfStatements elseStatement thenStatement
    | elseIfStatement thenStatement
    | 
    ;

elseIfStatement: ELSE_IF_KEY expression
    ;

elseStatement: ELSE_KEY statementList
    |
    ;

thenStatement: THEN_KEY statementList
    ;

whileStatement: WHILE_KEY expression DO_KEY statementList END_KEY
    ;

repeatStatement: REPEAT_KEY statementList UNTIL_KEY expression
    ;

forStatement: FOR_KEY identifier ASSIGN_OP expression optTo expression DO_KEY statementList END_KEY
    ;

optTo: TO_KEY
    | DOWN_TO_KEY
    ;

stopStatement: STOP_KEY
    ;

returnStatement: RETURN_KEY expression
    | RETURN_KEY
    ;

readStatement: READ_KEY OPEN_PAR lvalueList CLOSE_PAR
    ;

writeStatement: WRITE_KEY OPEN_PAR expressionList CLOSE_PAR
    ;

procedureCall: identifier OPEN_PAR optExpressionList CLOSE_PAR
    ;

nullStatement:
    ;

optExpressionList: expressionList
    |
    ;

expressionList: expressionList COMMA
    | expression
    ;

expression: expression OR_OP expression                 { printf("Found | expression\n"); }
    | expression AND_OP expression                      { printf("Found & expression\n"); }
    | expression EQ_OP expression                       { printf("Found = expression\n"); }
    | expression NOT_EQ_OP expression                   { printf("Found <> expression\n"); }
    | expression LT_EQ_OP expression                    { printf("Found <= expression\n"); }
    | expression GT_EQ_OP expression                    { printf("Found >= expression\n"); }
    | expression LT_OP expression                       { printf("Found < expression\n"); }
    | expression GT_OP expression                       { printf("Found > expression\n"); }
    | expression PLUS_OP expression                     { printf("Found + expression\n"); }
    | expression MINUS_OP expression                    { printf("Found - expression\n"); }
    | expression MULT_OP expression                     { printf("Found * expression\n"); }
    | expression DIV_OP expression                      { printf("Found \ expression\n"); }
    | expression MOD_OP expression                      { printf("Found % expression\n"); }
    | NOT_OP expression                                 { printf("Found ~ expression\n"); }
    | MINUS_OP expression %prec UMINUS_OP               { printf("Found u- expression\n"); }
    | OPEN_PAR expression CLOSE_PAR                     { printf("Found (exp) expression\n"); }
    | identifier OPEN_PAR optExpressionList CLOSE_PAR   { printf("Found function call expression\n"); }
    | CHR_KEY OPEN_PAR expression CLOSE_PAR             { printf("Found chr (exp) expression\n"); }
    | ORD_KEY OPEN_PAR expression CLOSE_PAR             { printf("Found ord (exp) expression\n"); }
    | PRED_KEY OPEN_PAR expression CLOSE_PAR            { printf("Found pred (exp) expression\n"); }
    | SUCC_KEY OPEN_PAR expression CLOSE_PAR            { printf("Found succ (exp) expression\n"); }
    | INT_CONST                                         { printf("Found int const expression\n"); }
    | CHR_CONST                                         { printf("Found chr const expression\n"); }
    | STRING_CONST                                      { printf("Found chr* const expression\n"); }
    | lvalue                                            { printf("Found lvalue expression\n"); }
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