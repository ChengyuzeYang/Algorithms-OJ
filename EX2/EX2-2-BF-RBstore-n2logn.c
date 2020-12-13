#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct RBnode{
    int id;
    char* val;
    char color;//'b' means black,while 'r' means red.
    struct RBnode* p;
    struct RBnode* left;
    struct RBnode* right;
};

struct RBtree{
    int nodes;
    struct RBnode* root;
    struct RBnode* nil;
};

struct RBtree *create_RBtree(){
    struct RBtree *tree = (struct RBtree*)malloc(sizeof(struct RBtree));
    struct RBnode *root = (struct RBnode*)malloc(sizeof(struct RBnode));
    struct RBnode *nil = (struct RBnode*)malloc(sizeof(struct RBnode));
    root->id = -1;
    root->val = NULL;
    root->color = 'b';
    root->p = nil;
    root->left = nil;
    root->right = nil;
    
    nil->id = -1;
    nil->val = NULL;
    nil->color = 'b';
    nil->p = NULL;
    nil->left = root;
    nil->right = root;

    tree->root = root;
    tree->nil = nil;
    tree->nodes = 0;
    return tree;
}

void left_rotate(struct RBtree* t,struct RBnode* x){
    struct RBnode *y = x->right;
    x->right = y->left;
    if(y->left->id != -1)
        y->left->p = x;
    y->p = x->p;
    if(x->p->id == -1)
        t->root = y;
    else if(x->id == x->p->left->id)
        x->p->left = y;
    else x->p->right = y;
    y->left = x;
    x->p = y;
    return;
}

void right_rotate(struct RBtree* t,struct RBnode* y){
    struct RBnode *x = y->left;
    y->left = x->right;
    if(x->right->id != -1)
        x->right->p = y;
    x->p = y->p;
    if(y->p->id == -1)
        t->root = x;
    else if(y->id == y->p->left->id)
        y->p->left = x;
    else y->p->right = x;
    x->right = y;
    y->p = x;
    return;
}

void RB_insert_fixup(struct RBtree* t,struct RBnode* z){
    while(z->p->color == 'r'){
        if(z->p->id == z->p->p->left->id){
            struct RBnode *y = z->p->p->right;
            if(y->color == 'r'){
                z->p->color = 'b';
                y->color = 'b';
                z->p->p->color = 'r';
                z = z->p->p;
            }
            else if(z->id == z->p->right->id){
                z = z->p;
                left_rotate(t,z);
            }
            else{
                z->p->color = 'b';
                z->p->p->color = 'r';
                right_rotate(t,z->p->p);
            }
        }
        else{
            struct RBnode *y = z->p->p->left;
            if(y->color == 'r'){
                z->p->color = 'b';
                y->color = 'b';
                z->p->p->color = 'r';
                z = z->p->p;
            }
            else if(z->id == z->p->left->id){
                z = z->p;
                right_rotate(t,z);
            }
            else{
                z->p->color = 'b';
                z->p->p->color = 'r';
                left_rotate(t,z->p->p);
            }
        }
    }
    t->root->color = 'b';
}

void RB_insert(struct RBtree* t,struct RBnode* z){
    struct RBnode *y = t->nil;
    struct RBnode *x = t->root;
    while(x->id != -1){
        y = x;
        if(strcmp(z->val,x->val) <= 0)
            x = x->left;
        else x = x->right;
    }
    z->p = y;
    if(y->id == -1)
        t->root = z;
    else if(strcmp(z->val,y->val) <= 0)
        y->left = z;
    else y->right = z;
    z->left = t->nil;
    z->right = t->nil;
    z->color = 'r';
    t->nodes++;
    RB_insert_fixup(t,z);
}

//_________________________________________________________________________________________
//_________________________________________________________________________________________
//_________________________________________________________________________________________
//_________________________________________________________________________________________
struct RBnode* locate(struct RBtree* t,char* target){
    struct RBnode *y = t->nil;
    struct RBnode *x = t->root;
    while(x->id != -1){
        y = x;
        if(strcmp(x->val,target) == 0)
            break;
        else if(strcmp(x->val,target) > 0)
            x = x->left;
        else x = x->right;
    }
    return x;
}

struct RBnode* Tree_minimum(struct RBtree* t,struct RBnode* x){
    while(x->left->id != t->nil->id)
        x = x->left;
    return x;
}

struct RBnode* Tree_maximum(struct RBtree* t,struct RBnode* x){
    while(x->right->id != t->nil->id)
        x = x->right;
    return x;
}

struct RBnode* Max_of_less_nodes(struct RBtree* t,struct RBnode* x){
    if(x->left->id != t->nil->id)
        return Tree_maximum(t,x->left);
    else{
        while(x->id == x->p->left->id && x->id != t->root->id)
            x = x->p;
        return x->p;
    }
}

void RB_transplant(struct RBtree* t,struct RBnode* u,struct RBnode* v){
    if(u->p->id == t->nil->id)
        t->root = v;
    else if(u->id == u->p->left->id)
        u->p->left = v;
    else u->p->right = v;
    v->p = u->p;
}

