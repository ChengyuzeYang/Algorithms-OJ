#include<stdio.h>
#include<string.h>
#define NODATA -1
struct Data{
    int id;
    int val;
    struct Data *next;
};

int main(){
    char *token = (char*)malloc(6*sizeof(char));
    memset(token,'\0',6*sizeof(char));
    struct Data *head = (struct Data *)malloc(sizeof(struct Data));
	struct Data *tail = (struct Data *)malloc(sizeof(struct Data));
    head->id = -1;
    head->val = -1;
    head->next = NULL;
    tail = head;
    char insert[] = "INSERT";
    char find[] = "FIND";
    char exit[] = "EXIT";
    while(1){
        scanf("%s",token);
        if(strcmp(token,insert)==0){
            struct Data *p = (struct Data *)malloc(sizeof(struct Data));;
            scanf("%d%d",&(p->id),&(p->val));
            p->next = NULL;
            tail->next = p;
            tail = tail->next;
		}
		else if(strcmp(token,find)==0){
			int target;
            scanf("%d",&target);
            struct Data *p = (struct Data *)malloc(sizeof(struct Data));;
            for(p = head->next; p->next != NULL; p = p->next){
                if(p->val == target){
                    printf("%d\n",p->id);
                    break;
                }
            }
            if(p->next == NULL){
                printf("%d\n",NODATA);
            }
		}
        if(strcmp(token,exit)==0)break;
    }
    return 0;
}
