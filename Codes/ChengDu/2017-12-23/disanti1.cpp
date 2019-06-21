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
const int MAXN = 3e5 + 5;
int a[MAXN], pos[MAXN];
int Max[MAXN], Min[MAXN], T[MAXN];
long long ans;
void dfs(int l, int r)
{
	if (l == r)
	{
		ans++;
		return;
	}
	int mid = l + r >> 1;
	Max[mid] = Min[mid] = a[mid];
	Max[mid + 1] = Min[mid + 1] = a[mid + 1];
	for (int i = mid - 1; i >= l; i--)
		Max[i] = max(Max[i + 1], a[i]), Min[i] = min(Min[i + 1], a[i]);
	for (int i = mid + 2; i <= r; i++)
		Max[i] = max(Max[i - 1], a[i]), Min[i] = min(Min[i - 1], a[i]);
	for (int j = mid; j >= l; j--)
	{
		int i = j + (Max[j] - Min[j]);
		if (i > mid && i <= r && Max[i] < Max[j] && Min[i] > Min[j])
			ans++;
	}
	for (int i = mid + 1; i <= r; i++)
	{
		int j = i - (Max[i] - Min[i]);
		if (j <= mid && j >= l && Max[j] < Max[i] && Min[j] > Min[i])
			ans++;
	}
	int p1 = mid + 1, p2 = mid + 1;
	for (int i = mid; i >= l; i--)
	{
		while (p1 <= r && Min[p1] >= Min[i])
		{
			T[Max[p1] - p1 + mid]++;
			p1++;
		}
		while (p2 < p1 && Max[p2] <= Max[i])
		{
			T[Max[p2] - p2 + mid]--;
			p2++;
		}
		ans += T[Min[i] - i + mid];
	}
	for (int i = l; i <= r; i++)
		T[Max[i] - i + mid] = 0;
	p1 = mid, p2 = mid;
	for (int i = mid + 1; i <= r; i++)
	{
		while (p1 >= l && Min[p1] >= Min[i])
		{
			T[Max[p1] + p1 - mid]++;
			p1--;
		}
		while (p2 > p1 && Max[p2] <= Max[i])
		{
			T[Max[p2] + p2 - mid]--;
			p2--;
		}
		ans += T[Min[i] + i - mid];
	}
	for (int i = l; i <= r; i++)
		T[Max[i] + i - mid] = 0;
	dfs(l, mid), dfs(mid + 1, r);
}

int main()
{
	// freopen("disanti.in", "r", stdin);
	// freopen("disanti.out", "w", stdout);
	int n;
	n = read();
	for (int i = 1; i <= n; i++)
		a[i] = read();
	dfs(1, n);
	printf ("%lld\n", ans);
}
