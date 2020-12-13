#include<stdio.h>
int main(){
    int n,i;
    scanf("%d",&n);
    int *students = (int*)malloc(sizeof(int) * n);
    int *math = (int*)malloc(sizeof(int) * n);
    int *english = (int*)malloc(sizeof(int) * n);
    for(i = 0; i < n; i++){
        scanf("%d %d %d",&students[i],&math[i],&english[i]);
    }
    int *total = (int*)malloc(sizeof(int) * n);
    for(i = 0; i < n; i++){
        total[i] = math[i] + english[i];
    }
    quicksort(0,n-1,total,students,math,english);
    for(i = 0; i < n; i++){
        printf("%d ",students[i]);
    }
    return 0;
}

void quicksort(int left, int right, int *total, int *students, int *math, int *english){
    if(left >= right)return;
    int i,j,temp_s,temp_t,temp_m,temp_e;
    i = left - 1;
    for(j = left; j < right; j++){
        if(total[j] > total[right]||(total[j] == total[right] && math[j] > math[right])||(total[j] == total[right] && math[j] == math[right] && students[j] >= students[right])){
            i++;
            temp_t = total[i];
            total[i] = total[j];
            total[j] = temp_t;

            temp_s = students[i];
            students[i] = students[j];
            students[j] = temp_s;

            temp_m = math[i];
            math[i] = math[j];
            math[j] = temp_m;

            temp_e = english[i];
            english[i] = english[j];
            english[j] = temp_e;
        }
    }
    temp_t = total[right];
    total[right] = total[i+1];
    total[i+1] = temp_t;

    temp_s = students[right];
    students[right] = students[i+1];
    students[i+1] = temp_s;
    
    temp_m = math[right];
    math[right] = math[i+1];
    math[i+1] = temp_m;

    temp_e = english[right];
    english[right] = english[i+1];
    english[i+1] = temp_e;
    quicksort(left,i,total,students,math,english);
    quicksort(i+2,right,total,students,math,english);
}
