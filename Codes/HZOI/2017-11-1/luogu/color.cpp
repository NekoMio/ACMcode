#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
const int N = 3e5 + 5;
char xch,xB[1<<15],*xS=xB,*xTT=xB;
// #define getc() (xS==xTT&&(xTT=(xS=xB)+fread(xB,1,1<<15,stdin),xS==xTT)?0:*xS++)
// inline int read()
// {
//     int x=0,f=1;char ch=getc();
//     while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getc();}
//     while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getc();}
//     return x*f;
// }
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int full = 19;
int C[N];
struct Trie
{
    struct Node
    {
        int s;
        Node *ch[2];
        Node()
        {
            s = 0;
            ch[0] = ch[1] = NULL; 
        }
#define size(_) ((_)?(_)->s: 0)
    }*root;
    Trie()
    {
        root = new Node();
    }
    void Insert(int x, int c)
    {
        Node *rt = root;
        for (int i = full; i >= 0; i--)
        {
            int nxt = (x >> i) & 1;
            if (rt->ch[nxt] == NULL)
                rt->ch[nxt] = new Node();
            rt = rt->ch[nxt];
            rt->s += c;
        }
    }
    int Rank(int x)
    {
        int res = 0;
        Node *rt = root;
        for (int i = full; i >= 0; i--)
        {
            bool next = x >> i & 1;
            if (next) res += size(rt->ch[0]);
            if (!rt->ch[next])
                break;
            rt = rt->ch[next];
        }
        return res;
    }
}root[N];
int Query(int l, int r, int x)
{
    return root[x].Rank(r + 1) - root[x].Rank(l);
}
int main()
{
    int n = read(), m = read();
    for (int i = 1; i <= n; i++)
    {
        C[i] = read();
        root[C[i]].Insert(i, 1);
    }
    int op, x, l, r;
    for (int i = 1; i <= m; i++)
    {
        op = read();
        if (op == 1)
        {
            l = read(), r = read();
            x = read();
            printf ("%d\n", Query(l, r, x));
        }
        else
        {
            x = read();
            root[C[x]].Insert(x, -1);
            root[C[x]].Insert(x + 1, 1);
            root[C[x + 1]].Insert(x + 1, -1);
            root[C[x + 1]].Insert(x, 1);
            swap(C[x + 1], C[x]);
        }
    }
    // while (1);
}
