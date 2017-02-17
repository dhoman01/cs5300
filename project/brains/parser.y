%{
#include <stdlib.h>
#include <stdio.h>
int yyerror(const char *s);
int yylex(void);

extern int yylineno;
extern int yycolno;

#include "Brain.hpp"
cpsl::Brain brain = cpsl::Brain.getInstance();
brain.enterScope();

cpsl::cpslType integer;
integer.size = 4;
integer.id = "integer";
brain.store(integer.id, integer);

cpsl::cpslType character;
character.size = 4;
character.id = "char";
brain.store(character.id, character);

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
program: progHead block DOT
    ;

progHead: optConstDecl optTypeDecl optVarDecl optProcFuncs
    ;

optConstDecl: CONST_KEY constDecls
    | 
    ;

constDecls: constDecls constDecl
    | constDecl
    ;

constDecl: identifier EQ_OP expression SEMI_COL
    ;

optProcFuncs: optProcFuncs procedureDecl
    | optProcFuncs functionDecl
    |
    ;

procedureDecl: procedureSig FORWARD_KEY SEMI_COL
    | procedureSig body SEMI_COL
    ;

procedureSig: PROCEDURE_KEY identifier OPEN_PAR optFormalParameters CLOSE_PAR SEMI_COL
    ;

functionDecl: functionSig FORWARD_KEY SEMI_COL 
    | functionSig body SEMI_COL 
    ;

functionSig: FUNCTION_KEY identifier OPEN_PAR optFormalParameters CLOSE_PAR COL type SEMI_COL
    ;

optFormalParameters: formalParameters
    |
    ;

formalParameters: formalParameters SEMI_COL formalParameter
    | formalParameter
    ;

formalParameter: optVar identifierList COL type 
    ;

optVar: VAR_KEY
    | REF_KEY
    |
    ;

body: optConstDecl optTypeDecl optVarDecl block
    ;

block: BEGIN_KEY statementList END_KEY 
    ;

optTypeDecl: TYPE_KEY typeDecls
    |
    ;

typeDecls: typeDecls typeDecl
    | typeDecl
    ;

typeDecl: identifier EQ_OP type SEMI_COL  
    ;

type: simpleType  
    | recordType  
    | arrayType   
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

identifier: IDENTIFIER 
    ;

optVarDecl: VAR_KEY varDecls
    |
    ;

varDecls: varDecls varDecl
    | varDecl
    ;

varDecl: identifierList COL type SEMI_COL 
    ;

statementList: statementList SEMI_COL statement
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

forHead: FOR_KEY identifier ASSIGN_OP expression optTo expression 
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

expressionList: expressionList COMMA expression
    | expression
    ;

expression: expression OR_OP expression                 
    | expression AND_OP expression                      
    | expression EQ_OP expression                       
    | expression NOT_EQ_OP expression                   
    | expression LT_EQ_OP expression                    
    | expression GT_EQ_OP expression                    
    | expression LT_OP expression                       
    | expression GT_OP expression                       
    | expression PLUS_OP expression                     
    | expression MINUS_OP expression                    
    | expression MULT_OP expression                     
    | expression DIV_OP expression                      
    | expression MOD_OP expression                      
    | NOT_OP expression                                 
    | MINUS_OP expression %prec UMINUS_OP               
    | OPEN_PAR expression CLOSE_PAR                     
    | identifier OPEN_PAR optExpressionList CLOSE_PAR   
    | CHR_KEY OPEN_PAR expression CLOSE_PAR             
    | ORD_KEY OPEN_PAR expression CLOSE_PAR             
    | PRED_KEY OPEN_PAR expression CLOSE_PAR            
    | SUCC_KEY OPEN_PAR expression CLOSE_PAR            
    | INT_CONST                                         
    | CHR_CONST                                         
    | STRING_CONST                                      
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

int yyerror(const char* s){
    extern char* yytext;
    printf("SYNTAX ERROR: Incorrect value \"%s\" on line %d column %d\n", yytext, yylineno, yycolno);
    exit(1);
}