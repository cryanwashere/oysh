#include <stdio.h>
#include <stdlib.h>

void init_shell() {
	printf("\n Welcome to oysh!");
	char* username = getenv("USER");
	printf("\nuser: @%s", username);


}
