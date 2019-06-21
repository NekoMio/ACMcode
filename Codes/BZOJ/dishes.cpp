#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;
struct edge
{
    int next, END;
} v[100005];
int p, first[100005];
int in[100005];
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
int main()
{
    //freopen("dishes.in","r",stdin);
    //freopen("dishes.out","w",stdout);
    int T;
    scanf("%d", &T);
    while (T--)
    {
        memset(first, -1, sizeof(first));
        memset(in, 0, sizeof(in));
        p = 0;
        int n, m;
        scanf("%d%d", &n, &m);
        int a, b;
        for (int i = 1; i <= m; i++)
        {
            scanf("%d%d", &a, &b);
            add(b, a);
            in[a]++;
        }
        priority_queue<int> Q;
        stack<int> st;
        for (int i = 1; i <= n; i++)
            if (!in[i])
                Q.push(i);
        while (!Q.empty())
        {
            int tmp = Q.top();
            st.push(tmp);
            Q.pop();
            for (int i = first[tmp]; i != -1; i = v[i].next)
            {
                in[v[i].END]--;
                if (in[v[i].END] == 0)
                    Q.push(v[i].END);
            }
        }
        int flag = 0;
        for (int i = 1; i <= n; i++)
            if (in[i] > 0)
                flag = 1;
        if (flag)
            puts("Impossible!");
        else
        {
            while (!st.empty())
            {
                printf("%d ", st.top());
                st.pop();
            }
            printf("\n");
        }
    }
}
