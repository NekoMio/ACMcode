#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;
#define LL long long
struct data
{
	LL Num;
	int pos;
	bool operator < (const data &a)const 
	{
		return Num == a.Num ? pos < a.pos : Num < a.Num;
	}
};
int fre[100005], nxt[100005];
LL a[100005];
set<data> st;
LL merge()
{
	int A = st.begin()->pos;
	LL ans = a[A];
	a[A] = -a[A];
	a[A] += a[fre[A]], a[A] += a[nxt[A]];
	st.erase(st.begin());
	st.erase((data){a[fre[A]], fre[A]});
	st.erase((data){a[nxt[A]], nxt[A]});
	st.insert((data){a[A], A});
	if(fre[fre[A]])
		nxt[fre[fre[A]]] = A;
	if(nxt[nxt[A]])
		fre[nxt[nxt[A]]] = A;
	fre[A] = fre[fre[A]];
	nxt[A] = nxt[nxt[A]];
	return ans;
}
int main()
{
	int n, k;
	scanf("%d%d", &n, &k);
	long long b, c;
	scanf("%lld", &b);
	for (int i = 1; i < n; i++)
	{
		scanf("%lld", &c);
		a[i] = c - b;
		b = c;
		fre[i] = i - 1;
		nxt[i] = i + 1;
		st.insert((data){a[i], i});
	}
	nxt[n - 1] = 0;
	a[0] = 0x3f3f3f3f3f3f3f3fll;
	LL ans = 0;
	while(k--)
	{
		ans+=merge();
	}
	printf("%lld",ans);
}