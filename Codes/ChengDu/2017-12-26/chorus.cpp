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

const int MAXN = 1e6;
int prime[MAXN + 2], mu[MAXN + 2], cnt, Sum[MAXN + 2];
bool isnprime[MAXN + 2];

struct Hash_Table
{
	struct data
	{
		int ans, next;
		int x;
	}v[MAXN];
	int first[76545], p;
	Hash_Table()
	{
		memset (first, -1, sizeof (first));
		p = 0;
	}
	bool count(const int x)
	{
		int H = x % 76543;
		for (int i = first[H]; i != -1; i = v[i].next)
			if (v[i].x == x)
				return 1;
		return 0;
	}
	int &operator[](const int x) 
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

void Get_mu()
{
	mu[1] = 1;
	isnprime[1] = 1;
	for (int i = 2; i <= MAXN; i++)
	{
		if (!isnprime[i]) prime[++cnt] = i, mu[i] = -1;
		for (int j = 1; j <= cnt; j++)
		{
			if (i * prime[j] > MAXN) break;
			isnprime[i * prime[j]] = 1;
			if (i % prime[j] == 0)
			{
				mu[i * prime[j]] = 0;
				break;
			}
			else
				mu[i * prime[j]] = -mu[i];
		}
	}
	for (int i = 1; i <= MAXN; i++)
		Sum[i] = Sum[i - 1] + mu[i];
}

#define g(_) (((double)(_) * (_) - (_)) / 4)

int sum(int x)
{
	if (x <= MAXN) return Sum[x];
	if (Hash.count(x)) return Hash[x];
	int ans = 1;
	int nxt = 1;
	for (int i = 2; i <= x; i = nxt + 1)
	{
		nxt = x / (x / i);
		ans -= (nxt - i + 1) * sum(x / i);
	}
	return Hash[x] = ans;
}

double Calc(int x)
{
	double ans = 0;
	x++;
	int nxt = 1;
	for (int i = 1; i <= x; i = nxt + 1)
	{
		nxt = x / (x / i);
		ans += sum(x / i) * (g(nxt) - g(i - 1));
	}
	return ans + (double)sum(x) / 2 - ((double)mu[1]) / 2;
}

int main()
{
	freopen("chorus.in", "r", stdin);
	freopen("chorus.out", "w", stdout);
	Get_mu();
	int a = read(), b = read();
	printf ("%.2f\n", Calc(b) - Calc(a - 1));
}