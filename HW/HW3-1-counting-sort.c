#include<stdio.h>
#define MAXAI 10001
int main(){
    int n = 1;
    int k = 1;
    scanf("%d%d",&n,&k);
    int *nums = (int*)malloc(sizeof(int) * n);
    int i;
    for(i = 0; i < n; i++){
        scanf("%d",&nums[i]);
    }
    int *ans = (int*)malloc(n*sizeof(int));
    memset(ans,0,n*sizeof(int));
    countingsort(nums,n,ans,MAXAI);
    printf("%d",ans[k-1]);
    return 0;
}

void countingsort(int *input, int n, int *output, int k){
    int *count = (int*)malloc(k*sizeof(int));
    memset(count,0,k*sizeof(int));
    int i;
    for(i = 0; i < n; i++){
        count[input[i]]++;
    }
    for(i = 1; i < k; i++){
        count[i] += count[i-1];
    }
    for(i = n-1; i >= 0; i--){
        output[count[input[i]]-1] = input[i];
        count[input[i]]--;
    }
    free(count);
}
