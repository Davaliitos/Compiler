%{
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

int yylex();
int yyerror(char const * s);
extern FILE* yyin;

//Symbol Table
struct symbol{
    char* name;
    double value;
    int type;
    struct ast *func;
    struct symlist *syms;
};


#define NHASH 9997
struct symbol symtab[NHASH];

struct symbol *lookup(char *);
struct symbol *install(char *,int type);

//Lista de símbolos
struct symlist{
    struct symbol *sym;
    struct symlist *next;
};

struct symlist *newsymlist(struct symbol *sym, struct symlist *next);
void symlistfree(struct symlist *sl);


//Aqui se guardan vari
enum bifs{
    print
};

//Nodos del arbol sintactico
struct node{
    int nodetype;
    struct node *l;
    struct node *r;
};

//Nodos de las funciones por default Eg. Print, Read
struct fncall{
    int nodetype;
    struct node *l;
    enum bifs functype;
};

//Nodos de las funciones creadas por el usuario
struct ufncall{
    int nodetype;
    struct node *l;
    struct symbol *s;
};

//Nodos para el manejo de flujo condicionado. If Else While
struct flow{
    int nodetype;
    struct node *cond;
    struct node *tl;
    struct node *el;
};

//Nodos para almacenar los números
struct numval{
    int nodetype;
    double number;
};

//Nodos para hacer referencia a los símbolos
struct symref{
    int nodetype;
    struct symbol *s;
};

//Nodos para hacer asignaciones
struct symasgn{
    int nodetype;
    struct symbol *s;
    struct node *v;
};

//Funciones del arbol sintáctico
struct node * readasgn(struct symbol *s);
struct node *newnode(int nodetype, struct node *l, struct node *r);
struct node *newcmp(int cmptype, struct node *l, struct node *r);
struct node *newfunc(int functype,struct node *l);
struct node *newcall(struct symbol *s, struct node *l);
struct node *newref(struct symbol *s);
struct node *newasgn(struct symbol *s, struct node *v);
struct node *newnum(double d);
struct node *newflow(int nodetype, struct node *cond, struct node *tl, struct node *tr);

//Funcion para crear funciones de usuario
void dodef(struct symbol *name, struct symlist *syms, struct node *stmts);
static double callbuiltin(struct fncall *f);
static double calluser(struct ufncall *);

//Función principal, recorre el arbol
double eval(struct node *);

void treefree(struct node *);

void Display();

%}


%union{
    struct node *a;
    double d;
    struct symbol *s;
    struct symlist *sl;
    char *c;
    int ty;
    int fn;
}

%token <d> NUMBER NUM
%token <s> NAME
%token <fn> PRINT
%token <fn> EOL
%token <ty> INT FLOAT 

%token IF IFELSE WHILE DO LET START END VAR FUN READ RETURN
%nonassoc <fn> CMP
%right '='
%left '+' '-'
%left '*' '/'

%type <a> expr factor term opt_stmts stmt stmt_list expression opt_args arg_lst
%type <sl> dec fun_dec opt_params param params_lst
%type <ty> tipo
%start prog

%%

prog : opt_decls opt_fun_decls START opt_stmts END {eval($4); treefree($4); exit(0);}
    ;

opt_decls : decls   {;}
    |               {;}
    ;

decls : dec ';' decls   {;}
    |   dec             {;}
    ;

dec : VAR NAME ':' tipo  {$$ = newsymlist(install($2,$4),NULL);}
    ;

opt_fun_decls : fun_decls   {;}
    |                           {;}
    ;

fun_decls : fun_dec ';' fun_decls       {;}
    |   fun_dec                         {;}
    ;

fun_dec : FUN NAME '(' opt_params ')' ':' tipo opt_decls START opt_stmts END    {dodef(install($2,$7),$4,$10);}
    ;

opt_params : params_lst     {;}
    |                       {;}
    ;

