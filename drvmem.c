#include "types.h"
#include "defs.h"
#include "spinlock.h"
#include "sleeplock.h"
#include "fs.h"
#include "file.h"
#include "memlayout.h"

#define CHK_MEM(addr)                          \
    do                                         \
    {                                          \
        if (addr < EXTMEM || addr > PHYSTOP)   \
            return -1;                         \
    } while (0)                                

int 
drvmemread(struct inode *ip, char *dst, int n, uint off)
{
    uint addr = off;

    switch (ip->minor)
    {
    case 1:
        memset(dst, 0, n);
        return n;
    case 2:
        if (addr < EXTMEM || addr > PHYSTOP)
            return -1;
        memmove(dst, (void *)off, n);
        return n;
    }
    return 0;
}

int 
drvmemwrite(struct inode *ip, char *buf, int n, uint off)
{
    switch (ip->minor)
    {
    case 2:
        memmove((void *)off, buf, n);
        return n;
    }
    return 0;
}

void 
drvmeminit(void) {
    devsw[P_DEV].write = drvmemwrite;
    devsw[P_DEV].read = drvmemread;
}