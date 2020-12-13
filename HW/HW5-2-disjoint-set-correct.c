#include<stdlib.h>
#include<stdio.h>
#define FRIENDS 1
#define STRANGERS 0

struct set
{
    int key;
    struct set* head;
    struct set* tail;
};


struct set* Make_set(int x){
    struct set* rep = (struct set*)malloc(sizeof(struct set));
    rep->key = 1;
    struct set* p = (struct set*)malloc(sizeof(struct set));
    p->key = x;
    p->head = rep;
    p->tail = NULL;

    rep->head = p;
    rep->tail = p;
    return p;
}

struct set* Find_set(struct set* x){
    return x->head->head;
}

void Union(struct set* x,struct set* y){
    struct set* x_head = x->head;
    struct set* y_head = y->head;
    if(x_head->key > y_head->key){
        x_head->key += y_head->key;
        struct set* p = y_head->head;
        while(p->tail != NULL){
            p->head = x_head;
            p = p->tail;
        }
        p->head = x_head;
        x_head->tail->tail = y_head->head;
        x_head->tail = p;
        //return x_head;
    }
    else{
        y_head->key += x_head->key;
        struct set* p = x_head->head;
        while(p->tail != NULL){
            p->head = y_head;
            p = p->tail;
        }
        p->head = y_head;
        y_head->tail->tail = x_head->head;
        y_head->tail = p;
        //return y_head;
    }
    return;
}

int main(){
    int n,m,k;
    scanf("%d%d%d",&n,&k,&m);
    int i;
    struct set** s = (struct set**)malloc(n*sizeof(struct set*));
    for(i = 0; i < n; i++){
        s[i] = (struct set*)malloc(sizeof(struct set));
        s[i] = Make_set(i);
    }
    int stu1,stu2;
    for(i = 0; i < m; i++){
        scanf("%d%d",&stu1,&stu2);
        struct set* loop1 = Find_set(s[stu1]);
        struct set* loop2 = Find_set(s[stu2]);
        if(loop1->key == loop2->key)continue;
        else
            Union(s[stu1],s[stu2]);
    }
    for(i = 0; i < k; i++){
        scanf("%d%d",&stu1,&stu2);
        struct set* loop1 = Find_set(s[stu1]);
        struct set* loop2 = Find_set(s[stu2]);
        if(loop1->key == loop2->key)
            printf("%d\n",FRIENDS);
        else
            printf("%d\n",STRANGERS);
    }
    return 0;
}
