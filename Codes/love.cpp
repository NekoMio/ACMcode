#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
class Treap1
{
  public:
    class Node
    {
      public:
        Node *ch[2];
        int v, key, s, Min, Max, C;
        Node(int x)
        {
            Min = x, Max = x, C = 1000000000;
            v = x, key = rand(), s = 1;
            ch[0] = ch[1] = NULL;
        }
#define Min(_) ((_) ? (_)->Min : 1000000000)
#define Max(_) ((_) ? (_)->Max : -1000000000)
#define C(_) ((_) ? (_)->C : 1000000000)
#define size(_) ((_) ? (_)->s : 0)
        void Pushup()
        {
            s = size(ch[0]) + size(ch[1]) + 1;
            Min = min(Min(ch[0]), v);
            Max = max(Max(ch[1]), v);
            C = min(C(ch[0]), C(ch[1]));
            C = min(C, min(Min(ch[1]) - v, v - Max(ch[0])));
        }
    } * root;
    Node *Merge(Node *A, Node *B)
    {
        if (!A)
            return B;
        if (!B)
            return A;
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
    typedef pair<Node *, Node *> DNode;
    DNode Split(Node *rt, int k)
    {
        if (!rt)
            return DNode(NULL, NULL);
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
    int Rank(Node *rt, int x)
    {
        if (!rt)
            return 0;
        return x <= rt->v ? Rank(rt->ch[0], x) : Rank(rt->ch[1], x) + size(rt->ch[0]) + 1;
    }
    void Insert(int x)
    {
        int k = Rank(root, x);
        DNode y = Split(root, k);
        Node *n = new Node(x);
        root = Merge(y.first, Merge(n, y.second));
    }
} Rt1;
struct BIT
{
    long long sum[50005];
#define lowbit(_) ((_) & (-_))
    void add(int x, int c)
    {
        for (int i = x; i <= 50000; i += lowbit(i))
            sum[i] += c;
    }
    long long Query(int x)
    {
        long long ans = 0;
        for (int i = x; i > 0; i -= lowbit(i))
            ans += sum[i];
        return ans;
    }
} bit;
int Abs(int x)
{
    return x >= 0 ? x : -x;
}
class Treap2
{
  public:
    class Node
    {
      public:
        Node *ch[2];
        int v, key, s, l, r, C;
        Node(int x)
        {
            l = x, r = x, C = 1000000000;
            v = x, key = rand(), s = 1;
            ch[0] = ch[1] = NULL;
        }
#define l(_) ((_) ? (_)->l : 1000000000)
#define r(_) ((_) ? (_)->r : -1000000000)
        //#define C(_) ((_) ? (_)->C : 0x7fffffff)
        //#define size(_) ((_) ? (_)->s : 0)
        void Pushup()
        {
            s = size(ch[0]) + size(ch[1]) + 1;
            l = ch[0] ? ch[0]->l : v;
            r = ch[1] ? ch[1]->r : v;
            C = min(C(ch[0]), C(ch[1]));
            C = min(C, min(Abs(l(ch[1]) - v), Abs(v - r(ch[0]))));
        }
    } * root;
    Node *Merge(Node *A, Node *B)
    {
        if (!A)
            return B;
        if (!B)
            return A;
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
    typedef pair<Node *, Node *> DNode;
    DNode Split(Node *rt, int k)
    {
        if (!rt)
            return DNode(NULL, NULL);
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
    void Insert(int k, int x)
    {
        DNode y = Split(root, k);
        Node *n = new Node(x);
        root = Merge(y.first, Merge(n, y.second));
    }
} Rt2;
int main()
{
    freopen("love.in","r",stdin);
    freopen("love.out","w",stdout);
    int n, m;
    scanf("%d%d", &n, &m);
    int a;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a);
        bit.add(i, 1);
        Rt1.Insert(a);
        Rt2.Insert(i, a);
    }
    char s[20];
    int x, k;
    for (int i = 1; i <= m; i++)
    {
        scanf("%s", s);
        if (s[0] == 'I')
        {
            scanf("%d%d", &x, &a);
            k = bit.Query(x);
            Rt1.Insert(a);
            Rt2.Insert(k, a);
            bit.add(x, 1);
        }
        else
        {
            if (s[5] == 'A')
            {
                printf("%d\n", C(Rt2.root));
            }
            else
            {
                printf("%d\n", C(Rt1.root));
            }
        }
    }
}
