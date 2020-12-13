#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 10000005

int Hash[N];
int num[N];
//int res;
int ELFhash(char *str)//思想就是一直杂糅，使字符之间互相影响
{
    int h = 0, g;
    while(*str)
    {
        h = (h<<4) + *str++; //h左移4位，当前字符占8位，加到h中进行杂糅
        if((g = h & 0xf0000000) != 0) //取h最左四位的值，若均为0，则括号中执行与否没区别，故不执行
        {
            h ^= g>>24; //用h的最左四位的值对h的右起5~8进行杂糅
            h &= ~g;//清空h的最左四位
        }
    }
    return h; //因为每次都清空了最左四位，最后结果最多也就是28位二进制整数，不会超int
}

void add2hash_table(int t,int k)
{
    
    //while(Hash[t] != k && Hash[t] != -1) t = (t + 1) % N;//开放地址法处理hash
    if(Hash[t] == -1){
        //num[t] = 1;
        Hash[t] = k;
    }
    //else res = max(res, ++num[t]);
}

void add2k(int t, int k,int* nums)
{
    //while(Hash[t] != k && Hash[t] != -1) t = (t + 1) % N;
    if(Hash[t] == k){
        num[t] = 1;
        (*nums)++;
    }
    //else res = max(res, ++num[t]);
}

int isInHashTable(int t){
    //while(Hash[t] != k && Hash[t] != -1) t = (t + 1) % N;
    if(num[t] == 1)return 1;
    else return 0;
}


int main(){
    int n,k;
    scanf("%d%d",&n,&k);
    int i,j,l;
    int queues = 0;
    memset(Hash, -1, N*sizeof(int));
    char** namelist = (char**)malloc(n*sizeof(char*));
    for(i = 0; i < n; i++){
        char* name = (char*)malloc(5*sizeof(char));
        scanf("%s",name);
        namelist[i] = name;
        int k = ELFhash(name);
        int t = k % N;
        add2hash_table(t,k);
    }

    
    //memset(num, 0, N*sizeof(int));

    int kfull = 0;
    for(i = 0; i < n-k+1; i++){
        int nums = 0;
        for(j = i; j < n; j++){
            int h = ELFhash(namelist[j]);
            int t = h % N;
            int isListed = isInHashTable(t);
            
            if(kfull == 1 && isListed == 0)
                break;
            else if(kfull == 1)
                queues++;
            else if(isListed == 0){
                //todo
                add2k(t,h,&nums);
                kfull = (nums == k) ? 1 : 0;
                if(kfull) queues++;
            }
            else
                continue;
        }

        kfull = 0;
        memset(num, 0, N*sizeof(int));
    }
    // for(i = 0; i < n; i++){
    //     printf("%s\n",namelist[i]);
    // }
    printf("%d",queues);
    return 0;
}