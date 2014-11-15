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

struct groupdef *groupdef_new(
		gid_t id)
{
	struct groupdef *newgroup;

	newgroup = malloc(sizeof(struct groupdef));

	newgroup->id   = id;
	newgroup->name = NULL;
	newgroup->next = NULL;

	return newgroup;
}

/**
 * Append an element after the current element. Create the new
 * structure, and add it after the reference element.
 *
 * \param[in]  *prev  The reference element, add after this one.
 * \param[in]   id    The ID of the group to append.
 *
 * \return            The last group created+added (to be the new reference).
 */
struct groupdef *append_to_grouplist(
		struct groupdef *prev,
		gid_t id)
{
	struct groupdef *newgroup;

	newgroup = groupdef_new(id);

	if(prev == NULL) {
		DEBUG("Creating first group: '%d'\n", id);
		prev = newgroup;
	}
	else {
		DEBUG("Adding group: '%d'\n", id);
		prev->next = newgroup;
	}

	return newgroup;
}

/**
 * Create the linked list, given the array of GIDs the user is member of.
 *
 * \param[in]  *idlist   The beginning of the IDs table.
 * \return               The head of the list.
 */
struct groupdef *create_grouplist(
		gid_t *idlist)
{
	struct groupdef *grouplist=NULL, *lastgroup=NULL;
	int i;
	struct group *group;

	for(i=0; idlist[i] != 0; i++) {
		group = getgrgid(idlist[i]);
		lastgroup = append_to_grouplist(lastgroup, idlist[i]);
		if(grouplist == NULL) {
			grouplist = lastgroup;
		}
	}

	return grouplist;
}

/**
 * look for a group ID in the linked list and check or update
 * its name.
 *
 * \param[in]   gid    The ID of the group to look for.
 * \param[in]  *name   A proposal for the group name.
 * \param[in]  *list   The linked list of groupdef structures.
 */
void find_group_in_grouplist(
		gid_t gid,
		char *name,
		struct groupdef *list)
{
	struct groupdef *group;

	for(group=list; group != NULL; group=group->next) {
		if(group->id == gid) {
			DEBUG("Validating names for group '%d'\n", gid);
			group->name = choose_name(group->name, name);
		}
	}
}

