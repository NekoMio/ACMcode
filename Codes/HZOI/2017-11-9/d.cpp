#include <cstdio>
#include <algorithm>
#include <cstring>
#include <set>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
set<int> st;
set<int>::iterator it;
int main()
{
	freopen ("d.in", "r", stdin);
	freopen ("d.out", "w", stdout);
	int T;
	T = read();
	while (T--)
	{
		int n = read(), k = read();
		int a, flag = 0;
		st.clear();
		for (int i = 1; i <= n; i++)
		{
			a = read();
			if (flag) continue;
			it = st.upper_bound(a);
			if (it != st.begin())
			{
				it--;
				st.erase(it);
				st.insert(a);
			}
			else if (st.size() < k)
			{
				st.insert(a);
			}
			else flag = 1;
		}
		if (flag) printf ("NO\n");
		else printf ("YES\n");
	}
	fclose(stdin), fclose(stdout);
	return 0;
}
