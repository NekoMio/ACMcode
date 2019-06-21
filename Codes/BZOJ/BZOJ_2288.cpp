#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;
struct data
{
    long long Num;
    int pos;
    bool operator < (const data &a)const
    {
        return Num == a.Num ? pos < a.pos : Num < a.Num;
    }
};
int fre[100005], nxt[100005];
long long a[100005], d[100005];
set<data> st;
long long merge()
{
    int A = st.begin()->pos;
    long long ans = a[A];
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
    int n, m;
    scanf("%d%d", &n, &m);
    int j = 0;
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &d[++j]);
        if(d[j] == 0) j--;
    }
    bool flag = (d[1] > 0);
    int tot = 0;
    a[++tot] += d[1];
    for (int i = 2; i <= j; i++)
    {
        if((d[i] > 0 && d[i - 1] > 0) || (d[i] < 0 && d[i - 1] < 0)) a[tot]+=d[i];
        else
        {
            if(tot == 1 && a[tot] < 0)
                tot--; 
            a[++tot] = d[i];
        }
    }
    if(a[tot] < 0)
        tot--;
    long long ans = 0;
    int k = 0;
    for (int i = 1; i <= tot; i++)
    {
        if(a[i] > 0)
            ans += a[i], k++;
        a[i] = abs(a[i]);
        st.insert((data){a[i],i});
        nxt[i] = i + 1;
        fre[i] = i - 1;
    }
    if (k <= m)
        return printf("%d\n",ans), 0;
    nxt[tot] = 0;
    a[0] = 0x3f3f3f3f3f3f3f3fll;
    while(k > m)
    {
        ans -= merge();
        k--;
    }
    printf("%lld",ans);
}