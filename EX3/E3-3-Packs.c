#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 100000
#define max(a,b) (a>b)?a:b;
int dp[MAX];

void ZeroOnePack(int weight,int value,int W)
{
    int i;
    for(i = W; i>=weight; i--)
    {
        dp[i] = max(dp[i],dp[i-weight]+value);
    }
}
void CompletePack(int weight,int value,int W)
{
    int i;
    for(i = weight; i<=W; i++)
    {
        dp[i] = max(dp[i],dp[i-weight]+value);
    }
}
void MultiplePack(int weight,int value,int number,int W)
{
    if(W <= number * weight)
    {
        CompletePack(weight,value,W);
        return;
    }
    else
    {
        int i;
        for(i = 0; i < number; i++){
            ZeroOnePack(weight,value,W);
        }
        return;
    }
}

int main(){
    int n,W;
    scanf("%d%d",&n,&W);
    int* w = (int*)malloc(n*sizeof(int));
    int* v = (int*)malloc(n*sizeof(int));
    int* num = (int*)malloc(n*sizeof(int));
    int i;
    for(i = 0; i < n; i++){
        scanf("%d%d%d",&w[i],&v[i],&num[i]);
    }
    memset(dp,0,sizeof(dp));
    for(i = 0; i<n; i++)
    {
        MultiplePack(w[i],v[i],num[i],W);
    }
    printf("%d",dp[W]);
    return 0;
}
