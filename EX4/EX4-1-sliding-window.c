#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 10000001
void quicksort(int left, int right, int *nums);

int main(){
    int N,R;
    scanf("%d%d",&N,&R);
    int *countries = (int*)malloc((N+1)*sizeof(int));
    int i;
    for(i = 0; i < N; i++){
        scanf("%d",&countries[i]);
    }
    countries[N] = MAX;
    quicksort(0,N,countries);
    // printf("\n");
    // for(i = 0; i < N+1; i++){
    //     printf("%d ",countries[i]);
    //     if(i%5 == 0)
    //     printf("\n");
    // }    
    int nums = 0;
    int left = 0;
    int right = 0;
    int station = 0;
    while(1){
        if(right == N)break;
        if(left == right && countries[right+1] - countries[left] > R){
            station = countries[right];
            left++;
            right++;
            nums++;
            continue;
        }
        right++;
        int dist = countries[right] - countries[left];
        if(dist <= R && dist > 0){
            station = countries[right];
            continue;
        }
        else {
            if(countries[right]-station>R){
                left = right;
                nums++;
                continue;
            }
            // else{
            //     left++;
            //     isset = 1;
            //     nums++;
            // }
        }
    }
    printf("%d",nums);
    return 0;
}

void quicksort(int left, int right, int *nums){
    if(left >= right)return;
    int i,j,temp;
    i = left - 1;
    for(j = left; j < right; j++){
        if(nums[j] < nums[right]){
            i++;
            temp = nums[i];
            nums[i] = nums[j];
            nums[j] = temp;
        }
    }
    temp = nums[right];
    nums[right] = nums[i+1];
    nums[i+1] = temp;
    quicksort(left,i,nums);
    quicksort(i+2,right,nums);
}
