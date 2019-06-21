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

const int MOD = 1e9 + 7;
const int MAXN = 4e6;
const int INV_2 = 5e8 + 4;
int prime[MAXN + 3], cnt;
long long Sum[MAXN + 3], phi[MAXN + 3];
bool isnprime[MAXN + 3];


struct Hash_Table
{
	struct data
	{
		long long x, ans;
		int next;
	}v[MAXN / 10];
	int first[76545], p;
	Hash_Table()
	{
		memset (first, -1, sizeof (first));
		p = 0;
	}
	bool count(const long long x)
	{
		int H = x % 76543;
		for (int i = first[H]; i != -1; i = v[i].next)
			if (v[i].x == x)
				return 1;
		return 0;
	}
	long long &operator[](const long long x)
	{
		int H = x % 76543;
		for (int i = first[H]; i != -1; i = v[i].next)
			if (v[i].x == x)
				return v[i].ans;
		v[p].x = x;
		v[p].next = first[H];
		first[H] = p++;
		return v[first[H]].ans = 0;
	}
}Hash;

void Get_phi()
{
	phi[1] = 1;
	isnprime[1] = 1;
	for (int i = 2; i <= MAXN; i++)
	{
		if (!isnprime[i]) prime[++cnt] = i, phi[i] = i - 1;
		for (int j = 1; j <= cnt; j++)
		{
			if (i * prime[j] > MAXN) break;
			isnprime[i * prime[j]] = 1;
			if (i % prime[j] == 0)
			{
				phi[i * prime[j]] = phi[i] * prime[j];
				break;
			}
			else
				phi[i * prime[j]] = phi[i] * (prime[j] - 1);
		}
	}
	for (int i = 1; i <= MAXN; i++)
		Sum[i] = (Sum[i - 1] + phi[i]) % MOD;
}

long long g(long long x)
{
	if (x <= MAXN) return Sum[x];
	if (Hash.count(x)) return Hash[x];
	long long ans = (x % MOD) * ((x + 1) % MOD) % MOD * INV_2 % MOD;
	long long tmp = 0;
	long long nxt = 1;
	for (long long i = 2; i <= x; i = nxt + 1)
	{
		nxt = x / (x / i);
		tmp = (tmp + ((nxt - i + 1) % MOD) * g(x / i) % MOD) % MOD;
	}
	return Hash[x] = (ans - tmp + MOD) % MOD;
}

int main()
{
	Get_phi();
	long long a = read();
	printf ("%lld\n", g(a));
}