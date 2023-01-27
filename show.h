#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int show(char* path) {
    FILE* ptr;
    char ch;

    ptr = fopen(path, "r");

    if (NULL == ptr) {
        printf("failed to open file");
    }

    printf("%s",path);

    do {
        ch = fgetc(ptr);
        printf("%c",ch);
    } while (ch != EOF);

    fclose(ptr);
    return 0;
}