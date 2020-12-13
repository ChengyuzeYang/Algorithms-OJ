#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int isInKlist(char* s, char** klist, int k){
    int i;
    for(i = 0; i < k; i++){
        if(klist[i] == NULL)
            break;
        if(strcmp(s,klist[i]) == 0)
            return 1;
    }
    return 0;
}

void Add2Klist(char* s, char** klist, int k, int* kfull){
    int i;
    for(i = 0; i < k; i++){
        if(klist[i] == NULL){
            klist[i] = s;
            break;
        }
    }
    if(i == k-1) *kfull = 1;
    //---------------------------------------------------------------
    // for(i = 0; i < k; i++){
    //     if(klist[i] != NULL)
    //     printf("%s\n",klist[i]);
    // }
    // printf("\n\n");
    //---------------------------------------------------------------
    return;
}

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
        char** klist = (char**)malloc(k*sizeof(char*));
        for(j = 0; j < k; j++){
            char* kname = (char*)malloc(5*sizeof(char));
            kname = NULL;
            klist[j] = kname;
        }
        
        for(j = i; j < n; j++){
            int isListed = isInKlist(namelist[j],klist,k);
            if(kfull == 1 && isListed == 0)
                break;
            else if(kfull == 1)
                queues++;
            else if(isListed == 0){
                Add2Klist(namelist[j],klist,k,&kfull);
                if(kfull) queues++;
            }
            else
                continue;
        }

        kfull = 0;
        for(j = 0; j < k; j++){
            klist[j] = NULL;
        }
    }
    // for(i = 0; i < n; i++){
    //     printf("%s\n",namelist[i]);
    // }
    printf("%d",queues);
    return 0;
}