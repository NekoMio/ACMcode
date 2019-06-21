#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>

using namespace std;

inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}

const int MAXN = 100005;
const int MOD = 1e9 + 7;


struct edge
{
	int END, next;
}v[MAXN << 1];                                                                                   
int first[MAXN], p;
void add(int a, int b)
{
	v[p].END = b;
	v[p].next = first[a];
	first[a] = p++;
}

long long pow_mod(long long a, int b)
{
	long long ans = 1;
	while (b)
	{
		if (b & 1) ans = ans * a % MOD;
		b >>= 1;
		a = a * a % MOD;
	}
	return ans;
}

long long size[MAXN];
int n;
long long ans = 0;
set<int> temp, st;
set<int>::iterator it, it1;

void Calc(int rt, int fa)
{
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == fa) continue;
		Calc(v[i].END, rt);
	}
	if (rt != 1)
	{
		it1 = it = st.find(rt);
		it--; it1++;  
		long long t1 = rt - *it, t2 = *it1 - rt;
		ans = (((long long)n - rt + 1) * rt % MOD - t1 * t2 % MOD + MOD + ans) % MOD;
	}
}

void Erase(int rt, int fa)
{
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == fa) continue;
		Erase(v[i].END, rt);
	}
	st.erase(rt);
}

void DFS(int rt, int fa)
{
	for (int i = first[rt]; i != -1; i = v[i].next)
	{
		if (v[i].END == fa) continue;
		st = temp;
		DFS(v[i].END, rt);
		Erase(v[i].END, rt);
		Calc(v[i].END, rt);
	}
}


int main()
{
	freopen("communicate.in", "r", stdin);
	freopen("communicate.out", "w", stdout);
	memset(first, -1, sizeof (first));
	n = read();
	int a, b;
	for (int i = 1; i <= n; i++) temp.insert(i);
	for (int i = 1; i < n; i++)
	{
		a = read(), b = read();
		add(a, b);
		add(b, a);
	}
	DFS(1, 0);
	long long ans1 = (long long)n * (n + 1) % MOD;
	printf ("%lld\n", 2 * ans * pow_mod(ans1, MOD - 2) % MOD);
}