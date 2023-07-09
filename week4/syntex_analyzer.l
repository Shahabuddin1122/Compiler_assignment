%option noyywrap
%{
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "syntex_analyzer.tab.h"
char* name;
float num;

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
"int"        {return INT;}
"float"      {return FLOAT;}
"double"     {return DOUBLE;}


{LETTER}{ALPHA}* {name=yytext; return ID;}

{intp}{fracp}?{expp}?|{fracp}{expp}?   {num=atof(yytext); return NUM;}


";"                   {return SEMICOLON;}

","          	      {return COMMA;}

"["		     {return LTHIRD;}

"]"		     {return RTHIRD;}

"="		     {return ASSIGNOP;}

"*"		     {return MULOP;}

"/"                  {return DIVOP;}

"%"		     {return MODOP;}

"+"		     {return ADDOP;}

"-"		     {return SUBOP;}

">"		     {return GRTTHAN;}

"<"		     {return LESSTHAN;}

"&&"                 {return LAND;}

"||"	             {return LOR;}

"("		     {return LPAREN;}

")"		     {return RPAREN;}

%%

