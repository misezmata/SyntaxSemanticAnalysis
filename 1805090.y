%{
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include "1805090_SymbolTable.h"
// #define YYSTYPE SymbolInfo*

using namespace std;

int yyparse(void);
int yylex(void);
extern FILE *yyin;
extern int yylineno;
SymbolTable *table;
string builder;
vector<pair<string, int> > decList;


void yyerror(char *s)
{
	//write your code
}

void print(string s){cout<<"LINE "<<yylineno<<": "<<s<<endl;}

void printVVector(vector<SymbolInfo*> v){
	int size = v.size();
	for(int i=0; i<size; i++){
		SymbolInfo* si = v[i];
		si->print();
	}
	cout<<endl;}

pair<string*, string*>* createPSS(string a, string b){
	return new pair<string*, string*> ({new string(a), new string(b)});
}

vector<SymbolInfo*>* addDeclaration(vector<SymbolInfo*>* prev, SymbolInfo* id, string size){
	id->setSpec(1);
	id->setSize(stoi(size));
	prev->push_back(id);
	return prev;}

vector<SymbolInfo*>* addParameter(vector<SymbolInfo*>* prev, SymbolInfo* id, string specifier){
	id->setSpec(1);
	// id->setSize(stoi(size));
	id->setType(specifier);
	prev->push_back(id);
	printVVector(*prev);
	return prev;}

string getParamList(vector<SymbolInfo*> v){
	string builder = "";
	int sz = v.size();
	for(int i=0; i<sz; i++){
		builder += v[i]->getType() + " " + v[i]->getName();
		if(i != sz - 1) builder += ",";
	}
	return builder;
}
string* createFunctionDeclaration(string specifier, string funName, vector<SymbolInfo*> v){
	string builder = specifier + " " + funName + "(";
	int sz = v.size();
	for(int i=0; i<sz; i++){
		builder += v[i]->getType() + " " + v[i]->getName();
		if(i != sz - 1) builder += ",";
	}
	builder += ");";
	return new string(builder);
}

string getHigherType(string a, string b){
	if(a == b) return a;
	return "CONST_FLOAT";
	// if(a == "CONST_INT")
}

void printPSS(pair<string*, string*> pss){
	cout<<*(pss.first)<<" ("<<*(pss.second)<<")"<<endl;
}

string* createVarDeclaration(string t, vector<SymbolInfo*> v){
	string builder = t;
	int sz = v.size();
	for(int i=0; i<sz; i++){
		builder+=" ";
		builder+=v[i]->getName();
		if(v[i]->getSize() != 0) builder+= "["+to_string(v[i]->getSize())+"]";
		if(i != sz - 1) builder += ", ";
	}
	builder+=";";
	return new string(builder);
}

void printVPSS(vector<pair<string*, string*>*> vpss){
	int sz = vpss.size();
	for(int i=0; i<sz; i++){
		printPSS(*vpss[i]);
	}
}

vector<pair<string*, string*>*>* addLogicalExpression(vector<pair<string*, string*>*>* vpss, pair<string*, string*>* pss){
	vpss->push_back(pss);
	printPSS(*pss);
	return vpss;
}

string getStringFromArgumentList(vector<pair<string*, string*>*> vpss){
	string builder = "";
	int sz = vpss.size();
	for(int i=0; i<sz; i++){
		builder += *(vpss[i]->first);
		if(i != sz-1) builder += ",";
	}
	return builder;
}





%}

%union {
	int iint; 
	double ddouble; 
	char cchar; 
	SymbolInfo* si;
	vector<SymbolInfo*>* vvector;	
	string* sstring;
	pair<string*, string*>* pss;
	vector<pair<string*, string*>*>* vss;}
%token INCOP DECOP PRINTLN IF ELSE FOR WHILE DO BREAK INT CHAR FLOAT DOUBLE VOID RETURN SWITCH CASE DEFAULT CONTINUE NOT LPAREN RPAREN LCURL RCURL LTHIRD RTHIRD COMMA SEMICOLON
%token <si> CONST_INT CONST_FLOAT CONST_CHAR ID ADDOP MULOP RELOP ASSIGNOP LOGICOP STRING
%type <vvector> declaration_list parameter_list
%type <sstring> type_specifier var_declaration func_declaration
%type <pss> expression_statement factor variable expression logic_expression rel_expression simple_expression term unary_expression
%type <vss> arguments argument_list
%type <sstring> statement compound_statement statements func_definition unit program
// %left 
// %right

// %nonassoc 

%%

start :
	| program {
		// cout<<"eikhane ken ashe?"<<endl;
		//write your code in this block in all the similar blocks below
	}
	;

program : program unit {
		print("program -> program unit");
		$$ = new string(*$1+"\n"+*$2);
		cout<<*$$<<endl;
	}
	| unit {
		print("program -> unit");
		$$ = $1;
		cout<<*$$<<endl;
	}
	;
	
