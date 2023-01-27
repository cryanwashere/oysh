#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>


#include "show.h"

#define MAXLIST 100
#define MAXCOM 1000

void init_shell() {
	printf("Welcome to OYster SHell!\n");
	//char* username = getenv("USER");
	//printf("\nuser: %s", username);
}




int takeInput(char* str) {
    char* buf;

    char* prompt;
    //char* username = getenv("USER");
    //strcat(prompt, username);
    buf = readline("@");
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

/*
int cmdHandler(char** parsed) {

}
*/
/*
int processString(char* str, char** parsed, char** parsedpipe)
{
    char* strpiped[2];
    int piped = 0;

    piped = parsePipe(str, strpiped);

    if (piped) {
        printf("oysh does not yet support piped inputs");
    } else {
        parseSpace(str, parsed);
    }
    return 0;
}
*/
void execArgs(char** parsed) {
    pid_t pid = fork();
    if (pid == -1) {
        printf("failed forking child\n");
        return;
    } else if (pid == 0) {
        if (execvp(parsed[0], parsed) < 0) {
            printf("\nfailed to execute command");
        }
        exit(0);
    } else {
        wait(NULL);
        return;
    }
}

int main() {

    char inputString[MAXCOM], *parsedArgs[MAXLIST];
    char* parsedArgsPiped[MAXLIST];
    int execFlag = 0;
    init_shell();

    while (1) {
        takeInput(inputString);

        if (strlen(inputString) == 0) {
            continue;
        }

        int usedBuiltInCommand = 0;
        if (strcmp(inputString,"what is the best shell?") == 0) {
            printf("OYster SHell");
            usedBuiltInCommand = 1;
        } 
        if (strcmp(inputString,"exit") == 0) {
            printf("goodbye");
            usedBuiltInCommand = 1;
            exit(0);
        }
        parseSpace(inputString, parsedArgs);
        if (strcmp(parsedArgs[0], "show") == 0) {
            show(parsedArgs[1]);
            usedBuiltInCommand = 1;
        }
        
        //execFlag = processString(inputString, parsedArgs, parsedArgsPiped);
        if (usedBuiltInCommand == 0) {
            
            execArgs(parsedArgs);
        }
        

        
    }
    
    return 0;
}