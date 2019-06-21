#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
    int x=0,f=1; char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') {x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int N = 100005;
struct Node
{
    Node *ch[2];
    int s, key, Max, v;
    Node(int x)
    {
        ch[0] = ch[1] = NULL;
        s = 1, key = rand(), v = Max = x;
    }
    #define size(_) ((_) ? (_)->s: 0)
    #define Max(_) ((_) ? (_)->Max: 0)
    void Pushup()
    {
        s = size(ch[0]) + size(ch[1]) + 1;
        Max = max(Max(ch[0]), max(Max(ch[1]), v));
    }
}*root;
Node *Merge(Node *A, Node *B)
{
    if (!A) return B;
    if (!B) return A;
    if (A->key > B->key)
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
typedef pair<Node*, Node*> DNode;
DNode Split(Node *rt, int k)
{
    if (!rt) return DNode(NULL, NULL);
    DNode o;
    if (k <= size(rt->ch[0]))
    {
        o = Split(rt->ch[0], k);
        rt->ch[0] = o.second;
        rt->Pushup();
        o.second = rt;
    }
    else
    {
        o = Split(rt->ch[1], k - size(rt->ch[0]) - 1);
        rt->ch[1] = o.first;
        rt->Pushup();
        o.first = rt;
    }
    return o;
}
int Ans[N],Max_Ans;
void Insert(int x, int k)
{
    DNode y = Split(root, k);
    Ans[x] = Max(y.first) + 1;
    Max_Ans = max(Max_Ans,Ans[x]);
    Node *n = new Node(Ans[x]);
    root = Merge(y.first, Merge(n, y.second));
}
int main()
{
    int n = read();
    for (int i = 1; i <= n; i++)
    {
        Insert(i, read());
        printf ("%d\n", Max_Ans);
    }
}