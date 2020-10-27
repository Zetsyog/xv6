#include "types.h"
#include "defs.h"
#include "spinlock.h"
#include "sleeplock.h"
#include "fs.h"
#include "file.h"
#include "memlayout.h"

int
drvmemread(struct inode * i, char * dst, int n, uint off) {
    switch(i->minor) {
    case 0:
        return 0;
    case 1:
        memset(dst, 0, n);
        return n;
    }
    return -1;
}
int
drvmemwrite(struct inode *i, char *buf, int n, uint off) {
    switch (i->minor)
    {
    case 0:
    case 1:
        return n;
    }
    return -1;
}

void drvmeminit(void)
{
    devsw[TP2_DEV].write = drvmemwrite;
    devsw[TP2_DEV].read = drvmemread;
}