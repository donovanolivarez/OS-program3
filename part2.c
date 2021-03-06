#include <stdio.h>
#include <stdlib.h>

#include "assign3.h"

int main (int argc, char *argv[]) {

    PageTable PT[32];                                  // page table array
    unsigned int freeFrames[8] = {0,1,1,1,1,1,1,1};    // array that tells us what frames are free
    unsigned int LRUCount[8] = {0};                    // array that helps with LRU algorithm
    unsigned int reverseMap[8] = {0};                  // array that helps us index into the pagetable with given frame.
    unsigned int p = 5, f = 3, d = 7;                  // p, d, and f bits. 
    unsigned int pnum, dnum, fnum;                     // variables to hold pnum, dnum, and fnum values when they are calculated.
    unsigned int clock = 0;                            // global clock for LRU algorithm
    unsigned int pageFaults = 0;                       // global page fault count

    unsigned long PA, LA;

    FILE *infile;   // pointer to infile
    FILE *outfile;  // pointer to outfile

    initializePT(PT, 32);   // set all valid bits in page table to 0  

    infile = fopen(argv[1], "rb");   // open infile and outfile for reading and writing. 
    outfile = fopen(argv[2], "wb");

    while (infile != NULL) {

         if (fread( &LA, sizeof(unsigned long), 1, infile) != 1) {  // error checking fread
             break;
         }

         dnum = LA & 0x07F;   // calculate dnum
         pnum = LA >> d;      // calculate pnum
         clock++;    // increase clock time by one
         

         if (PT[pnum].valid == 1) {
             translateLAPart2(&LA, &PA, PT, d, &fnum);   //translate LA to PA
             LRUCount[fnum] = clock;  // update fnum use time
             reverseMap[fnum] = pnum;  // set pnum in the reverseMap array
             fwrite(&PA, sizeof(unsigned long), 1, outfile);   // write physical address to outfile.
         } else {
             pageFaults++;   // since PTE is invalid, it is a page fault. So we add to total. 
             int x = 0;
             x = findFreeFrame(freeFrames, 7);  // find the free frame, if any.

             if (x > 0) {             // if free frame is found
                 PT[pnum].fnum = x;   // page table fnum is the free frame we found above.
                 PT[pnum].valid = 1;  // set valid bit in page table
                 translateLAPart2(&LA, &PA, PT, d, &fnum);   // perform translation
                 LRUCount[fnum] = clock;    // update LRU array to reflect current frame usage time
                 reverseMap[fnum] = pnum;   // update reverseMap to reflect current values in the page table
                 fwrite(&PA, sizeof(unsigned long), 1, outfile);    // write to outfile
             } else {                  // free frame is not found
                int v_frame = findVictim(LRUCount, 7);  // find the victim frame to be replaced
                PT[reverseMap[v_frame]].valid = 0;   // index page table to find where victim frame is stored to invalidate it.
                PT[pnum].fnum = v_frame;      // set fnum to the victim frame
                PT[pnum].valid = 1;           // validate the pnum
                translateLAPart2(&LA, &PA, PT, d, &fnum);     // perform translation
                fwrite(&PA, sizeof(unsigned long), 1, outfile);   // write to outfile
                LRUCount[fnum] = clock;     // update clock times in LRU array
                reverseMap[fnum] = pnum;    // update pnum in reverseMap array 
             }
         }
    }
    printf("Part 2 page faults: %d\n", pageFaults);
    fclose(infile);
    fclose(outfile);
    return 0;
}