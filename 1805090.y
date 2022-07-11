%{
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include "1805090_SymbolTable.h"

using namespace std;

int yyparse(void);
int yylex(void);
extern FILE *yyin;
extern int yylineno;
SymbolTable *table;
string builder;
vector<pair<string, string> > paramList;
ofstream errout;

void yyerror(char *s)
{
	//write your code
}

void errorr(const char *s){
	errout<<"Erro at line "<<yylineno<<": "<<s<<"\n"<<endl;
	printf("\033[1;31mError at line: %d:  %s \033[0m\n",yylineno, s);
}

void warning(const char *s){
	printf("\033[1;33mWARNING(at line: %d):  %s \033[0m\n",yylineno, s);
}

void print(string s){
	cout<<"LINE "<<yylineno<<": "<<s<<endl;
}

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

void addParamsToScopeTable(){
	int sz = paramList.size();
	// cout<<"\t\tSIZE: "<<sz<<endl;
	for(int i=0; i<sz; i++){
		SymbolInfo* si = new SymbolInfo(paramList[i].first, "ID");
		si->setVarType(paramList[i].second);
		si->setSpec(1);
		si->setSize(0);
		if(table->insert(si)){
			
		}else{
			errorr(("Multiple declaration of "+si->getName()+" in parameter").c_str());
		}
	}
	table->printAll();
	paramList.clear();
}

vector<SymbolInfo*>* addParameter(vector<SymbolInfo*>* prev, SymbolInfo* id, string specifier, bool flag = true){
	id->setSpec(1);
	// id->setSize(stoi(size));
	id->setVarType(specifier);
	prev->push_back(id);
	paramList.push_back({id->getName(), specifier});
	printVVector(*prev);
	return prev;}

string getParamList(vector<SymbolInfo*> v){
	string builder = "";
	int sz = v.size();
	for(int i=0; i<sz; i++){
		builder += v[i]->getVarType() + " " + v[i]->getName();
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

void normalize(string &a, string &b){
	if(a == "CONST_INT") a = "int";
	if(b == "CONST_INT") b = "int";
	if(a == "CONST_FLOAT") a = "float";
	if(b == "CONST_FLOAT") b = "float";
	if(a == "VOID") a = "void";
	if(b == "VOID") b = "void";
}

string getHigherType(string a, string b){
	normalize(a, b);
	if(a == b) return a;
	if(a == "void" || b == "void") {
		// errorr("Void function used in expression");
		return "void";
	}
	return "float";
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

void insertToSymbolTable(string type, vector<SymbolInfo*> v){
	if(type == "void" || type == "VOID"){
		errorr("Variable type cannot be void");
	}
	int sz = v.size();
	for(int i=0; i<sz; i++){
		v[i]->setVarType(type);
		if(table->insert(v[i])){

		}else{
			errorr(("Multiple declaration of "+v[i]->getName()).c_str());
		}
		table->printAll();
	}
}

bool matchParameterSignature(vector<SymbolInfo*>* v1, vector<SymbolInfo*>* v2, string funcName){
	if(v1 == nullptr && v2 == nullptr) {
		return true;
	}
	if(v1 == nullptr) return false;
	if(v2 == nullptr) return false;
	if(v1->size() != v2->size()) {
		errorr(("Total number of parameters mismatch with declaration in function "+funcName).c_str());
		return false;
	}
	int sz = v1->size();
	for(int i=0; i<sz; i++){
		if((*v1)[i]->getVarType() != (*v2)[i]->getVarType()) {
			errorr(((i+1)+"th parameter's type specifier mismatched in function definition of "+funcName).c_str());
			return false;
		}
	}
	return true;
}

string getIdVarType(string name){
	SymbolInfo* si = table->lookUp(name);
	if(si == nullptr) return "null";
	return si->getVarType();
}

void insertFunctionIdToSymbolTable(SymbolInfo* si, string specifier, bool isDefined, vector<SymbolInfo*>* v){
	SymbolInfo* found = table->lookUp(si->getName());
	si->setSpec(2);
	si->setSize(isDefined);
	si->setVarType(specifier);
	si->setParams(v);
	if(found == nullptr){
		table->insert(si);
		table->printAll();
		return;
	}
	if(found->getSpec() != 2){
		errorr(("Multiple declaration of "+si->getName()).c_str());
		return;
	}
	if(found->getSize()){
		errorr(("Multiple definition of "+si->getName()).c_str());
		return;
	}
	if(!isDefined){
		errorr(("Multiple declaration of "+si->getName()).c_str());
	}else {
		if(found->getVarType() != si->getVarType()){
			errorr(("Return type mismatch with function declaration in function "+si->getName()).c_str());
			return;
		}
		if(!matchParameterSignature(si->getParams(), found->getParams(), si->getName())){
			// errorr("Declaration and Definition parameter signature mismatched!");
			// errorr((si->getName()).c_str());
			return;
		}
		table->remove(si->getName());
		table->insert(si);
		table->printAll();
		return;
	}
	table->insert(si);
	return;
	// table->printAll();
}

void validateAndCreateFactor(SymbolInfo* si, vector<pair<string*, string*>*> v){
	SymbolInfo* found = table->lookUp(si->getName());
	if(found == nullptr){
		errorr(("Undeclared function "+si->getName()).c_str());
	}else if(found->getSpec() != 2){
		errorr((found->getName() + " is not a function").c_str());
	}else if(found->getParams()->size() != v.size()){
		cout<<found->getParams()->size()<<endl;
		cout<<v.size()<<endl;
		errorr(("Total number of arguments mismatch with declaration in function "+found->getName()).c_str());
	}else if(found->getVarType() == "void" || found->getVarType() == "VOID"){
		// errorr("Void function used in expression");
	}else{
		int sz = v.size();
		vector<SymbolInfo*> v2= *(found->getParams());
		for(int i=0; i<sz; i++){
			string t1 = *(v[i]->second);
			string t2 = v2[i]->getVarType();
			normalize(t1, t2);
			if(t1 != t2) {
				string er = to_string(i+1)+"th argument mismatch in function "+found->getName();
				errorr(er.c_str());
			}
		}
	}
}

string checkAndValidateID(string idName, string exp, string expType){
	SymbolInfo* found = table->lookUp(idName);
	if(found == nullptr){
		errorr(("Undeclared variable "+idName).c_str());
		return "VOID";
	}
	if(found->getSpec() == 2){
		errorr("NOT A VARIABLE!");
		return found->getVarType();
	}
	if(found->getSize() == 0){
		if(expType == "NOT_ARRAY") return found->getVarType();
		errorr((idName+" not an array").c_str());
		return found->getVarType();
	}
	if(expType == "NOT_ARRAY"){
		errorr(("Type mismatch, "+idName+" is an array").c_str());
		return found->getVarType();
	}
	if(expType != "CONST_INT" && expType != "int") {
		errorr("Expression inside third brackets not an integer");
		return found->getVarType();
	}
	if(expType == "int") {
		// errorr("inside");
		// errorr(exp.c_str());
		return found->getVarType();
	}
	int index;
	// errorr("LINE_249");
	// errorr(exp.c_str());
	sscanf(exp.c_str(), "%d", &index);
	// cout<<"\t\t\t: "<<index<<endl;
	if(index < 0) errorr("Expression inside third brackets cannot be negative");
	if(index >= found->getSize()) errorr("array index out of bound");
	return found->getVarType();
}

void checkAndValidAssign(string a, string b){
	normalize(a, b);
	// warning((a+", "+b).c_str());
	warning((a+' '+b).c_str());
	if(a == "void") errorr("CANNOT ASSIGN TO VOID!");
	if(b == "void"){
		errorr("Void function used in expression");
	}
	if(a != b){
		// warning(("Trying to assign "+b+" in "+a+" (potential precision loss)").c_str());
		if(a == "float" && b == "int") return;
		errorr("Type Mismatch");
	}
}

string getReturnType(string a, string b){
	warning((a+' '+b).c_str());
	normalize(a, b);
	if(a == b) return a;
	if(a == "null" && b != "null") return b;
	if(a != "null" && b == "null") return a;
	warning("MULTIPLE RETURN STATEMENT WITH DIFFERENT RETURN TYPE!");
	return a;
}

void chekAndValidateFunctionSignature(string a, string b){
	if(b == "null") b = "void";
	normalize(a, b);
	if(a != "void" && b == "void"){
		errorr("FUNCTION IS NOT VOID!");
		return;
	} 
	if(a == "void" && b!= "void"){
		errorr("Type mismatch, function is void");
	}
	if(a != b){
		if(a == "float" && b == "int") return;
		errorr("FUNCTION RETURN TYPE MISMATCHED!");
	}
}

void checkModulusOperator(string t1, string op, string t2, string s2){
	if(op != "%") return;
	normalize(t1, t2);
	if(t1 != "int" || t2 != "int") errorr("Non-Integer operand on modulus operator");
	if(s2 == "0") errorr("Modulus by Zero");
}

void checkLogicAndRelExpression(string a, string b){
	normalize(a, b);
	if(a == "void") errorr("void expression in logical or relational operation");
	else if(b == "void") errorr("void expression in logical or relational operation");
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
%token <si> CONST_INT CONST_FLOAT CONST_CHAR ID ADDOP MULOP RELOP ASSIGNOP LOGICOP STRING UNCHAR
%type <vvector> declaration_list parameter_list
%type <sstring> type_specifier var_declaration func_declaration
%type <pss> expression_statement factor variable expression logic_expression rel_expression simple_expression term unary_expression
%type <vss> arguments argument_list
%type <pss> statement compound_statement statements func_definition unit program start
// %left 
// %right

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%

start : program {
		print("start -> program");
		$$ = $1;
		cout<<*($$->first)<<endl;
		// cout<<"eikhane ken ashe?"<<endl;
		//write your code in this block in all the similar blocks below
	}
	;

program : program unit {
		print("program -> program unit");
		string fst = (*($1->first)+"\n"+*($2->first));
		$$ = createPSS(fst, "null");
		// cout<<*$$<<endl;
	}
	| unit {
		print("program -> unit");
		$$ = $1;
		// cout<<*$$<<endl;
	}
	;
	
unit : var_declaration {
		print("unit -> var_declaration");
		$$ = createPSS(*($1), "null");
	}
	| func_declaration {
		print("unit -> func_declaration");
		$$ = createPSS(*($1), "null");
	} 
	| func_definition {
		print("unit -> func_definition");
		$$ = $1;
	}
	;

func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON {
		print("func_declaration -> type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");
		insertFunctionIdToSymbolTable($2, *$1, false, $4);
		$$ = createFunctionDeclaration(*$1, $2->getName(), *$4);
		// cout<<(*$$)<<endl;
	}
	| type_specifier ID LPAREN RPAREN SEMICOLON {
		print("func_declaration -> type_specifier ID LPAREN RPAREN SEMICOLON");
		insertFunctionIdToSymbolTable($2, *$1, false, new vector<SymbolInfo*>);
		$$ = new string((*$1) + " " + ($2->getName()) + "();");
		// cout<<(*$$)<<endl;
	}
	;

func_definition : type_specifier ID LPAREN parameter_list RPAREN {
			insertFunctionIdToSymbolTable($2, *$1, true, $4);
		} compound_statement {
		warning("func_definition -> type_specifier ID LPAREN parameter_list RPAREN compound_statement");
		// insertFunctionIdToSymbolTable($2, *$1, true, $4);
		warning((*($7->second)+", " + *($1)).c_str());
		chekAndValidateFunctionSignature(*($1), *($7->second));
		$$ = createPSS((*$1 + " " + $2->getName() + "(" + getParamList(*$4) +")" + *($7->first)), *($7->second));
		string s = *($$->first); 
		warning(s.c_str());
	}
	| type_specifier ID LPAREN RPAREN {
			insertFunctionIdToSymbolTable($2, *$1, true, new vector<SymbolInfo*>);
		} compound_statement {
		// errorr("eikhane ekhane!");
		warning("func_definition -> type_specifier ID LPAREN RPAREN compound_statement");
		string fst = *$1 + " " + $2->getName() + "()" + *($6->first);
		chekAndValidateFunctionSignature(*($1), *($6->second));
		$$ = createPSS(fst, *($6->second));
		warning((*($6->second)+", " + *($1)).c_str());

		// cout<<*$$<<endl;
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

compound_statement : LCURL {table->enterScope(); addParamsToScopeTable();} statements RCURL {
		print("compound_statement -> LCURL statements RCURL");
		// $$ = new string("{\n"+*($3)+"\n}");
		// cout<<*$$<<endl;
		$$ = createPSS(("{\n"+*($3->first)+"\n}").c_str(), *($3->second));
		table->exitScope();
	}
	| LCURL RCURL {
		print("compound_statement -> LCURL RCURL");
		$$ = createPSS("{}", "void");
	}
	;

var_declaration : type_specifier declaration_list SEMICOLON {
		print("var_declaration -> type_specifier declaration_list SEMICOLON");
		$$ = createVarDeclaration(*$1, *$2);
		insertToSymbolTable(*$1, *$2);
		// cout<<(*$$)<<endl;
	}
	| error declaration_list SEMICOLON {
		print("var_declaration -> type_specifier declaration_list SEMICOLON");
		$$ = createVarDeclaration("void", *$2);
		insertToSymbolTable("void", *$2);
		errorr("type_specifier not specified");
		// cout<<(*$$)<<endl;
	}
	| error declaration_list error {
		print("var_declaration -> type_specifier declaration_list SEMICOLON");
		$$ = createVarDeclaration("void", *$2);
		insertToSymbolTable("void", *$2);
		errorr("type_specifier not specified, missing semicolon");
		// cout<<(*$$)<<endl;
	}
	| type_specifier declaration_list error {
		print("var_declaration -> type_specifier declaration_list SEMICOLON");
		$$ = createVarDeclaration(*$1, *$2);
		insertToSymbolTable(*$1, *$2);
		errorr("missing semicolon");
		// cout<<(*$$)<<endl;
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
		string type = getReturnType(*($1->second), *($2->second));
		$$ = createPSS(*($1->first)+"\n"+*($2->first), type);
		// cout<<(*$$)<<endl;
	}
	;

statement : var_declaration {
		print("statement -> var_declaration");
		$$ = createPSS(*$1, "null");
	}
	| expression_statement {
		print("statement -> expression_statement");
		$$ = createPSS(*($1->first), "null");
	}
	| compound_statement {
		print("statement -> compound_statement");
		// $$ = createPSS(*$1, *($1-.second));
		$$ = $1;
	}
	| FOR LPAREN expression_statement expression_statement expression RPAREN statement {
		string s = "for (" + *($3->first) + " " + *($4->first) + " " + *($5->first) + " ) " + *($7->first); 
		$$ = createPSS(s, *($7->second));
	}
	| IF LPAREN expression RPAREN statement %prec LOWER_THAN_ELSE {
		string s = "if (" + *($3->first) +") " + *($5->first);
		$$ = createPSS(s, *($5->second));
	}
	| IF LPAREN expression RPAREN statement ELSE statement {
		string s = "if ("+*($3->first)+") "+*($5->first) + "\nelse "+ *($7->first);
		string t1 = *($5->second);
		string t2 = *($7->second);
		normalize(t1, t2);
		string type = t1;
		if(t1 != t2){
			errorr("Return type mismatched in if statement else statement");
			if(t1 == "void") type = t2;
			if(t2 == "void") type = t1;
		}
		$$ = createPSS(s, type);
	}
	| WHILE LPAREN expression RPAREN statement {
		print("statement -> WHILE LPAREN expression RPAREN statement");
		$$ = createPSS("while("+*($3->first)+")", "null");
	}
	| PRINTLN LPAREN ID RPAREN SEMICOLON {
		if(table->lookUp($3->getName()) == nullptr){
			string s = "Undeclared variable "+$3->getName();
			errorr(s.c_str());
		}
		print("statement -> PRINTLN LPAREN ID RPAREN SEMICOLON");
		$$ = createPSS("printf("+$3->getName()+");", "null");
	}
	| RETURN expression SEMICOLON {
		print("statement -> RETURN expression SEMICOLON");
		$$ = createPSS("return "+*($2->first)+";", *($2->second));
	}
;

expression_statement : SEMICOLON	{
		$$ = createPSS(";", "VOID");
	}		
	| expression SEMICOLON {
		$$ = createPSS (*($1->first) + ";", *($1->second));
		printPSS(*$$);
	}
;

variable : ID 	{
		print("variable -> ID");
		string type = checkAndValidateID($1->getName(), "0", "NOT_ARRAY");
		$$ = createPSS ($1->getName(), type);
	}
	| ID LTHIRD expression RTHIRD {
		print("variable -> ID LTHIRD expression RTHIRD");
		string type = checkAndValidateID($1->getName(), *($3->first), *($3->second));
		$$ = createPSS ($1->getName() + "[" + *($3->first) + "]", type);
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
		checkAndValidAssign(*($1->second), *($3->second));
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
		checkLogicAndRelExpression(*($1->second), *($3->second));
		$$ = createPSS (*($1->first) +  " " + $2->getName() + " " + *($3->first), "int");
		printPSS(*$$);
	} 	
;

rel_expression	: simple_expression {
		print("rel_expression -> simple_expression");
		$$ = $1;
		printPSS(*$$);
	}
	| simple_expression RELOP simple_expression	{
		print("rel_expression -> simple_expression RELOP simple_expression");
		checkLogicAndRelExpression(*($1->second), *($3->second));
		$$ = createPSS (*($1->first) + " " + $2->getName() + " " + *($3->first), "int");
		printPSS(*$$);
	}
;

simple_expression : term {
		print("simple_expression -> term");
		$$ = $1;
	}
	| simple_expression ADDOP term {
		print("simple_expression -> simple_expression ADDOP term");
		$$ = createPSS(*($1->first) + " " + $2->getName() + " " + *($3->first), getHigherType(*($1->second), *($3->second)));
		// printPSS(*$$);
	}
;

term :	unary_expression {
		print("term -> unary_expression");
		$$ = $1;
	}
	| term MULOP unary_expression {
		print("term -> MULOP unary_expression");
		checkModulusOperator(*($1->second), $2->getName(), *($3->second), *($3->first));
		string type = $2->getName() == "%" ? "int" : getHigherType(*($1->second), *($3->second));
		$$ = createPSS(*($1->first) + " " + $2->getName() + " " + *($3->first), type);
		printPSS(*$$);
	}
;

unary_expression : ADDOP unary_expression {
		print("unary_expression -> ADDOP unary_expression");
		$$ = createPSS ($1->getName() + "" +(*($2->first)), *($2->second));
		printPSS(*$$);
	}
	| NOT unary_expression {
		print("unary_expression -> NOT unary_expression");
		$$ = createPSS ("! "+(*($2->first)),"int");
		// printPSS(*$$);
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
	| ID LPAREN argument_list RPAREN { //TODO TODO
		print("factor -> ID LPAREN argument_list RPAREN");
		validateAndCreateFactor($1, *$3);
		$$ = createPSS ($1->getName() + "(" + getStringFromArgumentList(*$3) + ")", getIdVarType($1->getName()));
	}
	| LPAREN expression RPAREN {
		print("factor -> LPAREN expression RPAREN");
		$$ = createPSS ("("+*($2->first)+")",*($2->second));
		// printPSS(*$$);
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
	| {
		$$ = new vector<pair<string*, string*>*>;
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
	table = new SymbolTable(7);
	errout.open("error.txt");
	yyparse();
	return 0;
}

