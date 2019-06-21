#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm> 
using namespace std;
int f[15][15],base[15];
/******************
初始化 加快转移速度
当然如果不初始化
也没法转移
******************/
void Init(){
	base[1]=1;
	for(int i=2;i<=10;i++)base[i]=base[i-1]*10;
	for(int i=0;i<=9;i++)f[1][i]=1;
	for(int i=2;i<=10;i++){
		for(int j=0;j<=9;j++){
			for(int k=0;k<=9;k++){
				if(abs(j-k)>=2)f[i][j]+=f[i-1][k];
			}
		}
	}
}
/*****************************
计算0~n 的windy数
*****************************/
int clac(int n){
	if(n==0)return 0;
	int ans=0,w=10;
	while(base[w]>n)w--;///计算n的位数
	///比n位数少的
	for(int i=1;i<w;i++){
		for(int j=1;j<=9;j++){
			ans+=f[i][j];
		}
	}
	int cur=n/base[w];
	for(int i=1;i<cur;i++)ans+=f[w][i];///位数相同但第一位小于n的
	n%=base[w];///去掉一位
	int pre=cur;
	for(int i=w-1;i;i--){///一位一位每一位都计算比n小的
		cur=n/base[i];
		if(i!=1){///要注意可以有前导0
			for(int j=0;j<cur;j++) if(abs(pre-j)>=2)ans+=f[i][j];
		}else{
			for(int j=0;j<=cur;j++) if(abs(pre-j)>=2)ans+=f[i][j];
		}
		if(abs(cur-pre)<2)break;
		pre=cur;
		n%=base[i];
	}
	return ans;
}
int main()
{
    freopen("bzoj1026.in", "r", stdin);
    freopen("bzoj1026.out", "w", stdout);
	Init();
	int A,B;
	scanf("%d%d",&A,&B);
	printf("%d\n",clac(B)-clac(A-1));
	return 0;
}