#include "test.h"
#include "test.h"
#include "stdio.h"
#include "stdbool.h"
#include "stdint.h"
#include "stdarg.h"


static uint32_t my_rand(){
    static uint32_t ret=19260817;
    ret=ret*0x8088405+1;
    return ret;
}

static size_t my_printf(const char *fmt,...){
    static char buf[1024];
    va_list args={0};
    va_start(args,fmt);
    size_t len=vsprintf(buf,fmt,args);
    my_transmit(buf,len);
    return len;
}

typedef struct _Node Node;

struct _Node{
    Node *pre,*next;
    void *start,*end;
};

typedef struct{
    Node *head,*tail;
    size_t size;
}List;

#define N 32

static Node pool[N],*pool_stk[N];
static int pool_top,pool_cnt;

static Node *Alloc_Node(){
    Node *ptr=NULL;
    if(pool_top)ptr=pool_stk[--pool_top];
    else ptr=&pool[pool_cnt++];
    ptr->pre=ptr->next=NULL;
    ptr->start=ptr->end=NULL;
    return ptr;
}

static void Release_Node(Node *ptr){
    pool_stk[pool_top++]=ptr;
}


static void List_Init(List *list){
    list->head=list->tail=Alloc_Node();
    list->tail->start=list->tail->end=(void*)0x40000000;
    list->size=0;
}
static void Node_Print(Node *p){
    my_printf("    start at %#08x and end at %#08x\r\n",(uint32_t)p->start,(uint32_t)p->end);
}
static void List_Insert(List *list,void *ptr,size_t len){
    Node *p=list->head;
    Node *q=Alloc_Node();
    q->start=ptr;
    q->end=(char*)ptr+len;
    while(p->start<=q->start)p=p->next;
    if(p->pre&&q->start<p->pre->end){
        my_printf("Wrong alloc!(Conflict)\r\n");
        Node_Print(p->pre);
        Node_Print(q);
    }
    if(p->start<q->end){
        my_printf("Wrong alloc!(Conflict)\r\n");
        Node_Print(q);
        Node_Print(p);
        while(1);
    }
    q->pre=p->pre;
    q->next=p;
    if(q->pre)q->pre->next=q;
    else list->head=q;
    q->next->pre=q;
    list->size++;
}
static void* List_Erase(List *list,size_t pos){
    Node *p=list->head;
    while(pos--)p=p->next;
    if(p->pre)p->pre->next=p->next;
    else list->head=list->head->next;
    if(p->next)p->next->pre=p->pre;
    Release_Node(p);
    list->size--;
    return p->start;
}

static void List_Print(List *list){
    Node *p=list->head;
    my_printf("Current list(%ld):\r\n",list->size);
    while(p!=list->tail){
        Node_Print(p);
        p=p->next;
    }
}








void start_test(void *heap,size_t heap_size){
    my_printf("test start!\r\n");
    List list;
    List_Init(&list);
    while(true){
        if(list.size<4)goto do_malloc;
        if(list.size>16)goto do_free;
        if(my_rand()&0x40)goto do_malloc;
        goto do_free;
        do_free:{
            void* ptr=List_Erase(&list,my_rand()%list.size);
            my_free(ptr);
            my_printf("free\r\n");
            my_printf("    addr: %#08x\r\n",(uint32_t)ptr);
            goto end;
        }
        do_malloc:{
            size_t len=1<<(my_rand()%10);
            void* ptr=my_malloc(len);
            if(ptr)List_Insert(&list,ptr,len);
            my_printf("malloc\r\n");
            my_printf("    length: %#08x\r\n",len);
            my_printf("    addr:   %#08x\r\n",ptr);
            if(ptr<heap||(char*)ptr+len>(char*)heap+heap_size){
                my_printf("Wrong alloc!(Out of range.)\r\n");
                while(1);
            }
            goto end;
        }
    end:;
        List_Print(&list);
        my_delay(2000);
    }
}
