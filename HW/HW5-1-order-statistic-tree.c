#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct RBnode{
    int id;
    int val;
    char color;//'b' means black,while 'r' means red.
    int size;//number of nodes in this node's subtrees and itself.
    struct RBnode* p;
    struct RBnode* left;
    struct RBnode* right;
};

struct RBtree{
    struct RBnode* root;
    struct RBnode* nil;
};

struct RBtree *create_RBtree(){
    struct RBtree *tree = (struct RBtree*)malloc(sizeof(struct RBtree));
    struct RBnode *root = (struct RBnode*)malloc(sizeof(struct RBnode));
    struct RBnode *nil = (struct RBnode*)malloc(sizeof(struct RBnode));
    root->id = -1;
    root->val = -1;
    root->color = 'b';
    root->size = 1;
    root->p = nil;
    root->left = nil;
    root->right = nil;
    
    nil->id = -1;
    nil->val = -1;
    nil->color = 'b';
    nil->size = 0;
    nil->p = NULL;
    nil->left = root;
    nil->right = root;

    tree->root = root;
    tree->nil = nil;
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
    y->size = x->size;
    x->size = x->left->size + x->right->size + 1;
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
    x->size = y->size;
    y->size = y->left->size + y->right->size + 1;
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
        ++(x->size);
        y = x;
        if(z->val <= x->val)
            x = x->left;
        else x = x->right;
    }
    z->p = y;
    if(y->id == -1)
        t->root = z;
    else if(z->val <= y->val)
        y->left = z;
    else y->right = z;
    z->left = t->nil;
    z->right = t->nil;
    z->color = 'r';
    RB_insert_fixup(t,z);
}

struct RBnode* locate_before_delete(struct RBtree* t,int target){
    struct RBnode *x = t->root;
    while(x->id != -1){
        --(x->size);
        if(x->val == target)
            break;
        else if(x->val > target)
            x = x->left;
        else x = x->right;
    }
    return x;
}

struct RBnode* Tree_minimum(struct RBtree* t,struct RBnode* x){
    while(x->left->id != t->nil->id){
        --(x->size);
        x = x->left;
        
    } 
    return x;
}
/*
struct RBnode* Tree_maximum(struct RBtree* t,struct RBnode* x){
    while(x->right->id != t->nil->id){
        x = x->right;
    }
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
*/
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
        y->size = z->size;
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
//DEBUG UNIT
/*
void print_intertaverse(struct RBnode* x){
    if(x->id == -1){
        return;
    }
    print_intertaverse(x->left);
    printf("%d ",x->val);
    print_intertaverse(x->right);
    return;
}

void print_root(struct RBtree* t){
    printf("\nthe root is %d\n",t->root->val);
    printf("the size of the tree is %d\n",t->root->size);
    return;
}
*/
//_________________________________________________________________________________________
//_________________________________________________________________________________________
//_________________________________________________________________________________________
//_________________________________________________________________________________________

struct RBnode* OS_select(struct RBnode *x, int i){
    int rank = x->left->size + 1;
    if(i == rank)
        return x;
    else if(i < rank)
        return OS_select(x->left,i);
    else
        return OS_select(x->right,i-rank);
}

int OS_rank(struct RBtree* t,struct RBnode* x){
    int rank = x->left->size + 1;
    struct RBnode* y = x;
    while(y->id != t->root->id){
        if(y->id == y->p->right->id){
            rank = rank + y->p->left->size + 1;
        }
        y = y->p;
    }
    return rank;
}
//_________________________________________________________________________________________
//_________________________________________________________________________________________
//_________________________________________________________________________________________
//_________________________________________________________________________________________

int find_val_in_RB(struct RBtree* t, int target){
    struct RBnode *y = OS_select(t->root,target);
    return y->val;
}

int main(){
    char *token = (char*)malloc(sizeof(char));
    memset(token,'\0',sizeof(char));
    char insert[] = "I";
    char delete[] = "D";
    char find[] = "K";
    char exit[] = "E";
    struct RBtree *t = create_RBtree();
    int nums = 0;
    int ops;
    scanf("%d",&ops);
    while(1){
        int input;
        scanf("%s%d",token,&input);
        if(strcmp(token,insert)==0){
            struct RBnode *z = (struct RBnode*)malloc(sizeof(struct RBnode));
            z->id = (++nums);
            z->size = 1;
            z->val = input;
            RB_insert(t,z);
            //print_root(t);
            //print_intertaverse(t->root);
            //printf("\n\n");
		}
        else if(strcmp(token,delete)==0){
            struct RBnode *z = (struct RBnode*)malloc(sizeof(struct RBnode));
            z->val = input;
            z = locate_before_delete(t,z->val);
            RB_delete(t,z);
            //print_root(t);
            //print_intertaverse(t->root);
            //printf("\n\n");
        }
		else if(strcmp(token,find)==0){
            int ans = find_val_in_RB(t,input);
            printf("%d\n",ans);
		}
        if(strcmp(token,exit)==0)break;
        --ops;
        if(ops == 0)break;
    }
    return 0;
}