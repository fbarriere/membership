/******************************************************************************
 * Handle a linked list of group descriptions (ID, name).
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
 * Group description structure constructor. Given an ID, create a new
 * groupdef structure.
 *
 * \param[in]  id   The ID of the new group description to create.
 * \return          The pointer to the new groupdef structure.
 */
struct groupdef *groupdef_new(
		gid_t id)
{
	struct groupdef *newgroup;

	newgroup = malloc(sizeof(struct groupdef));

	newgroup->id   = id;
	newgroup->name = NULL;

	return newgroup;
}

/**
 * Add the given group (ID+name) to the list of groups the current user
 * is member of. If the group is already in the list (a group with the same
 * ID is already listed), compare the name and choose the most relevant one.
 *
 * \param[in]  **grouplist  The current list of groups. Used to trigger the
 *                          building of an intial empty list, if NULL.
 * \param[in]    id         The ID of the new group to add to the list.
 * \param[in]    gname      The name of the group to add to the list.
 * \return                  The head of the table of groupdef structures.
 */
struct groupdef **add_group_to_grouplist(
		struct groupdef **grouplist,
		gid_t id,
		const char *gname)
{
	int i;

	if(grouplist == NULL) {
		DEBUG("Creating membership list\n");
		grouplist = calloc(1024, sizeof(struct groupdef *));
	}

	for(i=0; grouplist[i] != NULL; i++) {
		if((grouplist[i])->id == id) {
			DEBUG("Group (id) %d is already in the list [%d)\n", id, i);
			(grouplist[i])->name = choose_name((grouplist[i])->name, gname);
			return grouplist;
		}
	}
	DEBUG("Adding group (id) %d (name) %s to the list [%d]\n", id, gname, i);
	grouplist[i]         = groupdef_new(id);
	(grouplist[i])->name = choose_name((grouplist[i])->name, gname);

	return grouplist;
}

