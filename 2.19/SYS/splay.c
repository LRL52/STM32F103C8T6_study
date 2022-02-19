#include "splay.h"
#include <stdio.h>
#include <stdlib.h>

static Node *root;
static const int inf = 0x3f3f3f3f;

static int comp(const Data *t1, const Data *t2){ //��cntΪ��1�ؼ��֣�addrΪ��2�ؼ��ֱȽϣ���t1 > t2ʱ����1
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
static void rotate(Node *x){ //�ⲿ�ִ���ܳ�Ҳû�취
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


Node *splay_suc(const Data *x){ //��Ȼ����ĺ�����ϸ���ڣ����ڷ����ڴ������ƽ������ʱ��ֻ���x�ĵ�ַ��Ϊ��С��Ҳ�����ڴ��������ڽ��������ѡ��
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
    init_data.cnt = inf, init_data.addr = 0; //��32�ֽ�Ϊһ������㣬inf����ǡ���൱��31GB�ڴ棬�ڴ����ʱ���ܳ�����
    splay_insert(&init_data);
}