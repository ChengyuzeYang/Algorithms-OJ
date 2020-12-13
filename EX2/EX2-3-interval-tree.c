#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct RBnode{
    int id;
    int val;
    char color;//'b' means black,while 'r' means red.
    struct RBnode* p;
    struct RBnode* left;
    struct RBnode* right;
    struct interval* inter; //interval tree
    int isOverlapped;
};

struct RBtree{
    struct RBnode* root;
    struct RBnode* nil;
};

//definition of interval
struct interval{
    int low;
    int high;
};

struct RBtree *create_RBtree(){
    struct RBtree *tree = (struct RBtree*)malloc(sizeof(struct RBtree));
    struct RBnode *root = (struct RBnode*)malloc(sizeof(struct RBnode));
    struct RBnode *nil = (struct RBnode*)malloc(sizeof(struct RBnode));
    root->id = -1;
    root->val = -1;
    root->color = 'b';
    root->p = nil;
    root->left = nil;
    root->right = nil;
    root->isOverlapped = 0;
    
    nil->id = -1;
    nil->val = -1;
    nil->color = 'b';
    nil->p = NULL;
    nil->left = root;
    nil->right = root;
    nil->isOverlapped = 0;

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
        if(z->val <= x->val){
            x = x->left;
            if(z->inter->high >= y->val)
                z->isOverlapped = -1;
        }
        else{
            x = x->right;
            if(z->inter->low <= y->inter->high)
                z->isOverlapped = -1;
        }
    }
    z->p = y;
    if(y->id == -1)
        t->root = z;
    else if(z->val <= y->val){
        y->left = z;
        if(z->val == y->val || z->inter->high >= y->val)
            z->isOverlapped = -1;
    }
    else{
        y->right = z;
        if(z->inter->low <= y->inter->high)
            z->isOverlapped = -1;
    }
    z->left = t->nil;
    z->right = t->nil;
    z->color = 'r';
    RB_insert_fixup(t,z);
}

//_________________________________________________________________________________________
//_________________________________________________________________________________________
//_________________________________________________________________________________________
//_________________________________________________________________________________________
struct RBnode* locate(struct RBtree* t,int target){
    struct RBnode *y = t->nil;
    struct RBnode *x = t->root;
    while(x->id != -1){
        y = x;
        if(x->val == target)
            break;
        else if(x->val > target)
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
    printf("%d ",x->val);
    print_intertaverse(x->right);
    return;
}

void print_root(struct RBtree* t){
    printf("the root is %d\n",t->root->val);
    return;
}
//_________________________________________________________________________________________
//_________________________________________________________________________________________
//_________________________________________________________________________________________
//_________________________________________________________________________________________

int find_val_in_RB(struct RBtree* t, int target){
    struct RBnode *y = t->nil;
    struct RBnode *x = t->root;
    while(x->id != -1){
        y = x;
        if(x->val == target)
            break;
        else if(x->val > target)
            x = x->left;
        else x = x->right;
    }
    if(x->id != t->nil->id)
        return x->val;
    else{
        struct RBnode *z = (struct RBnode*)malloc(sizeof(struct RBnode));
        z->id = 0;
        z->val = target;
        RB_insert(t,z);
        struct RBnode *temp = Max_of_less_nodes(t,z);
        int ans = temp->val;
        RB_delete(t,z);
        return ans;
    }
}

int main(){
    int i,n;
    scanf("%d",&n);
    struct RBtree *t = create_RBtree();
    int nums = 0;
    for(i = 0; i < n; i++){
        struct RBnode *z = (struct RBnode*)malloc(sizeof(struct RBnode));
        struct interval *in = (struct interval*)malloc(sizeof(struct interval));
        z->id = (++nums);
        scanf("%d%d",&(in->low),&(in->high));
        z->inter = in;
        z->val = in->low;
        z->isOverlapped = 0;
        RB_insert(t,z);
        //print_root(t);
        //print_intertaverse(t->root);
        printf("%d\n",z->isOverlapped);
        if(z->isOverlapped == -1){
            RB_delete(t,z);
            free(z);
        }
    }
    return 0;
}