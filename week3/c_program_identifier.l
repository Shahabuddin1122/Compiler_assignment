%option noyywrap
%{
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "202114092_Akhon.h"


FILE *yyout1;
int cnt=0;
int com=0;
%}

DIGIT       [0-9]
LETTER      [a-zA-Z]
ALPHA       [a-zA-Z0-9_]
WS          [ \t]+



%%

if|for|do|int|float|void|switch|default|else|while|break|char|double|return|case|continue  {int i;for (i = 0; i < yyleng; i++) {yytext[i] = toupper(yytext[i]);}fprintf(yyout,"<KEYWORD, %s >", yytext); fprintf(yyout1,"Line No. <%d>: Token <KEYWORD> Lexeme <%s> found\n", cnt,yytext); }

{LETTER}{ALPHA}* { fprintf(yyout,"<ID, %s >", yytext); fprintf(yyout1,"Line No. <%d>: Token <ID> Lexeme <%s> found\n", cnt,yytext); SymbolInfo a(yytext,"ID"); b.Insert(a);
b.display();}

">="        { fprintf(yyout,"< RELOP,>= >"); fprintf(yyout1,"Line No. <%d>: Token <ADDOP> Lexeme <%s> found\n", cnt,yytext); }
"<="        { fprintf(yyout,"< RELOP,<= >"); fprintf(yyout1,"Line No. <%d>: Token <ADDOP> Lexeme <%s> found\n", cnt,yytext); }
"=="        { fprintf(yyout,"< RELOP,== >"); fprintf(yyout1,"Line No. <%d>: Token <ADDOP> Lexeme <%s> found\n", cnt,yytext); }
"!="        { fprintf(yyout,"< RELOP,!= >"); fprintf(yyout1,"Line No. <%d>: Token <ADDOP> Lexeme <%s> found\n", cnt,yytext); }
">"         { fprintf(yyout,"< RELOP,> >"); fprintf(yyout1,"Line No. <%d>: Token <ADDOP> Lexeme <%s> found\n", cnt,yytext); }
"<"         { fprintf(yyout,"< RELOP,< >"); fprintf(yyout1,"Line No. <%d>: Token <ADDOP> Lexeme <%s> found\n", cnt,yytext); }
"+"         { fprintf(yyout,"< ADDOP,+ >"); fprintf(yyout1,"Line No. <%d>: Token <ADDOP> Lexeme <%s> found\n", cnt,yytext); }
"-"         { fprintf(yyout,"< ADDOP,- >"); fprintf(yyout1,"Line No. <%d>: Token <ADDOP> Lexeme <%s> found\n", cnt,yytext);}
"*"         { fprintf(yyout,"< MULOP,* >"); fprintf(yyout1,"Line No. <%d>: Token <MULOP> Lexeme <%s> found\n", cnt,yytext);}
"/"         { fprintf(yyout,"< MULOP,/ >"); fprintf(yyout1,"Line No. <%d>: Token <MULOP> Lexeme <%s> found\n", cnt,yytext);}
"%"		    { fprintf(yyout,"< MULOP,% >"); fprintf(yyout1,"Line No. <%d>: Token <MULOP> Lexeme <%s> found\n", cnt,yytext);}
"="         { fprintf(yyout,"< ASSIGNOP,= >"); fprintf(yyout1,"Line No. <%d>: Token <ASSIGNOP> Lexeme <%s> found\n", cnt,yytext);}
";"         { fprintf(yyout,"< SEMMICOLON,; >"); fprintf(yyout1,"Line No. <%d>: Token <SEMMICOLON> Lexeme <%s> found\n", cnt,yytext);}
"("         { fprintf(yyout,"< LPAREN,( >"); fprintf(yyout1,"Line No. <%d>: Token <LPAREN> Lexeme <%s> found\n", cnt,yytext);}
")"         { fprintf(yyout,"< RPAREN,) >"); fprintf(yyout1,"Line No. <%d>: Token <RPAREN> Lexeme <%s> found\n", cnt,yytext);}
"{"         { fprintf(yyout,"< LCURL,{ >"); fprintf(yyout1,"Line No. <%d>: Token <LCURL> Lexeme <%s> found\n", cnt,yytext);}
"}"         { fprintf(yyout,"< RCURL,} >"); fprintf(yyout1,"Line No. <%d>: Token <RCURL> Lexeme <%s> found\n", cnt,yytext);}
","         { fprintf(yyout,"< COMMA, , >"); fprintf(yyout1,"Line No. <%d>: Token <COMMA> Lexeme <%s> found\n", cnt,yytext);}

