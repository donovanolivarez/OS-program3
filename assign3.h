typedef struct pagetable
{
    unsigned int fnum;
    unsigned int valid;
    
} PageTable;

/* Part 1 Functions */
void translateVirtualAddress(unsigned long *LA, unsigned long *PA);
void printAddress(unsigned long);


/* Part 2 and 3 Functions */
void translateLAPart2( unsigned long *LA, unsigned long *PA, PageTable *PT, unsigned int d, unsigned int *fnum);
void translateLAPart3( unsigned long *LA, unsigned long *PA, PageTable *PT, unsigned int d, unsigned int *fnum, unsigned int mask);
void initializePT(PageTable *PT, unsigned int PTEs);
void initializeFreeFrames(unsigned int *freeFrames, unsigned int frames );
int findVictim(unsigned int *LRUCount, unsigned int frames);
int findFreeFrame(unsigned int *freeFrames , unsigned int frames);
void calculateBits( unsigned int *input , unsigned int *p, unsigned int *d, unsigned int *f);
void calculateEntrySizes(unsigned int *input, unsigned int *PTEs, unsigned int *frames);