#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<map>
#include<algorithm>
#include<ctime>
#define N 100005
#define lowbit(i) (i&(-i))
using namespace std;
int main()
{
	srand(time(0));
	// freopen("test.in","w",stdout);
	int T=6;
	cout<<T<<endl;
	while(T--)
	{
		int n=50000;
		cout<<n<<endl;
		for(int i=1;i<=n;i++)
		{
			cout<<rand()*rand()%10+400<<' '<<rand()*rand()%400<<' '<<rand()*rand()%10+500<<' '<<rand()*rand()%10+500<<endl;
		}
		for(int i=1;i<n;i++)
		{
			cout<<rand()*rand()%10000<<' '<<rand()*rand()%1000<<' '<<rand()*rand()%1000<<endl;
		}
	}
	return 0;
}
