/*
*	type.h
*
*/


#ifndef _type_h
#define _type_h


typedef char *string;


typedef struct booknode {
	char title[256];
	char author[5][256];
	long catalongnum;
	char headings[5][256];
	char publisher[256];
	int year;
	int ifcirculating;
	struct booknode *next;
} booknode;



#endif
