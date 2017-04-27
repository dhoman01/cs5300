%skeleton "lalr1.cc"
%require  "3.0"
%debug 
%defines 
%define api.namespace {cpsl}
%define parser_class_name {Parser}

%code requires{
    #include "../utils/structures.hpp"
    namespace cpsl {
        class Brain;
        struct Expression;
        class Scanner;
    }

}

%parse-param { Scanner& scanner }
%parse-param { Brain& brain     }

%code{
    #include <iostream>
    #include <cstdlib>
    #include <fstream>

    #include "../Brain.hpp"

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
%token <std::string> IDENTIFIER
%token <std::string> INT_CONST
%token <char> CHR_CONST
%token <std::string> STRING_CONST


%left AND_OP OR_OP
%right NOT_OP
%nonassoc EQ_OP LT_EQ_OP GT_EQ_OP GT_OP LT_OP NOT_EQ_OP
%left PLUS_OP MINUS_OP
%left DIV_OP MOD_OP MULT_OP
%right UMINUS_OP

%type<cpsl::Expression>                                                                         expression whileExpr
%type<std::vector<std::string>>                                                                 identifierList
%type<std::vector<std::shared_ptr<cpsl::LValue>>>                                               lvalueList
%type<std::shared_ptr<cpsl::LValue>>                                                            lvalue
%type<std::vector<cpsl::Expression>>                                                            expressionList optExpressionList
%type<int>                                                                                      constDecl assignment whileHdr whileKey ifKey ifHdr elseIfHdr elseIfStatement repeatHdr
%type<std::vector<int>>                                                                         optElseIfStatements elseIfStatements
%type<std::string>                                                                              identifier optTo optVar funcId procedureId
%type<cpsl::ForHeaderInfo>                                                                      forHdr forBegin
%type<std::shared_ptr<cpsl::Procedure>>                                                         procedureSig funcSig
%type<std::vector<std::shared_ptr<cpsl::Parameter>>>                                            formalParameter formalParameters optFormalParameters
%type<std::vector<cpsl::Field>>                                                                 fields field
%type<std::shared_ptr<cpsl::Record>>                                                            recordType
%type<std::shared_ptr<cpsl::Array>>                                                             arrayType
%type<std::shared_ptr<cpsl::Type>>                                                              type simpleType

%locations

%%

program: progHead block DOT                                                                     { brain.Finalize(); }
    ;

progHead: optConstDecl optTypeDecl optVarDecl optProcFuncs                                      { brain.InitMain(); }
    ;

optConstDecl: CONST_KEY constDecls
    |
    ;

constDecls: constDecls constDecl
    | constDecl
    ;

constDecl: identifier EQ_OP expression SEMI_COL                                                 { brain.statements.ConstDeclaration($1, $3); }
    ;

optProcFuncs: optProcFuncs procedureDecl
    | optProcFuncs funcDecl
    |
    ;

procedureDecl: procedureId OPEN_PAR optFormalParameters CLOSE_PAR SEMI_COL FORWARD_KEY SEMI_COL { brain.statements.MakeProcedure($1, $3, true); }
    | procedureSig body SEMI_COL                                                                { brain.statements.FunctionPrologue($1); brain.statements.FunctionEpilogue($1); }
    ;

procedureSig: procedureId OPEN_PAR optFormalParameters CLOSE_PAR SEMI_COL                        { $$ = brain.statements.MakeProcedure($1, $3); }
    ;

procedureId: PROCEDURE_KEY identifier                                                           { $$ = $2; }
    ;

funcDecl: funcId OPEN_PAR optFormalParameters CLOSE_PAR COL type SEMI_COL FORWARD_KEY SEMI_COL  { brain.statements.MakeFunction($1, $3, $6, true); }                                               {  }
    | funcSig body SEMI_COL                                                                     { brain.statements.FunctionPrologue($1); brain.statements.FunctionEpilogue($1); }
    ;

funcSig: funcId OPEN_PAR optFormalParameters CLOSE_PAR COL type SEMI_COL                        { $$ = brain.statements.MakeFunction($1, $3, $6); }
    ;

funcId: FUNCTION_KEY identifier                                                                 { $$ = $2; }
    ;

optFormalParameters: formalParameters                                                           { $$ = $1; }
    |                                                                                           { $$ = std::vector<std::shared_ptr<cpsl::Parameter>>(); }
    ;

formalParameters: formalParameters SEMI_COL formalParameter                                     { $1.insert($1.end(), $3.begin(), $3.end()); $$ = $1; }
    | formalParameter                                                                           { $$ = $1; }
    ;

formalParameter: optVar identifierList COL type                                                 { $$ = brain.statements.MakeParameters($1, $2, $4); }
    ;

optVar: VAR_KEY                                                                                 { $$ = "var"; }
    | REF_KEY                                                                                   { $$ = "ref"; }
    |                                                                                           { $$ = ""; }
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

typeDecl: identifier EQ_OP type SEMI_COL                                                        { brain.statements.DeclareType($1, $3); }
    ;

type: simpleType                                                                                { $$ = $1; }
    | recordType                                                                                { $$ = $1; }
    | arrayType                                                                                 { $$ = $1; }
    ;

simpleType: identifier                                                                          { $$ = brain.statements.TypeLookup($1); }
    ;

recordType: RECORD_KEY fields END_KEY                                                           { $$ = brain.statements.MakeRecord($2); }
    ;

fields: fields field                                                                            { $1.insert($1.end(), $2.begin(), $2.end()); $$ = $1; }
    |                                                                                           { $$ = std::vector<cpsl::Field>(); }
    ;   
field: identifierList COL type SEMI_COL                                                         { $$ = brain.statements.MakeFields($1, $3); }
    ;

arrayType: ARRAY_KEY OPEN_SQ expression COL expression CLOSE_SQ OF_KEY type                     { $$ = brain.statements.MakeArray($3, $5, $8); }
    ;

identifierList: identifierList COMMA identifier                                                 { $1.push_back($3); $$ = $1; }
    | identifier                                                                                { std::vector<std::string> list; list.push_back($1); $$ = list; }
    ;

identifier: IDENTIFIER                                                                          { $$ = $1; }
    ;

optVarDecl: VAR_KEY varDecls
    |
    ;

varDecls: varDecls varDecl
    | varDecl
    ;

varDecl: identifierList COL type SEMI_COL                                                       { brain.statements.VariableDeclaration($1, $3); }
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

assignment: lvalue ASSIGN_OP expression                                                         { brain.statements.Assignment($1, $3); }
    ;

ifStatement: ifHdr optElseIfStatements elseStatement END_KEY                                    { $2.push_back($1); brain.statements.IfEnd($2); }
    ;

ifHdr: ifKey thenStatement                                                                      { $$ = $1; brain.statements.IfHeader($1); }
    ;

ifKey: IF_KEY expression                                                                        { $$ = brain.statements.IfBegin($2); }
    ;

thenStatement: THEN_KEY statementList
    ;

optElseIfStatements: elseIfStatements                                                           { $$ = $1; }
    |                                                                                           { $$ = std::vector<int>(0); }
    ;

elseIfStatements: elseIfStatements elseIfStatement                                              { $1.push_back($2); $$ = $1; }
    | elseIfStatement                                                                           { std::vector<int> list; list.push_back($1); $$ = list; }
    ;

elseIfStatement: elseIfHdr thenStatement                                                        { $$ = $1; brain.statements.IfHeader($1); }
    ;

elseIfHdr: ELSE_IF_KEY expression                                                               { $$ = brain.statements.IfBegin($2); }
    ;

elseStatement: ELSE_KEY statementList
    |
    ;

whileStatement: whileHdr statementList END_KEY                                                  { brain.statements.WhileEnd($1); }
    ;

whileHdr: whileKey whileExpr DO_KEY                                                             { $$ = $1; brain.statements.WhileHeader($1, $2); }
    ;

whileKey: WHILE_KEY                                                                             { $$ = brain.statements.WhileBegin(); }
    ;

whileExpr: expression                                                                           { $$ = $1; }
    ;

repeatStatement: repeatHdr statementList UNTIL_KEY expression                                   { brain.statements.RepeatEnd($1, $4); }
    ;

repeatHdr: REPEAT_KEY                                                                           { $$ = brain.statements.RepeatBegin(); }
    ;
                                                                
forStatement: forHdr DO_KEY statementList END_KEY                                               { brain.statements.ForEnd($1); }
    ;
                                                                
forHdr: forBegin optTo expression                                                               { $1.optTo = $2; brain.statements.ForHeader($1, $3); $$ = $1; }
    ;

forBegin: FOR_KEY identifier ASSIGN_OP expression                                               { $$ = brain.statements.ForBegin($2, $4); }
    ;

optTo: TO_KEY                                                                                   { $$ = "1"; }
    | DOWN_TO_KEY                                                                               { $$ = "-1"; }
    ;

stopStatement: STOP_KEY                                                                         { brain.statements.StopStatement(); }
    ;

returnStatement: RETURN_KEY expression                                                          { brain.statements.ReturnStatement($2); }
    | RETURN_KEY                                                                                { brain.statements.ReturnStatement(); }
    ;

readStatement: READ_KEY OPEN_PAR lvalueList CLOSE_PAR                                           { brain.statements.ReadStatement($3); }
    ;

writeStatement: WRITE_KEY OPEN_PAR expressionList CLOSE_PAR                                     { brain.statements.WriteStatement($3); }
    ;

procedureCall: identifier OPEN_PAR optExpressionList CLOSE_PAR                                  { auto precall = brain.statements.FunctionPrecall($1, $3); brain.statements.FunctionPostcall(precall); }
    ;

nullStatement:
    ;

optExpressionList: expressionList                                                               { $$ = $1;}
    |                                                                                           { $$ = std::vector<cpsl::Expression>(); }
    ;

expressionList: expressionList COMMA expression                                                 { $1.push_back($3); $$ = $1;}
    | expression                                                                                { std::vector<cpsl::Expression> list; list.push_back($1); $$ = list; }
    ;

expression: expression OR_OP expression                                                         { $$ = brain.expressions.OrExpression($1, $3); }            
    | expression AND_OP expression                                                              { $$ = brain.expressions.AndExpression($1, $3); }              
    | expression EQ_OP expression                                                               { $$ = brain.expressions.EqExpression($1, $3); } 
    | expression NOT_EQ_OP expression                                                           { $$ = brain.expressions.NotEqExpression($1, $3); } 
    | expression LT_EQ_OP expression                                                            { $$ = brain.expressions.LtEqExpression($1, $3); } 
    | expression GT_EQ_OP expression                                                            { $$ = brain.expressions.GtEqExpression($1, $3); } 
    | expression LT_OP expression                                                               { $$ = brain.expressions.LtExpression($1, $3); } 
    | expression GT_OP expression                                                               { $$ = brain.expressions.GtExpression($1, $3); } 
    | expression PLUS_OP expression                                                             { $$ = brain.expressions.PlusExpression($1, $3); } 
    | expression MINUS_OP expression                                                            { $$ = brain.expressions.MinusExpression($1, $3); } 
    | expression MULT_OP expression                                                             { $$ = brain.expressions.MultExpression($1, $3); }
    | expression DIV_OP expression                                                              { $$ = brain.expressions.DivExpression($1, $3); } 
    | expression MOD_OP expression                                                              { $$ = brain.expressions.ModExpression($1, $3); } 
    | NOT_OP expression                                                                         { $$ = brain.expressions.NotExpression($2); }           
    | MINUS_OP expression %prec UMINUS_OP                                                       { $$ = brain.expressions.UMinusExpression($2); } 
    | OPEN_PAR expression CLOSE_PAR                                                             { $$ = $2; } 
    | identifier OPEN_PAR optExpressionList CLOSE_PAR                                           { auto precall = brain.statements.FunctionPrecall($1, $3); $$ = brain.statements.FunctionPostcall(precall); }
    | CHR_KEY OPEN_PAR expression CLOSE_PAR                                                     { $$ = brain.expressions.ChrExpression($3); }
    | ORD_KEY OPEN_PAR expression CLOSE_PAR                                                     { $$ = brain.expressions.OrdExpression($3); }
    | PRED_KEY OPEN_PAR expression CLOSE_PAR                                                    { $$ = brain.expressions.PredExpression($3); }
    | SUCC_KEY OPEN_PAR expression CLOSE_PAR                                                    { $$ = brain.expressions.SuccExpression($3); }
    | INT_CONST                                                                                 { $$ = brain.expressions.IntConstant($1); }
    | CHR_CONST                                                                                 { $$ = brain.expressions.CharConstant($1); }
    | STRING_CONST                                                                              { $$ = brain.AddString($1); } 
    | lvalue                                                                                    { $$ = brain.statements.MakeLValueExpression($1); }
    ;

lvalueList: lvalueList COMMA lvalue                                                             { $$ = $1; }
    | lvalue                                                                                    { std::vector<std::shared_ptr<cpsl::LValue>> list; list.push_back($1); $$ = list;}
    ;

lvalue: lvalue DOT identifier                                                                   { $$ = brain.statements.LoadRecordMember($1, $3); }
    | lvalue OPEN_SQ expression CLOSE_SQ                                                        { $$ = brain.statements.LoadArrayElement($1, $3); }
    | identifier                                                                                { $$ = brain.statements.LoadVariable($1);}
    ;

%%

void cpsl::Parser::error(const location_type& loc, const std::string& err_message)
{
    std::cerr << "Syntax Error: " << err_message << " at ";
    std::cerr << loc.begin.line << ":" << loc.begin.column << " - ";
    std::cerr << loc.end.line << ":" << loc.end.column << "\n";
}