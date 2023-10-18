/* 
 * Header file for PA4
 * Author: Keith Muller
 * the next two lines are called header guards
 * we will cover this later in the quarter
 */
#ifndef TOKEN_H
#define TOKEN_H
/*
 * Constants
 */
#define MINCOL  1       /* min number of columns */
#define INDELIM ','     /* input column delimiter default */
#define OUTDELIM ','    /* input column delimiter default */

 /*
  * Function prototypes
  */
int token(char *, char, int, char **, unsigned long, char *);
#endif
