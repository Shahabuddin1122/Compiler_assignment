%option noyywrap
%{
#include<bits/stdc++.h>
#include "202114092_Akhon.h"
#define YYSTYPE SymbolInfo
#include "a.tab.h"
using namespace std;
// void yyerror(const char* msg);
SymbolTable b;

%}

DIGIT       [0-9]+
LETTER      [_a-zA-Z]
ALPHA       [a-zA-Z0-9_]
WS          [ \t]+
newline     [\n]+
intp {DIGIT}

fracp [.]{DIGIT}

expp [Ee][+-]?{DIGIT}


%%
{newline}    {return NEWLINE;}
{WS}         {}
"main"       {return MAIN;}
"int"        {return INT;}
"float"      {return FLOAT;}
"double"     {return DOUBLE;}


{LETTER}{ALPHA}* {
		SymbolInfo ob(string(yytext),"IDENTIFIER");
		yylval=ob;
		b.Insert(ob);		
		return ID;}

{intp}{fracp}?{expp}?|{fracp}{expp}?   {
		SymbolInfo ob(string(yytext),"NUMBER");
		yylval=ob;
		b.Insert(ob); 
		return NUM;}


";"                   {return SEMICOLON;}

","          	      {return COMMA;}

"["		     {return LTHIRD;}

"]"		     {return RTHIRD;}
"{"          {return LCURL;}
"}"          {return RCURL;}

"="		     {return ASSIGNOP;}

"*"		     {return MULOP;}

"/"          {return DIVOP;}

"%"		     {return MODOP;}

"+"		     {return ADDOP;}

"-"		     {return SUBOP;}

">"		     {return GRTTHAN;}

"<"		     {return LESSTHAN;}

"&&"                 {return LAND;}

"||"	             {return LOR;}

"("		     {return LPAREN;}

")"		     {return RPAREN;}
.            {
				char m[25];
				sprintf(m,"invalid character  <%s> Found",yytext);
		     }

%%

