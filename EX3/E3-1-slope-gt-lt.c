#include<stdio.h>
#include<stdlib.h>
#define INF 2147483647
#define max(a,b) (a > b) ? a : b;
#define min(a,b) (a < b) ? a : b;

struct point{
    int x;
    int y;
    int slope;
    int gt;
    int lt;
};

void quicksort(int left, int right, struct point* p);

void printp(int n, struct point* p){
    int i;
    for(i = 0; i < n; i++){
        printf("%d\t%d\t%d\t%d\t%d\n",p[i].x,p[i].y,p[i].slope,p[i].gt,p[i].lt);
    }
    printf("\n");
    return;
}

int main(){
    int n;
    scanf("%d",&n);
    struct point* p = (struct point*)malloc(n*sizeof(struct point));
    int i,j;
    for(i = 0; i < n; i++){
        scanf("%d%d",&(p[i].x),&(p[i].y));
        p[i].slope = p[i].x + p[i].y;
        p[i].gt = 1;
        p[i].lt = 1;
    }
    //printp(n,p);
    quicksort(0,n-1,p);
    //printp(n,p);
    for(i = 1; i < n; i++){
        int max = 0;
        for(j = i-1; j >= 0; j--){
            if(p[i].slope <= p[j].slope)continue;
            else if(p[j].x <= p[i].x && p[j].y <= p[i].y){
                max = max(max,p[j].lt); 
            }
            else continue;
        }
        p[i].lt += max;
        max = 0;
        for(j = n-i; j < n; j++){
            if(p[n-i-1].slope == p[j].slope)continue;
            else if(p[j].x >= p[n-i-1].x && p[j].y >= p[n-i-1].y){
                max = max(max,p[j].gt);
            }
            else continue;
        }
        p[n-i-1].gt += max;
    }
    int max = 0;
    for(i = 0; i < n; i++){
        max = max(max,p[i].gt+p[i].lt-1);
    }
    //printp(n,p);
    printf("%d",max);
    return 0;
}

void quicksort(int left, int right, struct point* p){
    if(left >= right)return;
    int i,j,temp,temp_t,temp_y;
    i = left - 1;
    for(j = left; j < right; j++){
        if((p[j].slope < p[right].slope || (p[j].slope == p[right].slope && p[j].x < p[right].x))){
            i++;
            temp = p[i].x;
            p[i].x = p[j].x;
            p[j].x = temp;
            temp_y = p[i].y;
            p[i].y = p[j].y;
            p[j].y = temp_y;
            temp_t = p[i].slope;
            p[i].slope = p[j].slope;
            p[j].slope = temp_t;
        }
    }
    temp = p[right].x;
    p[right].x = p[i+1].x;
    p[i+1].x = temp;
    temp_y = p[right].y;
    p[right].y = p[i+1].y;
    p[i+1].y = temp_y;
    temp_t = p[right].slope;
    p[right].slope = p[i+1].slope;
    p[i+1].slope = temp_t;
    quicksort(left,i,p);
    quicksort(i+2,right,p);
}