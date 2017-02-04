%{
#include <stdlib.h>
#include <stdio.h>
int yyerror(const char *s);
int yylex(void);

extern int yylineno;
extern int yycolno;
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

%type<str> IDENTIFIER STRING_CONST identifier
%type<chr> CHR_CONST
%type<integer> INT_CONST

%start program

%%
program: progHead block DOT { printf("(%d:%d) Parser found program\n", yylineno, yycolno); }
    ;

progHead: optConstDecl optTypeDecl optVarDecl optProcFuncs
    ;

optConstDecl: CONST_KEY constDecls
    | 
    ;

constDecls: constDecls constDecl
    | constDecl
    ;

constDecl: identifier EQ_OP expression SEMI_COL { printf("(%d:%d) Parser found const declaration\n", yylineno, yycolno); }
    ;

optProcFuncs: optProcFuncs procedureDecl
    | optProcFuncs functionDecl
    |
    ;

procedureDecl: procedureSig FORWARD_KEY SEMI_COL { printf("(%d:%d) Parser found procedure declaration\n", yylineno, yycolno); }
    | procedureSig body SEMI_COL { printf("(%d:%d) Parser found procedure declaration\n", yylineno, yycolno); }
    ;

procedureSig: PROCEDURE_KEY identifier OPEN_PAR optFormalParameters CLOSE_PAR SEMI_COL
    ;

functionDecl: functionSig FORWARD_KEY SEMI_COL { printf("(%d:%d) Parser found function declaration\n", yylineno, yycolno); }
    | functionSig body SEMI_COL { printf("(%d:%d) Parser found function declaration\n", yylineno, yycolno); }
    ;

functionSig: FUNCTION_KEY identifier OPEN_PAR optFormalParameters CLOSE_PAR COL type SEMI_COL
    ;

optFormalParameters: formalParameters
    |
    ;

formalParameters: formalParameters SEMI_COL formalParameter
    | formalParameter
    ;

formalParameter: optVar identifierList COL type { printf("(%d:%d) Parser found formal parameter\n", yylineno, yycolno); }
    ;

optVar: VAR_KEY
    | REF_KEY
    |
    ;

body: optConstDecl optTypeDecl optVarDecl block
    ;

block: BEGIN_KEY statementList END_KEY { printf("(%d:%d) Parser found block\n", yylineno, yycolno); }
    ;

optTypeDecl: TYPE_KEY typeDecls
    |
    ;

typeDecls: typeDecls typeDecl
    | typeDecl
    ;

typeDecl: identifier EQ_OP type SEMI_COL  { printf("(%d:%d) Parser found type declaration\n", yylineno, yycolno); }
    ;

type: simpleType  { printf("(%d:%d) Parser found simple type declaration\n", yylineno, yycolno); }
    | recordType  { printf("(%d:%d) Parser found record type declaration\n", yylineno, yycolno); }
    | arrayType   { printf("(%d:%d) Parser found array type declaration\n", yylineno, yycolno); }
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

identifier: IDENTIFIER { printf("(%d:%d) Parser found an identifier: %s\n", yylineno, yycolno, $1); }
    ;

optVarDecl: VAR_KEY varDecls
    |
    ;

varDecls: varDecls varDecl
    | varDecl
    ;

varDecl: identifierList COL type SEMI_COL { printf("(%d:%d) Parser found var declaration\n", yylineno, yycolno); }
    ;

statementList: statementList SEMI_COL statement
    | statement
    ;

statement: assignment   { printf("(%d:%d) Parser found assignment statement\n", yylineno, yycolno); }
    | ifStatement       { printf("(%d:%d) Parser found if statement\n", yylineno, yycolno); }
    | whileStatement    { printf("(%d:%d) Parser found while statement\n", yylineno, yycolno); }
    | repeatStatement   { printf("(%d:%d) Parser found repeat statement\n", yylineno, yycolno); }
    | forStatement      { printf("(%d:%d) Parser found for statement\n", yylineno, yycolno); }
    | stopStatement     { printf("(%d:%d) Parser found stop statement\n", yylineno, yycolno); }
    | returnStatement   { printf("(%d:%d) Parser found return statement\n", yylineno, yycolno); }
    | readStatement     { printf("(%d:%d) Parser found read statement\n", yylineno, yycolno); }
    | writeStatement    { printf("(%d:%d) Parser found write statement\n", yylineno, yycolno); }
    | procedureCall     { printf("(%d:%d) Parser found procedure callstatement\n", yylineno, yycolno); }
    | nullStatement     { printf("(%d:%d) Parser found null statement\n", yylineno, yycolno); }
    ;

assignment: lvalue ASSIGN_OP expression
    ;

ifStatement: IF_KEY expression thenStatement optElseIfStatements elseStatement END_KEY
    ;

thenStatement: THEN_KEY statementList
    ;

optElseIfStatements: elseIfStatements
    |
    ;

elseIfStatements: elseIfStatements elseIfStatement
    | elseIfStatement
    ;

elseIfStatement: ELSE_IF_KEY expression thenStatement
    ;

elseStatement: ELSE_KEY statementList
    |
    ;

whileStatement: WHILE_KEY expression DO_KEY statementList END_KEY
    ;

repeatStatement: REPEAT_KEY statementList UNTIL_KEY expression
    ;

forStatement: forHead DO_KEY statementList END_KEY
    ;

forHead: FOR_KEY identifier ASSIGN_OP expression optTo expression { printf("(%d:%d) Parser found for signature\n", yylineno, yycolno); }
    ;

optTo: TO_KEY       { printf("(%d:%d) Parser found \"to\" for\n", yylineno, yycolno); }
    | DOWN_TO_KEY   { printf("(%d:%d) Parser found \"downto\"\n", yylineno, yycolno); }
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

expressionList: expressionList COMMA expression
    | expression
    ;

expression: expression OR_OP expression                 { printf("(%d:%d) Parser found | expression\n", yylineno, yycolno); }
    | expression AND_OP expression                      { printf("(%d:%d) Parser found & expression\n", yylineno, yycolno); }
    | expression EQ_OP expression                       { printf("(%d:%d) Parser found = expression\n", yylineno, yycolno); }
    | expression NOT_EQ_OP expression                   { printf("(%d:%d) Parser found <> expression\n", yylineno, yycolno); }
    | expression LT_EQ_OP expression                    { printf("(%d:%d) Parser found <= expression\n", yylineno, yycolno); }
    | expression GT_EQ_OP expression                    { printf("(%d:%d) Parser found >= expression\n", yylineno, yycolno); }
    | expression LT_OP expression                       { printf("(%d:%d) Parser found < expression\n", yylineno, yycolno); }
    | expression GT_OP expression                       { printf("(%d:%d) Parser found > expression\n", yylineno, yycolno); }
    | expression PLUS_OP expression                     { printf("(%d:%d) Parser found + expression\n", yylineno, yycolno); }
    | expression MINUS_OP expression                    { printf("(%d:%d) Parser found - expression\n", yylineno, yycolno); }
    | expression MULT_OP expression                     { printf("(%d:%d) Parser found * expression\n", yylineno, yycolno); }
    | expression DIV_OP expression                      { printf("(%d:%d) Parser found \\ expression\n", yylineno, yycolno); }
    | expression MOD_OP expression                      { printf("(%d:%d) Parser found %% expression\n", yylineno, yycolno); }
    | NOT_OP expression                                 { printf("(%d:%d) Parser found ~ expression\n", yylineno, yycolno); }
    | MINUS_OP expression %prec UMINUS_OP               { printf("(%d:%d) Parser found u- expression\n", yylineno, yycolno); }
    | OPEN_PAR expression CLOSE_PAR                     { printf("(%d:%d) Parser found (exp) expression\n", yylineno, yycolno); }
    | identifier OPEN_PAR optExpressionList CLOSE_PAR   { printf("(%d:%d) Parser found function call expression\n", yylineno, yycolno); }
    | CHR_KEY OPEN_PAR expression CLOSE_PAR             { printf("(%d:%d) Parser found chr (exp) expression\n", yylineno, yycolno); }
    | ORD_KEY OPEN_PAR expression CLOSE_PAR             { printf("(%d:%d) Parser found ord (exp) expression\n", yylineno, yycolno); }
    | PRED_KEY OPEN_PAR expression CLOSE_PAR            { printf("(%d:%d) Parser found pred (exp) expression\n", yylineno, yycolno); }
    | SUCC_KEY OPEN_PAR expression CLOSE_PAR            { printf("(%d:%d) Parser found succ (exp) expression\n", yylineno, yycolno); }
    | INT_CONST                                         { printf("(%d:%d) Parser found int const expression: %d\n", yylineno, yycolno, $1); }
    | CHR_CONST                                         { printf("(%d:%d) Parser found chr const expression: %c\n", yylineno, yycolno, $1); }
    | STRING_CONST                                      { printf("(%d:%d) Parser found chr* const expression: %s\n", yylineno, yycolno, $1); }
    | lvalue                                            { printf("(%d:%d) Parser found lvalue expression\n", yylineno, yycolno); }
    ;

lvalueList: lvalueList COMMA
    | lvalue
    ;

lvalue: lvalue DOT identifier
    | lvalue OPEN_SQ expression CLOSE_SQ
    | identifier
    ;

%%

int yyerror(const char* s){
    extern char* yytext;
    printf("ERROR: Incorrect value \"%s\" on line %d column %d\n", yytext, yylineno, yycolno);
    exit(1);
}