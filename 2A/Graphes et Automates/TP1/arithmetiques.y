%{
#include <stdio.h>
#include <ctype.h>
int yylex(void);
%define parse.error verbose
#define YYSTYPE double
int yyerror(const char*);
%}
%error-verbose
%token NB
%token EOL
%%
input:
/* Ligne vide */
|input ligne
;
ligne: expr '\n' {printf("%f\n",$1);}
| EOL {}
;
/* Le reste de la grammaire*/
expr:
    expr '+' expr {$$ = $1 + $3;}
    | expr '-' expr {$$ = $1 - $3;}
    | expr '*' expr {$$ = $1 * $3;}
    | expr '/' expr {$$ = $1 / $3;}
    | '(' expr ')' {$$ = $2;}
    | '-' expr expr {$$ =-$2;}
    | NB {$$ = $1}
;
%%
#include "arithmetiques.yy.c"
int main()
{
return yyparse();
}
int yyerror( const char *s )
{
fprintf( stderr, "Erreur: %s\n", s);
return 0;
}
