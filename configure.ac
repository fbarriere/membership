#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([membership], [1.0.0], [vieil.anarchiste@gmail.com])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([src/membership.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_TESTDIR([tests])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_UID_T
AC_TYPE_SIZE_T

# Checks for library functions.
#AC_FUNC_MALLOC
AC_CHECK_FUNCS([endgrent strdup])

AC_OUTPUT([Makefile src/Makefile tests/Makefile])
