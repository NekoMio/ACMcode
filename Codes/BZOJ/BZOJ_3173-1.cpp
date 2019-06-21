#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 100005;
struct Node
{
    Node *ch[2];
    int s, key, val;
    Node(int x)
    {
        ch[0] = ch[1] = NULL;
        s = 1, key = rand(), val = x;
    }
    #define Size(_) ((_)?(_)->s : 0)
    void Pushup()
    {
        s = Size(ch[0]) + Size(ch[1]) + 1;
    }
}*root;
Node *Merge(Node *A, Node *B)
{
    if (!B) return A;
    if (!A) return B;
    if (A->key < B->key)
    {
        A->ch[1] = Merge(A->ch[1], B);
        A->Pushup();
        return A;
    }
    else
    {
        B->ch[0] = Merge(A, B->ch[0]);
        B->Pushup();
        return B;
    }
}
typedef pair<Node*,Node*> DNode;
DNode Split(Node *rt, int k)
{
    if (!rt) return DNode(NULL, NULL);
    DNode o;
    if (Size(rt->ch[0]) >= k)
    {
        o = Split(rt->ch[0], k);
        rt->ch[0] = o.second;
        rt->Pushup();
        o.second = rt;
    }
    else
    {
        o = Split(rt->ch[1], k - Size(rt->ch[0]) - 1);
        rt->ch[1] = o.first;
        rt->Pushup();
        o.first = rt;
    }
    return o;
}
int a[MAXN];
int pos[MAXN], cnt;
void DFS(Node *rt)
{
    if (rt)
    {
        DFS(rt->ch[0]);
        pos[rt->val] = ++cnt;
        DFS(rt->ch[1]);
    }
}
int Max[MAXN];
#define lowbit(_) ((_)&(-_))
void Update(int x, int c)
{
    for (int i = x; i <= cnt; i += lowbit(i))
        Max[i] = max(Max[i], c);
}
int Query(int x)
{
    int ans = 0;
    for (int i = x; i >= 1; i -= lowbit(i))
        ans = max(ans, Max[i]);
    return ans;
}
int main()
{
    int n = read();
    for (int i = 1; i <= n; i++)
        a[i] = read();
    for (int i = 1; i <= n; i++)
    {
        DNode x = Split(root, a[i]);
        Node *z = new Node(i);
        root = Merge(x.first, Merge(z, x.second));
    }
    DFS(root);
    for (int i = 1; i <= n; i++)
    {
        Update(pos[i], Query(pos[i]) + 1);
        printf ("%d\n", Query(n));
    }
}