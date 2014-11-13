/******************************************************************************
 * Utilities: error reporting, group name selection, etc...
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
#include <stdarg.h>

#include "membership.h"

/**
 * Print a fatal error message and exit. Same prototype as printf()
 * functions. Prefixes the message with an error marker, add the carriage
 * return character, exit as a failure.
 *
 * \param[in]  format  The message format string (see printf doc)
 * \param[in]  ...     The variables to format...
 */
void fatal_error(char *format, ...)
{
	va_list params;

	va_start(params, format);
	fprintf(stderr, "[FATAL] ");
	vfprintf(stderr, format, params);
	fprintf(stderr, "\n");
	va_end(params);
	exit(EXIT_FAILURE);
}

/**
 * Choose a name for the group.
 *
 * Compare the already defined name for the group with a possible friend.
 * If the current name is null (not set yet), use the proposed name.
 * If the proposed name is smaller than the current name, and they match up to
 * the proposed name, choose the proposed name.
 * In all cases, if choosing the (new) proposed name, use a copy of the string
 * as it may be cleared without notice...
 *
 *\param[in]  currentname   The current group name.
 *\param[in]  comparedname  A possible shorter name for the group.
 *\return                   The chosen name (the shorter one).
 */
char *choose_name(
		char *currentname,
		char *comparedname)
{
	size_t currentlength, comparedlength;

	if(currentname == NULL) {
		DEBUG("Setting name to '%s'\n", comparedname);
		return strdup(comparedname);
	}

	currentlength  = strlen(currentname);
	comparedlength = strlen(comparedname);

	if(comparedlength < currentlength && strncmp(currentname, comparedname, comparedlength) == 0) {
		DEBUG("Changing name of '%s' into '%s'\n", currentname, comparedname);
		return strdup(comparedname);
	}

	return currentname;
}

