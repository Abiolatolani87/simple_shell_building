#include "main.h"

/**
 * prompt_user - prints shell prompt
*/
void prompt_user(void)
{
	/**
	 * char buffer[1024] = {0};
	 * newputs(getcwd(buffer, 1024));
	 * newputs(" ");
	 */
	printf("this is argv: %s", *argvalues);
	newputs("$ ");
}
