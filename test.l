%option noyywrap

%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "1805090_SymbolInfo.h"
#include "y.tab.h"

%}


WS [ \t]+
DIGIT [0-9]
NUMBER [-]?{DIGIT}+(\.{DIGIT}+)?

%%

{NUMBER}  {
        SymbolInfo* si = new SymbolInfo(yytext, "CONST_FLOAT");
        yylval.si = si;
	    return CONST_FLOAT;
	  }

"+"       { return ADD; }
"-"       { return SUB; }
"/"       { return DIV; }
"*"       { return MULT; }
"\n"      { return NEWLINE;}
{WS} { /* No action and no return */}
