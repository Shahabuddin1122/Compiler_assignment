%{
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "202114092_Akhon.h"


extern int yylex();

SymbolTable b;


extern FILE *yyin, *yyout;
extern float num;
extern char* name;
void yyerror(const char *s){fprintf(yyout,"Syntex Error %s\n",s);}

int cnt=1;
int com=0;

%}

%token ID INT FLOAT DOUBLE NUM NEWLINE SEMICOLON LPAREN RPAREN
%left LTHIRD RTHIRD
%left ADDOP SUBOP
%left MULOP DIVOP MODOP
%left GRTTHAN LESSTHAN
%left LAND
%left LOR
%right ASSIGNOP
%left COMMA

%%
stmt: stmt unit {fprintf(yyout,"\n\n");cnt++;}
    | unit      {fprintf(yyout,"\n\n");cnt++;}
    ;

unit: var_decl NEWLINE   {fprintf(yyout,"Line Number: %d\n",cnt); 				fprintf(yyout,"unit: var_decl NEWLINE\n");}
    | expr_decl NEWLINE  {fprintf(yyout,"Line Number: %d\n",cnt); 				fprintf(yyout,"unit: expr_decl NEWLINE\n");}
    | error NEWLINE {yyerrok;}
    ;

var_decl: type_spec decl_list SEMICOLON      {
		fprintf(yyout,"Line Number: %d\n",cnt); 				fprintf(yyout,"var_decl: type_spec decl_list SEMICOLON\n");
		}
    ;
expr_decl: term ASSIGNOP expr SEMICOLON     {
		fprintf(yyout,"Line Number: %d\n",cnt); 				fprintf(yyout,"expr_decl: term ASSIGNOP expr SEMICOLON\n");
		}
    ;

type_spec: INT    {fprintf(yyout,"Line Number: %d\n",cnt); 
		  fprintf(yyout,"type_spec: INT\n");}
    | FLOAT       {fprintf(yyout,"Line Number: %d\n",cnt); 
		  fprintf(yyout,"type_spec: FLOAT\n");}
    | DOUBLE      {fprintf(yyout,"Line Number: %d\n",cnt); 
		  fprintf(yyout,"type_spec: DOUBLE\n");}
    ;

decl_list: decl_list COMMA term     {fprintf(yyout,"Line Number: %d\n",cnt);  
				fprintf(yyout,"decl_list: decl_list COMMA term\n");}
    | decl_list COMMA term LTHIRD NUM RTHIRD    {fprintf(yyout,"Line Number: %d\n",cnt);  
		 fprintf(yyout,"decl_list: decl_list COMMA term LTHIRD NUM RTHIRD\n");}
    | term        {fprintf(yyout,"Line Number: %d\n",cnt); 
				fprintf(yyout,"decl_list: term\n"); }
    | term LTHIRD NUM RTHIRD   {if(num!=(int)num){
fprintf(yyout,"Line Number: %d\n",cnt);  
				fprintf(yyout,"Syntex error\n");}else {fprintf(yyout,"Line Number: %d\n",cnt);fprintf(yyout,"decl_list: term LTHIRD NUM RTHIRD\n");}}
    | ass_list        {fprintf(yyout,"Line Number: %d\n",cnt);  
				fprintf(yyout,"decl_list: ass_list\n");}
    ;

ass_list: term ASSIGNOP expr   {fprintf(yyout,"Line Number: %d\n",cnt); 
				fprintf(yyout,"ass_list: term ASSiGNOP expr\n");}
    ;

expr: LPAREN expr RPAREN {fprintf(yyout,"Line Number: %d\n",cnt); 
			fprintf(yyout,"expr: LPAREN expr RPAREN\n");}
    | expr MULOP expr      {fprintf(yyout,"Line Number: %d\n",cnt); 
				      fprintf(yyout,"expr: expr MULOP expr\n");}
    | expr DIVOP expr     {fprintf(yyout,"Line Number: %d\n",cnt); 
				      fprintf(yyout,"expr: expr DIVOP expr\n");} 
    | expr MODOP expr     {fprintf(yyout,"Line Number: %d\n",cnt); 
				      fprintf(yyout,"expr: expr MODOP expr\n");} 
    | expr ADDOP expr     {fprintf(yyout,"Line Number: %d\n",cnt); 
				      fprintf(yyout,"expr: expr ADD expr\n");}
    | expr SUBOP expr     {fprintf(yyout,"Line Number: %d\n",cnt); 
				      fprintf(yyout,"expr: expr SUBOP expr\n");}
    | expr LAND expr      {fprintf(yyout,"Line Number: %d\n",cnt); 
				      fprintf(yyout,"expr: expr LAND expr\n");}
    | expr LOR expr       {fprintf(yyout,"Line Number: %d\n",cnt); 
				      fprintf(yyout,"expr: expr LOR expr\n");}
    | term         {fprintf(yyout,"Line Number: %d\n",cnt); 
					  fprintf(yyout,"expr: term\n");}

    ;

term: ID     {SymbolInfo a(name,"IDENTIFIER");b.Insert(a); fprintf(yyout,"Line Number: %d\n",cnt); 		fprintf(yyout,"term: ID\n");}
    | NUM    {fprintf(yyout,"Line Number: %d\n",cnt); 
			  fprintf(yyout,"expr: NUM\n");}
    ;



%%

int main(int argc, char* argv[]) {
    yyin=fopen("input.txt","r");
    yyout=fopen("log_error.txt","w");
    yyparse();
    fclose(yyin);
    fclose(yyout);
    b.display();
    printf("\nparser is finished\n");
    return 0;
}