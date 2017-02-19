%skeleton "lalr1.cc"
%require  "3.0"
%debug 
%defines 
%define api.namespace {cpsl}
%define parser_class_name {Parser}

%code requires{
    #include "structures.hpp"
    namespace cpsl {
        class Brain;
        struct Expression;
        class Scanner;
    }

// The following definitions is missing when %locations isn't used
# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

}

%parse-param { Scanner& scanner }
%parse-param { Brain& brain}

%code{
    #include <iostream>
    #include <cstdlib>
    #include <fstream>

    #include "Brain.hpp"

#undef yylex
#define yylex scanner.yylex
}

%define api.value.type variant
%define parse.assert

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
%token <int> INT_CONST
%token <char> CHR_CONST
%token <char*> STRING_CONST


%left AND_OP OR_OP
%right NOT_OP
%nonassoc EQ_OP LT_EQ_OP GT_EQ_OP GT_OP LT_OP NOT_EQ_OP
%left PLUS_OP MINUS_OP
%left DIV_OP MOD_OP MULT_OP
%right UMINUS_OP

%type<cpsl::Expression> expression IDENTIFIER identifier

%locations

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

expression: expression OR_OP expression                 { $$ = brain.expressions.OrExpression($1, $3); }            
    | expression AND_OP expression                      { $$ = brain.expressions.AndExpression($1, $3); }              
    | expression EQ_OP expression                       { $$ = brain.expressions.EqExpression($1, $3); } 
    | expression NOT_EQ_OP expression                   { $$ = brain.expressions.NotEqExpression($1, $3); } 
    | expression LT_EQ_OP expression                    { $$ = brain.expressions.LtEqExpression($1, $3); } 
    | expression GT_EQ_OP expression                    { $$ = brain.expressions.GtEqExpression($1, $3); } 
    | expression LT_OP expression                       { $$ = brain.expressions.LtExpression($1, $3); } 
    | expression GT_OP expression                       { $$ = brain.expressions.GtExpression($1, $3); } 
    | expression PLUS_OP expression                     { $$ = brain.expressions.PlusExpression($1, $3); } 
    | expression MINUS_OP expression                    { $$ = brain.expressions.MinusExpression($1, $3); } 
    | expression MULT_OP expression                     { $$ = brain.expressions.MultExpression($1, $3); }
    | expression DIV_OP expression                      { $$ = brain.expressions.DivExpression($1, $3); } 
    | expression MOD_OP expression                      { $$ = brain.expressions.ModExpression($1, $3); } 
    | NOT_OP expression                                 { $$ = brain.expressions.NotExpression($2); }           
    | MINUS_OP expression %prec UMINUS_OP               { $$ = brain.expressions.UMinusExpression($2); } 
    | OPEN_PAR expression CLOSE_PAR                     { $$ = $2; } 
    | identifier OPEN_PAR optExpressionList CLOSE_PAR   { $$ = $1; }
    | CHR_KEY OPEN_PAR expression CLOSE_PAR             { $$ = $3; }
    | ORD_KEY OPEN_PAR expression CLOSE_PAR             { $$ = $3; }
    | PRED_KEY OPEN_PAR expression CLOSE_PAR            { $$ = $3; }
    | SUCC_KEY OPEN_PAR expression CLOSE_PAR            { $$ = $3; }
    | INT_CONST                                         { $$ = brain.expressions.IntConstant($1); }
    | CHR_CONST                                         { $$ = brain.expressions.CharConstant($1); }
    | STRING_CONST                                      { $$ = brain.expressions.StringConstant($1); } 
    | lvalue                                            {  }
    ;

lvalueList: lvalueList COMMA
    | lvalue
    ;

lvalue: lvalue DOT identifier
    | lvalue OPEN_SQ expression CLOSE_SQ
    | identifier
    ;

%%

void cpsl::Parser::error(const location_type& l, const std::string& err_message)
{
    std::cerr << "Syntax Error: " << err_message << " at " << l << "\n";
}