unit : var_declaration {
		print("unit -> var_declaration");
		$$ = $1;
	}
	| func_declaration {
		print("unit -> func_declaration");
		$$ = $1;
	} 
	| func_definition {
		print("unit -> func_definition");
		$$ = $1;
	}
	;

func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON {
		print("func_declaration -> type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");
		$$ = createFunctionDeclaration(*$1, $2->getName(), *$4);
		cout<<(*$$)<<endl;
	}
	| type_specifier ID LPAREN RPAREN SEMICOLON {
		print("func_declaration -> type_specifier ID LPAREN RPAREN SEMICOLON");
		$$ = new string((*$1) + " " + ($2->getName()) + "();");
		cout<<(*$$)<<endl;
	}
	;

func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement {
		print("func_definition -> type_specifier ID LPAREN parameter_list RPAREN compound_statement");
		$$ = new string(*$1 + " " + $2->getName() + "(" + getParamList(*$4) +")" + *$6);
		cout<<*$$<<endl;
	}
	| type_specifier ID LPAREN RPAREN compound_statement {
		print("func_definition -> type_specifier ID LPAREN RPAREN compound_statement");
		$$ = new string(*$1 + " " + $2->getName() + "()" + *$5);
		cout<<*$$<<endl;
	}
	;				


parameter_list  : parameter_list COMMA type_specifier ID {
		print("parameter_list -> parameter_list COMMA type_specifier ID");
		$$ = addParameter($1, $4, *$3);
	}
	| parameter_list COMMA type_specifier {
		print("parameter_list -> parameter_list COMMA type_specifier");
		$$ = addParameter($1, new SymbolInfo("", *$3), *$3);
	}
	| type_specifier ID {
		print("parameter_list -> type_specifier ID");
		$$ = addParameter(new vector<SymbolInfo*>, $2, *$1);
	}
	| type_specifier {
		print("parameter_list -> type_specifier");
		$$ = addParameter(new vector<SymbolInfo*>, new SymbolInfo("", (*$1)), *$1);
	}
	;

compound_statement : LCURL statements RCURL {
		print("compound_statement -> LCURL statements RCURL");
		$$ = new string("{\n"+*$2+"\n}");
		cout<<*$$<<endl;
	}
	| LCURL RCURL {
		print("compound_statement -> LCURL RCURL");
		$$ = new string("{}");
	}
	;

var_declaration : type_specifier declaration_list SEMICOLON {
		print("var_declaration -> type_specifier declaration_list SEMICOLON");
		$$ = createVarDeclaration(*$1, *$2);
		cout<<(*$$)<<endl;
	}
	;

type_specifier	: INT {print("type_specifier -> INT"); $$ = new string("int");}
	| FLOAT {print("type_specifier -> FLOAT"); $$ = new string("float");}
	| VOID {print("type_specifier -> VOID"); $$ = new string("void");}
	;

declaration_list : declaration_list COMMA ID {
		print("declaration_list -> declaration_list COMMA ID");
		$$ = addDeclaration($1, $3, "0");}
	| declaration_list COMMA ID LTHIRD CONST_INT RTHIRD {
		print("declaration_list -> declaration_list COMMA ID LTHIRD CONST_INT RTHIRD");
		$$ = addDeclaration($1, $3, $5->getName());	}
	| ID 	{	
		print("declaration_list -> ID");
		$$ = addDeclaration(new vector<SymbolInfo*>, $1, "0");}
	| ID LTHIRD CONST_INT RTHIRD {	
		print("declaration_list -> ID LTHIRD CONST_INT RTHIRD");
		$$ = addDeclaration(new vector<SymbolInfo*>, $1, $3->getName());} 
	;

statements : statement {
		print("statements -> statement");
		$$ = $1;
		// cout<<'\t'<<(*$$)<<endl;
	}
	| statements statement {
		print("statements -> statements statement");
		$$ = new string((*$1)+"\n"+(*$2));
		cout<<(*$$)<<endl;
	}
	;

statement : var_declaration {
		print("statement -> var_declaration");
		$$ = $1;
	}
	| expression_statement {
		print("statement -> expression_statement");
		$$ = $1->first;
	}
	| compound_statement {
		print("statement -> compound_statement");
		$$ = $1;
	}
	| FOR LPAREN expression_statement expression_statement expression RPAREN statement {
		$$ = new string("apatoto nothing!");
	}
	| IF LPAREN expression RPAREN statement {
		$$ = new string("apatoto nothing!");
	}
	| IF LPAREN expression RPAREN statement ELSE statement {
		$$ = new string("apatoto nothing!");
	}
	| WHILE LPAREN expression RPAREN statement {
		print("statement -> WHILE LPAREN expression RPAREN statement");
		$$ = new string("while("+*($3->first)+")");
	}
	| PRINTLN LPAREN ID RPAREN SEMICOLON {
		print("statement -> PRINTLN LPAREN ID RPAREN SEMICOLON");
		$$ = new string("println("+$3->getName()+");");
	}
	| RETURN expression SEMICOLON {
		print("statement -> RETURN expression SEMICOLON");
		$$ = new string("return "+*($2->first)+";");
	}
