#include <stdio.h>
#include <stdlib.h>

#include "assign3.h"


 // TODO: add documentation and comments. modularize where possible
int findFreeFrame(unsigned int *freeFrames) {
    int i;

    for(i = 1; i <= 7; i++) {
        if (freeFrames[i] == 1) {
            freeFrames[i] = 0;
            return i;   // if free frame is found, return i
        }
    }
    printf("free frame not found!\n");
    return 0;   // hit this return if no free frames are found.
}


int findVictim(unsigned int *LRUCount ) {
    int i = 1, frame = 1;  // frame variable to hold return value.
    int min = LRUCount[1];  // initialize the minimum to the first value in the array.
    for (i = 1; i <= 7; i++) {
        if (min > LRUCount[i]) {   
            min = LRUCount[i];   // update min
            frame = i;  // save the frame that is to be returned upon exiting the loop.
        }
    }
    return frame;
}

void printAddress(unsigned long addr){   
    printf("%lx\n", addr);
}