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
const int MAXN = 5e5 + 5;
const int len = 20;
struct Node
{
    Node *ch[2];
    int s;
    Node()
    {
        s = 0;
        ch[0] = ch[1] = NULL;
    }
}*root[MAXN], *null;
Node *NewNode()
{
    Node *o = new Node();
    o->ch[0] = o->ch[1] = null;
    return o;
}
void Copy(Node *&rt1, Node *rt2)
{
    if (rt2 == null) rt1 = null;
    else rt1 = NewNode(), *rt1 = *rt2;
}
void insert(int cnt, int x)
{
    Node *rt = root[cnt];
    for (int i = len; i >= 0; i--)
    {
        int nxt = (x >> i) & 1;
        if (rt->ch[nxt] == null) rt->ch[nxt] = NewNode();
        rt = rt->ch[nxt];
        rt->s++;
    }
}
void Insert(int cnt, int x)
{
    Copy(root[cnt], root[cnt - 1]);
    Node *rt1 = root[cnt - 1], *rt2 = root[cnt];
    for (int i = len; i >= 0; i--)
    {
        int nxt = (x >> i) & 1;
        Copy(rt2->ch[nxt], rt1->ch[nxt]);
        if (rt2->ch[nxt] == null) rt2->ch[nxt] = NewNode();
        rt2 = rt2->ch[nxt], rt1 = rt1->ch[nxt];
        rt2->s++;
    }
}
int QueryXor(Node *rt1, Node *rt2, int x)
{
    int ans = 0;
    for (int i = len; i >= 0; i--)
    {
        int nxt = (x >> i) & 1;
        if (rt2->ch[nxt ^ 1]->s - rt1->ch[nxt ^ 1]->s)
        {
            ans |= (1 << i);
            rt2 = rt2->ch[nxt ^ 1], rt1 = rt1->ch[nxt ^ 1];
        }
        else
            rt2 = rt2->ch[nxt], rt1 = rt1->ch[nxt];
    }
    return ans;
}
int Rank(Node *rt1, Node *rt2, int x)
{
    int ans = 0;
    for (int i = len; i >= 0; i--)
    {
        int nxt = (x >> i) & 1;
        if (nxt)
        {
            ans += rt2->ch[0]->s - rt1->ch[0]->s;
            rt2 = rt2->ch[1], rt1 = rt1->ch[1];
        }
        else
            rt2 = rt2->ch[0], rt1 = rt1->ch[0];
    }
    return ans;
}
int Kth(Node *rt1, Node *rt2, int k)
{
    int ans = 0;
    for (int i = len; i >= 0; i--)
    {
        if (k > rt2->ch[0]->s - rt1->ch[0]->s)
        {
            ans |= (1 << i);
            k -= rt2->ch[0]->s - rt1->ch[0]->s;
            rt2 = rt2->ch[1], rt1 = rt1->ch[1];
        }
        else
            rt2 = rt2->ch[0], rt1 = rt1->ch[0]; 
    }
    return ans;
}
int main()
{
    // freopen ("operator.in", "r", stdin);
    // freopen ("operator.out", "w", stdout);
    int m = read();
    null = new Node();
    null->ch[0] = null->ch[1] = null;
    root[0] = NewNode();
    // insert(0, 0);
    int cnt = 0;
    while (m--)
    {
        int op = read();
        if (op == 0)
        {
            cnt++;
            Insert(cnt, read());
        }
        else if (op == 1)
        {
            int l = read(), r = read(), x = read();
            printf ("%d\n", x ^ QueryXor(root[l - 1], root[r], x));
        }
        else if (op == 2)
        {
            cnt -= read();
        }
        else if (op == 3)
        {
            int l = read(), r = read();
            printf ("%d\n", Rank(root[l - 1], root[r], read() + 1));
        }
        else if (op == 4)
        {
            int l = read(), r = read();
            printf ("%d\n", Kth(root[l - 1], root[r], read()));
        }
    }
}