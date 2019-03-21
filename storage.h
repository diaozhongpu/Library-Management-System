/*
 * File: storage.h
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

#ifndef _storage_h
#define _storage_h

//#include "type.h"

#define UPPERBOND 1000
#define EndMarker "-----"
#define BigEndMarker "----------"
#define EndOfFile "=========="



static booknode * ReadDatabase();


 
void SaveDatabase();




#endif
