/******************************************************************************
 * This program reports the list of groups the user is member of as a list
 * of group names separated by commas.
 * The reason for this program is to overcome the NIS group/record size limit
 * that generates several groups with the same ID and similar (but not exactly
 * the same) names.
 * It seems, NIS generates group names by keeping the original name and adding
 * a number suffix, so we just list the groups the user is member of (storing
 * the group IDs), then we resolve the group name and keep, for the groups with
 * the same ID, only the shorter name...
 ******************************************************************************
 *            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *                    Version 2, December 2004
 *
 * Copyright (C) 2014 Francois Barriere / ATMEL corp <francois.barriere@atmel.com>
 *
 * Everyone is permitted to copy and distribute verbatim or modified
 * copies of this license document, and changing it is allowed as long
 * as the name is changed.
 *
 *            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 *
 *  0. You just DO WHAT THE FUCK YOU WANT TO.
 *
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://sam.zoy.org/wtfpl/COPYING for more details.
 ******************************************************************************
 * \TODO: If the user name is not provided, use the current user.
 * \TODO: Select the output name separator by a command line switch.
 * \TODO: Only search group names matching a pattern (look eng-* groups),
 *        with the definition of the pattern through a command line switch.
 ******************************************************************************
 */

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>

#include "membership.h"

/**
 * The usage message for the program. Just a simple array of strings to
 * print, each element on its own line, until NULL.
 */
static
char *usage[] = {
	"",
	" Usage:",
	"",
	"   membership --user <user-name> [--debug]",
	"",
	NULL
};

/**
 * Print the usage to STDERR and exit with an success exit status.
 */
void show_usage(void)
{
	int i;

	for(i=0; usage[i] != NULL; i++) {
		fprintf(stderr, "%s\n", usage[i]);
	}
	exit(EXIT_SUCCESS);
}

/**
 * The name says it all...
 */
int main(int argc, char **argv)
{
	int i;
	char *myname=NULL;
	gid_t *membership;
	struct groupdef *groups;

	for(i=1; i < argc; i++) {
		if(strcmp(argv[i], "--help") == 0) {
			show_usage();
		}
		else if(strcmp(argv[i], "--user") == 0) {
			i++;
			if(i < argc) {
				myname = argv[i];
			}
			else {
				fatal_error("--user switch must be followed by a user name.");
			}
		}
		else if(strcmp(argv[i], "--debug") == 0) {
			debug=1;
			DEBUG("Turning on debugging.\n");
		}
		else {
			fatal_error("Unknown switch '%s'. Use --help for usage.", argv[i]);
		}
	}

	/*
	 * For the moment we just fail if no user name is provided...
	 */
	if(myname == NULL) {
		fatal_error("Please provide a user name.");
	}

	start_sysgroup();

	membership = list_group_ids(myname);
	groups     = create_grouplist(membership);
	resolve_group_names(groups);
	report_membership(groups, ", ");

	end_sysgroup();

	exit(EXIT_SUCCESS);
}
