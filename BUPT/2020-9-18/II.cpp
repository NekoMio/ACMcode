#include <bits/stdc++.h>
using namespace std;
void cal_next(){
	nxt[1]=0;
	for(int i=2,j=0;i<=n;i++){
		while(j>0 && s[i]!=s[j+1]) j=nxt[j];
		if(s[i]==s[j+1]) j++;
		nxt[i]=j;
	}
}
int main() {
  int a,b
}