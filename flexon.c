#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "flexon.h"

void init() {
	#ifdef __linux__
        system("touch lexer.l syntax.y");
    #elif defined(WIN32) || defined(_WIN32)
        system("echo.>lexer.l && echo.>syntax.y");
    #endif
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

void compile() {
    system("flex lexer.l");
    system("bison -d syntax.y");
    system("gcc lex.yy.c syntax.tab.c -lfl -o compiler.exe");
}

void run(char* arg) {
	char cmd[50];
	#ifdef __linux__
        strcpy(cmd, "./compiler.exe");
    #elif defined(WIN32) || defined(_WIN32)
        strcpy(cmd, "compiler.exe");
    #endif
    if (arg != NULL) {
		strcat(cmd, " < ");
		strncat(cmd, arg, 33);
    } 
	system(cmd);
}

void delete() {
	#ifdef __linux__
        system("rm lexer.l syntax.y lex.yy.c syntax.tab.c syntax.tab.h");
    #elif defined(WIN32) || defined(_WIN32)
        system("del /Q lexer.l syntax.y lex.yy.c syntax.tab.c syntax.tab.h");
    #endif
}


int main(int argc, char* argv[]) {
    if (argc < 2) { noarg:
		printf("Please include flags:\n");
		printf("-i: initializes a basic Flex and Bison project\n");
		printf("-c: compiles the current directory's Bison and Flex files\n");
		printf("-r: runs the compiled output\n");
		printf("-x: compiles and runs\n");
		printf("-d: deletes all flexon created files\n");
		exit(EXIT_FAILURE);
    }

    int opt = getopt(argc, argv, "icrxd");
    switch (opt) {
		case 'i': 
		    init();
		    break;
		case 'c': 
		    compile();
		    break;
		case 'r':
		    run(argv[2]);
		    break;
		case 'x': 
		    compile(); run(argv[2]);
		    break;
		case 'd':
		    delete();
		    break;
		default:
		    goto noarg;
		    break;
    }

    return 0;
}
