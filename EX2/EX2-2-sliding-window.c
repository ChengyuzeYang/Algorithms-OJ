#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 10000000
#define add 26*26*26*26*26
int times[add];
int hash[N];
char names[N][5];

int main(){
    int n,k;
    scanf("%d%d",&n,&k);
    memset(hash,0,sizeof(int)*N);
    int i;
    for(i = 0; i < n; i++){
        scanf("%s",names[i]);
        hash[i] =  (((((names[i][0]-'a') 
                    + ((names[i][1]-'a') * 26))
                    + ((names[i][2]-'a') * 26 * 26))
                    + ((names[i][3]-'a') * 26 * 26 * 26))
                    + ((names[i][4]-'a') * 26 * 26 * 26 * 26));
    }

    int klist = 0;
    int ans = 0;
    int left = -1;
    int right = 0;

    i = 0;
    while(i < n){
        times[hash[i]]++;
        if(times[hash[i]] == 1)
            klist++;
        if(klist < k){ //sliding window is not full
            i++;
            continue;
        }
        else if(klist > k){ //the first value in sliding window is not equivalent to the next value
            times[hash[right]]--;//pop the first value
            klist = k;//slide
            left = right;//set a flag
            right++;//"right" redirect to head of sliding window
        }
        while(1){
            if(times[hash[right]] == 1) // has found new head
                break;
            else{
                times[hash[right]]--; //avoid "y y y y", look for new head
                right++;
            }
        }
        ans += right - left;
        i++;
    }
    printf("%d",ans);
    return 0;
}