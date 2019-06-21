#include <cstring>
#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
struct Node
{
    Node *ch[2];
    int val, s, key;
    Node(int x = 0)
    {
        ch[0] = ch[1] = NULL;
        val = x, s = 1, key = rand();
    }
    #define size(_) ((_) ? (_)->s : 0)
    void Pushup()
    {
        s = size(ch[0]) + size(ch[1]) + 1;
    }
}*root[300005];
void Copy(Node *&A, Node *B)
{
    if (B == NULL) A = NULL;
    else A = new Node(), *A = *B;
}
Node *Merge(Node *A, Node *B)
{
    if (!A) return B;
    if (!B) return A;
    Node *x;
    if (A->key < B->key)
    {
        Copy(x, A);
        x->ch[1] = Merge(A->ch[1], B);
        x->Pushup();
        return x;
    }
    else
    {
        Copy(x, B);
        x->ch[0] = Merge(A, B->ch[0]);
        x->Pushup();
        return x;
    }
}
typedef pair<Node*, Node*> DNode;
DNode Split(Node *rt, int k)
{
    if (rt == NULL) return DNode(NULL, NULL);
    DNode o;
    Node *x;
    Copy(x, rt);
    if (size(rt->ch[0]) >= k)
    {
        o = Split(rt->ch[0], k);
        x->ch[0] = o.second;
        x->Pushup();
        o.second = x;
    }
    else
    {
        o = Split(rt->ch[1], k - size(rt->ch[0]) - 1);
        x->ch[1] = o.first;
        x->Pushup();
        o.first = x;
    }
    return o;
}
Node *Insert(Node *rt, int x, int k)
{
    DNode z = Split(rt, k - 1);
    Node *n = new Node(x);
    n = Merge(z.first, Merge(n, z.second));
    return n;
}
Node *erase(Node *rt, int k)
{
    DNode z = Split(rt, k - 1), y = Split(z.second, 1);
    return Merge(z.first, y.second);
}
int kth(Node *rt, int k)
{
    while (rt)
    {
        if (size(rt->ch[0]) + 1 == k) return rt->val;
        if (size(rt->ch[0]) + 1 > k) rt = rt->ch[0];
        else k -= size(rt->ch[0]) + 1, rt = rt->ch[1];
    }
    return 0;
}
int main()
{
    int n = read();
    int cnt = 0;
    while (n--)
    {
        int opt = read();
        if (opt == 1)
        {
            int t = read(), k = read(), x = read();
            root[++cnt] = Insert(root[t], x, k);
        }
        else if (opt == 2)
        {
            int t = read(), k = read();
            root[++cnt] = erase(root[t], k);
        }
        else
        {
            int t = read(), k = read();
            printf ("%d\n", kth(root[t], k));
        }
    }
}