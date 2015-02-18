# membership

Description:
===========

  Simple tool to report user group membership on UNIX. Because of some NIS limitations,
for large groups, the group is splitted into several groups with the same ID but
different names. This makes finding the actual (or intended) group name more difficult
using the usual id command.
This tool is here to simplify this and return the best match in this case.

This tool comes from the need for the atcual group name of the user during the
shell setup (in .cshrc files). The goal is to have something faster and more
flexible (we can make it do what we want) than a collection of id commands piped
into greps and sorts and seds...
