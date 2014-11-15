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
 * Loop through the group names in the group NIS map, search for
 * the ID in the list of groups the user is member of.
 *
 * \param[in]  *grouplist  The linked list of groups the user is member of.
 */
void resolve_group_names(
		struct groupdef *grouplist)
{
	struct group *group;

	setgrent();
	while( (group=getgrent()) ) {
		DEBUG("Looking for membership of '%d', '%s'\n", group->gr_gid, group->gr_name);
		find_group_in_grouplist(group->gr_gid, group->gr_name, grouplist);
	}
}

/**
 * Read the group NIS map and save each group ID the user is member of (compare
 * the username with each member of the group in turn).
 * Generates a table of group IDs limited to 1024 entries.
 * The group 0 is not handled as it is used to stop the list. But as this is the
 * root group, we can consider we don't want to list it...
 *
 * \TODO: Directly generate a table of groupdef structures (not sure it's better).
 * \TODO: manage the table overflow (the user is member of more than 1024 groups).
 *
 * \param[in]  *username  The name of the user to search in the group map.
 * \return                The table of group IDs. Group 0 not handled.
 */
gid_t *list_group_ids(
		const char *username)
{
	gid_t *idlist;
	struct group *group;
	int i, ii=0;

	idlist = calloc(1024, sizeof(gid_t));

	DEBUG("Looking for groups, user '%s'\n", username);

	setgrent();
	while( (group=getgrent()) ) {
		for(i=0; (group->gr_mem)[i] != NULL; i++) {
			if(strcmp((group->gr_mem)[i], username) == 0 && group->gr_gid != 0) {
				DEBUG("User is member of group '%d' (%d)\n", group->gr_gid, ii);
				idlist[ii++] = group->gr_gid;
				break;
			}
		}
	}

	return idlist;
}

