#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
#define N 100005
using namespace std;
pair<int, int> a[N];
int n,m;
int main()
{
	freopen("test.in","w",stdout);
	srand(time(0));
	int n=100000,m=100000;
	cout<<n<<' '<<m<<endl;
	for(int i=1;i<=n;i++)
	{
		// cout<<rand()*rand()%1000000000<<' ';
		a[i].first = rand(), a[i].second = i;
	}
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i++)
		printf ("%d ", a[i].second);
	printf("\n");
	for (int i = 1; i <= n; i++) {
		int l = rand() % n + 1, r = rand() % n + 1;
		if (l > r) swap(l, r);
		printf ("%d %d\n", l, r);
	}
	return 0;
} 
