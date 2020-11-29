#include<stdio.h>
int main(){
	int n,a,i,m;
	scanf("%d",&n);
	for(a=1;a<=n/2;a++){
	for(i=2;i<a&&a%i!=0;i++){
	for(m=2;m<n-a&&(n-a)%m!=0;m++){
	}}
	if(i==a&&m==n-a){printf("%d and %d\n",a,n-a);}
	}
	return 0;
}
