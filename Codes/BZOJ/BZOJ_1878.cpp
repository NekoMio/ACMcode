#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int a[50005], in[50005];
int block = 500;
struct Query
{
	int l, r, ID;
	bool operator < (const Query &b) const 
	{
		return in[l] == in[b.l] ? r > b.r : l < b.l;
	}
}Q[200005];
int cnt[1000005];
int out[200005];
int main()
{
	int n, m, ans = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &a[i]);	
		in[i] = (i - 1) / block + 1;
		cnt[a[i]]++;
		if(cnt[a[i]] == 1)
			ans++;
	}
	scanf("%d", &m);
	for (int i = 1; i <= m; i++)
		scanf("%d%d", &Q[i].l, &Q[i].r), Q[i].ID = i;
	sort(Q + 1, Q + m + 1);
	int l = 1, r = n + 1;
	for (int i = 1; i <= m; i++)
	{
		while(l < Q[i].l) {cnt[a[l]]--; if(cnt[a[l]] == 0) ans--; l++;}
		while(l > Q[i].l) {l--; cnt[a[l]]++; if(cnt[a[l]] == 1) ans++;}
		while(r > Q[i].r) {cnt[a[r]]--; if(cnt[a[r]] == 0) ans--; r--;}
		while(r < Q[i].r) {r++; cnt[a[r]]++; if(cnt[a[r]] == 1) ans++;}
		out[Q[i].ID] = ans;
	}
	for (int i = 1; i <= m; i++)
		printf("%d\n", out[i]);
}