params_lst : param ',' params_lst       {$$ = newsymlist($1,$3);}
    |   param                           {;}
    ;

param : NAME ':' tipo   {$$ = newsymlist(install($1,$3),NULL);}
    ;

tipo : INT              {;}
    |  FLOAT            {;}
    ;

opt_stmts:  stmt_list   {;}
    |                   {;}
    ;

stmt_list : stmt ';' stmt_list  {$$ = newnode('L',$1,$3);}
    |   stmt                    {$$ = $1;}
    ;

stmt : NAME '<-' expr   {$$ = newasgn(lookup($1),$3);}
    | IF '(' expression ')' stmt {$$ = newflow('I',$3,$5,NULL);}
    | IFELSE '(' expression ')' stmt stmt {$$ = newflow('I',$3,$5,$6);}
    | WHILE '(' expression ')' stmt {$$ = newflow('W',$3,$5,NULL);}
    | PRINT expr        {$$ = newfunc($1,$2);}
    | READ NAME         {$$ = readasgn(lookup($2))}
    | START opt_stmts END           {$$ = newnode('L',$2,NULL);;}
    ;

expr: expr '+' term {$$ = newnode('+',$1,$3);}
    | expr '-' term {$$ = newnode('-',$1,$3);}
    | term
    ;

term : term '*' factor {$$ = newnode('*',$1,$3);}
    | term '/' factor {$$ = newnode('/',$1,$3);}
    | factor
    ;

factor : NAME    {$$ = newref(lookup($1));}
    | NUM        {$$ = newnum($1);}
    | NUMBER     {$$ = newnum($1);}
    | NAME '(' opt_args ')' {$$ = newcall(lookup($1),$3);}
    | '(' expr ')' {$$ = $2;}
    ;

opt_args: arg_lst       {;}
    |                   {;}
    ;

arg_lst: expr ',' arg_lst   { $$ = newnode('L',$1,$3);}
    | expr                  {;}



expression: expr CMP expr   {$$ = newcmp($2,$1,$3);}



%%

//Funcion que guarda en la lista las funciones
void dodef(struct symbol *name, struct symlist *syms, struct node *func){
    
    if(name -> syms) symlistfree(name->syms);
    if(name -> func) treefree(name->func);
    name->syms = syms;
    name->func = func;
    
}

struct symlist * newsymlist(struct symbol *sym, struct symlist *next){
    struct symlist *sl = malloc(sizeof(struct symlist));
    if(!sl){
        yyerror("outofspace");
        exit(0);
    }
    sl->sym = sym;
    sl->next = next;
    return sl;
}

void symlistfree(struct symlist *sl){
    struct symlist *nsl;

    while(sl){
        nsl = sl->next;
        free(sl);
        sl = nsl;
    }
}


double eval(struct node *a){
    double v;
    double b;
    
    if(!a) {
        yyerror("internal error, null eval");
        return 0.0;
    }
    switch(a->nodetype){
        case 'K' : v = ((struct numval *) a)->number; break;

        case 'N' : v = ((struct symref *) a)->s->value;break;

        case '+' : v = eval(a->l) + eval(a->r); break;

        case '-' : v = eval(a->l) - eval(a->r); break;

        case '*' : v = eval(a->l) * eval(a->r); break;

        case '/' : v = eval(a->l) / eval(a->r); break;

        case '=' : 
            switch(((struct symasgn *) a)->s->type){
                case 1:
                    v = ((struct symasgn *) a)->s->value = (int)eval(((struct symasgn *)a)->v);break;
                    break;
                case 2:
                    v = ((struct symasgn *) a)->s->value = eval(((struct symasgn *)a)->v);break;
                    break;
            }
            break;

        case 'F' : v = callbuiltin((struct fncall *)a); break;

        case 'L' : eval(a->l); v= eval(a->r); break;

        case '1': v = (eval(a->l) > eval(a->r))? 1 : 0; break;

        case '2': v = (eval(a->l) < eval(a->r))? 1 : 0; break;

        case '3': v = (eval(a->l) == eval(a->r))? 1 : 0; break;

        case '4': v = (eval(a->l) >= eval(a->r))? 1 : 0; break;

        case '5': v = (eval(a->l) <= eval(a->r))? 1 : 0; break;

        case 'R' : scanf("%lf",&b); v = ((struct symasgn *) a)->s->value = b;break;

        case 'I':
            if( eval( ((struct flow *)a)->cond) != 0) { 
                if( ((struct flow *)a)->tl) { 
                    v = eval( ((struct flow *)a)->tl);
                } 
                else
                    v = 0.0; 
            } 
            else {
                if( ((struct flow *)a)->el) {
                    v = eval(((struct flow *)a)->el);
                } 
                else
                v = 0.0; 
            }
            break;

        case 'W':
            v = 0.0;
            if( ((struct flow *)a)->tl) {
                while( eval(((struct flow *)a)->cond) != 0) 
                    v = eval(((struct flow *)a)->tl);
            }
            break;

        case 'C' : v = calluser((struct ufncall *)a); break;

    }
    return v;
}

