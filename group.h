#ifndef GROUP_H
#define GROUP_H

#include <stdio.h>
#include <stdlib.h>

extern void init_group_array(group *group);

extern void expand_group_array(group *group);

extern void expand_groups(group **group, int *size);

extern void remove_groups(group *group, int number_of_groups);

extern int search_for_group(group *group, int number_of_groups, int number);

extern void print_groups(group *group, int number_of_groups);

#endif /* GROUP_H */