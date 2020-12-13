#include<stdio.h>
#include<string.h>
#define max(a,b) (a > b) ? a : b;
#define N 10001

int dp[N][N];

int main(){
    int n;
    scanf("%d",&n);
    memset(dp,0,N*N*sizeof(int));
    int i,j;
    for(i = 0; i < n; i++){
        int x,y;
        scanf("%d%d",&x,&y);
        dp[x+1][y+1] = 1;
    }
    // for(i = 1; i < N; i++){
    //     for(j = 1; j < N; j++){
    //         printf("%d ",dp[i][j]);
    //     }
    //     printf("\n");
    // }
    // printf("\n");
    for(i = 1; i < N; i++){
        for(j = 1; j < N; j++){
            dp[i][j] += max(dp[i-1][j],dp[i][j-1]);
        }
    }
    printf("%d",dp[N-1][N-1]);
    return 0;
}