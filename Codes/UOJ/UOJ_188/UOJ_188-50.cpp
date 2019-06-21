#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline long long read()
{
	long long x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int MAXN = 1e6;
int prime[MAXN + 2], cnt;
bool isnprime[MAXN + 2];
void Get_Prime()
{
	isnprime[1] = 1;
	for (int i = 2; i <= MAXN; i++)
	{
		if (!isnprime[i]) prime[++cnt] = i;
		for (int j = 1; j <= cnt; j++)
		{
			if (i * prime[j] > MAXN) break;
			isnprime[i * prime[j]] = 1;
			if (i % prime[j] == 0)
				break;
		}
	}
}
const int Mx = 1e7 + 5;
int p[Mx], np[Mx];
long long now[Mx];
int main()
{
	// freopen ("1.out", "w", stdout);
	long long l = read(), r = read();
	Get_Prime();
	for (int i = 0; i <= r - l; i++) now[i] = 1ll + i + l - 1;
	for (int i = 1; i <= cnt; i++)
	{
	    // printf ("%d\n", prime[i]);
		// if (i <= 100) printf ("%d %lld\n", prime[i], (l / prime[i] + (l % prime[i] != 0)) * prime[i]);
		for (long long j = (l / prime[i] + (l % prime[i] != 0)) * prime[i]; j <= r; j += prime[i])
		{
			while (now[j - l] % prime[i] == 0)
			{
				np[j - l] = p[j - l], p[j - l] = prime[i];
				now[j - l] /= prime[i];
			}
	    }
	}
	long long ans = 0;
	// printf ("%d %d\n", np[0], p[0]);
	for (int i = 0; i <= r - l; i++)
	{
		// printf ("%lld %d %d %d\n", i + l, np[i], p[i], now[i]); 
		if (now[i] != 1) ans += p[i];
		else ans += np[i];
	}
	printf ("%lld\n", ans);	
}
