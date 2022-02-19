#include "splay.h"
#include <stdio.h>
#include <stdlib.h>

static Node *root;
static const int inf = 0x3f3f3f3f;

static int comp(const Data *t1, const Data *t2){ //以cnt为第1关键字，addr为第2关键字比较，当t1 > t2时返回1
    if(t1->cnt != t2->cnt) return t1->cnt > t2->cnt;
    return t1->addr > t2->addr;
}

static int equal(const Data *t1, const Data *t2){
    return t1->cnt == t2->cnt && t1->addr == t2->addr;
}

static inline int chk(Node* cur){
    if(cur->par != NULL) return cur->par->rs == cur;
    return 0;
}
static void pushup(Node* cur){
    int size = cur->cnt;
    if(cur->ls) size += cur->ls->size;
    if(cur->rs) size += cur->rs->size;
    cur->size = size;
}
static void rotate(Node *x){ //这部分代码很丑，也没办法
    Node *y = x->par, *w, *z = y ? y->par: NULL; int k = chk(x);
    if(k == 0) w = x->rs, y->ls = w; 
    else w = x->ls, y->rs = w;
    if(w != NULL) w->par = y;
    if(chk(y) && z && z->rs) z->rs = x; 
    else if(z && z->ls) z->ls = x;
    x->par = z;
    if(k == 0) x->rs = y; else x->ls = y;
    y->par = x;
    pushup(y); pushup(x);
}

static void splay(Node* x, Node* goal){
    while(x->par != goal){
        Node *y = x->par, *z = y->par;
        if(z != goal){
            if(chk(x) == chk(y)) rotate(y);
            else rotate(x);
        }
        rotate(x);
    }
    if(goal == NULL) root = x;
}

static void find(const Data *x){
    Node *cur = root;
    while(!equal(&cur->data, x)){
        if(comp(x, &cur->data) && cur->rs) cur = cur->rs;
        else if(!comp(x, &cur->data) && cur->ls) cur = cur->ls;
        else break;
    }
    splay(cur, NULL);
}

void splay_insert(const Data *x){
    Node *cur = root, *p = NULL;
    while(cur != NULL && !equal(&cur->data, x)){
        p = cur;
        if(comp(x, &cur->data)) cur = cur->rs;
        else cur = cur->ls;
    }
    if(cur != NULL) ++cur->cnt;
    else{
        cur = (Node*)malloc(sizeof(Node));
        if(p != NULL)
            if(comp(x, &p->data)) p->rs = cur;
            else p->ls = cur;
        cur->par = p, cur->data = *x;
        cur->size = cur->cnt = 1;
        cur->ls = cur->rs = NULL;
    }
    splay(cur, NULL);
}

static Node *pre(const Data *x){
    find(x); if(comp(x, &root->data)) return root;
    Node *cur = root->ls;
    while(cur->rs) cur = cur->rs;
    return cur;
}


Node *splay_suc(const Data *x){ //虽然这里的后继是严格大于，但在分配内存块搜索平衡树的时候只需把x的地址设为极小，也能让内存块个数等于结点的情况被选中
    find(x); if(comp(&root->data, x)) return root;
    Node *cur = root->rs;
    while(cur->ls) cur = cur->ls;
    return cur;
}

void splay_remove(const Data *x){
    Node *prex = pre(x), *sucx = splay_suc(x);
    splay(prex, NULL); splay(sucx, prex);
    Node *cur = sucx->ls;
    if(cur->cnt > 1){
        --cur->cnt; splay(cur, NULL);
    } else {
        free(sucx->ls);
        sucx->ls = NULL; splay(sucx, NULL);
    }
}


void splay_init(void){
    Data init_data;
    init_data.cnt = -1, init_data.addr = 0;
    splay_insert(&init_data);
    init_data.cnt = inf, init_data.addr = 0; //以32字节为一个块计算，inf个块恰好相当于31GB内存，内存管理时不能超过它
    splay_insert(&init_data);
}