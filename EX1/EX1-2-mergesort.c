#include <stdio.h>
#define SCALE 10000019

void merge(int left, int right, int mid, int *array, long *count){
    int *L = (int*)malloc(sizeof(int)*(mid-left+1));
    int *R = (int*)malloc(sizeof(int)*(right-mid));
    int i,j,k;
    for(i = 0; i < (mid-left+1); i++){
        L[i] = array[left + i];
    }
    for(j = 0; j < (right-mid); j++){
        R[j] = array[mid + j + 1];
    }
    i = 0;
    j = 0;
    for(k = left; k <= right; k++){
        if(i == mid-left+1){
            array[k] = R[j];
            j++;
            continue;
        }
        if(j == right-mid){
            for(k; k <= right; k++){
                array[k] = L[i];
                i++;
            }
            break;
        }
        if(L[i] > R[j]){
            array[k] = R[j];
            (*count) += mid-left+1 -i;
            j++;
        }else{
            array[k] = L[i];
            i++;
        }
    }
    free(L);
    free(R);
    return;
}

void mergesort(int* array, int left, int right, long *count){
    if(left >= right)return;
    else{
        int mid = ((left+right)%2) ? (left+right-1)/2 : (left+right)/2 ;
        mergesort(array,left,mid,count);
        mergesort(array,mid+1,right,count);
        merge(left,right,mid,array,count);
        return;
    }
}

int main(){
    int n;
    scanf("%d",&n);
    int i;
    int *stock = (int *)malloc(sizeof(int) * n);
    for(i = 0; i < n; i++){
        scanf("%d",&stock[i]);
    }
    long count = 0;
    mergesort(stock,0,n-1,&count);
    /*for(i = 0; i < n; i++){
        printf("%d ",stock[i]);
    }*/
    printf("%ld",count%SCALE);
    return 0;
}