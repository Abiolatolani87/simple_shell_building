#include "main.h"

/**
 * callback - callback function
 * @signum: signal number
*/
void callback(int signum)
{
	newputs("\n$ ");
	(void)signum;
}
