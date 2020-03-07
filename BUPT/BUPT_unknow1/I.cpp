#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		unsigned long long a,b,c,d;
		cin>>a>>b>>c>>d;
		if(a!=0&&a+b+c+d==0)
		{
			printf("18446744073709551616\n");
		}
		else cout<<a+b+c+d<<endl;
	}
	return 0;
}
/*
*/