#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100000
#define max(a,b) (a>b)?a:b;
int dp[MAX];
int main(){
    int n,W;
    scanf("%d%d",&n,&W);

    int* w = (int*)malloc(n*sizeof(int));
    int* v = (int*)malloc(n*sizeof(int));
    int* num = (int*)malloc(n*sizeof(int));
    int i,j;
    int sum = 0;
    for(i = 0; i < n; i++){
        scanf("%d%d%d",&w[i],&v[i],&num[i]);
        sum += num[i];
    }
    int* weight = (int*)malloc(sum*sizeof(int));
    int* value = (int*)malloc(sum*sizeof(int));
    int pos = 0;
    for(i = 0; i < n; i++){
        for(j = 0; j < num[i]; j++){
            weight[pos] = w[i];
            value[pos] = v[i];
            pos++;
        }
    }
    memset(dp,0,sizeof(dp));
    for(i = 0; i < sum; i++)
    {
        for(j = W; j >= weight[i]; j--)
        {
            dp[j] = max(dp[j],dp[j-weight[i]]+value[i]);
        }
    }
    printf("%d",dp[W]);
    return 0;
}
