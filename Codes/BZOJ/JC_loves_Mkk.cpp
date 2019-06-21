#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
int que[2][200005];
int h[2], t[2];
int a[200005], n, L, R, len;
long double sum[200005];
bool Judge(long double mid)
{
	for (int i = 1; i <= 2 * n; i++)
		sum[i] = sum[i - 1] + (long double)a[i] - mid;
	h[0] = h[1] = 1, t[0] = t[1] = 0;
	for (int i = L; i <= 2 * n; i++)
	{
		int j = i - L, now = i & 1;
		while (h[now] <= t[now] && sum[j] < sum[que[now][t[now]]]) 
			t[now]--;
		que[now][++t[now]] = j;
		if (i - que[now][h[now]] > R) h[now]++;
		if (sum[i] - sum[que[now][h[now]]] > 1e-9)
		{
			len = i - que[now][h[now]]; 
			return 1;
		}
	}
	return 0;
}
long long gcd(long long a,long long b)
{
	return b == 0? a : gcd(b, a % b);
}
int main()
{
	long double l = 0, r = 0;
	scanf("%d%d%d", &n, &L, &R);
	L += (L&1), R-= (R&1);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d",a + i);
		r = max((long double)a[i], r);
	}
	for (int i = 1; i <= n; i++)
		a[i + n] = a[i];
	r += 1;
	int d = 0;
	while(r - l > 1e-9)
	{
		long double mid = (l + r) / 2;
		if (Judge(mid))
			l = mid;
		else
			r = mid;
	}
	//cout<<l<<endl;
	long long Z = round(len * l);
	long long M = len;
	long long Gcd = gcd(Z, M);
	Z/=Gcd, M/=Gcd;
	if(M == 1)
		return printf("%lld\n",Z), 0;
	printf("%lld/%lld",Z,M);
}