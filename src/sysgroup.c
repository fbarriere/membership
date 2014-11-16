/******************************************************************************
 * System/NIS groups interface functions.
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
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>

#include "membership.h"

/**
 * Dummy function used to initialize stuff... For the moment there
 * is nothing to initialize, but as we need to call an end function, we
 * create an init one... I like structure and order!
 */
void start_sysgroup(void)
{

}

/**
 * Ending function: call the endgrent() function to clean the group
 * functions interface (see endgrent() man page).
 */
void end_sysgroup(void)
{
	endgrent();
}

/**
 * List the groups the given user is member of. Given a user name, loop
 * through the groups and build a list of group definitions (ID+name).
 *
 * \param[in]  username  The name of the user to search for in the group members.
 * \return               The head of a table of groupdef structures.
 */
struct groupdef **list_groups(
		const char *username)
{
	struct groupdef **grouplist=NULL;
	struct group *group;
	int i;

	DEBUG("Looking for groups, user '%s'\n", username);

	setgrent();
	while( (group=getgrent()) ) {
		for(i=0; (group->gr_mem)[i] != NULL; i++) {
			if(strcmp((group->gr_mem)[i], username) == 0 && group->gr_gid != 0) {
				DEBUG("User is member of group '%d'\n", group->gr_gid);
				grouplist = add_group_to_grouplist(grouplist, group->gr_gid, group->gr_name);
				break;
			}
		}
	}

	return grouplist;

}
