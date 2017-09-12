%{
#include <stdio.h>
#include "imageprocessing.h"
#include <FreeImage.h>

void yyerror(char *c);
int yylex(void);

%}
%union {
  char    strval[50];
  int     ival;
  float   fval;
}
%token <strval> STRING
%token <ival> VAR IGUAL EOL ASPA COLCHETE AST BARRA
%token <fval> FLOAT
%left SOMA

%%

PROGRAMA:
        PROGRAMA EXPRESSAO EOL
        |
        ;

EXPRESSAO:
   /* |STRING IGUAL EXPRESSAO { printf("Entrou na função");


        }*/
        
   
	 |STRING IGUAL STRING AST FLOAT  {
	
	printf("IMPLEMENTAR FUNÇÃO MULTIPLICACAO\n");
    imagem I = abrir_imagem($3); 
	float multi = $5;  
	BRILHOMUL (&I, &multi);
    salvar_imagem($1, &I);
	liberar_imagem(&I);
   	
	
    }
   
    |STRING IGUAL STRING BARRA FLOAT {
    
	printf("IMPLEMENTAR FUNÇÃO DIVISAO");
	imagem I = abrir_imagem($3);
	float divi = $5;
    BRILHODIV (&I, &divi);
    salvar_imagem($1, &I);
	liberar_imagem(&I);
   
    }
    | COLCHETE STRING COLCHETE {
    
	printf("IMPLEMENTAR FUNÇÃO VALOR MAXIMO\n");
	imagem I = abrir_imagem($2);
	max(&I);
	

    }
	| STRING IGUAL STRING {
        printf("Copiando %s para %s\n", $3, $1);
        imagem I = abrir_imagem($3);
        printf("Li imagem %d por %d\n", I.width, I.height);
        salvar_imagem($1, &I);
        liberar_imagem(&I);
                          }
    ;

%%

void yyerror(char *s) {
    fprintf(stderr, "%s\n", s);
}

int main() {
  FreeImage_Initialise(0);
  yyparse();
  return 0;

}
