#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int a[100005], Sum[100005];
int n, N;
struct Node
{
    int s;
    Node *ch[2];
    Node()
    {
        ch[0] = ch[1] = NULL;
        s = 0;
    }
    #define size(_) ((_) ? (_)->s: 0)
}*root;
void Insert(int x)
{
    Node *rt = root;
    for (int i = n - 1; i >= 0; i--)
    {
        int next = (x >> i) & 1;
        if (!rt->ch[next])
            rt->ch[next] = new Node();
        rt = rt->ch[next];
        rt->s++;
    }
}
int Change(int x)
{
    return ((x >> (n - 1)) + (x << 1)) & N;
}
int ans = 0, cnt = 0;
void DFS(Node *rt, int Dep, int now)
{
    if (rt->ch[0] == NULL && rt->ch[1] == NULL)
    {
        if (now > ans) cnt = 1, ans = now;
        else if (ans == now) cnt += 1;
        return;
    }
    if (rt->ch[0] != NULL && rt->ch[1] != NULL)
    {
        DFS(rt->ch[0], Dep - 1, now);
        DFS(rt->ch[1], Dep - 1, now);
    }
    else
    {
        if (rt->ch[0] != NULL)
            DFS(rt->ch[0], Dep - 1, now | (1 << (Dep - 1)));
        else
            DFS(rt->ch[1], Dep - 1, now | (1 << (Dep - 1))) ;
    }
}
int main()
{
    root = new Node();
    int m;
    scanf("%d%d", &n, &m);
    N = (1 << n) - 1;
    for (int i = 1; i <= m; i++)
        scanf("%d", &a[i]);
    for (int i = 1; i <= m; i++)
        Sum[i] = Sum[i - 1] ^ a[i];
    int now = 0;
    for (int i = 0; i <= m; i++)
    {
        now ^= Change(a[i]);
        Insert(now ^ Sum[m] ^ Sum[i]);
    }
    DFS(root, n, 0);
    printf("%d\n%d\n", ans, cnt);
    // while (1);
}