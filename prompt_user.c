#include "main.h"

void prompt_user(void)
{
	char buffer[1024] = {0};
	//printf("%s ", getcwd(buffer, 1024));
	newputs(getcwd(buffer, 1024));
	newputs(" ");
	newputs("#cisfun$ ");
}