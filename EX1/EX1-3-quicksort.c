#include<stdio.h>
int quicksort(int left, int right, int *nums);
int max_of_4_int(int a1,int a2,int a3,int a4);

int main(){
    int n;
    int minDiameter = 1;
    scanf("%d",&n);
    int *nums = (int*)malloc(sizeof(int) * n);
    int i;
    for(i = 0; i < n; i++){
        scanf("%d",&nums[i]);
    }
    minDiameter = quicksort(0,n-1,nums);
    printf("%d\n",minDiameter);
    return 0;
}

int quicksort(int left, int right, int *nums){
    if(left >= right)return 1;
    int i,j;
    int temp;
    int max_of_min = nums[right-1];
    int min_of_max = nums[right-1];
    i = left - 1;
    for(j = left; j < right; j++){
        if(nums[j] < nums[right]){
            i++;
            temp = nums[i];
            nums[i] = nums[j];
            nums[j] = temp;
            max_of_min = (max_of_min > nums[j]) ? max_of_min : nums[j];
        }
        else
        {
            min_of_max = (min_of_max < nums[j]) ? min_of_max : nums[j];
        }
    }
    temp = nums[right];
    nums[right] = nums[i+1];
    nums[i+1] = temp;
    return max_of_4_int(temp-max_of_min,min_of_max-temp,quicksort(left,i,nums),quicksort(i+2,right,nums));
}

int max_of_4_int(int a1,int a2,int a3,int a4){
    if(a1>=a2 && a1>=a3 && a1>=a4)return a1;
    if(a2>=a1 && a2>=a3 && a2>=a4)return a2;
    if(a3>=a2 && a3>=a1 && a3>=a4)return a3;
    if(a4>=a2 && a4>=a3 && a4>=a1)return a4;
}
