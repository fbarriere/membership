
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>

#include "membership.h"

int main(int argc, char **argv)
{
	int errors=0;

	/* Test the name selection */

	char *newname;
	newname = choose_name(NULL, "hello");
	if(strcmp(newname, "hello") != 0)
		errors++;

	exit(errors);
}
