#pragma GCC optimize("O3")
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <set>
using namespace std;
set<int> st;
set<int>::iterator it; 
template<typename _Tp>
inline void read(_Tp &a)
{
    int f = 1;
    a = 0;
    char ch = getchar();
    while (ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
    while (ch<='9'&&ch>='0'){a=a*10+ch-'0';ch=getchar();}
    a *= f;
}
bool OK(int x, int D, int L)
{
    int now = 0;
    while (now + D < L)
    {
        it = st.upper_bound(now + D);
        --it;
        if (*it <= now) return 0;
        else
        {
            now = *it;
            st.erase(it);
        }
    }
    return 1;
}
int main()
{
    // freopen("blue.in", "r", stdin);
    int T, a;
    read(T);
    while (T--)
    {
        st.clear();st.insert(0);
        int n, m, D, L;
        read(n), read(m), read(D), read(L);
        for (int i = 1; i <= n; i++)
            read(a), st.insert(a);
        int t = 0;
        while (OK(t + 1, D, L) && t < m) t++;
        if (t == m) printf("Excited\n");
        else printf("%d\n", t); 
    }
    // while (1);
}