"&&"        { fprintf(yyout,"< LOGICOP,&& >"); fprintf(yyout1,"Line No. <%d>: Token <LOGICOP> Lexeme <%s> found\n", cnt,yytext);}
"||"        { fprintf(yyout,"< LOGICOP,|| >"); fprintf(yyout1,"Line No. <%d>: Token <LOGICOP> Lexeme <%s> found\n", cnt,yytext);}

"++"        { fprintf(yyout,"<INCOP,++>"); fprintf(yyout1,"Line No. <%d>: Token <INCOP> Lexeme <%s> found\n", cnt,yytext);}
"--"        { fprintf(yyout,"<INCOP,-->"); fprintf(yyout1,"Line No. <%d>: Token <INCOP> Lexeme <%s> found\n", cnt,yytext); }

[ \t]     { /* Ignore whitespace */ }

{DIGIT}+    { fprintf(yyout,"<CONST_INT, %s >", yytext); fprintf(yyout1,"Line No. <%d>: Token <CONST_INT> Lexeme <%s> found\n", cnt,yytext);  SymbolInfo a(yytext,"CONST_INT"); b.Insert(a);
b.display();}

{DIGIT}*[.]?{DIGIT}+[Ee]?[+-]?{DIGIT}+ { fprintf(yyout,"<CONST_FLOAT: %s >", yytext);fprintf(yyout1,"Line No. <%d>: Token <CONST_FLOAT> Lexeme <%s> found\n", cnt,yytext); SymbolInfo a(yytext,"CONST_FLOAT"); b.Insert(a);
b.display(); }

\'{LETTER}\' { fprintf(yyout,"<CONST_CHAR, %s >", yytext); fprintf(yyout1,"Line No. <%d>: Token <CONST_CHAR> Lexeme <%s> found\n", cnt,yytext); SymbolInfo a(yytext,"CONST_CHAR"); b.Insert(a);
b.display(); }


\"([^\\\"]|\\.)*\" { fprintf(yyout1,"Literal: %s\n", yytext); }
[/][/]+[^\n]+ { fprintf(yyout1,"Single line Comment: %s\n",yytext); }
[/][*]([*]+|[^*/]|[^//])*[*][/] { fprintf(yyout1,"Multiple line Comment: %s\n",yytext); }

{DIGIT}+[.]{DIGIT}+([.]{DIGIT}+)+ {fprintf(yyout1,"Line no %d Too many decimal point error for character sequence\n",cnt);}
{DIGIT}+{ALPHA}+ {fprintf(yyout1,"Line no %d Invalid Suffix on numeric constant\n",cnt);}
\'{LETTER}{LETTER}+\' {fprintf(yyout1,"Line no %d  Multi character constant error for character sequence\n",cnt);}


{LETTER}{ALPHA}*[(] { 

	yytext[yyleng - 1] = '\0';
	fprintf(yyout,"<Function, %s >",yytext);
	fprintf(yyout,"< LPAREN,( >");

    fprintf(yyout1,"Line No. <%d>: Token <FUNCTION> Lexeme <%s> found\n", cnt,yytext);
	fprintf(yyout1,"Line No. <%d>: Token <LPAREN> Lexeme <(> found\n", cnt);

}
\n {cnt++;}

. {printf("LEXICAL ERROR");}

%%

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Please provide a file name as an argument.\n");
        return 1;
    }

    yyin= fopen(argv[1], "r");
    yyout = fopen("output.txt", "w");
    yyout1 = fopen("202114092_log.txt", "w");

    if (!yyin) {
        printf("Failed to open the input file.\n");
        return 1;
    }

    
    yylex();

    fclose(yyin);
	fclose(yyout);
	fclose(yyout1);
	
    return 0;
}