#ifndef __MEM_H__
#define __MEM_H__
#include "splay.h"

#define MEMBASESIZE 14*1024
#define MEMBLKSIZE 32
#define MEMTBLSIZE MEMBASESIZE/MEMBLKSIZE

void mem_init(void);
void* my_malloc(unsigned int sz);
void my_free(void *ptr);
#endif
