/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "1805090.y"

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
vector<pair<string, string> > paramList;
ofstream errout;
ofstream logout;
int errorno = 0;

void yyerror(char *s)
{
	//write your code
}

void errorr(const char *s){
	errorno++;
	errout<<"Error at line "<<yylineno<<": "<<s<<"\n"<<endl;
	logout<<"Error at line "<<yylineno<<": "<<s<<"\n"<<endl;
	// printf("\033[1;31mError at line: %d:  %s \033[0m\n",yylineno, s);
}

void warning(const char *s){
	// printf("\033[1;33mWARNING(at line: %d):  %s \033[0m\n",yylineno, s);
}

void print(string s){
	// cout<<"Line "<<yylineno<<": "<<s<<endl;
	logout<<"Line "<<yylineno<<": "<<s<<endl<<endl;
}
void log(const char *s){
	logout<<s<<endl<<endl;
}

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
			// errorr(("Multiple declaration of "+si->getName()+" in parameter").c_str());
		}
	}
	paramList.clear();
}

vector<SymbolInfo*>* addParameter(vector<SymbolInfo*>* prev, SymbolInfo* id, string specifier, bool flag = true){
	id->setSpec(1);
	// id->setSize(stoi(size));
	id->setVarType(specifier);
	prev->push_back(id);
	paramList.push_back({id->getName(), specifier});
	// printVVector(*prev);
	int sz = prev->size();
	for(int i=0; i<sz; i++){
		if((*prev)[i]->getName() == id->getName()){
			errorr(("Multiple declaration of "+id->getName()+" in parameter").c_str());
		}
	}
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
		builder += v[i]->getVarType() + " " + v[i]->getName();
		if(i != sz - 1) builder += ",";
	}
	builder += ");\n";
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
	if(a == "null" || b == "null") return "null";
	if(a == "void" || b == "void") {
		// errorr("Void function used in expression");
		return "void";
	}
	return "float";
}

void printPSS(pair<string*, string*> pss){
	// cout<<*(pss.first)<<" ("<<*(pss.second)<<")"<<endl;
	// log((*(pss.first)).c_str());
}

string getStringFromDeclarationList(vector<SymbolInfo*> v){
	string builder;
	int sz = v.size();
	for(int i=0; i<sz; i++){
		builder+=v[i]->getName();
		if(v[i]->getSize() != 0) builder+= "["+to_string(v[i]->getSize())+"]";
		if(i != sz - 1) builder += ",";
	}
	return builder;
}


string* createVarDeclaration(string t, vector<SymbolInfo*> v){
	string builder = t+" ";
	builder += getStringFromDeclarationList(v);
	builder+=";";
	return new string(builder);
}


void printVPSS(vector<pair<string*, string*>*> vpss){
	int sz = vpss.size();
	for(int i=0; i<sz; i++){
		printPSS(*vpss[i]);
	}
}

string getStringFromArguments(vector<pair<string*, string*>*> vpss){
	int sz = vpss.size();
	string s = "";
	for(int i=0; i<sz; i++){
		s += *(vpss[i]->first);
		if(i != sz - 1) s+=",";
	}
	return s;
}

vector<pair<string*, string*>*>* addLogicalExpression(vector<pair<string*, string*>*>* vpss, pair<string*, string*>* pss){
	vpss->push_back(pss);
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
	}
}

bool matchParameterSignature(vector<SymbolInfo*>* v1, vector<SymbolInfo*>* v2, string funcName){
	if(v1 == nullptr && v2 == nullptr) {
		return true;
	}
	if(v1 == nullptr) return false;
	if(v2 == nullptr) return false;
	if(v1->size() != v2->size()) {
		errorr(("Total number of arguments mismatch with declaration in function "+funcName).c_str());
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
		return;
	}
	table->insert(si);
	return;
}

