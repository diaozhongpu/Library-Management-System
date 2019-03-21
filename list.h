/*
 * File: list.h
 * Version: 1.0
 * Last modified on Sun Jul 24 10:32:49 1994 by eroberts
 * -----------------------------------------------------
 * This file contains several definitions that form the
 * core of a general-purpose ANSI C library developed by Eric
 * Roberts.  The goal of this library is to provide a basic
 * set of tools and conventions that increase the readability
 * of C programs, particularly as they are used in a teaching
 * environment.
 *
 * The basic definitions provided by genlib.h are:
 *
 *    1.  Declarations for several new "primitive" types
 *        (most importantly bool and string) that are
 *        used throughout the other libraries and
 *        applications as fundamental types.
 *
 *    2.  A new set of functions for memory allocation.
 *
 *    3.  A function for error handling.
 *
 *    4.  A repeat statement for loops with interior exits.
 */

#ifndef _list_h
#define _list_h


//#include"type.h"

#define UPPERBOUND 1000

/*
 * Type: string
 * ------------
 * The type string is identical to the type char *, which is
 * traditionally used in C programs.  The main point of defining a
 * new type is to improve program readability.   At the abstraction
 * levels at which the type string is used, it is usually not
 * important to take the string apart into its component characters.
 * Declaring it as a string emphasizes this atomicity.
 */


//typedef booknode libraryDB[UPPERBOUND];


//static booknode * CreateDoc();

static booknode * InsertDoc(struct booknode *head);

static booknode * DeleteDoc(struct booknode *head);

void PrintDoc(struct booknode *head);

void SearchBySubject (booknode *libdata,string subject);


#endif
