#pragma GCC optimize("O3")
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int a[1000005];
int in[1000005], block = 1000;
int read()
{
	int ans = 0, f = 1;char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
	while(ch >= '0' && ch <= '9'){ans = ans * 10 + ch - '0'; ch = getchar();}
	return ans * f;
}
struct Query
{
	int l, r, ID;
	bool operator < (const Query &a)const
	{
		return in[l] == in[a.l] ? r > a.r : in[l] < in[a.l];
	}
}Q[1000005];
int out[1000005];
int cnt[1000005];
int main()
{
	// freopen("count.in","r",stdin);
	// freopen("count.out","w",stdout);
	int n, q;
	n = read(), q = read();
	int r = n, ans = 0;
	for (int i = 1; i <= n; i++)
	{
		a[i] = read();
		in[i] = (i - 1) / block + 1;
		cnt[a[i]]++;
	}
	for (int i = 1; i <= n; i++)
		if(cnt[i] == i) 
			ans++;
	for (int j = 1; j <= q; j++)
	{
		Q[j].l = read();
		Q[j].r = read();
		if(Q[j].l > Q[j].r) 
			swap(Q[j].l, Q[j].r);
		Q[j].ID = j;
	}
	sort(Q + 1, Q + q + 1);
	int l = 1;
	for (int i = 1; i <= q; i++)
	{
		while(l < Q[i].l){ cnt[a[l]]--; if(cnt[a[l]] == a[l] - 1) ans--; else if (cnt[a[l]] == a[l]) ans++; l++;}
		while(l > Q[i].l){ l--; cnt[a[l]]++; if(cnt[a[l]] == a[l]) ans++; else if (cnt[a[l]] == a[l] + 1) ans--;}
		while(r > Q[i].r){ cnt[a[r]]--; if(cnt[a[r]] == a[r] - 1) ans--; else if (cnt[a[r]] == a[r]) ans++; r--;}
		while(r < Q[i].r){ r++; cnt[a[r]]++; if(cnt[a[r]] == a[r]) ans++; else if (cnt[a[r]] == a[r] + 1) ans--;}
		out[Q[i].ID] = ans;
	}
	for (int i = 1; i <= q; i++)
		printf("%d\n", out[i]);
}
