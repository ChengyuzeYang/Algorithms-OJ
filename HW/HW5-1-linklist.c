#include<stdio.h>
#include<stdlib.h>
struct Listnode{
    int val;
    struct Listnode* next;
};

struct Listnode* insert(struct Listnode* head,int newval){
    struct Listnode* newp = (struct Listnode*)malloc(sizeof(struct Listnode));
    newp->val = newval;
    if(head == NULL){
        newp->next = NULL;
        head = newp;
    }
    else if(head->val > newval){
        newp->next = head;
        head = newp;
    }
    else if(head->next == NULL){
        head->next = newp;
        newp->next = NULL;
    }
    else{
        struct Listnode* p = head;
        struct Listnode* p_pre = (struct Listnode*)malloc(sizeof(struct Listnode));
        p_pre->next = head;
        while(p->val <= newp->val && p->next != NULL){
            p_pre = p;
            p = p->next;
        }
        if(p->next == NULL){
            if(p->val > newp->val){
                newp->next = p;
                p_pre->next = newp;
            }
            else{
                p->next = newp;
                newp->next = NULL;
            }
        }
        else{
            p_pre->next = newp;
            newp->next = p;
        }
    }
    return head;
}

struct Listnode* delete(struct Listnode* head,int delval){
    if(head->val == delval){
        head = head->next;
    }
    else{
        struct Listnode* p = head->next;
        struct Listnode* p_pre = head;
        while(p->val != delval){
            p_pre = p;
            p = p->next;
        }
        p_pre->next = p->next;     
    }
    return head;
}

int Kth_mintime(struct Listnode* head,int k){
    int i;
    struct Listnode* p = head;
    for(i = 1; i < k; i++){
        p = p->next;
    }
    return p->val;
}

int main(){
    int n,i;
    scanf("%d",&n);
    char op;
    int time;
    struct Listnode* head = NULL;
    for(i = 0; i < n; i++){
        getchar();
        scanf("%c%d",&op,&time);
        switch (op)
        {
        case 'I':
            head = insert(head,time);
            break;
        case 'D':
            head = delete(head,time);
            break;
        case 'K':
            printf("%d\n",Kth_mintime(head,time));
            break;
        default:
            break;
        }
    }
    return 0;
}