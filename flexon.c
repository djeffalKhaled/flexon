#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "flexon.h"

void init() {
    system("touch lexer.l syntax.y");
    FILE* lexer = fopen("lexer.l", "w");
    if (lexer == NULL) {
	perror("Lexer File Error"); printf("Could not create or find lexer.l file!\n");
	exit(EXIT_FAILURE);
    }

    fprintf(lexer, "%s", lexer_code);

    FILE* syntax = fopen("syntax.y", "w");
    if (syntax == NULL) {
	perror("Syntax File Error"); printf("Could not create or find syntax.y file!\n");
	exit(EXIT_FAILURE);
    }

    fprintf(syntax, "%s", syntax_code);
}

void exec() {
    system("flex lexer.l");
    system("bison -d syntax.y");
    system("gcc lex.yy.c syntax.tab.c -lfl -o compiler.exe");
}

void delete() {
    system("rm lexer.l syntax.y");
    system("rm lex.yy.c syntax.tab.c syntax.tab.h");
}


int main(int argc, char* argv[]) {
    if (argc < 2) {
	printf("Please include flags:\n");
	printf("-i: initializes a basic Flex and Bison project\n");
	printf("-x: compiles the current directory's Bison and Flex files\n");
	printf("-r: runs the compiled output");
	printf("-d: deletes all flexon created files");
	exit(EXIT_FAILURE);
    }

    int opt = getopt(argc, argv, "ixrd");
    switch (opt) {
	case 'i': 
	    init();
	    break;
	case 'x': 
	    exec();
	    break;
	case 'r':
	    system("./compiler.exe");
	    break;
	case 'd':
	    delete();
	    break;
    }

    return 0;
}
