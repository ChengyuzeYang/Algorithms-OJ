#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define INT 2147483647
#define min(a,b) (a > b) ? b : a

int main(){
    int n;
    scanf("%d",&n);
    int **dp = (int**)malloc(sizeof(int*)*n);
    int **single = (int**)malloc(sizeof(int*)*n);
    int i;
    for(i = 0; i < n; i++){
        dp[i] = (int*)malloc(sizeof(int)*n);
        single[i] = (int*)malloc(sizeof(int)*n);
    }
    int *nums = (int*)malloc(sizeof(int)*n);
    for(i = 0; i < n; i++){
        scanf("%d",&nums[i]);
    }
    int left,right;
    for(left = 0; left < n; left++){
        for(right = 0; right < n; right++){
            dp[left][right] = 0;
            single[left][right] = 0;
        }
    }

    for(left = n-1; left >= 0; left--){
        for(right = left; right < n; right++){
            if(left == right){
                dp[left][right] = nums[left];
                single[left][right] = nums[left];
            }    
            else if(left == right-1){
                dp[left][right] = nums[left] + nums[right];
                single[left][right] = nums[left] + nums[right];
            }
            else {
                int mini = INT;
                int mins = INT;
                int j;
                for(j = left+1; j <= right; j++){
                    mins = min(mins,single[left][j-1]+single[j][right]);
                    if(j == left+1)
                        mini = min(mini,dp[left][j-1]+dp[j][right]+single[j][right]);
                    else if(j == right)
                        mini = min(mini,dp[left][j-1]+dp[j][right]+single[left][j-1]);
                    else
                        mini = min(mini,dp[left][j-1]+dp[j][right]+single[left][j-1]+single[j][right]);
                }
                single[left][right] = mins;
                dp[left][right] = mini;
            }
        }
    }
    int j;
    // for(i = 0; i < n; i++){
    //     for(j = 0; j < n; j++){
    //         printf("%d\t",dp[i][j]);
    //     }
    //     printf("\n");
    // }
    // printf("\n");
    // for(i = 0; i < n; i++){
    //     for(j = 0; j < n; j++){
    //         printf("%d\t",single[i][j]);
    //     }
    //     printf("\n");
    // }
    printf("%d",dp[0][n-1]);
    return 0;
}