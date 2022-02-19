#include "splay.h"
#include "mem.h"

//__align(32) unsigned char membase[MEMBASESIZE] ;//__attribute__((at(0x20000100)));
//__align(32) int memtbl[MEMTBLSIZE] ;//__attribute__((at(0x20000100 + MEMBASESIZE + 32))); //用int可以支持更多内存块，short仅能支持3w+个；正数表示未分配，负数表示已分配
extern unsigned char membase[];
extern int memtbl[];
static const int inf = 0x3f3f3f3f;

void mem_init(){
    splay_init();
    Data data; int i;
    data.cnt = MEMTBLSIZE, data.addr = membase;
    splay_insert(&data);
    for(i = 0; i < MEMTBLSIZE; ++i) 
		memtbl[i] = 0;
    memtbl[0] = memtbl[MEMTBLSIZE - 1] = MEMTBLSIZE;
}

//返回指向内存空间首地址的指针，分配失败返回NULL
void* my_malloc(unsigned int sz){ //sz单位：字节
    if(sz == 0) return (void*)0;
    Data data; int cnt = sz / MEMBLKSIZE;
    if(sz % MEMBLKSIZE) ++cnt;
    data.cnt = cnt, data.addr = (void*)0;
    Node *suc = splay_suc(&data);
    if(suc->cnt == inf) return (void*)0; //查询到splay的右边界，即没有足够大的内存块
    Data cur = suc->data; //cur 当前取出的内存块
    void *ret = cur.addr; splay_remove(&suc->data);
    int idx = (int)((unsigned char*)cur.addr - membase) / MEMBLKSIZE;
    memtbl[idx] = memtbl[idx + cnt - 1] = -cnt; 
    if(cur.cnt > cnt){
        cur.cnt -= cnt;
        cur.addr += cnt * MEMBLKSIZE;
        splay_insert(&cur);
        memtbl[idx + cnt] = cur.cnt, memtbl[idx + cnt + cur.cnt - 1] = cur.cnt;
    }
    return ret;
}

void my_free(void *ptr){
    Data data, rm; data.cnt = 0;
    int idx = (int)((unsigned char*)ptr - membase) / MEMBLKSIZE;
    if(memtbl[idx] >= 0) return; //不是my_malloc分配的内存
    int cnt = -memtbl[idx]; data.cnt += cnt;
    memtbl[idx] = memtbl[idx + cnt - 1] = 0;
    int L = 0, R = 0; //L, R表示左右是否有空内存块，有的话就合并
    if(idx > 0 && memtbl[idx - 1] > 0) L = 1;
    if(idx + cnt < MEMTBLSIZE && memtbl[idx + cnt] > 0) R = 1;
    int Lcnt = 0, Rcnt = 0;
    if(L == 1){
        Lcnt = memtbl[idx - 1]; memtbl[idx - 1] = 0;
        data.cnt += Lcnt;
    }
    if(R == 1){
        Rcnt = memtbl[idx + cnt]; memtbl[idx + cnt] = 0;
        data.cnt += Rcnt;
    }
    //分类讨论，有点脑壳疼
    if(L == 0 && R == 0){
        data.addr = ptr;
        memtbl[idx] = memtbl[idx + cnt - 1] = data.cnt;
    } else
    if(L == 1 && R == 0){
        data.addr = ptr - Lcnt * MEMBLKSIZE;
        memtbl[idx - Lcnt] = memtbl[idx + cnt - 1] = data.cnt;
        rm.addr = data.addr, rm.cnt = Lcnt;
        splay_remove(&rm);
    } else
    if(L == 0 && R == 1){
        data.addr = ptr;
        memtbl[idx] = memtbl[idx + cnt + Rcnt - 1] = data.cnt;
        rm.addr = ptr + cnt * MEMBLKSIZE, rm.cnt = Rcnt;
        splay_remove(&rm);
    } else
    if(L == 1 && R == 1){
        data.addr = ptr - Lcnt * MEMBLKSIZE;
        memtbl[idx - Lcnt] = memtbl[idx + cnt + Rcnt - 1] = data.cnt;
        rm.addr = data.addr, rm.cnt = Lcnt;
        splay_remove(&rm);
        rm.addr = ptr + cnt * MEMBLKSIZE, rm.cnt = Rcnt;
        splay_remove(&rm);
    }
    splay_insert(&data);
}