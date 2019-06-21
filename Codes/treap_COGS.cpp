#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
class data
{
  public:
    int v, key;
    bool operator<(const data &a) const
    {
        return v < a.v;
    }
} a[500005];
class Node
{
  public:
    Node *ch[2];
    int key, v;
    Node(data x)
    {
        key = x.key;
        v = x.v;
        ch[0] = ch[1] = NULL;
    }
    ~Node();
} * st[500005];
Node *build(int m)
{
    Node *x, *last;
    int p = 0;
    for (int i = 1; i <= m; i++)
    {
        x = new Node(a[i]);
        last = NULL;
        while (p && st[p]->key > x->key)
        {
            last = st[p];
            st[p--] = NULL;
        }
        if (p)
            st[p]->ch[1] = x;
        x->ch[0] = last;
        st[++p] = x;
    }
    return st[1];
}
void dfs(Node *a)
{
    if (a)
    {
        printf("%d ", a->v);
        dfs(a->ch[0]);
        dfs(a->ch[1]);
    }
}
int main()
{
    int __size__ = 128 << 20;
    char *__p__ = (char *)malloc(__size__) + __size__;
    __asm__("movl %0, %%esp\n" ::"r"(__p__));
    freopen("treap.in","r",stdin);
    freopen("treap.out","w",stdout);
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i].v);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i].key);
    sort(a + 1, a + n + 1);
    Node *rt = build(n);
    dfs(rt);
}