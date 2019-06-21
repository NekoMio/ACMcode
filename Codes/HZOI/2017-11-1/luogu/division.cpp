#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <cmath>
#include <vector>
using namespace std;
const int N = 131075;
int a[N];
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
vector<int> st[(N << 1) + 200];
int fa[(N << 1) + 200];
int ans[N], cnt = 0;
int find(int x)
{
	if (fa[x] != x) fa[x] = find(fa[x]);
	return fa[x];
}
int main()
{
    int n = read(), k = read();
    for (int i = 1; i <= n; i++)
        a[i] = read();
    if (k == 1)
    {
    	ans[0] = n;
        for (int i = n; i >= 1; i--)
        {
            bool flag = 0;
            for (int j = sqrt(a[i]) + 1; j <= 512; j++)
                if (st[j * j - a[i]].size())
                    flag = 1;
            if (flag)
            {
                ans[++cnt] = i;
            	for (int j = ans[cnt] + 1; j <= ans[cnt - 1]; j++)
					st[a[j]].clear();
            }
            st[a[i]].push_back(1);
         }
        printf ("%d\n", cnt + 1);
        for (int i = cnt; i >= 1; i--)
            printf ("%d ", ans[i]);
        printf("\n");
    }
    else
    {
        for (int i = 1; i <= 2 * N; i++)
        	fa[i] = i;
        ans[0] = n;
		for (int i = n; i >= 1; i--)
        {
        	bool flag = 0;
        	for (int j = sqrt(a[i]) + 1; j <= 512; j++)
        		if (st[j * j - a[i]].size())
    			{
    				int p = j * j - a[i];	
					for (int k = 0; k < st[p].size(); k++)
					{
						if (find(i) == find(st[p][k]))
    					{
    						flag = 1;
    						break;
						}
						fa[find(i)] = find(st[p][k] + N);
						fa[find(st[p][k])] = find(i + N);
 					}
 					if (flag) break;
				}
			if (flag) 
			{
				ans[++cnt] = i;
				for (int j = ans[cnt] + 1; j <= ans[cnt - 1]; j++)
					st[a[j]].clear();
			}
			st[a[i]].push_back(i);
	    }
	    printf ("%d\n", cnt + 1);
        for (int i = cnt; i >= 1; i--)
            printf ("%d ", ans[i]);
        printf("\n");
    }
    // while(1);
}