struct node * newfunc(int functype, struct node *l){
    struct fncall *a = malloc(sizeof(struct fncall));

    if(!a){
        yyerror("out of space");
        exit(0);
    }
    a->nodetype = 'F';
    a->l = l;
    a->functype = functype;
    return (struct node *)a;
}

struct node * newcall(struct symbol *s, struct node *l){
    struct ufncall *a = malloc(sizeof(struct ufncall));

    if(!a){
        yyerror("Out of space");
        exit(0);
    }

    a->nodetype = 'C';
    a->l = l;
    a->s = s;
    return (struct node *)a;

}


static double callbuiltin(struct fncall *f){
    enum bifs functype = f->functype;
    double v = eval(f->l);

    switch(functype){
        case print:
            printf("= %4.4g\n", v);
            return v;

    }

}

static double calluser(struct ufncall *f){
    struct symbol *fn = f->s;
    struct symlist *sl;
    struct node *args = f->l;
    double *oldval, *newval;
    double v;
    int nargs;
    int i;

    if(!fn->func){
        yyerror("call to undefined function");
        return 0;
    }

    sl = fn->syms;
    for(nargs = 0;sl;sl = sl->next){
        nargs++;
    }

    oldval = (double *)malloc(nargs * sizeof(double));
    newval = (double *)malloc(nargs * sizeof(double));
    if(!oldval || !newval){
        yyerror("Out of space");
        return 0.0;
    }

    for(i=0; i<nargs; i++){
        if(!args){
            yyerror("too few arguments in call to ");
            free(oldval); free(newval);
            return 0.0;
        }
        if(args->nodetype == 'L'){
            newval[i] = eval(args->l);
            args = args->r;
        }else{
            newval[i] = eval(args);
            args = NULL;
        }
    }

    sl = fn->syms;
    for(i = 0; i<nargs;i++){
        struct symbol *s = sl->sym;

        oldval[i] = s->value;
        s->value = newval[i];
        sl = sl-> next;
    }

    free(newval);

    v = eval(fn->func);

    sl = fn->syms;
    for(i=0; i<nargs; i++){
        struct symbol *s = sl->sym;

        s->value = oldval[i];
        sl = sl->next;
    }

    free(oldval);
    return v;

}

void treefree(struct node *a){
    switch(a->nodetype){
        case '+':
        case '-':
        case '*':
        case '/':
        case '1': case '2': case '3': case '4': case '5': case '6':
        case 'L':
            treefree(a->r);

        case 'M': case 'C': case 'F':
            treefree(a->l);


        case 'K' : case 'N':
            break;
        case '=' :
            free( ((struct symasgn *)a)->v);
            break;

        case 'I': case 'W':
            free( ((struct flow *)a)->cond);
            if( ((struct flow *)a)->tl) treefree( ((struct flow *)a)->tl);
            if( ((struct flow *)a)->el) treefree( ((struct flow *)a)->el);
        break;

    }
    free(a);
}

