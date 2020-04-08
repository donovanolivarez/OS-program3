#include <stdlib.h>
#include <stdio.h>

#include "assign3.h"

unsigned int pageTable[32] = {2,4,1,7,3,5,6,0};   // globals for the simulator
unsigned int p = 5, f = 3, d = 7;


void printAddress(unsigned long addr){
    printf("%lx\n", addr);
}

void translateVirtualAddress(unsigned long *LA, unsigned long *PA) {
    int pnum, fnum, dnum;   // local values that are needed for PA translation
    dnum = *LA & 0x7F;  // calculate dnum  
    pnum = *LA >> d;   // calculate pnum
    fnum = pageTable[pnum];   // calculate fnum
    *PA = (fnum << d) + dnum;   // calculate PA
}

int main(int argc, char * argv[]){

    unsigned long PA, LA;

    FILE *infile;  //pointer to input file
    FILE *outfile; // pointer to output file


    infile = fopen(argv[1], "rb");    // open the infile, point infile variable to the open file.
    outfile = fopen(argv[2], "wb");  // same as above, but with outfile

     while(infile != NULL){

         if (fread(&LA, sizeof(unsigned long), 1, infile) != 1) { // check for successful read from the file, break if unsuccessful.
             break;
         }

         translateVirtualAddress(&LA, &PA);  // function to translate given vitural address into a physical address.
         // printBinaryAddress(LA);  // uncomment to check what is being read from file.
         // printBinaryAddress(PA);  // uncomment to check what is being read from file.
         fwrite(&PA, sizeof(unsigned long), 1, outfile);  // write physical address to the outfile
     }

    fclose(infile);  // close files on program exit
    fclose(outfile);
    return 0;
}

