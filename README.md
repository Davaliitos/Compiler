# Interpreter-Compiler
Final Project - Compiler's Course- Using Bison and Flex

This compiler is using the following grammar:

prog → opt decls opt fun decls begin opt stmts end

opt decls → decls | ε

decls → dec ; decls | dec

dec → var id: tipo

opt fun decls → fun decls | ε

fun decls → fun dec; fun decls | fun dec

fun dec → fun id(opt params): tipo opt decls begin opt stmts end

opt params → param lst | ε

param lst → param, param lst | param

param → id : tipo

tipo → int | float

stmt → id ← expr
| if (expresion)stmt
| ifelse (expresion)stmt stmt
| while (expresion)stmt
| read id
| print expr
| begin opt stmts end
| return expr

opt stmts → stmt lst | ε

stmt lst → stmt ; stmt lst | stmt

expresion → expr | expr relop expr

expr → expr + term
| expr - term
| signo term
| term

term → term * factor
| term / factor
| factor

factor → ( expr )
| id
| numint
| numfloat
| id(opt args)

opt args → arg lst | ε

arg lst → expr, arg lst | expr

relop → <
| >
| =
| <=
| >=

signo → ∼

Instructions to run:

Cmd line
bison -d final.y
flex final.l
gcc lex.yy.c final.tab.c -o final

