#include<stdio.h>
#include<stdlib.h>
int main(){
    int n,k;
    scanf("%d%d",&n,&k);
    int *nums = (int*)malloc(sizeof(int)*n);
    int i,j;
    for(i = 0; i < n; i++){
        scanf("%d",&nums[i]);
    }

    int *left = (int*)malloc(sizeof(int)*n);
    int *right = (int*)malloc(sizeof(int)*n);
    for(i = 0; i < n; i++){
        //last item of a k length block
        j = (i - (i%k)) + k - 1 - i%k;

        //initialize left[] and right[]
        if(i % k == 0){
            left[i] = nums[i];
            if(j < n)
                right[j] = nums[j];
        }
        else{
            left[i] = (nums[i] > left[i-1]) ? nums[i] : left[i-1];
            if(j < n-1)
                right[j] = (nums[j] > right[j+1]) ? nums[j] : right[j+1];
        }
    }

    int *ans = (int*)malloc(sizeof(int)*(n - k + 1));
    for(i = 0; i < n-k+1; i++){
        ans[i] = (left[i+k-1] > right[i]) ? left[i+k-1] : right[i];
        printf("%d ",ans[i]);
    }
    return 0;
}