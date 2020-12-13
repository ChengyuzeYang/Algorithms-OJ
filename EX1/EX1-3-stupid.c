#include<stdio.h>
void quicksort(int left, int right, int *nums);
//int max_of_4_int(int a1,int a2,int a3,int a4);

int main(){
    int n;
    int maxDiameter = 1;
    scanf("%d",&n);
    int *nums = (int*)malloc(sizeof(int) * n);
    int i;
    for(i = 0; i < n; i++){
        scanf("%d",&nums[i]);
    }
    quicksort(0,n-1,nums);
    for(i = 0; i < n-1; i++){
        maxDiameter = ((nums[i+1]-nums[i]) > maxDiameter) ? (nums[i+1]-nums[i]): maxDiameter;
    }
    printf("%d\n",maxDiameter);
    return 0;
}

void quicksort(int left, int right, int *nums){
    if(left >= right)return;
    int i,j;
    int temp;
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
    return;
}
/*
int max_of_4_int(int a1,int a2,int a3,int a4){
    if(a1>=a2 && a1>=a3 && a1>=a4)return a1;
    if(a2>=a1 && a2>=a3 && a2>=a4)return a2;
    if(a3>=a2 && a3>=a1 && a3>=a4)return a3;
    if(a4>=a2 && a4>=a3 && a4>=a1)return a4;
}
*/