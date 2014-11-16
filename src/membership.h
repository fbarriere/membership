/*
 * userinfo.h
 *
 *  Created on: 7 nov. 2014
 *      Author: francois
 */

#ifndef MEMBERSHIP_H_
#define MEMBERSHIP_H_

/**
 * Simple linked list structure to handle user groups (name and id).
 */
struct groupdef {
	char *name;
	gid_t id;
	struct groupdef *next;
};

#define DEBUG(...) if(debug > 0) { printf("[DEBUG] "); printf(__VA_ARGS__) ; }

int debug;

/* Utility functions */

void  fatal_error(char *format, ...);
char *choose_name(char *currentname, const char *comparedname);

/* List of group definitions (id, name) management functions */

struct groupdef *groupdef_new(gid_t id);
struct groupdef **add_group_to_grouplist(struct groupdef **grouplist, gid_t id, const char *gname);

/* System group file interface functions */

void start_sysgroup(void);
void end_sysgroup(void);

struct groupdef **list_groups(const char *username);

/* Report part */

void report_membership(struct groupdef **grouplist, const char *sep);

#endif /* MEMBERSHIP_H_ */
