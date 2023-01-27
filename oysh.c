#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>

#define MAXLIST 100
#define MAXCOM 1000

void init_shell() {
	printf("Welcome to OYster SHell!");
	//char* username = getenv("USER");
	//printf("\nuser: %s", username);
}


int takeInput(char* str) {
    char* buf;
    buf = readline("\n@");
    if (strlen(buf) != 0) {
        strcpy(str,buf);
        return 0;
    } else { 
       return 1;
    }
}

int parsePipe(char* str, char** strpiped) {
    int i;
    for (i=0;i<2;i++) {
        strpiped[i] = strsep(&str, "|");
        if (strpiped[i] == NULL) {
            break;
        }
    }
    if (strpiped[1] == NULL) {
        return 0;
    } else {
        return 1;
    }
}

void parseSpace(char* str, char** parsed)
{
    int i;
    for (i=0;i<MAXLIST;i++) {
        parsed[i] = strsep(&str, " ");
        if (parsed[i] == NULL) {
            break;
        }
        if (strlen(parsed[i]) == 0) {
            i--;
        }
    }
}

int processString(char* str, char** parsed, char** parsedpipe)
{
    char* strpiped[2];
    int piped = 0;

    piped = parsePipe(str, strpiped);

    if (piped) {
        printf("found a piped input");
    } else {
        parseSpace(str, parsed);
    }
    return 0;
}

int main() {

    char inputString[MAXCOM], *parsedArgs[MAXLIST];
    char* parsedArgsPiped[MAXLIST];
    int execFlag = 0;
    init_shell();

    takeInput(inputString) ;
    execFlag = processString(inputString, parsedArgs, parsedArgsPiped);
    
}