static unsigned symhash(char *sym){
    unsigned int hash = 0;
    unsigned c;

    while(c=*sym++){
        hash = hash*9 ^ c;
    }
    return hash;
}

struct symbol * install(char *sym, int type){
    struct symbol *sp = &symtab[symhash(sym)%NHASH];
    int scount = NHASH;
    while(--scount >= 0){
        if(sp->name && !strcmp(sp->name,sym)){
            yyerror("La variable ya ha sido declarada");
        }
        if(!sp->name){
            switch(type){
                case 1 :
                    sp->type = 1;
                    break;
                case 2:
                    sp->type = 2;
                    break;
            }

            sp->name = strdup(sym);
            sp->value = 0;
            sp->func = NULL;
            sp->syms = NULL;
            return sp;
        }
        if(++sp >= symtab+NHASH)
            sp = symtab;
    }
    yyerror("symbol table overflow\n");
    abort(); /* tried them all, table is full */

}

struct symbol * lookup(char* sym){
    struct symbol *sp = &symtab[symhash(sym)%NHASH];
    int scount = NHASH;

    while(--scount >= 0){
        if(sp->name && !strcmp(sp->name,sym)){
            return sp;
        }
        if(!sp->name){
            printf("%s",sp->name);
            yyerror(sp->name);
            
            exit(0);
        }
        if(++sp >= symtab+NHASH)
            sp = symtab;
    }
    yyerror("symbol table overflow\n");
    abort(); /* tried them all, table is full */
}

struct node *newnode(int nodetype, struct node *l, struct node *r){
    struct node *a = malloc(sizeof(struct node));

    if(!a){
        yyerror("Out of space");
        exit(0);
    }
    a->nodetype = nodetype;
    a->l = l;
    a->r = r;
    return a;
}

struct node *newnum(double d){
    struct numval *a = malloc(sizeof(struct numval));

    if(!a){
        yyerror("Out of space");
        exit(0);
    }
    a->nodetype = 'K';
    a->number = d;
    return (struct node *)a;
}

struct node *newcmp(int cmptype, struct node *l, struct node *r){
    struct node *a = malloc(sizeof(struct node));

    if(!a){
        yyerror("Out of space");
        exit(0);
    }
    a->nodetype = '0' + cmptype;
    a->l = l;
    a->r = r;
    return a;

}

struct node *newref(struct symbol *s){
    struct symref *a = malloc(sizeof(struct symref));
    if(!a) {
        yyerror("out of space");
        exit(0);
    }
    a->nodetype = 'N';
    a->s = s;
    return (struct node *)a;

}

struct node * readasgn(struct symbol *s){
    struct symasgn *a = malloc(sizeof(struct symasgn));
    if(!a) {
        yyerror("out of space");
        exit(0);
    }
    a->nodetype = 'R';
    a->s = s;
    return (struct node *)a;
}

struct node * newasgn(struct symbol *s, struct node *v){
    struct symasgn *a = malloc(sizeof(struct symasgn));
    if(!a) {
        yyerror("out of space");
        exit(0);
    }
    a->nodetype = '=';
    a->s = s;
    a->v = v;
    return (struct node *)a;


}

struct node * newflow(int nodetype, struct node *cond, struct node *tl, struct node *el){
    struct flow *a = malloc(sizeof(struct flow));

    if(!a){
        yyerror("out of space");
        exit(0);
    }
    a->nodetype=nodetype;
    a->cond = cond;
    a->tl = tl;
    a->el = el;
    return (struct node *)a;
}

int yyerror(char const * s) {
    extern int yylineno;
    fprintf(stderr,"Error %s | Line: %d\n",s,yylineno);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    yyin= fopen(argv[1],"r");
    yyparse();

}
