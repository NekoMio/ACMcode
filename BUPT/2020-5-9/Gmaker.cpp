#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<ctime>
#define N 105
using namespace std;
int main()
{
	srand(time(0));
	freopen("G.in","w",stdout);
	int T=2;
	cout<<T<<endl;
	while(T--)
	{
		int n=6,K=rand()%10+1;
		cout<<n<<' '<<K<<endl;
		for(int i=1;i<=n;i++)
		{
			cout<<rand()%5+1<<' ';
		}
		cout<<endl;
		for(int i=1;i<=n;i++)
		{
			cout<<rand()%5+1<<' ';
		}
		cout<<endl; 
	}
	return 0;
}
