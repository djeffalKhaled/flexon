#ifndef FLEXON_H
#define FLEXON_H

const char* lexer_code = 
"%{\n"
"    #include<stdio.h>\n"
"    #include \"syntax.tab.h\"\n"
"    extern YYSTYPE yylval;\n"
"    extern int nb_ligne;\n"
"    extern int col;\n"
"%}\n"
"/*Regular Expressions Definitions*/\n"
"letter [a-zA-Z]\n"
"number [0-9]\n"
"\n"
"%%\n"
"\n"
"int {printf(\"LEXER: INT\\n\"); col=col+yyleng; return INT;}\n"
"main {printf(\"LEXER: MAIN\\n\"); return MAIN;}\n"
"\"(\" {printf(\"LEXER: (\\n\"); col=col+yyleng; return LEFT_BRACKET;}\n"
"\")\" {printf(\"LEXER: (\\n\"); col=col+yyleng; return RIGHT_BRACKET;}\n"
"\"{\" {printf(\"LEXER: {\\n\"); col=col+yyleng; return LEFT_BRACE;}\n"
"\"}\" {printf(\"LEXER: }\\n\"); col=col+yyleng; return RIGHT_BRACE;}\n"
"\n"
"[ \\t]\n"
"\\n nb_ligne++;\n"
". printf(\"Lexical error at line %d column %d\\n\", nb_ligne, col);\n"
"%%\n";

const char* syntax_code = 
"%{\n"
"    #include <stdio.h>\n"
"    #include <string.h>\n"
"    int nb_ligne = 0;\n"
"    int col=0;\n"
"    extern int yylex(void);\n"
"    void yyerror(const char *msg); \n"
"%}\n"
"\n"
"%token INT MAIN\n"
"%token LEFT_BRACE RIGHT_BRACE\n"
"%token LEFT_BRACKET RIGHT_BRACKET\n"
"\n"
"%start S\n"
"%%\n"
"S:   \n"
"    |  INT MAIN LEFT_BRACKET RIGHT_BRACKET LEFT_BRACE RIGHT_BRACE { printf(\"Correct Syntax\\n\"); }\n"
"    ;\n"
"%%\n"
"\n"
"int main(int argc, char *argv[]) {\n"
"    yyparse();\n"
"    return 0;\n"
"}\n"
"int yywrap(void) {  \n"
"    return 1;\n"
"}\n"
"void yyerror(const char *msg) { \n"
"    printf(\"Syntax Error at lign %d column %d\\n\", nb_ligne, col);\n"
"}\n";

#endif