void RB_delete_fixup(struct RBtree* t,struct RBnode* x){
    while(x->p->id != t->nil->id && x->color == 'b'){
        if(x->id == x->p->left->id){
            struct RBnode* w = x->p->right;
            if(w->color == 'r'){
                w->color = 'b';
                x->p->color = 'r';
                left_rotate(t,x->p);
                w = x->p->right;
            }
            if(w->left->color == 'b' && w->right->color == 'b'){
                w->color = 'r';
                x = x->p;
            }
            else if(w->right->color == 'b'){
                w->left->color = 'b';
                w->color = 'r';
                right_rotate(t,w);
                w = x->p->right;
            }
            else{
                w->color = x->p->color;
                x->p->color = 'b';
                w->right->color = 'b';
                left_rotate(t,x->p);
                x = t->root;
            }
        }
        else{
            //todo
            struct RBnode* w = x->p->left;
            if(w->color == 'r'){
                w->color = 'b';
                x->p->color = 'r';
                right_rotate(t,x->p);
                w = x->p->left;
            }
            if(w->left->color == 'b' && w->right->color == 'b'){
                w->color = 'r';
                x = x->p;
            }
            else if(w->left->color == 'b'){
                w->right->color = 'b';
                w->color = 'r';
                left_rotate(t,w);
                w = x->p->left;
            }
            else{
                w->color = x->p->color;
                x->p->color = 'b';
                w->left->color = 'b';
                right_rotate(t,x->p);
                x = t->root;
            }
        }
    }
    x->color = 'b';
}

void RB_delete(struct RBtree* t,struct RBnode* z){
    struct RBnode* y = z;
    struct RBnode* x;
    char y_original_color = y->color;
    if(z->left->id == t->nil->id){
        x = z->right;
        RB_transplant(t,z,z->right);
    }
    else if(z->right->id == t->nil->id){
        x = z->left;
        RB_transplant(t,z,z->left);
    }
    else{
        y = Tree_minimum(t,z->right);
        y_original_color = y->color;
        x = y->right;
        if(y->p->id == z->id)
            x->p = y;
        else{
            RB_transplant(t,y,y->right);
            y->right = z->right;
            y->right->p = y;
        }
        RB_transplant(t,z,y);
        y->left = z->left;
        y->left->p = y;
        y->color = z->color;
    }
    if(y_original_color == 'b')
        RB_delete_fixup(t,x);
}

void print_intertaverse(struct RBnode* x){
    if(x->id == -1){
        return;
    }
    print_intertaverse(x->left);
    printf("%s ",x->val);
    print_intertaverse(x->right);
    return;
}

void print_root(struct RBtree* t){
    printf("the root is %s\n",t->root->val);
    return;
}
//_________________________________________________________________________________________
//_________________________________________________________________________________________
//_________________________________________________________________________________________
//_________________________________________________________________________________________

int find_val_in_RB(struct RBtree* t, char* target){
    struct RBnode *y = t->nil;
    struct RBnode *x = t->root;
    while(x->id != -1){
        y = x;
        if(strcmp(x->val,target) == 0)
            break;
        else if(strcmp(x->val,target) > 0)
            x = x->left;
        else x = x->right;
    }
    if(x->id != t->nil->id)
        return 1;
    else
        return 0;
}

//---------------------------------------------------------------
// int isInKlist(char* s, char** klist, int k){
//     int i;
//     for(i = 0; i < k; i++){
//         if(klist[i] == NULL)
//             break;
//         if(strcmp(s,klist[i]) == 0)
//             return 1;
//     }
//     return 0;
// }

// void Add2Klist(char* s, char** klist, int k, int* kfull){
//     int i;
//     for(i = 0; i < k; i++){
//         if(klist[i] == NULL){
//             klist[i] = s;
//             break;
//         }
//     }
//     if(i == k-1) *kfull = 1;
//     return;
// }
//---------------------------------------------------------------

int main(){
    int n,k;
    scanf("%d%d",&n,&k);
    int i,j,l;
    int queues = 0;
    char** namelist = (char**)malloc(n*sizeof(char*));
    for(i = 0; i < n; i++){
        char* name = (char*)malloc(5*sizeof(char));
        scanf("%s",name);
        namelist[i] = name;
    }

    int kfull = 0;
    for(i = 0; i < n-k+1; i++){
        struct RBtree *t = create_RBtree();
        int nums = 0;
        
        for(j = i; j < n; j++){
            int isListed = find_val_in_RB(t,namelist[j]);
            if(kfull == 1 && isListed == 0)
                break;
            else if(kfull == 1)
                queues++;
            else if(isListed == 0){
                struct RBnode *z = (struct RBnode*)malloc(sizeof(struct RBnode));
                z->id = (++nums);
                z->val = namelist[j];
                RB_insert(t,z);
                kfull = (t->nodes == k) ? 1 : 0;
                if(kfull) queues++;
            }
            else
                continue;
        }

        kfull = 0;
    }
    // for(i = 0; i < n; i++){
    //     printf("%s\n",namelist[i]);
    // }
    printf("%d",queues);
    return 0;
}