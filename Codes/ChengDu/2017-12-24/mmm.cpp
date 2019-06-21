#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}

priority_queue<long long, vector<long long>, greater<long long> > Q;

int main()
{
	freopen("mmm.in", "r", stdin);
	freopen("mmm.out", "w", stdout);
	int n = read();
	for (int i = 1; i <= n; i++)
		Q.push(read());
	long long ans = 0;
	while (Q.size() != 1)
	{
		long long t1 = Q.top(); Q.pop();
		long long t2 = Q.top(); Q.pop();
		Q.push(t1 + t2);
		ans += t1 + t2;
	}
	printf("%lld\n", ans);
}