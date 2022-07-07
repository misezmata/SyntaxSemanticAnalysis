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
void yyerror(char *s){
	//write your code
}

stack<double> s;

%}
%union {SymbolInfo* si;}
%token TERM DIV MULT ADD SUB NEWLINE
%token<si> CONST_INT CONST_FLOAT CONST_CHAR
%%

expr: 
    | term {cout<<"EXPR -> TERM"<<endl; 
            cout<<(s.top())<<endl;
            }
    | expr ADD term {
                        double num1 = s.top();
                        s.pop();
                        double num2 = s.top();
                        s.pop();
                        double num3 = num1 + num2;
                        s.push(num3);
                        cout<<num2 << "+" << num1<<"=" << num3<<endl;
                        cout<<"EXPR -> EXPR + TERM"<<endl; }
    | expr SUB term {
                        double num1 = s.top();
                        s.pop();
                        double num2 = s.top();
                        s.pop();
                        double num3 = num1 - num2;
                        s.push(num3);
                        cout<<num2 << "-" << num1<<"=" << num3<<endl;
                        cout<<"EXPR -> EXPR - TERM"<<endl;
                    }
    ;
term: number {cout<<"TERM -> NUMBER"<<endl; cout<<(s.top())<<endl;}
    | term MULT number  {
                            double num1 = s.top();
                            s.pop();
                            double num2 = s.top();
                            s.pop();
                            double num3 = num1 * num2;
                            s.push(num3);
                            cout<<"TERM -> TERM * NUMBER"<<endl;
                            cout<<num2 << "*" << num1<<"=" << num3<<endl;
                        }
    | term DIV number {
                            double num1 = s.top();
                            s.pop();
                            double num2 = s.top();
                            s.pop();
                            double num3 = num1 / num2;
                            s.push(num3);
                            cout<<"TERM -> TERM * NUMBER"<<endl;
                            cout<<"TERM -> TERM / NUMBER"<<endl;
                            cout<<num2 << "/" << num1<<"-" << num3<<endl;
                        }
    ;
number: CONST_FLOAT {
                        cout<<"NUMBER->FLOAT"<<endl;
                        cout<<($1->getName())<<endl;
                        s.push(stof($1->getName()));
                    }
        ;


%%
int main(int argc,char *argv[])
{
	yyparse();
	
	return 0;
}

