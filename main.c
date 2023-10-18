/*
 * Programming assignment 5 part 2
 * Sue-Hyun Hong
 */ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "token.h"
#include "wrtrow.h"

/*
 * main
 */ 
int 
main(int argc, char **argv)
{
    char **ptable;              /* array of pointers to column starts */
    int  *coltab;               /* array of column indexes to print */
    char *buf = NULL;           /* input buffer, getline() will allocate it */
    size_t bufsz = 0;           /* size of buffer altered by getline()*/
    unsigned long linecnt = 0;  /* input line counter */
    unsigned long dropcnt = 0;  /* number of input lines dropped counter */
    int incols = 0;             /* number of columns in the input */
    int outcols = 0;            /* number of columns in the output */
    char *ptr;                  /* pointer for use by strtoul() */
    int opt;                    /* option flag returns by getopt */
    char indelim = INDELIM;     /* input delimter set to default */
    char outdelim = OUTDELIM;   /* ouput delimter set to default */
    int  *colptr;               /* pointer to coltab  */


    /*
     * parse the options with getopt
     */
    while ((opt = getopt(argc, argv, "c:i:o:")) != -1) {
        switch (opt) {
        case 'c':
            /* set number of columns in the input
             * number of columns in dsv file must be >= MINCOL
             */
			errno=0;
            incols=(int)strtol(optarg, &ptr, 10);
        	/*if successful conversion, ptr has address of the nul char of the
             * string in it.*/
        	if ((*ptr != '\0') || (errno != 0)||(incols < MINCOL)){
                fprintf(stderr, "%s: improper input column count\n", *argv);
                return EXIT_FAILURE;
            }
            break;
             
        case 'i':
            /*
             * set the input delimiter
             */
			if ((*(optarg+1)!='\0')||(*optarg == '\n')||(*optarg == '\"')){
                fprintf(stderr, "%s: -i operand must be a single char\n",
                *argv);
                return EXIT_FAILURE;
            }
			indelim=*optarg;
            break;
        case 'o':
            /*
             * set the output delimiter
             */
            if ((*(optarg+1)!='\0')||(*optarg == '\n')||(*optarg == '\"')){
                fprintf(stderr, "%s: -o operand must be a single char\n", *argv);
                return EXIT_FAILURE;
            }
            outdelim=*optarg;
             /* PA5 action: delete this comment and complete this section
              * use the following error message and return with EXIT_FAILURE
              * fprintf(stderr, "%s: -o operand must be a single char\n", *argv);
              */
            break;
        case '?':
            /* FALL THROUGH */
        default:
            fprintf(stderr,
                "Usage: %s -c count [-i inputdelim] [-o outputdelim] col [..]\n",
                *argv);
            return EXIT_FAILURE;
            /* NOT REACHED */
        }
    }

    /*
     * make sure we have the required -c flag if not error
     */
     if (incols==0){
        fprintf(stderr,
        "Usage: %s -c count [-i inputdelim] [-o outputdelim] col [..]\n", *argv);
        return EXIT_FAILURE;
     }

    /*
     * make sure there is at least one output column specified, outcols
     * calculates the number of output columns
     */
    if ((outcols = argc - optind) <= 0) {
        fprintf(stderr,"%s: at least one output column required\n", *argv);
        return EXIT_FAILURE;
    }
    
    /*
     * allocate space for input pointer table using incols to size the array
     * if unable to allocate, return with EXIT_FAILURE
     */
    errno=0;
    if (((ptable = malloc(incols * sizeof(*ptable))) == NULL) || (errno!=0)){
        fprintf(stderr, "%s: malloc() failed input table\n", *argv);
        return EXIT_FAILURE;
    }

    /*
     * allocate space for the output table, an array of index offsets
     * into ptable using outcols to size the array
     */
    errno=0;
    if (((coltab = malloc(outcols * sizeof(*coltab))) == NULL) || (errno!=0)){
       fprintf(stderr, "%s: malloc() failed output index table\n", *argv);
       return EXIT_FAILURE;
    }
    /*colptr to traverse coltab*/
    colptr=coltab;

    /*
     * fill in the index table
     * and check that each of columns specified is valid
     * (each must be MINCOL or greater and less than equal to incols)
     * getopt() places the index value of the argument after the last flag 
     * in the variable optind. The index of the last argument is in argc-1
     * so write a loop that takes each parameter from argv + optind to
     * the last argument. In the loop use strtol() to convert the string column
     * number to an integer and store it in order to the array coltab.
     */
     for(int i = optind; i < argc; i++){
        *colptr=(int)strtol(*(argv+i), &ptr, 10);
        if ((*ptr != '\0') || (errno != 0) ||
        (*colptr < MINCOL) || (*colptr > incols)){
            fprintf(stderr, "%s: improper output column value\n", *argv);
            return EXIT_FAILURE;
        }
        
        *colptr=*colptr-1;
        colptr++;
     }
    

    /*
     * read the input one line at a time, break into tokens and write out the
     * selected columns
     * getline() does a malloc() for you of the correct sized buffer and puts
     * the address in buf and the size of the allocated buffer in bufsz
     * do not forget to free the space in buf before you exit.
     */
    
    while (getline(&buf, &bufsz, stdin) > 0) {
        linecnt++;

        /*
         * break the input into data fields pointed at by array ptable
         */

        if (token(buf, indelim, incols, ptable, linecnt, *argv) != 0)
            dropcnt++;        /* count the dropped rows */
        else
           wrtrow(ptable, coltab, outcols, outdelim);

        free(buf);
        buf=NULL;
    }

    /*
     * free buffers include the one allocated by getline in buf
     * to keep valgrind happy
     */

    free(buf);
    free(ptable);
    free(coltab);
    /* PA5 action: delete this comment and complete this section */

    /*
     * write summary
     */
    fprintf(stderr, "%s: %lu records input, %lu dropped\n", *argv,
            linecnt, dropcnt);
    if (dropcnt > 0)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}
