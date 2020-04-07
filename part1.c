#include <stdlib.h>
#include <stdio.h>

#include "assign3.h"

unsigned int pageTable[32] = {2,4,1,7,3,5,6,0};   // globals for the simulator
unsigned int p = 5, f = 3, d = 7;

void printBinaryAddress(unsigned long addr){
    printf("%lx\n", addr);
}

void translateVirtualAddress(unsigned long *LA, unsigned long *PA) {
    int pnum, fnum, dnum;
    dnum = *LA & 0x7F;
    pnum = *LA >> d;
    fnum = pageTable[pnum];
    *PA = (fnum << d) + dnum;
}

int main(int argc, char * argv[]){

    unsigned long PA, LA;

    FILE *infile;
    FILE *outfile;

    int r_success; // variable for error checking

    infile = fopen(argv[1], "rb");    // open the infile, point infile variable to the open file.

     while(infile != NULL){

         if (fread(&LA, sizeof(unsigned long), 1, infile) != 1) { // check for successful read from the file, break if unsuccessful.
             break;
         }

         translateVirtualAddress(&LA, &PA);  // function translate given vitural address into a physical address.
         printBinaryAddress(LA);
         printBinaryAddress(PA);
     }

    fclose(infile);  // close file on program exit
    return 0;
}