;

expression_statement 	: SEMICOLON	{
		$$ = createPSS(";", "VOID");
	}		
	| expression SEMICOLON {
		$$ = createPSS (*($1->first) + ";", *($1->second));
		printPSS(*$$);
	}
;

variable : ID 	{
		print("variable -> ID");
		$$ = createPSS ($1->getName(), $1->getType());
	}
	| ID LTHIRD expression RTHIRD {
		print("variable -> ID LTHIRD expression RTHIRD");
		$$ = createPSS ($1->getName() + "[" + *($3->first) + "]", $1->getType());
		printPSS(*$$);
	}
;

expression : logic_expression {
		print("expression -> logic_expression");
		$$ = $1;
		printPSS(*$$);
	}
	| variable ASSIGNOP logic_expression {
		// cout<<"\t\t\t\teikhane keno ashe?"<<endl;
		//TODO eikhane onek kahini kora lagbe 
		print("expression -> variable ASSIGNOP logic_expression");
		$$ = createPSS (*($1->first) + " = " + *($3->first), *($1->second));
		printPSS(*$$);
	} 	
;

logic_expression : rel_expression {
		print("logic_expression -> rel_expression");
		$$ = $1;
	}
	| rel_expression LOGICOP rel_expression {
		print("rel_expression LOGICOP rel_expression");
		$$ = createPSS (*($1->first) +  " " + $2->getName() + " " + *($3->first), "CONST_INT");
		printPSS(*$$);
	} 	
;

rel_expression	: simple_expression {
		print("rel_expression -> simple_expression");
		$$ = $1;
	}
	| simple_expression RELOP simple_expression	{
		print("rel_expression -> simple_expression RELOP simple_expression");
		$$ = createPSS (*($1->first) + " " + $2->getName() + " " + *($3->first), "CONST_INT");
		printPSS(*$$);
	}
;

simple_expression : term {
		print("simple_expression -> term");
		$$ = $1;
	}
	| simple_expression ADDOP term {
		print("simple_expression -> term");
		$$ = createPSS(*($1->first) + " " + $2->getName() + " " + *($3->first), getHigherType(*($1->second), *($3->second)));
		printPSS(*$$);
	}
;

term :	unary_expression {
		print("term -> unary_expression");
		$$ = $1;
		printPSS(*$$);
	}
	| term MULOP unary_expression {
		print("term -> MULOP unary_expression");
		$$ = createPSS(*($1->first) + " " + $2->getName() + " " + *($3->first), getHigherType(*($1->second), *($3->second)));
		printPSS(*$$);
	}
;

unary_expression : ADDOP unary_expression {
		print("unary_expression -> ADDOP unary_expression");
		$$ = createPSS ($1->getName() + " " +(*($2->first)), *($2->second));
		printPSS(*$$);
	}
	| NOT unary_expression {
		print("unary_expression -> NOT unary_expression");
		$$ = createPSS ("! "+(*($2->first)),*($2->second));
		printPSS(*$$);
	}
	| factor {
		print("unary_expression -> factor");
		$$ = $1;
	}
;

factor	: variable {
		print("factor -> variable");
		$$ = $1;
	}
	| ID LPAREN argument_list RPAREN {
		print("factor -> ID LPAREN argument_list RPAREN");
		$$ = createPSS ($1->getName() + "(" + getStringFromArgumentList(*$3) + ")", "AKASH");
	}
	| LPAREN expression RPAREN {
		print("factor -> LPAREN expression RPAREN");
		$$ = createPSS ("("+*($2->first)+")",*($2->second));
		printPSS(*$$);
	}
	| CONST_INT {
		print("factor -> CONST_INT");
		$$ = createPSS ($1->getName(),"CONST_INT");
	}
	| CONST_FLOAT {
		print("factor -> CONST_FLOAT");
		$$ = createPSS ($1->getName(), "CONST_FLOAT");
	}
	| variable INCOP {
		print("factor -> variable INCOP");
		$$ = createPSS (*($1->first) + "++", *($1->second));
		printPSS(*$$);
	}
	| variable DECOP {
		print("factor -> variable DECOP");
		$$ = createPSS (*($1->first) + "--", *($1->second));
		printPSS(*$$);
	}
;

argument_list : arguments {
		print("arguments_list -> arguments");
		$$ = $1;
	}
;

arguments : arguments COMMA logic_expression {
		print("arguments -> arguments COMMA logic_expression");
		$$ = addLogicalExpression($1, $3);
	}
	| logic_expression {
		print("arguments -> logic_expression");
		$$ = addLogicalExpression(new vector<pair<string*, string*>*>, $1);
	}
;


%%
int main(int argc,char *argv[])
{
	yyparse();
	return 0;
}

