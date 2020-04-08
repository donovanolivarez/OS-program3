#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "assign3.h"

void initializePT(PageTable *PT, unsigned int PTEs) {
    int i;
    for (i = 0; i < PTEs; i++) {
        PT[i].valid = 0;
    }
}

void initializeFreeFrames(unsigned int *freeFrames, unsigned int frames ) {
    freeFrames[0] = 0;   //reserved for OS

    int i;
    for (i = 1; i <= frames; i++) freeFrames[i] = 1;
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


/**
 * Function that translates logical address to physical address.
 * Adjusted to accept the input mask as a parameter.
 */
void translateLAPart3( unsigned long *LA, unsigned long *PA, PageTable *PT, unsigned int d, unsigned int *fnum, unsigned int mask) {
    int pnum, dnum;   // local values that are needed for PA translation
    dnum = *LA & mask;  // calculate dnum  
    pnum = *LA >> d;   // calculate pnum
    *fnum = PT[pnum].fnum;   // calculate fnum
    *PA = (*fnum << d) + dnum;   // calculate PA
}


/**
 * Function that calculates the bits we need , based on the 
 * sizes specified by the user. Bits are returned though the parameter
 */ 
void calculateBits( unsigned int *input , unsigned int *p, unsigned int *d, unsigned int *f) {
    unsigned int pageSize, virtualMemSize, physicalMemSize, pageSizeBits, virtualMemBits, physicalMemBits;
    pageSize = input[0];
    virtualMemSize = input[1];
    physicalMemSize = input[2];
    pageSizeBits = log2(pageSize);  // log will give us the bits we are looking for. 
    virtualMemBits = log2(virtualMemSize);
    physicalMemBits = log2(physicalMemSize);
    *p = virtualMemBits - pageSizeBits;    // subtract the total from the offset bits to get the bits we need.
    *d = pageSizeBits;
    *f = physicalMemBits - pageSizeBits;
}


/**
 * Function to calculate the number of pages and frames 
 * needed for arrays to properly allocate space.
 */
void calculateEntrySizes(unsigned int *input, unsigned int *PTEs, unsigned int *frames) {
    unsigned int pageSize, virtualMemSize, physicalMemSize;
    pageSize = input[0];
    virtualMemSize = input[1];
    physicalMemSize = input[2];
    *PTEs = virtualMemSize / pageSize;    // since sizes are in bytes, we can divide the total by the page size to get the number of entries we have
    *frames = physicalMemSize / pageSize;
}

