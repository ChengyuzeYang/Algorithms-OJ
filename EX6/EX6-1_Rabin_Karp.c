#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define MAXSTR 1000000
#define MAXPAT 10000

int Rabin_Karp_matcher(char* string,char* pattern,int q){
	int n = strlen(string);
	int m = strlen(pattern);
	int p = 0;
	int sum = 0;
	int sum_mod = 0;
	int cnt = 0;
	for(int i = 0; i < m; i++){
		p += (pattern[i] - 'a');
		sum += (string[i] - 'a');
	}
	p = p%q;
	sum_mod = sum%q;
	for(int i = 0; i < n-m; i++){
		if(p == sum_mod){
			if(strncmp(pattern,&string[i],m) == 0)
				cnt++;
		}
		sum = sum - string[i] + string[i+m];
		sum_mod = sum%q;
	}
	if(p == sum_mod){
		if(strncmp(pattern,&string[n-m],m) == 0)
			cnt++;
	}
	return cnt;
}

int main(){
	int t;
	scanf("%d",&t);
	int i;
	for(i = 0; i < t; i++){
		char* s = (char*)malloc(MAXSTR*sizeof(char));
		char* p = (char*)malloc(MAXPAT*sizeof(char));
		scanf("%s%s",p,s);
		int ans = Rabin_Karp_matcher(s,p,26);
		free(s);
		free(p);
		printf("%d\n",ans);
	}
	return 0;
}