void validateAndCreateFactor(SymbolInfo* si, vector<pair<string*, string*>*> v){
	SymbolInfo* found = table->lookUp(si->getName());
	if(found == nullptr){
		errorr(("Undeclared function "+si->getName()).c_str());
	}else if(found->getSpec() != 2){
		errorr((found->getName() + " is not a function").c_str());
	}else if(found->getParams()->size() != v.size()){
		// cout<<found->getParams()->size()<<endl;
		// cout<<v.size()<<endl;
		errorr(("Total number of arguments mismatch in function "+found->getName()).c_str());
	}else if(found->getVarType() == "void" || found->getVarType() == "VOID"){
		// errorr("Void function used in expression");
	}else{
		int sz = v.size();
		vector<SymbolInfo*> v2= *( found->getParams());
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
	if(a == "void") {
		// errorr("CANNOT ASSIGN TO VOID!");
		return;
	}
	if(b == "void"){
		errorr("Void function used in expression");
		return;
	}
	if(a != b){
		// warning(("Trying to assign "+b+" in "+a+" (potential precision loss)").c_str());
		if(a == "float" && b == "int") return;
		if(b == "null") return;
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
		errorr("Type mismatch, function is not void");
		return;
	} 
	if(a == "void" && b!= "void"){
		errorr("Type mismatch, function is void");
		return;
	}
	if(a != b){
		if(a == "float" && b == "int") return;
		errorr("Type mismatch, int function is returning float");
	}
}

void checkMulOp(string t1, string op, string t2, string s2){
	// if(op != "%") return;
	normalize(t1, t2);
	if(op == "%"){
		if(t1 != "int" || t2 != "int") errorr("Non-Integer operand on modulus operator");
		if(s2 == "0") errorr("Modulus by Zero");
	}else if(op == "/"){
		if(s2 == "0" || s2 == "0.0") errorr("Divided by zero");
	}
}

void checkLogicAndRelExpression(string a, string b){
	normalize(a, b);
	if(a == "void") errorr("void expression in logical or relational operation");
	else if(b == "void") errorr("void expression in logical or relational operation");
}

// string getStringFromDeclarationList(vector<SymbolInfo*> vs){
// 	int sz = vs.size();
// 	string s = "";
// 	for(int i=0; i<sz; i++){

// 	}
// }
void deleteMe(string* s){
	if(s != nullptr) delete s;
}
void deleteMe(pair<string*, string*>* pss){
	if(pss == nullptr) return;
	if(pss->first != nullptr) delete pss->first;
	if(pss->second != nullptr) delete pss->second;
	delete pss;
}
void deleteMe(vector<pair<string*, string*>*>* vss){
	if(vss == nullptr) return;
	int sz = vss->size();
	for(int i=0; i<sz; i++){
		deleteMe((*(vss))[i]);
	}
	delete vss;
}
void deleteMe(vector<SymbolInfo*>* vsi){
	if(vsi == nullptr) return;
	int sz = vsi->size();
	for(int i=0; i<sz; i++){
		delete ((*(vsi))[i]);
	}
	delete vsi;
}
void deleteMe(SymbolInfo* si){
	if(si != nullptr)delete si;
}



#line 500 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    INCOP = 258,                   /* INCOP  */
    DECOP = 259,                   /* DECOP  */
    PRINTLN = 260,                 /* PRINTLN  */
    IF = 261,                      /* IF  */
    ELSE = 262,                    /* ELSE  */
    FOR = 263,                     /* FOR  */
    WHILE = 264,                   /* WHILE  */
    DO = 265,                      /* DO  */
    BREAK = 266,                   /* BREAK  */
    INT = 267,                     /* INT  */
    CHAR = 268,                    /* CHAR  */
    FLOAT = 269,                   /* FLOAT  */
    DOUBLE = 270,                  /* DOUBLE  */
    VOID = 271,                    /* VOID  */
    RETURN = 272,                  /* RETURN  */
    SWITCH = 273,                  /* SWITCH  */
    CASE = 274,                    /* CASE  */
    DEFAULT = 275,                 /* DEFAULT  */
    CONTINUE = 276,                /* CONTINUE  */
    NOT = 277,                     /* NOT  */
    LPAREN = 278,                  /* LPAREN  */
    RPAREN = 279,                  /* RPAREN  */
    LCURL = 280,                   /* LCURL  */
    RCURL = 281,                   /* RCURL  */
    LTHIRD = 282,                  /* LTHIRD  */
    RTHIRD = 283,                  /* RTHIRD  */
    COMMA = 284,                   /* COMMA  */
    SEMICOLON = 285,               /* SEMICOLON  */
    CONST_INT = 286,               /* CONST_INT  */
    CONST_FLOAT = 287,             /* CONST_FLOAT  */
    CONST_CHAR = 288,              /* CONST_CHAR  */
    ID = 289,                      /* ID  */
    ADDOP = 290,                   /* ADDOP  */
    MULOP = 291,                   /* MULOP  */
    RELOP = 292,                   /* RELOP  */
    ASSIGNOP = 293,                /* ASSIGNOP  */
    LOGICOP = 294,                 /* LOGICOP  */
    STRING = 295,                  /* STRING  */
    UNCHAR = 296,                  /* UNCHAR  */
    LOWER_THAN_ELSE = 297          /* LOWER_THAN_ELSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define INCOP 258
#define DECOP 259
#define PRINTLN 260
#define IF 261
#define ELSE 262
#define FOR 263
#define WHILE 264
#define DO 265
#define BREAK 266
#define INT 267
#define CHAR 268
#define FLOAT 269
#define DOUBLE 270
#define VOID 271
#define RETURN 272
#define SWITCH 273
#define CASE 274
#define DEFAULT 275
#define CONTINUE 276
#define NOT 277
#define LPAREN 278
#define RPAREN 279
#define LCURL 280
#define RCURL 281
#define LTHIRD 282
#define RTHIRD 283
#define COMMA 284
#define SEMICOLON 285
#define CONST_INT 286
#define CONST_FLOAT 287
#define CONST_CHAR 288
#define ID 289
#define ADDOP 290
#define MULOP 291
#define RELOP 292
#define ASSIGNOP 293
#define LOGICOP 294
#define STRING 295
#define UNCHAR 296
#define LOWER_THAN_ELSE 297

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 430 "1805090.y"

	SymbolInfo* si;
	vector<SymbolInfo*>* vvector;	
	string* sstring;
	pair<string*, string*>* pss;
	vector<pair<string*, string*>*>* vss;

#line 645 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INCOP = 3,                      /* INCOP  */
  YYSYMBOL_DECOP = 4,                      /* DECOP  */
  YYSYMBOL_PRINTLN = 5,                    /* PRINTLN  */
  YYSYMBOL_IF = 6,                         /* IF  */
  YYSYMBOL_ELSE = 7,                       /* ELSE  */
  YYSYMBOL_FOR = 8,                        /* FOR  */
  YYSYMBOL_WHILE = 9,                      /* WHILE  */
  YYSYMBOL_DO = 10,                        /* DO  */
  YYSYMBOL_BREAK = 11,                     /* BREAK  */
  YYSYMBOL_INT = 12,                       /* INT  */
  YYSYMBOL_CHAR = 13,                      /* CHAR  */
  YYSYMBOL_FLOAT = 14,                     /* FLOAT  */
  YYSYMBOL_DOUBLE = 15,                    /* DOUBLE  */
  YYSYMBOL_VOID = 16,                      /* VOID  */
  YYSYMBOL_RETURN = 17,                    /* RETURN  */
  YYSYMBOL_SWITCH = 18,                    /* SWITCH  */
  YYSYMBOL_CASE = 19,                      /* CASE  */
  YYSYMBOL_DEFAULT = 20,                   /* DEFAULT  */
  YYSYMBOL_CONTINUE = 21,                  /* CONTINUE  */
  YYSYMBOL_NOT = 22,                       /* NOT  */
  YYSYMBOL_LPAREN = 23,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 24,                    /* RPAREN  */
  YYSYMBOL_LCURL = 25,                     /* LCURL  */
  YYSYMBOL_RCURL = 26,                     /* RCURL  */
  YYSYMBOL_LTHIRD = 27,                    /* LTHIRD  */
  YYSYMBOL_RTHIRD = 28,                    /* RTHIRD  */
  YYSYMBOL_COMMA = 29,                     /* COMMA  */
  YYSYMBOL_SEMICOLON = 30,                 /* SEMICOLON  */
  YYSYMBOL_CONST_INT = 31,                 /* CONST_INT  */
  YYSYMBOL_CONST_FLOAT = 32,               /* CONST_FLOAT  */
  YYSYMBOL_CONST_CHAR = 33,                /* CONST_CHAR  */
  YYSYMBOL_ID = 34,                        /* ID  */
  YYSYMBOL_ADDOP = 35,                     /* ADDOP  */
  YYSYMBOL_MULOP = 36,                     /* MULOP  */
  YYSYMBOL_RELOP = 37,                     /* RELOP  */
  YYSYMBOL_ASSIGNOP = 38,                  /* ASSIGNOP  */
  YYSYMBOL_LOGICOP = 39,                   /* LOGICOP  */
  YYSYMBOL_STRING = 40,                    /* STRING  */
  YYSYMBOL_UNCHAR = 41,                    /* UNCHAR  */
  YYSYMBOL_LOWER_THAN_ELSE = 42,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 43,                  /* $accept  */
  YYSYMBOL_start = 44,                     /* start  */
  YYSYMBOL_program = 45,                   /* program  */
  YYSYMBOL_unit = 46,                      /* unit  */
  YYSYMBOL_func_declaration = 47,          /* func_declaration  */
  YYSYMBOL_func_definition = 48,           /* func_definition  */
  YYSYMBOL_49_1 = 49,                      /* $@1  */
  YYSYMBOL_50_2 = 50,                      /* $@2  */
  YYSYMBOL_51_3 = 51,                      /* $@3  */
  YYSYMBOL_parameter_list = 52,            /* parameter_list  */
  YYSYMBOL_compound_statement = 53,        /* compound_statement  */
  YYSYMBOL_54_4 = 54,                      /* $@4  */
  YYSYMBOL_var_declaration = 55,           /* var_declaration  */
  YYSYMBOL_type_specifier = 56,            /* type_specifier  */
  YYSYMBOL_declaration_list = 57,          /* declaration_list  */
  YYSYMBOL_statements = 58,                /* statements  */
  YYSYMBOL_statement = 59,                 /* statement  */
  YYSYMBOL_expression_statement = 60,      /* expression_statement  */
  YYSYMBOL_variable = 61,                  /* variable  */
  YYSYMBOL_expression = 62,                /* expression  */
  YYSYMBOL_logic_expression = 63,          /* logic_expression  */
  YYSYMBOL_rel_expression = 64,            /* rel_expression  */
  YYSYMBOL_simple_expression = 65,         /* simple_expression  */
  YYSYMBOL_term = 66,                      /* term  */
  YYSYMBOL_unary_expression = 67,          /* unary_expression  */
  YYSYMBOL_factor = 68,                    /* factor  */
  YYSYMBOL_argument_list = 69,             /* argument_list  */
  YYSYMBOL_arguments = 70                  /* arguments  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  14
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   201

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  79
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  141

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   297


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   451,   451,   464,   473,   481,   487,   494,   502,   511,
     522,   522,   535,   535,   548,   548,   564,   570,   576,   582,
     589,   598,   598,   609,   620,   628,   636,   644,   655,   656,
     657,   660,   665,   671,   677,   683,   688,   694,   702,   710,
     722,   728,   734,   741,   751,   759,   777,   784,   794,   802,
     807,   813,   822,   828,   835,   845,   850,   859,   865,   870,
     879,   884,   893,   898,   906,   911,   921,   928,   935,   942,
     947,   956,   962,   968,   974,   980,   988,   993,   999,  1004
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "INCOP", "DECOP",
  "PRINTLN", "IF", "ELSE", "FOR", "WHILE", "DO", "BREAK", "INT", "CHAR",
  "FLOAT", "DOUBLE", "VOID", "RETURN", "SWITCH", "CASE", "DEFAULT",
  "CONTINUE", "NOT", "LPAREN", "RPAREN", "LCURL", "RCURL", "LTHIRD",
  "RTHIRD", "COMMA", "SEMICOLON", "CONST_INT", "CONST_FLOAT", "CONST_CHAR",
  "ID", "ADDOP", "MULOP", "RELOP", "ASSIGNOP", "LOGICOP", "STRING",
  "UNCHAR", "LOWER_THAN_ELSE", "$accept", "start", "program", "unit",
  "func_declaration", "func_definition", "$@1", "$@2", "$@3",
  "parameter_list", "compound_statement", "$@4", "var_declaration",
  "type_specifier", "declaration_list", "statements", "statement",
  "expression_statement", "variable", "expression", "logic_expression",
  "rel_expression", "simple_expression", "term", "unary_expression",
  "factor", "argument_list", "arguments", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-80)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-21)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     171,    -8,   -80,   -80,   -80,    29,   178,   -80,   -80,   -80,
     -80,    37,    60,    19,   -80,   -80,    35,   146,   -12,   -80,
      54,   -80,    55,   153,   -80,   -80,   -80,    44,    63,   -80,
      72,    49,    -1,    16,   -80,    45,   -80,   -80,    73,    67,
      68,   -80,   -80,   -80,    65,    73,    79,   -80,   -80,    73,
      77,   -80,   -80,   -80,   101,   -80,   -80,    -2,    89,    91,
      93,    96,   139,   166,   139,   -80,   -80,   -80,    38,   166,
     -80,   -80,    -8,    69,   -80,   -80,     8,     9,   -80,    81,
       0,    85,   -80,   -80,   166,    94,   139,   107,   139,    87,
      97,    52,   -80,   110,   166,   121,   -80,   -80,   -80,   -80,
     -80,   166,   -80,   -80,   166,   166,   166,   166,   -80,   122,
     124,   107,   126,   -80,   -80,   -80,   127,   116,   -80,   129,
     -80,   -80,    85,   123,   -80,   130,   101,   139,   101,   -80,
     166,   -80,   -80,   152,   140,   -80,   -80,   101,   101,   -80,
     -80
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,    28,    29,    30,     0,     0,     4,     6,     7,
       5,     0,    35,     0,     1,     3,    35,     0,     0,    26,
       0,    25,     0,     0,    27,    24,    37,     0,    31,    32,
       0,    14,     0,     0,    36,     0,    12,     9,     0,    10,
       0,    19,    18,    34,     0,     0,    21,    15,     8,     0,
      17,    33,    13,    23,     0,    11,    16,     0,     0,     0,
       0,     0,     0,     0,     0,    49,    72,    73,    52,     0,
      42,    40,     0,     0,    38,    41,    69,     0,    55,    58,
      60,    62,    64,    68,     0,     0,     0,     0,     0,     0,
       0,    69,    67,     0,    77,     0,    66,    22,    39,    74,
      75,     0,    51,    50,     0,     0,     0,     0,    57,     0,
       0,     0,     0,    48,    71,    79,     0,    76,    54,     0,
      56,    59,    63,    61,    65,     0,     0,     0,     0,    70,
       0,    53,    47,    44,     0,    46,    78,     0,     0,    45,
      43
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -80,   -80,   -80,   157,   -80,   -80,   -80,   -80,   -80,   -80,
      15,   -80,    18,     7,    -9,   -80,   -69,   -78,   -63,   -61,
     -79,    62,    74,    86,   -55,   -80,   -80,   -80
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     5,     6,     7,     8,     9,    49,    45,    38,    32,
      70,    54,    71,    72,    13,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,   116,   117
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      91,    90,    17,    93,    98,   108,    91,    11,    92,   111,
     102,    99,   100,    11,    96,   115,    26,    41,    10,    27,
      19,    91,   120,    39,    10,   110,    12,   112,    40,    14,
      33,    91,    12,   127,   119,   105,    84,   106,    91,   103,
     -20,    91,    91,    91,    91,   -20,   101,    50,    20,    21,
      42,   136,   124,    47,    22,    99,   100,   133,    23,   135,
      52,    94,    18,    17,    55,    95,   134,    91,   139,   140,
      57,    16,    34,    43,    58,    59,    44,    60,    61,    37,
       2,     2,     3,     3,     4,     4,    62,    18,    28,    29,
      35,    63,    64,    51,    46,    97,    36,    48,    46,    65,
      66,    67,    57,    68,    69,    53,    58,    59,    89,    60,
      61,    56,    85,     2,    86,     3,    87,     4,    62,    88,
     104,   107,    89,    63,    64,    84,    46,   113,   109,    63,
      64,    65,    66,    67,   114,    68,    69,    65,    66,    67,
      89,    68,    69,    63,    64,   130,   125,    24,   126,   118,
     128,   129,    66,    67,    30,    68,    69,   131,   105,   137,
     132,    63,    64,    15,   138,     2,   121,     3,     0,     4,
      66,    67,     1,    68,    69,    20,    25,    31,    -2,     1,
     123,    22,     0,     2,     0,     3,     0,     4,    63,    64,
       2,   122,     3,     0,     4,     0,     0,    66,    67,     0,
      68,    69
};

static const yytype_int16 yycheck[] =
{
      63,    62,    11,    64,    73,    84,    69,     0,    63,    87,
       1,     3,     4,     6,    69,    94,    28,     1,     0,    31,
       1,    84,   101,    24,     6,    86,    34,    88,    29,     0,
      23,    94,    34,   111,    95,    35,    38,    37,   101,    30,
      24,   104,   105,   106,   107,    29,    38,    40,    29,    30,
      34,   130,   107,    38,    35,     3,     4,   126,    23,   128,
      45,    23,    27,    72,    49,    27,   127,   130,   137,   138,
       1,    34,    28,    28,     5,     6,    31,     8,     9,    30,
      12,    12,    14,    14,    16,    16,    17,    27,    34,    34,
      27,    22,    23,    28,    25,    26,    24,    30,    25,    30,
      31,    32,     1,    34,    35,    26,     5,     6,     1,     8,
       9,    34,    23,    12,    23,    14,    23,    16,    17,    23,
      39,    36,     1,    22,    23,    38,    25,    30,    34,    22,
      23,    30,    31,    32,    24,    34,    35,    30,    31,    32,
       1,    34,    35,    22,    23,    29,    24,     1,    24,    28,
      24,    24,    31,    32,     1,    34,    35,    28,    35,     7,
      30,    22,    23,     6,    24,    12,   104,    14,    -1,    16,
      31,    32,     1,    34,    35,    29,    30,    24,     0,     1,
     106,    35,    -1,    12,    -1,    14,    -1,    16,    22,    23,
      12,   105,    14,    -1,    16,    -1,    -1,    31,    32,    -1,
      34,    35
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,    12,    14,    16,    44,    45,    46,    47,    48,
      55,    56,    34,    57,     0,    46,    34,    57,    27,     1,
      29,    30,    35,    23,     1,    30,    28,    31,    34,    34,
       1,    24,    52,    56,    28,    27,    24,    30,    51,    24,
      29,     1,    34,    28,    31,    50,    25,    53,    30,    49,
      56,    28,    53,    26,    54,    53,    34,     1,     5,     6,
       8,     9,    17,    22,    23,    30,    31,    32,    34,    35,
      53,    55,    56,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    38,    23,    23,    23,    23,     1,
      62,    61,    67,    62,    23,    27,    67,    26,    59,     3,
       4,    38,     1,    30,    39,    35,    37,    36,    63,    34,
      62,    60,    62,    30,    24,    63,    69,    70,    28,    62,
      63,    64,    66,    65,    67,    24,    24,    60,    24,    24,
      29,    28,    30,    59,    62,    59,    63,     7,    24,    59,
      59
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    43,    44,    45,    45,    46,    46,    46,    47,    47,
      49,    48,    50,    48,    51,    48,    52,    52,    52,    52,
      52,    54,    53,    53,    55,    55,    55,    55,    56,    56,
      56,    57,    57,    57,    57,    57,    57,    57,    58,    58,
      59,    59,    59,    59,    59,    59,    59,    59,    59,    60,
      60,    60,    61,    61,    61,    62,    62,    62,    63,    63,
      64,    64,    65,    65,    66,    66,    67,    67,    67,    68,
      68,    68,    68,    68,    68,    68,    69,    69,    70,    70
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     6,     5,
       0,     7,     0,     7,     0,     6,     4,     3,     2,     2,
       1,     0,     4,     2,     3,     3,     3,     3,     1,     1,
       1,     3,     3,     6,     5,     1,     4,     3,     1,     2,
       1,     1,     1,     7,     5,     7,     5,     5,     3,     1,
       2,     2,     1,     4,     3,     1,     3,     3,     1,     3,
       1,     3,     1,     3,     1,     3,     2,     2,     1,     1,
       4,     3,     1,     1,     2,     2,     1,     0,     3,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* start: program  */
#line 451 "1805090.y"
                {
		print("start : program");
		(yyval.pss) = (yyvsp[0].pss);
		table->printAll(logout);
		logout<<"Total lines: "<<yylineno<<endl;
		logout<<"Total errors: "<<errorno<<endl<<endl;
		// cout<<*($$->first)<<endl;
		// log((*($$->first) ).c_str());
		// cout<<"eikhane ken ashe?"<<endl;
		//write your code in this block in all the similar blocks below
	}
#line 1812 "y.tab.c"
    break;

  case 3: /* program: program unit  */
#line 464 "1805090.y"
                       {
		print("program : program unit");
		string fst = (*((yyvsp[-1].pss)->first)+*((yyvsp[0].pss)->first));
		(yyval.pss) = createPSS(fst, "null");
		log((*((yyval.pss)->first)).c_str());
		// cout<<*$$<<endl;
		deleteMe((yyvsp[-1].pss));
		deleteMe((yyvsp[0].pss));
	}
#line 1826 "y.tab.c"
    break;

  case 4: /* program: unit  */
#line 473 "1805090.y"
               {
		print("program : unit");
		(yyval.pss) = (yyvsp[0].pss);
		log((*((yyval.pss)->first)).c_str());
		// cout<<*$$<<endl;
	}
#line 1837 "y.tab.c"
    break;

  case 5: /* unit: var_declaration  */
#line 481 "1805090.y"
                       {
		print("unit : var_declaration");
		(yyval.pss) = createPSS(*((yyvsp[0].sstring)) + "\n", "null");
		log((*((yyval.pss)->first) ).c_str());
		deleteMe((yyvsp[0].sstring));
	}
#line 1848 "y.tab.c"
    break;

  case 6: /* unit: func_declaration  */
#line 487 "1805090.y"
                           {
		print("unit : func_declaration");
		(yyval.pss) = createPSS(*((yyvsp[0].sstring)), "null");
		paramList.clear();
		log((*((yyval.pss)->first)).c_str());
		deleteMe((yyvsp[0].sstring));
	}
#line 1860 "y.tab.c"
    break;

  case 7: /* unit: func_definition  */
#line 494 "1805090.y"
                          {
		print("unit : func_definition");
		(yyval.pss) = createPSS((*((yyvsp[0].pss))->first+"\n"), "null");
		log((*((yyval.pss)->first)).c_str());
		deleteMe((yyvsp[0].pss));
	}
#line 1871 "y.tab.c"
    break;

  case 8: /* func_declaration: type_specifier ID LPAREN parameter_list RPAREN SEMICOLON  */
#line 502 "1805090.y"
                                                                            {
		print("func_declaration : type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");
		insertFunctionIdToSymbolTable((yyvsp[-4].si), *(yyvsp[-5].sstring), false, (yyvsp[-2].vvector));
		(yyval.sstring) = createFunctionDeclaration(*(yyvsp[-5].sstring), (yyvsp[-4].si)->getName(), *(yyvsp[-2].vvector));
		// cout<<(*$$)<<endl;
		table->enterScope(); table->exitScope();
		log((*(yyval.sstring)).c_str());
		deleteMe((yyvsp[-5].sstring));
	}
#line 1885 "y.tab.c"
    break;

  case 9: /* func_declaration: type_specifier ID LPAREN RPAREN SEMICOLON  */
#line 511 "1805090.y"
                                                    {
		print("func_declaration : type_specifier ID LPAREN RPAREN SEMICOLON");
		insertFunctionIdToSymbolTable((yyvsp[-3].si), *(yyvsp[-4].sstring), false, new vector<SymbolInfo*>);
		(yyval.sstring) = new string((*(yyvsp[-4].sstring)) + " " + ((yyvsp[-3].si)->getName()) + "();\n");
		// cout<<(*$$)<<endl;
		table->enterScope(); table->exitScope();
		log((*(yyval.sstring) ).c_str());
		deleteMe((yyvsp[-4].sstring));
	}
#line 1899 "y.tab.c"
    break;

  case 10: /* $@1: %empty  */
#line 522 "1805090.y"
                                                                 {
			insertFunctionIdToSymbolTable((yyvsp[-3].si), *(yyvsp[-4].sstring), true, (yyvsp[-1].vvector));
		}
#line 1907 "y.tab.c"
    break;

  case 11: /* func_definition: type_specifier ID LPAREN parameter_list RPAREN $@1 compound_statement  */
#line 524 "1805090.y"
                                     {
		print("func_definition : type_specifier ID LPAREN parameter_list RPAREN compound_statement");
		// insertFunctionIdToSymbolTable($2, *$1, true, $4);
		warning((*((yyvsp[0].pss)->second)+", " + *((yyvsp[-6].sstring))).c_str());
		chekAndValidateFunctionSignature(*((yyvsp[-6].sstring)), *((yyvsp[0].pss)->second));
		(yyval.pss) = createPSS((*(yyvsp[-6].sstring) + " " + (yyvsp[-5].si)->getName() + "(" + getParamList(*(yyvsp[-3].vvector)) +")" + *((yyvsp[0].pss)->first)), *((yyvsp[0].pss)->second));
		string s = *((yyval.pss)->first); 
		warning(s.c_str());
		log((*((yyval.pss)->first) ).c_str());
		deleteMe((yyvsp[-6].sstring));
	}
#line 1923 "y.tab.c"
    break;

  case 12: /* $@2: %empty  */
#line 535 "1805090.y"
                                                 {
			insertFunctionIdToSymbolTable((yyvsp[-3].si), *(yyvsp[-4].sstring), true, new vector<SymbolInfo*>);
		}
#line 1931 "y.tab.c"
    break;

  case 13: /* func_definition: type_specifier ID LPAREN error RPAREN $@2 compound_statement  */
#line 537 "1805090.y"
                                     {
		print("func_definition : type_specifier ID LPAREN error RPAREN compound_statement");
		// insertFunctionIdToSymbolTable($2, *$1, true, $4);
		warning((*((yyvsp[0].pss)->second)+", " + *((yyvsp[-6].sstring))).c_str());
		chekAndValidateFunctionSignature(*((yyvsp[-6].sstring)), *((yyvsp[0].pss)->second));
		(yyval.pss) = createPSS((*(yyvsp[-6].sstring) + " " + (yyvsp[-5].si)->getName() + "(" + getParamList(*(new vector<SymbolInfo*>)) +")" + *((yyvsp[0].pss)->first)), *((yyvsp[0].pss)->second));
		string s = *((yyval.pss)->first); 
		warning(s.c_str());
		log((*((yyval.pss)->first) ).c_str());
		deleteMe((yyvsp[-6].sstring));
	}
#line 1947 "y.tab.c"
    break;

  case 14: /* $@3: %empty  */
#line 548 "1805090.y"
                                          {
			insertFunctionIdToSymbolTable((yyvsp[-2].si), *(yyvsp[-3].sstring), true, new vector<SymbolInfo*>);
		}
#line 1955 "y.tab.c"
    break;

  case 15: /* func_definition: type_specifier ID LPAREN RPAREN $@3 compound_statement  */
#line 550 "1805090.y"
                                     {
		// errorr("eikhane ekhane!");
		print("func_definition : type_specifier ID LPAREN RPAREN compound_statement");
		string fst = *(yyvsp[-5].sstring) + " " + (yyvsp[-4].si)->getName() + "()" + *((yyvsp[0].pss)->first);
		chekAndValidateFunctionSignature(*((yyvsp[-5].sstring)), *((yyvsp[0].pss)->second));
		(yyval.pss) = createPSS(fst, *((yyvsp[0].pss)->second));
		warning((*((yyvsp[0].pss)->second)+", " + *((yyvsp[-5].sstring))).c_str());
		// log((*($$->first)).c_str());
		log((*((yyval.pss)->first) ).c_str());
		deleteMe((yyvsp[-5].sstring));
		// cout<<*$$<<endl;
	}
#line 1972 "y.tab.c"
    break;

  case 16: /* parameter_list: parameter_list COMMA type_specifier ID  */
#line 564 "1805090.y"
                                                         {
		print("parameter_list : parameter_list COMMA type_specifier ID");
		(yyval.vvector) = addParameter((yyvsp[-3].vvector), (yyvsp[0].si), *(yyvsp[-1].sstring));
		log(getParamList(*(yyval.vvector)).c_str());
		deleteMe((yyvsp[-1].sstring));
	}
#line 1983 "y.tab.c"
    break;

  case 17: /* parameter_list: parameter_list COMMA type_specifier  */
#line 570 "1805090.y"
                                              {
		print("parameter_list : parameter_list COMMA type_specifier");
		(yyval.vvector) = addParameter((yyvsp[-2].vvector), new SymbolInfo("", *(yyvsp[0].sstring)), *(yyvsp[0].sstring));
		log(getParamList(*(yyval.vvector)).c_str());
		deleteMe((yyvsp[0].sstring));
	}
#line 1994 "y.tab.c"
    break;

  case 18: /* parameter_list: type_specifier ID  */
#line 576 "1805090.y"
                            {
		print("parameter_list : type_specifier ID");
		(yyval.vvector) = addParameter(new vector<SymbolInfo*>, (yyvsp[0].si), *(yyvsp[-1].sstring));
		log(getParamList(*(yyval.vvector)).c_str());
		deleteMe((yyvsp[-1].sstring));
	}
#line 2005 "y.tab.c"
    break;

  case 19: /* parameter_list: type_specifier error  */
#line 582 "1805090.y"
                               {
		errorr("Syntax error");
		print("parameter_list : type_specifier error");
		(yyval.vvector) = addParameter(new vector<SymbolInfo*>, new SymbolInfo("XX", (*(yyvsp[-1].sstring))), *(yyvsp[-1].sstring));
		// log((*($$->first)).c_str());
		log(getParamList(*(yyval.vvector)).c_str());
	}
#line 2017 "y.tab.c"
    break;

  case 20: /* parameter_list: type_specifier  */
#line 589 "1805090.y"
                         {
		print("parameter_list : type_specifier");
		(yyval.vvector) = addParameter(new vector<SymbolInfo*>, new SymbolInfo("", (*(yyvsp[0].sstring))), *(yyvsp[0].sstring));
		// log((*($$->first)).c_str());
		log(getParamList(*(yyval.vvector)).c_str());
		deleteMe((yyvsp[0].sstring));
	}
#line 2029 "y.tab.c"
    break;

  case 21: /* $@4: %empty  */
#line 598 "1805090.y"
                           {table->enterScope(); addParamsToScopeTable();}
#line 2035 "y.tab.c"
    break;

  case 22: /* compound_statement: LCURL $@4 statements RCURL  */
#line 598 "1805090.y"
                                                                                            {
		print("compound_statement : LCURL statements RCURL");
		// $$ = new string("{\n"+*($3)+"\n}");
		// cout<<*$$<<endl;
		(yyval.pss) = createPSS(("{\n"+*((yyvsp[-1].pss)->first)+"}\n").c_str(), *((yyvsp[-1].pss)->second));
		log((*((yyval.pss)->first)).c_str());
		table->printAll(logout);
		table->exitScope();
		deleteMe((yyvsp[-1].pss));
		// log((*($$->first)).c_str());
	}
#line 2051 "y.tab.c"
    break;

  case 23: /* compound_statement: LCURL RCURL  */
#line 609 "1805090.y"
                      {
		print("compound_statement : LCURL RCURL");
		(yyval.pss) = createPSS("{}\n", "void");
		table->enterScope(); 
		table->printAll(logout);
		table->exitScope();
		// log((*($$->first)).c_str());
		log((*((yyval.pss)->first)).c_str());
	}
#line 2065 "y.tab.c"
    break;

  case 24: /* var_declaration: type_specifier declaration_list SEMICOLON  */
#line 620 "1805090.y"
                                                            {
		print("var_declaration : type_specifier declaration_list SEMICOLON");
		(yyval.sstring) = createVarDeclaration(*(yyvsp[-2].sstring), *(yyvsp[-1].vvector));
		insertToSymbolTable(*(yyvsp[-2].sstring), *(yyvsp[-1].vvector));
		// cout<<(*$$)<<endl;
		log((*(yyval.sstring)).c_str());
		deleteMe((yyvsp[-2].sstring));
	}
#line 2078 "y.tab.c"
    break;

  case 25: /* var_declaration: error declaration_list SEMICOLON  */
#line 628 "1805090.y"
                                           {
		print("var_declaration : type_specifier declaration_list SEMICOLON");
		(yyval.sstring) = createVarDeclaration("null", *(yyvsp[-1].vvector));
		insertToSymbolTable("null", *(yyvsp[-1].vvector));
		errorr("type_specifier not specified");
		// cout<<(*$$)<<endl;
		log((*(yyval.sstring)).c_str());
	}
#line 2091 "y.tab.c"
    break;

  case 26: /* var_declaration: error declaration_list error  */
#line 636 "1805090.y"
                                       {
		print("var_declaration : type_specifier declaration_list SEMICOLON");
		(yyval.sstring) = createVarDeclaration("void", *(yyvsp[-1].vvector));
		insertToSymbolTable("void", *(yyvsp[-1].vvector));
		errorr("type_specifier not specified, missing semicolon");
		// cout<<(*$$)<<endl;
		log((*(yyval.sstring)).c_str());
	}
#line 2104 "y.tab.c"
    break;

  case 27: /* var_declaration: type_specifier declaration_list error  */
#line 644 "1805090.y"
                                                {
		print("var_declaration : type_specifier declaration_list SEMICOLON");
		(yyval.sstring) = createVarDeclaration(*(yyvsp[-2].sstring), *(yyvsp[-1].vvector));
		insertToSymbolTable(*(yyvsp[-2].sstring), *(yyvsp[-1].vvector));
		errorr("missing semicolon");
		log((*(yyval.sstring)).c_str());
		deleteMe((yyvsp[-2].sstring));
		// cout<<(*$$)<<endl;
	}
#line 2118 "y.tab.c"
    break;

  case 28: /* type_specifier: INT  */
#line 655 "1805090.y"
                      {print("type_specifier : INT"); (yyval.sstring) = new string("int"); log("int");}
#line 2124 "y.tab.c"
    break;

  case 29: /* type_specifier: FLOAT  */
#line 656 "1805090.y"
                {print("type_specifier : FLOAT"); (yyval.sstring) = new string("float"); log("float");}
#line 2130 "y.tab.c"
    break;

  case 30: /* type_specifier: VOID  */
#line 657 "1805090.y"
               {print("type_specifier : VOID"); (yyval.sstring) = new string("void"); log("void");}
#line 2136 "y.tab.c"
    break;

  case 31: /* declaration_list: declaration_list COMMA ID  */
#line 660 "1805090.y"
                                             {
		print("declaration_list : declaration_list COMMA ID");
		(yyval.vvector) = addDeclaration((yyvsp[-2].vvector), (yyvsp[0].si), "0");
		log(getStringFromDeclarationList(*(yyval.vvector)).c_str());
	}
#line 2146 "y.tab.c"
    break;

  case 32: /* declaration_list: declaration_list ADDOP ID  */
#line 665 "1805090.y"
                                    {
		errorr("Syntax error, ADDOP used instead of semicolon");
		print("declaration_list : declaration_list COMMA ID");
		(yyval.vvector) = addDeclaration((yyvsp[-2].vvector), (yyvsp[0].si), "0");
		log(getStringFromDeclarationList(*(yyval.vvector)).c_str());
	}
#line 2157 "y.tab.c"
    break;

  case 33: /* declaration_list: declaration_list COMMA ID LTHIRD CONST_INT RTHIRD  */
#line 671 "1805090.y"
                                                            {
		print("declaration_list : declaration_list COMMA ID LTHIRD CONST_INT RTHIRD");
		(yyval.vvector) = addDeclaration((yyvsp[-5].vvector), (yyvsp[-3].si), (yyvsp[-1].si)->getName());	
		log(getStringFromDeclarationList(*(yyval.vvector)).c_str());
		deleteMe((yyvsp[-1].si));
	}
#line 2168 "y.tab.c"
    break;

  case 34: /* declaration_list: declaration_list COMMA ID LTHIRD RTHIRD  */
#line 677 "1805090.y"
                                                  {
		print("declaration_list : declaration_list COMMA ID LTHIRD RTHIRD");
		errorr("Syntax error, no expresison inside third third brackets");
		(yyval.vvector) = addDeclaration((yyvsp[-4].vvector), (yyvsp[-2].si), "1");	
		log(getStringFromDeclarationList(*(yyval.vvector)).c_str());
	}
#line 2179 "y.tab.c"
    break;

  case 35: /* declaration_list: ID  */
#line 683 "1805090.y"
             {	
		print("declaration_list : ID");
		(yyval.vvector) = addDeclaration(new vector<SymbolInfo*>, (yyvsp[0].si), "0");
		log(getStringFromDeclarationList(*(yyval.vvector)).c_str());
	}
#line 2189 "y.tab.c"
    break;

  case 36: /* declaration_list: ID LTHIRD CONST_INT RTHIRD  */
#line 688 "1805090.y"
                                     {	
		print("declaration_list : ID LTHIRD CONST_INT RTHIRD");
		(yyval.vvector) = addDeclaration(new vector<SymbolInfo*>, (yyvsp[-3].si), (yyvsp[-1].si)->getName());
		log(getStringFromDeclarationList(*(yyval.vvector)).c_str());
		deleteMe((yyvsp[-1].si));
	}
#line 2200 "y.tab.c"
    break;

  case 37: /* declaration_list: ID LTHIRD RTHIRD  */
#line 694 "1805090.y"
                           {	
		print("declaration_list : ID LTHIRD RTHIRD");
		errorr("Syntax error, no expresison inside third third brackets");
		(yyval.vvector) = addDeclaration(new vector<SymbolInfo*>, (yyvsp[-2].si), "1");
		log(getStringFromDeclarationList(*(yyval.vvector)).c_str());
	}
#line 2211 "y.tab.c"
    break;

  case 38: /* statements: statement  */
#line 702 "1805090.y"
                       {
		print("statements : statement");
		(yyval.pss) = createPSS(*((yyvsp[0].pss)->first), *((yyvsp[0].pss)->second));
		// cout<<'\t'<<(*$$)<<endl;
		// log((*($$->first)).c_str());
		log((*((yyval.pss)->first)).c_str());
		deleteMe((yyvsp[0].pss));
	}
#line 2224 "y.tab.c"
    break;

  case 39: /* statements: statements statement  */
#line 710 "1805090.y"
                               {
		print("statements : statements statement");
		string type = getReturnType(*((yyvsp[-1].pss)->second), *((yyvsp[0].pss)->second));
		(yyval.pss) = createPSS(*((yyvsp[-1].pss)->first)+*((yyvsp[0].pss)->first), type);
		// cout<<(*$$)<<endl;
		// log((*($$->first)).c_str());
		log((*((yyval.pss)->first)).c_str());
		deleteMe((yyvsp[-1].pss));
		deleteMe((yyvsp[0].pss));
	}
#line 2239 "y.tab.c"
    break;

  case 40: /* statement: var_declaration  */
#line 722 "1805090.y"
                            {
		print("statement : var_declaration");
		(yyval.pss) = createPSS(*(yyvsp[0].sstring)+"\n", "null");
		log((*((yyval.pss)->first)).c_str());
		deleteMe((yyvsp[0].sstring));
	}
#line 2250 "y.tab.c"
    break;

  case 41: /* statement: expression_statement  */
#line 728 "1805090.y"
                               {
		print("statement : expression_statement");
		(yyval.pss) = createPSS(*((yyvsp[0].pss)->first) + "\n", "null");
		log((*((yyval.pss)->first)).c_str());
		deleteMe((yyvsp[0].pss));
	}
#line 2261 "y.tab.c"
    break;

  case 42: /* statement: compound_statement  */
#line 734 "1805090.y"
                             {
		print("statement : compound_statement");
		// $$ = createPSS(*$1, *($1-.second));
		// $$ = createPSS(*($1->first), *($1->second));
		(yyval.pss) = (yyvsp[0].pss);
		log((*((yyval.pss)->first)).c_str());
	}
#line 2273 "y.tab.c"
    break;

  case 43: /* statement: FOR LPAREN expression_statement expression_statement expression RPAREN statement  */
#line 741 "1805090.y"
                                                                                           {
		print("statement : FOR LPAREN expression_statement expression_statement expression RPAREN statement");
		string s = "for(" + *((yyvsp[-4].pss)->first) + *((yyvsp[-3].pss)->first)  + *((yyvsp[-2].pss)->first) + ")" + *((yyvsp[0].pss)->first) ; 
		(yyval.pss) = createPSS(s, *((yyvsp[0].pss)->second));
		log((*((yyval.pss)->first)).c_str());
		deleteMe((yyvsp[-4].pss));
		deleteMe((yyvsp[-3].pss));
		deleteMe((yyvsp[-2].pss));
		deleteMe((yyvsp[0].pss));
	}
#line 2288 "y.tab.c"
    break;

  case 44: /* statement: IF LPAREN expression RPAREN statement  */
#line 751 "1805090.y"
                                                                      {
		print("statement : IF LPAREN expression RPAREN statement");
		string s = "if (" + *((yyvsp[-2].pss)->first) +")" + *((yyvsp[0].pss)->first);
		(yyval.pss) = createPSS(s, *((yyvsp[0].pss)->second));
		log((*((yyval.pss)->first)).c_str());
		deleteMe((yyvsp[-2].pss));
		deleteMe((yyvsp[0].pss));
	}
#line 2301 "y.tab.c"
    break;

  case 45: /* statement: IF LPAREN expression RPAREN statement ELSE statement  */
#line 759 "1805090.y"
                                                               {
		print("statement : IF LPAREN expression RPAREN statement ELSE statement");
		string s = "if ("+*((yyvsp[-4].pss)->first)+")"+*((yyvsp[-2].pss)->first) + "else\n"+ *((yyvsp[0].pss)->first) ;
		string t1 = *((yyvsp[-2].pss)->second);
		string t2 = *((yyvsp[0].pss)->second);
		normalize(t1, t2);
		string type = t1;
		if(t1 != t2){
			errorr("Return type mismatched in if statement else statement");
			if(t1 == "void") type = t2;
			if(t2 == "void") type = t1;
		}
		(yyval.pss) = createPSS(s, type);
		log((*((yyval.pss)->first)).c_str());
		deleteMe((yyvsp[-4].pss));
		deleteMe((yyvsp[-2].pss));
		deleteMe((yyvsp[0].pss));
	}
#line 2324 "y.tab.c"
    break;

  case 46: /* statement: WHILE LPAREN expression RPAREN statement  */
#line 777 "1805090.y"
                                                   {
		print("statement : WHILE LPAREN expression RPAREN statement");
		(yyval.pss) = createPSS("while ("+*((yyvsp[-2].pss)->first)+")"+*((yyvsp[0].pss)->first), "null");
		log((*((yyval.pss)->first)).c_str());
		deleteMe((yyvsp[-2].pss));
		deleteMe((yyvsp[0].pss));
	}
#line 2336 "y.tab.c"
    break;

  case 47: /* statement: PRINTLN LPAREN ID RPAREN SEMICOLON  */
#line 784 "1805090.y"
                                             {
		print("statement : PRINTLN LPAREN ID RPAREN SEMICOLON");
		if(table->lookUp((yyvsp[-2].si)->getName()) == nullptr){
			string s = "Undeclared variable "+(yyvsp[-2].si)->getName();
			errorr(s.c_str());
		}
		(yyval.pss) = createPSS("printf("+(yyvsp[-2].si)->getName()+");\n", "null");
		log((*((yyval.pss)->first)).c_str());
		deleteMe((yyvsp[-2].si));
	}
#line 2351 "y.tab.c"
    break;

  case 48: /* statement: RETURN expression SEMICOLON  */
#line 794 "1805090.y"
                                      {
		print("statement : RETURN expression SEMICOLON");
		(yyval.pss) = createPSS("return "+*((yyvsp[-1].pss)->first)+";\n", *((yyvsp[-1].pss)->second));
		log((*((yyval.pss)->first)).c_str());
		deleteMe((yyvsp[-1].pss));
	}
#line 2362 "y.tab.c"
    break;

  case 49: /* expression_statement: SEMICOLON  */
#line 802 "1805090.y"
                                        {
		print("expression_statement : SEMICOLON");
		(yyval.pss) = createPSS(";", "VOID");
		log((*((yyval.pss)->first)).c_str());
	}
#line 2372 "y.tab.c"
    break;

  case 50: /* expression_statement: expression SEMICOLON  */
#line 807 "1805090.y"
                               {
		print("expression_statement : expression SEMICOLON");
		(yyval.pss) = createPSS (*((yyvsp[-1].pss)->first) + ";", *((yyvsp[-1].pss)->second));
		log((*((yyval.pss)->first)).c_str());
		deleteMe((yyvsp[-1].pss));
	}
#line 2383 "y.tab.c"
    break;

  case 51: /* expression_statement: expression error  */
#line 813 "1805090.y"
                          {
		errorr("Syntax error, semicolon missing.");
		print("expression_statement : expression");
		(yyval.pss) = createPSS (*((yyvsp[-1].pss)->first) + ";", *((yyvsp[-1].pss)->second));
		log((*((yyval.pss)->first)).c_str());
		deleteMe((yyvsp[-1].pss));
	}
#line 2395 "y.tab.c"
    break;

  case 52: /* variable: ID  */
#line 822 "1805090.y"
                {
		print("variable : ID");
		string type = checkAndValidateID((yyvsp[0].si)->getName(), "0", "NOT_ARRAY");
		(yyval.pss) = createPSS ((yyvsp[0].si)->getName(), type);
		log((*((yyval.pss)->first)).c_str());
	}
#line 2406 "y.tab.c"
    break;

  case 53: /* variable: ID LTHIRD expression RTHIRD  */
#line 828 "1805090.y"
                                      {
		print("variable : ID LTHIRD expression RTHIRD");
		string type = checkAndValidateID((yyvsp[-3].si)->getName(), *((yyvsp[-1].pss)->first), *((yyvsp[-1].pss)->second));
		(yyval.pss) = createPSS ((yyvsp[-3].si)->getName() + "[" + *((yyvsp[-1].pss)->first) + "]", type);
		log((*((yyval.pss)->first)).c_str());
		deleteMe((yyvsp[-3].si));deleteMe((yyvsp[-1].pss));
	}
#line 2418 "y.tab.c"
    break;

  case 54: /* variable: ID LTHIRD RTHIRD  */
#line 835 "1805090.y"
                           {
		print("variable : ID LTHIRD RTHIRD");
		errorr("Syntax error, no expression inside third bracekts");
		string type = checkAndValidateID((yyvsp[-2].si)->getName(), "0", "CONST_INT");
		(yyval.pss) = createPSS ((yyvsp[-2].si)->getName() + "[]", type);
		log((*((yyval.pss)->first)).c_str());
		deleteMe((yyvsp[-2].si));
	}
#line 2431 "y.tab.c"
    break;

  case 55: /* expression: logic_expression  */
#line 845 "1805090.y"
                              {
		print("expression : logic_expression");
		(yyval.pss) = createPSS(*((yyvsp[0].pss)->first) , *((yyvsp[0].pss)->second));
		log((*((yyval.pss)->first)).c_str());
	}
#line 2441 "y.tab.c"
    break;

  case 56: /* expression: variable ASSIGNOP logic_expression  */
#line 850 "1805090.y"
                                             {
		// cout<<"\t\t\t\teikhane keno ashe?"<<endl;
		//TODO eikhane onek kahini kora lagbe 
		print("expression : variable ASSIGNOP logic_expression");
		checkAndValidAssign(*((yyvsp[-2].pss)->second), *((yyvsp[0].pss)->second));
		(yyval.pss) = createPSS (*((yyvsp[-2].pss)->first) + "=" + *((yyvsp[0].pss)->first), *((yyvsp[-2].pss)->second));
		log((*((yyval.pss)->first)).c_str());
		deleteMe((yyvsp[-2].pss));deleteMe((yyvsp[0].pss));
	}
#line 2455 "y.tab.c"
    break;

  case 57: /* expression: error ASSIGNOP logic_expression  */
#line 859 "1805090.y"
                                          {
		errorr("Syntax error");
		(yyval.pss) = createPSS("", "null");
	}
#line 2464 "y.tab.c"
    break;

  case 58: /* logic_expression: rel_expression  */
#line 865 "1805090.y"
                                  {
		print("logic_expression : rel_expression");
		(yyval.pss) = (yyvsp[0].pss);
		log((*((yyval.pss)->first)).c_str());
	}
#line 2474 "y.tab.c"
    break;

  case 59: /* logic_expression: rel_expression LOGICOP rel_expression  */
#line 870 "1805090.y"
                                                {
		print("logic_expression : rel_expression LOGICOP rel_expression");
		checkLogicAndRelExpression(*((yyvsp[-2].pss)->second), *((yyvsp[0].pss)->second));
		(yyval.pss) = createPSS (*((yyvsp[-2].pss)->first) + (yyvsp[-1].si)->getName() + *((yyvsp[0].pss)->first), "int");
		log((*((yyval.pss)->first)).c_str());
		deleteMe((yyvsp[-2].pss));deleteMe((yyvsp[-1].si));deleteMe((yyvsp[0].pss));
	}
#line 2486 "y.tab.c"
    break;

  case 60: /* rel_expression: simple_expression  */
#line 879 "1805090.y"
                                    {
		print("rel_expression : simple_expression");
		(yyval.pss) = (yyvsp[0].pss);
		log((*((yyval.pss)->first)).c_str());
	}
#line 2496 "y.tab.c"
    break;

  case 61: /* rel_expression: simple_expression RELOP simple_expression  */
#line 884 "1805090.y"
                                                        {
		print("rel_expression : simple_expression RELOP simple_expression");
		checkLogicAndRelExpression(*((yyvsp[-2].pss)->second), *((yyvsp[0].pss)->second));
		(yyval.pss) = createPSS (*((yyvsp[-2].pss)->first) + (yyvsp[-1].si)->getName() + *((yyvsp[0].pss)->first), "int");
		log((*((yyval.pss)->first)).c_str());
		deleteMe((yyvsp[-2].pss));deleteMe((yyvsp[0].pss));
	}
#line 2508 "y.tab.c"
    break;

  case 62: /* simple_expression: term  */
#line 893 "1805090.y"
                         {
		print("simple_expression : term");
		(yyval.pss) = (yyvsp[0].pss);
		log((*((yyval.pss)->first)).c_str());
	}
#line 2518 "y.tab.c"
    break;

  case 63: /* simple_expression: simple_expression ADDOP term  */
#line 898 "1805090.y"
                                       {
		print("simple_expression : simple_expression ADDOP term");
		(yyval.pss) = createPSS(*((yyvsp[-2].pss)->first) + (yyvsp[-1].si)->getName() + *((yyvsp[0].pss)->first), getHigherType(*((yyvsp[-2].pss)->second), *((yyvsp[0].pss)->second)));
		log((*((yyval.pss)->first)).c_str());
		deleteMe((yyvsp[-2].pss));deleteMe((yyvsp[-1].si));deleteMe((yyvsp[0].pss));
	}
#line 2529 "y.tab.c"
    break;

  case 64: /* term: unary_expression  */
#line 906 "1805090.y"
                         {
		print("term : unary_expression");
		(yyval.pss) = (yyvsp[0].pss);
		log((*((yyval.pss)->first)).c_str());
	}
#line 2539 "y.tab.c"
    break;

  case 65: /* term: term MULOP unary_expression  */
#line 911 "1805090.y"
                                      {
		print("term : term MULOP unary_expression");
		checkMulOp(*((yyvsp[-2].pss)->second), (yyvsp[-1].si)->getName(), *((yyvsp[0].pss)->second), *((yyvsp[0].pss)->first));
		string type = (yyvsp[-1].si)->getName() == "%" ? "int" : getHigherType(*((yyvsp[-2].pss)->second), *((yyvsp[0].pss)->second));
		(yyval.pss) = createPSS(*((yyvsp[-2].pss)->first) + (yyvsp[-1].si)->getName() + *((yyvsp[0].pss)->first), type);
		log((*((yyval.pss)->first)).c_str());
		deleteMe((yyvsp[-2].pss));deleteMe((yyvsp[-1].si));deleteMe((yyvsp[0].pss));
	}
#line 2552 "y.tab.c"
    break;

  case 66: /* unary_expression: ADDOP unary_expression  */
#line 921 "1805090.y"
                                          {
		print("unary_expression : ADDOP unary_expression");
		(yyval.pss) = createPSS ((yyvsp[-1].si)->getName() + "" +(*((yyvsp[0].pss)->first)), *((yyvsp[0].pss)->second));
		log((*((yyval.pss)->first)).c_str());
		deleteMe((yyvsp[-1].si));
		deleteMe((yyvsp[0].pss));
	}
#line 2564 "y.tab.c"
    break;

  case 67: /* unary_expression: NOT unary_expression  */
#line 928 "1805090.y"
                               {
		print("unary_expression : NOT unary_expression");
		(yyval.pss) = createPSS ("!"+(*((yyvsp[0].pss)->first)),"int");
		// log((*($$->first)).c_str());
		log((*((yyval.pss)->first)).c_str());
		deleteMe((yyvsp[0].pss));
	}
#line 2576 "y.tab.c"
    break;

  case 68: /* unary_expression: factor  */
#line 935 "1805090.y"
                 {
		print("unary_expression : factor");
		(yyval.pss) = (yyvsp[0].pss);
		log((*((yyval.pss)->first)).c_str());
	}
#line 2586 "y.tab.c"
    break;

  case 69: /* factor: variable  */
#line 942 "1805090.y"
                   {
		print("factor : variable");
		(yyval.pss) = (yyvsp[0].pss);
		log((*((yyval.pss)->first)).c_str());
	}
#line 2596 "y.tab.c"
    break;

  case 70: /* factor: ID LPAREN argument_list RPAREN  */
#line 947 "1805090.y"
                                         { //TODO TODO
		print("factor : ID LPAREN argument_list RPAREN");
		validateAndCreateFactor((yyvsp[-3].si), *(yyvsp[-1].vss));
		(yyval.pss) = createPSS ((yyvsp[-3].si)->getName() + "(" + getStringFromArgumentList(*(yyvsp[-1].vss)) + ")", getIdVarType((yyvsp[-3].si)->getName()));
		log((*((yyval.pss)->first)).c_str());
		deleteMe((yyvsp[-3].si));
		deleteMe((yyvsp[-1].vss)); 

	}
#line 2610 "y.tab.c"
    break;

  case 71: /* factor: LPAREN expression RPAREN  */
#line 956 "1805090.y"
                                   {
		print("factor : LPAREN expression RPAREN");
		(yyval.pss) = createPSS ("("+*((yyvsp[-1].pss)->first)+")",*((yyvsp[-1].pss)->second));
		log((*((yyval.pss)->first)).c_str());
		deleteMe((yyvsp[-1].pss));
	}
#line 2621 "y.tab.c"
    break;

  case 72: /* factor: CONST_INT  */
#line 962 "1805090.y"
                    {
		print("factor : CONST_INT");
		(yyval.pss) = createPSS ((yyvsp[0].si)->getName(),"CONST_INT");
		log((*((yyval.pss)->first)).c_str());
		deleteMe((yyvsp[0].si));
	}
#line 2632 "y.tab.c"
    break;

  case 73: /* factor: CONST_FLOAT  */
#line 968 "1805090.y"
                      {
		print("factor : CONST_FLOAT");
		(yyval.pss) = createPSS ((yyvsp[0].si)->getName(), "CONST_FLOAT");
		log((*((yyval.pss)->first)).c_str());
		deleteMe((yyvsp[0].si));
	}
#line 2643 "y.tab.c"
    break;

  case 74: /* factor: variable INCOP  */
#line 974 "1805090.y"
                         {
		print("factor : variable INCOP");
		(yyval.pss) = createPSS (*((yyvsp[-1].pss)->first) + "++", *((yyvsp[-1].pss)->second));
		log((*((yyval.pss)->first)).c_str());
		deleteMe((yyvsp[-1].pss));
	}
#line 2654 "y.tab.c"
    break;

  case 75: /* factor: variable DECOP  */
#line 980 "1805090.y"
                         {
		print("factor : variable DECOP");
		(yyval.pss) = createPSS (*((yyvsp[-1].pss)->first) + "--", *((yyvsp[-1].pss)->second));
		log((*((yyval.pss)->first)).c_str());
		deleteMe((yyvsp[-1].pss));
	}
#line 2665 "y.tab.c"
    break;

  case 76: /* argument_list: arguments  */
#line 988 "1805090.y"
                          {
		print("argument_list : arguments");
		(yyval.vss) = (yyvsp[0].vss);
		log(getStringFromArguments(*(yyval.vss)).c_str());
	}
#line 2675 "y.tab.c"
    break;

  case 77: /* argument_list: %empty  */
#line 993 "1805090.y"
          {
		(yyval.vss) = new vector<pair<string*, string*>*>;
		log(getStringFromArguments(*(yyval.vss)).c_str());
	}
#line 2684 "y.tab.c"
    break;

  case 78: /* arguments: arguments COMMA logic_expression  */
#line 999 "1805090.y"
                                             {
		print("arguments : arguments COMMA logic_expression");
		(yyval.vss) = addLogicalExpression((yyvsp[-2].vss), (yyvsp[0].pss));
		log(getStringFromArguments(*(yyval.vss)).c_str());
	}
#line 2694 "y.tab.c"
    break;

  case 79: /* arguments: logic_expression  */
#line 1004 "1805090.y"
                           {
		print("arguments : logic_expression");
		(yyval.vss) = addLogicalExpression(new vector<pair<string*, string*>*>, (yyvsp[0].pss));
		log(getStringFromArguments(*(yyval.vss)).c_str());
	}
#line 2704 "y.tab.c"
    break;


#line 2708 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 1011 "1805090.y"

int main(int argc,char *argv[])
{
	if(argc < 2){
		cout<<"Input file name missing!"<<endl;
		return 0;
	}
	FILE* fp;
	if((fp = fopen(argv[1], "r")) == NULL){
		cout<<"Failed to open file: "<<argv[1]<<endl;
		return 0;
	}
	table = new SymbolTable(7);
	if(argc == 4){
		errout.open(argv[3]);
		logout.open(argv[2]);
	}else {
		errout.open("error.txt");
		logout.open("log.txt");
	}
	yyin = fp;
	yyparse();
	return 0;
}

