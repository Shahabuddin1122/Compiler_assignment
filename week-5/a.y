%{
#include<bits/stdc++.h>
#include "202114092_Akhon.h"
#define YYSTYPE SymbolInfo
using namespace std;

int yylex(void);

extern SymbolTable b;
SymbolInfo assemb;

extern FILE *yyin, *yyout;

void yyerror(const char *s){fprintf(stderr,"Syntax Error %s\n",s); return;}
int cnt=1;
char *c;
ofstream inter("code.ir");
ofstream assembly("code.asm");
char* Temp()
{
	char *val=(char*)malloc(100);
	sprintf(val,"t%d",cnt);
	return val;
}
%}


%token NUM
%token INT
%token FLOAT
%token DOUBLE
%token CHAR
%token ID
%token MAIN
%token NEWLINE
%token SEMICOLON
%token LCURL
%token RCURL



%left LAND
%left LOR
%left LTHIRD 
%left RTHIRD
%left ADDOP
%left SUBOP
%left MULOP
%left DIVOP
%left MODOP
%left GRTTHAN 
%left LESSTHAN
%left LPAREN 
%left RPAREN
%right ASSIGNOP
%left COMMA



%%
prog: MAIN LPAREN RPAREN LCURL NEWLINE stmt RCURL     {

								assemb.code=assemb.code+"MAIN ENDP\nEND";
								assembly<<assemb.code;
							}
stmt: stmt line                               {}
| line                                        {    
												    cnt=1;
													printf("\t\n");
													
													

											  }
;

line: var_decl NEWLINE                        {}
| expr_decl NEWLINE                           {}
| error NEWLINE									{yyerrok;}
;
var_decl:  type_spec decl_list SEMICOLON      {} 
;
type_spec: INT                                {}
;
decl_list: term                               {}

expr_decl: term ASSIGNOP expr SEMICOLON         {
							cnt-=1;
							c=Temp();
							SymbolInfo k(string(c),"");
							$$=k;
							inter<<$1.getvar()<<" = "<<$3.getvar()<<endl;
							assemb.code=assemb.code+"Mov "+$1.getvar()+",AX\n";
							assemb.code=assemb.code+"MOV AH,02h\nMov BX, "+$$.getvar()+"\nADD BX,30H\nMOV DX,BX\n"+"INT 21h\nMOV DX,0AH\nINT 21H\nMOV DX,0DH\nINT 21H\n";
							cnt=1;
						}

expr: NUM                                     {   c=Temp();
												  SymbolInfo k(string(c),"");
                                                  $$=k;
												  assemb.code=assemb.code+"Mov AX,"+$1.getvar()+"\n Mov "+$$.getvar()+",AX\n";
												  
							
												  $$=$1;
												   
											  }
| expr ADDOP expr                               {
							c = Temp();
						    SymbolInfo k(string(c), "");					
							$$=k;
							inter<<$$.getvar()<<" = "<<$1.getvar()<<" + "<<$3.getvar()<<endl;					  
							assemb.code=assemb.code+"MOV AX, "+$1.getvar()+"\nMOV BX, "+$3.getvar()+"\nADD AX, BX\nMOV "+$$.getvar()+", AX\n";
							cnt++;
							     
						}
| expr MULOP expr                            	{
							c = Temp();
							SymbolInfo k(string(c), "");					
							$$=k;
							inter<<$$.getvar()<<" = "<<$1.getvar()<<" * "<<$3.getvar()<<endl;
							assemb.code=assemb.code+"MOV AX, "+$1.getvar()+"\nMOV BX, "+$3.getvar()+"\nMUL BX\nMOV "+$$.getvar()+", AX\n";
							cnt++;
						}
| expr SUBOP expr                              	{
							c = Temp();
							SymbolInfo k(string(c), "");					
							$$=k;
							inter<<$$.getvar()<<" = "<<$1.getvar()<<" - "<<$3.getvar()<<endl;
							assemb.code=assemb.code+"MOV AX, "+$1.getvar()+"\nMOV BX, "+$3.getvar()+"\nSUB AX, BX\nMOV "+$$.getvar()+", AX\n";
							cnt++; 
						}
| expr DIVOP expr       {
							c = Temp();
							SymbolInfo k(string(c), "");	
							$$=k;
							inter<<$$.getvar()<<" = "<<$1.getvar()<<" / "<<$3.getvar()<<endl;
							assemb.code=assemb.code+"MOV AX, "+$1.getvar()+"\nMOV BX, "+$3.getvar()+"\nDIV BX\nMOV "+$$.getvar()+", AX\n";
							cnt++;	
						}

|  expr MODOP expr      {
						       c = Temp();
						       SymbolInfo k(string(c), "");					
						       $$=k;
						       inter<<$$.getvar()<<" = "<<$1.getvar()<<" % "<<$3.getvar()<<endl;
						       assemb.code=assemb.code+"MOV AX, "+$1.getvar()+"\nMOV BX, "+$3.getvar()+"\nMOD AX, BX\nMOV "+$$.getvar()+", AX\n";
							   cnt++;	

						}

|  LPAREN expr RPAREN   {  $$=$2;}
|  expr LAND expr       {
					         c = Temp();
							SymbolInfo k(string(c), "");					
							$$=k;
							inter<<$$.getvar()<<" = "<<$1.getvar()<<" / "<<$3.getvar()<<endl;
							assemb.code=assemb.code+"MOV AX, "+$1.getvar()+"\nMOV BX, "+$3.getvar()+"\nAND AX,BX\nMOV "+$$.getvar()+", AX\n";
				       	    cnt++;
}
|  expr LOR expr        {
							c = Temp();
							SymbolInfo k(string(c), "");					
							$$=k;
							inter<<$$.getvar()<<" = "<<$1.getvar()<<" / "<<$3.getvar()<<endl;
							assemb.code=assemb.code+"MOV AX, "+$1.getvar()+"\nMOV BX, "+$3.getvar()+"\nOR AX,BX\nMOV "+$$.getvar()+", AX\n";
							cnt++;
					    }

|  term                                     {   $$=$1;}
;
term: ID                                     {  $$=$1;}







%%

int main(int argc, char* argv[]) {
    assemb.code=assemb.code+".MODEL SMALL\n.STACK 100H\n.DATA\na DW ?\nc DW ?\nb DW ?\nt0 DW ?\nt1 DW ?\nt2 DW ?\nt3 DW ?\nt4 DW ?\n";
    assemb.code=assemb.code+".CODE\nMAIN PROC\nMOV AX,@DATA\nMOV DS,AX \n";
    yyin=fopen("input2.txt","r");
    yyparse();
    fclose(yyin);
    inter.close();
    assembly.close();
    b.display();
    printf("\nparser is finished\n");
    return 0;
}