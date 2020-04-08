typedef struct pagetable
{
    unsigned int fnum;
    unsigned int valid;
    
} PageTable;

/* Part 1 Functions */
void translateVirtualAddress(unsigned long *LA, unsigned long *PA);
void printAddress(unsigned long);


/* Part 2 Functions */
void translateLAPart2( unsigned long *LA, unsigned long *PA, PageTable *PT, unsigned int d, unsigned int *fnum);
void initializePT(PageTable *PT);
int findVictim(unsigned int *LRUCount );
int findFreeFrame(unsigned int *freeFrames);