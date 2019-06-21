#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <ctime>
using namespace std;
// char xch,xB[1<<15],*xS=xB,*xTT=xB;
// #define getc() (xS==xTT&&(xTT=(xS=xB)+fread(xB,1,1<<15,stdin),xS==xTT)?0:*xS++)
// inline int read()
// {
//     int x=0,f=1;char ch=getc();
//     while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getc();}
//     while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getc();}
//     return x*f;
// }
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
    int Sum;
    Node()
    {
        ch[0] = ch[1] = NULL;
        Sum = 0;
    }
#define size(_) ((_)?(_)->Sum:0)
    void* operator new(size_t);
}*root, *C, *mempool;
void* Node::operator new(size_t)
{
    if (C == mempool)
    {
        C = new Node[1 << 15];
        mempool = C + (1 << 15);
    }
    return C++;
}
void Update(int x, int c, int l, int r, Node *&rt)
{
    if (rt == NULL) rt = new Node();
    rt->Sum += c;
    if (l == r) return;
    int m = l + r >> 1;
    if (x <= m) Update(x, c, l, m, rt->ch[0]);
    else Update(x, c, m + 1, r, rt->ch[1]);
}
int Query(int l, int r, Node *rt)
{
    if (!rt) return l;
    if (l == r) return l;
    int m = l + r >> 1;
    if (size(rt->ch[0]) < m - l + 1) return Query(l, m, rt->ch[0]);
    else return Query(m + 1, r, rt->ch[1]);
}
int Q[10000005], h = 1, t = 0;
int main()
{
    // freopen ("knowledge.in", "r", stdin);
    // freopen ("knowledge.out", "w", stdout);
    int m, type;
    m = read(), type = read();
    int op, x, lastans = 0;
    while (m--)
    {
        op = read();
        if (op == 1)
        {
            x = read();
            if (type) x ^= lastans;
            printf ("add %d\n", x);
            Update(x, 1, 0, 0x7fffffff, root);
        }
        else if (op == 2)
        {
            x = read();
            if (type) x ^= lastans;
            printf ("rm %d\n", x);
            Q[++t] = x;
            Update(x, -1, 0, 0x7fffffff, root);
        }
        else if (op == 3)
        {
            x = Q[h++];
            Update(x, 1, 0, 0x7fffffff, root);
        }
        else
        {
            printf ("%d\n", lastans = Query(0, 0x7fffffff, root));
        }
    }
}