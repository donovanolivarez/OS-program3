#include <stdio.h>
#include <stdlib.h>

#include "assign3.h"


 // TODO: add documentation and comments. modularize where possible
 
void initializePT(PageTable *PT) {
    int i;
    for (i = 0; i < 32; i++) {
        PT[i].valid = 0;
    }
}


/**
 * Function that translates logical address to physical address.
 * PA and fnum are passed by reference so they can be used in 
 * other calculations in the main function.
 */
void translateLAPart2( unsigned long *LA, unsigned long *PA, PageTable *PT, unsigned int d, unsigned int *fnum) {
    int pnum, dnum;   // local values that are needed for PA translation
    dnum = *LA & 0x7F;  // calculate dnum  
    pnum = *LA >> d;   // calculate pnum
    *fnum = PT[pnum].fnum;   // calculate fnum
    *PA = (*fnum << d) + dnum;   // calculate PA
}
