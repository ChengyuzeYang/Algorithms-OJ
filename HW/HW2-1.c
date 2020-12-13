#include<stdio.h>
#define MAXN 1001
void counting(int n, int *nums, int *count, int *ns, int *times);
void quicksort(int left, int right, int *nums, int *times);

int main(){
    int n = 1;
    scanf("%d",&n);
    int *nums = (int*)malloc(sizeof(int) * n);
    int i;
    for(i = 0; i < n; i++){
        scanf("%d",&nums[i]);
    }
    int count = 0;
    int ns[MAXN];
    int times[MAXN];
    for(i = 0; i < MAXN; i++){
        ns[i] = -1;
        times[i] = 0;
    }
    counting(n,nums,&count,ns,times);
    int *ns_t = (int*)malloc(sizeof(int) * count);
    int *times_t = (int*)malloc(sizeof(int) * count);
    for(i = 0; i < count; i++){
        ns_t[i] = ns[i];
        times_t[i] = times[i];
    }
    quicksort(0,count-1,ns_t,times_t);
    for(i = 0; i < count; i++){
        printf("%d %d\n",ns_t[i],times_t[i]);
    }
    return 0;
}

void counting(int n, int *nums, int *count, int *ns, int *times){
    int i,j;    
    for(i = 0; i < n; i++){
        for(j = 0; j <= *count; j++){
            if(nums[i] == ns[j]){
                times[j]++;
                break;
            }
            else if(j == *count){
                ns[j] = nums[i];
                times[j]++;
                (*count)++;
                break;
            }
        }
        if(i == n-1){
            ns[*count] = '\0';
            times[*count] = '\0';
        }
    }
    return;
}

void quicksort(int left, int right, int *nums, int *times){
    if(left >= right)return;
    int i,j,temp,temp_t;
    i = left - 1;
    for(j = left; j < right; j++){
        if((times[j] > times[right]||(times[j] == times[right] && nums[j] < nums[right]))){
            i++;
            temp = nums[i];
            nums[i] = nums[j];
            nums[j] = temp;
            temp_t = times[i];
            times[i] = times[j];
            times[j] = temp_t;
        }
    }
    temp = nums[right];
    nums[right] = nums[i+1];
    nums[i+1] = temp;
    temp_t = times[right];
    times[right] = times[i+1];
    times[i+1] = temp_t;
    quicksort(left,i,nums,times);
    quicksort(i+2,right,nums,times);
}