/*
 * @Author: WildRage 
 * @Date: 2017-07-01 10:17:47 
 * @Last Modified by: WildRage
 * @Last Modified time: 2017-07-01 11:08:00
 */
#include<iostream>
#include<cstdio>
#include<cstring>
namespace MineWorkSpace{
	char s[10005][80];
	int next[10005][80];
	int next2[80][10005];
	int gcd(int a,int b){
		return b==0? a: gcd(b,a%b);
	}
	int lcm(int a,int b){
		return a/gcd(a,b)*b;
	}
	int Main()
	{
	#ifdef Mine
	    freopen("mgrid.in","r",stdin);
	    freopen("mgrid.out","w",stdout);
	#endif
		int n,m;
		scanf("%d%d",&n,&m);
		for(int i=0;i<n;i++){
			scanf("%s",s[i]);
		}
		int ans1=1,ans2=1;
		for(int i=0;i<n;i++){
			int j=0,k=-1;
			next[i][0]=-1;
			while(j<m){
				if(k==-1||s[i][j]==s[i][k]){
					next[i][++j]=++k;
				}
				else k=next[i][k];
			}
			if(m-next[i][m]) ans1=lcm(ans1,m-next[i][m]);
			if(ans1>m)ans1=m;
		}
		for(int i=0;i<m;i++){
			int j=0,k=-1;
			next2[i][0]=-1;
			while(j<n){
				if(k==-1||s[j][i]==s[k][i]){
					next2[i][++j]=++k;
				}
				else k=next2[i][k];
			}
			if(n-next2[i][n])ans2=lcm(ans2,n-next2[i][n]);
			if(ans2>n)ans2=n;
		}
		return printf("%d",ans1*ans2);
	}
}
int main()
{
	MineWorkSpace::Main();
	//while(1);
}
