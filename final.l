%{
#include <string.h>
#include<stdlib.h>
#include<math.h>
#include "final.tab.h"
void yyerror (char *s);
int yylex();
enum bifs{
    print
};
%}
%option yylineno
LETRA [A-Za-z]
DIGITO [0-9]
identifier ({LETRA}|$|_)({LETRA}|{DIGITO}|_)*
compareSymbols (=|<|<=|>=|>)
integer ([-]?{DIGITO}+)
float ([-]?{DIGITO}+.{DIGITO}+)
%%
"begin" {return START;}                                                         
"end" {return END;}
"if" {return IF;}
"ifelse" {return IFELSE;}
"while" {return WHILE;}
"var" {return VAR;}
"int" {yylval.ty = 1; return INT;}
"float" {yylval.ty = 2;return FLOAT;}
"fun" {return FUN;}
"print" {yylval.fn = print; return PRINT;}
"read" {return READ;}
"return" {return RETURN;}
{identifier}   {yylval.c = (char *)strdup(yytext); return NAME;}            //Manda al archivo .y el identificador y lo detecta como tipo c
{integer}* {yylval.d = atoi(yytext); return NUM;}                           //Manda al archivo .y el entero y lo detecta como tipo d
{float} {yylval.d = atof(yytext); return NUMBER;}                           //Manda al archivo .y el flotante y lo detecta como tipo d
">" { yylval.fn = 1; return CMP; }                                          //Los simbolos de comparación los regresa con un identificador
"<" { yylval.fn = 2; return CMP; }
"==" { yylval.fn = 3; return CMP; }
">=" { yylval.fn = 4; return CMP; }
"<=" { yylval.fn = 5; return CMP; }
"+" |
"-" |
"*" |
"/" |
"=" |
"|" |
"," |
";" |
"(" |
":" |
"<-" |
"," |
")" { return yytext[0]; }
[\n]      {;}

%%
int yywrap (void) {return 1;}