#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "assign3.h"


int main (int argc, char *argv[]) {

    unsigned long PA, LA;    // variables to hold addresses
    unsigned int sizeInputs[3];  // variables to hold sizes of the inputs as integers
    unsigned int p, d, f;   // varibales to hold p d and f bits
    unsigned int PTEs, frames;   // variables for the number of pages and frames.


    int i;
    for (i = 0; i <= 2; i++) { sizeInputs[i] = atoi(argv[i+1]); }   // convert args into integers

    calculateBits(sizeInputs, &p, &d, &f);              // calculate bit values
    calculateEntrySizes(sizeInputs, &PTEs, &frames);    //  calculate number of pages and frames

    PageTable PT[PTEs];                                // page table array
    unsigned int freeFrames[frames];                   // array that tells us what frames are free
    unsigned int LRUCount[frames];                     // array that helps with LRU algorithm
    unsigned int reverseMap[frames];                   // array that helps us index into the pagetable with given frame.
    unsigned int pnum, dnum, fnum;                     // variables to hold pnum, dnum, and fnum values when they are calculated.
    unsigned int clock = 0;                            // global clock for LRU algorithm
    unsigned int pageFaults = 0;                       // global page fault count

    FILE *infile;   // pointer to infile
    FILE *outfile;  // pointer to outfile

    initializePT(PT, PTEs);   // set all valid bits in page table to 0 
    initializeFreeFrames(freeFrames, frames);  // set all free frames to 1, excluding space for OS.
    
    infile = fopen(argv[4], "rb");   // open infile and outfile for reading and writing. 
    outfile = fopen(argv[5], "wb");

    while (infile != NULL) {
        
         if (fread( &LA, sizeof(unsigned long), 1, infile) != 1) {  // error checking fread
             break;
         }

        unsigned int mask = 0;
        for (i=0; i < d; i++) { mask += pow(2, i); }     // generate mask to use in dnum calculation
        
        dnum = LA & mask;   // calculate dnum
        pnum = LA >> d;      // calculate pnum
        clock++;    // increase clock time by one

         if (PT[pnum].valid == 1) {
             translateLAPart3(&LA, &PA, PT, d, &fnum, mask);   //translate LA to PA
             LRUCount[fnum] = clock;  // update fnum use time
             reverseMap[fnum] = pnum;  // set pnum in the reverseMap array
             fwrite(&PA, sizeof(unsigned long), 1, outfile);   // write physical address to outfile.
         } else {
             pageFaults++;   // since PTE is invalid, it is a page fault. So we add to total. 
             int x = 0;
             x = findFreeFrame(freeFrames, frames - 1) ;  // find the free frame, if any.

             if (x > 0) {             // if free frame is found
                 PT[pnum].fnum = x;   // page table fnum is the free frame we found above.
                 PT[pnum].valid = 1;  // set valid bit in page table
                 translateLAPart3(&LA, &PA, PT, d, &fnum, mask);   // perform translation
                 LRUCount[fnum] = clock;    // update LRU array to reflect current frame usage time
                 reverseMap[fnum] = pnum;   // update reverseMap to reflect current values in the page table
                 fwrite(&PA, sizeof(unsigned long), 1, outfile);    // write to outfile
             } else {                  // free frame is not found
                int v_frame = findVictim(LRUCount, frames - 1);  // find the victim frame to be replaced
                PT[reverseMap[v_frame]].valid = 0;   // index page table to find where victim frame is stored to invalidate it.
                PT[pnum].fnum = v_frame;      // set fnum to the victim frame
                PT[pnum].valid = 1;           // validate the pnum
                translateLAPart3(&LA, &PA, PT, d, &fnum, mask);     // perform translation
                fwrite(&PA, sizeof(unsigned long), 1, outfile);   // write to outfile
                LRUCount[fnum] = clock;     // update clock times in LRU array
                reverseMap[fnum] = pnum;    // update pnum in reverseMap array 
             }
         }
    }
    printf("Part 3 page faults: %d\n", pageFaults);
    fclose(infile);
    fclose(outfile);
    return 0;
}