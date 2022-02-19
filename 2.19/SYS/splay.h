#ifndef __SPLAY_H__
#define __SPLAY_H__

typedef struct Data{
    void *addr; //内存块首地址
    int cnt; //内存块个数
    //unsigned char status; //内存块状态：0表示没被占用，可以用于分配；1表示被占用，不能用于分配
}Data;
typedef struct Node{
    Data data;
    int cnt, size;
    struct Node *ls, *rs, *par;
}Node;

void splay_insert(const Data *x);
Node *splay_suc(const Data *x);
void splay_remove(const Data *x);
void splay_init(void);
#endif
