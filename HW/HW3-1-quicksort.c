#include<stdio.h>
int main(){
    int n = 1;
    int k = 1;
    scanf("%d%d",&n,&k);
    int *nums = (int*)malloc(sizeof(int) * n);
    int i;
    for(i = 0; i < n; i++){
        scanf("%d",&nums[i]);
    }
    quicksort(0,n-1,nums);
    printf("%d",nums[k-1]);
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
