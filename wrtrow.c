#include <stdio.h>
#include "wrtrow.h"

/*
 * wrtrow
 *
 * usage:   given an array of pointers to columns and an array of columns to
 *          ouput and a count of output columns
 *          output those columns specified in the output array (contents are
 *          index numbers of the input array)
 * args:
 *  ptable  points at array of pointers each element points at a data field
 *  coltab  points array of ints each element is an index in ptable in print order
 *  outcols number of elements in array coltab
 *  outdelim the output field delimiter to use
 */
void
wrtrow(char **ptable, int *coltab, int outcols, char outdelim)
{  
    int *lastcol;
    lastcol=coltab+outcols-1;
    
    while(coltab != lastcol){
       //printf("%s %d %c\n", *ptable,*coltab, outdelim);
       printf("%s%c", *(ptable+*coltab), outdelim);
       coltab++;
    }
    //printf("%s %d %c\n", *ptable, *coltab, outdelim);
    printf("%s\n", *(ptable+*coltab));
    
}
