#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#define MAXSTR 1000000
#define MAXPAT 10000

int* compute_prefix(char* pattern){
	int len = strlen(pattern);
	int* pi = (int*)malloc(len*sizeof(int));
	pi[0] = 0;
	int k = 0;
	for(int q = 1; q < len; q++){
		while(k > 0 && pattern[k] != pattern[q])
			k = pi[k];
		if(pattern[k] == pattern[q])
			k++;
		pi[q] = k;
	}
	// for(int q = 0; q < len; q++){
	// 	printf("%c %d\n",pattern[q],pi[q]);
	// }
	return pi;
}

int KMP_matcher(char* string,char* pattern){
	int n = strlen(string);
	int m = strlen(pattern);
	int* pi = compute_prefix(pattern);
	int q = 0;
	int cnt = 0;
	for(int i = 0; i < n; i++){
		while(q > 0 && pattern[q] != string[i])
			q = pi[q-1];
		if(pattern[q] == string[i])
			q++;
		if(q == m){
			cnt++;
			q = pi[q-1];
		}
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
		int ans = KMP_matcher(s,p);
		free(s);
		free(p);
		printf("%d\n",ans);
	}
	return 0;
}