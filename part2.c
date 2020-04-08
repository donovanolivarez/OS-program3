#include <stdio.h>
#include <stdlib.h>

#include "assign3.h"

 // TODO: add documentation and comments. modularize where possible

PageTable PT[32]; 
unsigned int freeFrames[8] = {0,1,1,1,1,1,1,1};
unsigned int LRUCount[8] = {0};
unsigned int reverseMap[8] = {0};
unsigned int p = 5, f = 3, d = 7;
unsigned int pnum, dnum, fnum;
unsigned int clock = 0;
unsigned int pageFaults = 0;

int main (int argc, char *argv[]) {

    unsigned long PA, LA;

    FILE *infile;   // pointer to infile
    FILE *outfile;  // pointer to outfile

    //initializePT(PT);   // set valid bits to 0 

    int i;
    for (i = 0; i < 32; i++) {
        PT[i].valid = 0;
    }

    infile = fopen(argv[1], "rb");
    outfile = fopen(argv[2], "wb");

    while (infile != NULL) {

         if (fread( &LA, sizeof(unsigned long), 1, infile) != 1) { // error check
             break;
         }

         dnum = LA & 0x07F;
         pnum = LA >> d;
         clock++;

         if (PT[pnum].valid == 1) {
             translateLAPart2(&LA, &PA, PT, d, &fnum);
             LRUCount[fnum] = clock;  // update fnum use time
             reverseMap[fnum] = pnum;  // set pnum in the reverseMap array
             fwrite(&PA, sizeof(unsigned long), 1, outfile);   // write physical address to outfile.
         } else {
             pageFaults++;   // since PTE is invalid, it is a page fault. So we add to total. 
             int x = 0;
             x = findFreeFrame(freeFrames);  // find the free frame, if any.

             if (x > 0) {
                 PT[pnum].fnum = x;
                 PT[pnum].valid = 1;
                 translateLAPart2(&LA, &PA, PT, d, &fnum);
                 LRUCount[fnum] = clock;
                 reverseMap[fnum] = pnum;
                 fwrite(&PA, sizeof(unsigned long), 1, outfile);
             } else {
                int v_frame = findVictim(LRUCount);
                PT[reverseMap[v_frame]].valid = 0;
                PT[pnum].fnum = v_frame;
                PT[pnum].valid = 1;
                translateLAPart2(&LA, &PA, PT, d, &fnum);
                fwrite(&PA, sizeof(unsigned long), 1, outfile);
                LRUCount[fnum] = clock;
                reverseMap[fnum] = pnum;
             }
         }
    }
    printf("page faults %d\n", pageFaults);
    fclose(infile);
    fclose(outfile);
    return 0;
}