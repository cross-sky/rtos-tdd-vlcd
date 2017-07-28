#ifndef __COMMBOO_H
#define __COMMBOO_H

#define bool char
#define true 1
#define false 0

/* This is used to represent production code that cannot run in the */
/* test environment. */
void explodesInTestEnvironment(void *);

#endif