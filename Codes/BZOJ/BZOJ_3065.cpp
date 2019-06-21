#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MAXN = 70005;
const int INF = 70000;
const double alpha = 0.75;
#define Size(_) ((_) ? (_)->s : 0)
struct Seg_Tree
{
    struct Seg_Node
    {
        Seg_Node *ch[2];
        int s;
        Seg_Node()
        {
            s = 0;
            ch[0] = ch[1] = NULL;
        }
    }*root;
    Seg_Tree()
    {
        root = new Seg_Node();
    }
    inline void Insert(Seg_Node *rt, int l, int r, int x)
    {
        rt->s++;
        if (l == r) return;
        int mid = l + r >> 1;
        if (x <= mid)
        {
            if (rt->ch[0] == NULL) rt->ch[0] = new Seg_Node();
            Insert(rt->ch[0], l, mid, x);
        }
        else
        {
            if (rt->ch[1] == NULL) rt->ch[1] = new Seg_Node();
            Insert(rt->ch[1], mid + 1, r, x);
        }
    }
    inline void insert(int x)
    {
        Insert(root, 0, INF, x);
    }
    void Remove(Seg_Node *rt, int l, int r, int x)
    {
        rt->s--;
        if (l == r) return;
        int mid = l + r >> 1;
        if (x <= mid)
        {
            Remove(rt->ch[0], l, mid, x);
            if (rt->ch[0]->s == 0)
            {
                delete rt->ch[0];
                rt->ch[0] = NULL;
            }
        }
        else
        {
            Remove(rt->ch[1], mid + 1, r, x);
            if (rt->ch[1]->s == 0)
            {
                delete rt->ch[1];
                rt->ch[1] = NULL;
            }
        }
    }
    inline void erase(int x)
    {
        Remove(root, 0, INF, x);
    }
    inline void remove(Seg_Node *&rt)
    {
        if (rt == NULL) return;
        remove(rt->ch[0]);
        remove(rt->ch[1]);
        delete rt;
        rt = NULL;
    }
    inline void clear()
    {
        remove(root);
        root = new Seg_Node();
    }
};
int a[35005];
struct Node
{
    Node *ch[2];
    int s, v;
    Seg_Tree rt;
    Node(int x)
    {
        s = 1;
        v = x;
        ch[0] = ch[1] = NULL;
    }
    void Pushup()
    {
        s = Size(ch[0]) + Size(ch[1]) + 1;
    }
    bool isBad()
    {
        return (Size(ch[0]) > s * alpha || Size(ch[1]) > s * alpha);
    }
};
void Dfsprint(Seg_Tree::Seg_Node *rt, int l, int r)
{
    if (l == r) 
    {
        cerr << l << " ";
        return;
    }
    int mid = l + r >> 1;
    if (rt->ch[0]) Dfsprint(rt->ch[0], l, mid);
    if (rt->ch[1]) Dfsprint(rt->ch[1], mid + 1, r);
}
struct Stree
{
    Node *root;
    Node *ls[MAXN];
    int lab[MAXN];
    int top;
    Node **res;
    vector<Seg_Tree::Seg_Node*> h;
    vector<int> q;
    inline void Insert(Node *&rt, int val, int k)
    {
        if (rt == NULL)
        {
            rt = new Node(val);
            rt->rt.insert(val);
        }
        else
        {
            rt->rt.insert(val);
            if (Size(rt->ch[0]) >= k)
            {
                Insert(rt->ch[0], val, k);
                rt->Pushup();
            }
            else
            {
                k = k - Size(rt->ch[0]) - 1;
                Insert(rt->ch[1], val, k);
                rt->Pushup();
            }
            if (rt->isBad()) res = &rt;
        }
    }
    inline void Travel(Node *rt)
    {
        if (rt == NULL) return;
        Travel(rt->ch[0]);
        ls[++top] = rt;
        lab[top] = rt->v;
        Travel(rt->ch[1]);
    }
    inline Node *Divide(int l, int r)
    {
        if (l > r) return NULL;
        int mid = l + r >> 1;
        Node *o = ls[mid];
        o->rt.clear();
        for (int i = l; i <= r; i++)
            o->rt.insert(lab[i]);
        o->ch[0] = Divide(l, mid - 1);
        o->ch[1] = Divide(mid + 1, r);
        o->Pushup();
        return o;
    }
    inline void reBuild(Node *&rt)
    {
        top = 0;
        Travel(rt);
        rt = Divide(1, top);
    }
    inline void insert(int k, int val)
    {
        res = NULL;
        Insert(root, val, k);
        if (res) reBuild(*res);
    }
    inline int Change(Node *rt, int k, int val)
    {
        rt->rt.insert(val);
        int t, L = Size(rt->ch[0]);
        if (L + 1 == k)
        {
            t = rt->v;
            rt->v = val;
        }
        else if (L >= k) 
            t = Change(rt->ch[0], k, val);
        else t = Change(rt->ch[1], k - L - 1, val);
        rt->rt.erase(t);
        return t;
    }
    inline void Change(int k, int val)
    {
        Change(root, k, val);
    }
    inline Node *build(int l, int r)
    {
        if (l > r) return NULL;
        int mid = l + r >> 1;
        Node *o = new Node(a[mid]);
        for (int i = l; i <= r; i++)
            o->rt.insert(a[i]);
        o->ch[0] = build(l, mid - 1);
        o->ch[1] = build(mid + 1, r);
        o->Pushup();
        return o;
    }
    inline void Build(int l, int r)
    {
        root = build(l, r);
    }
    inline void query(Node *rt, int l, int r)
    {
        int L = Size(rt->ch[0]), R = Size(rt);
        // cerr << L << " " << R << endl; 
        if (l == 1 && r == R) 
        {
            h.push_back(rt->rt.root);
            return;
        }
        if (l <= L + 1 && r >= L + 1)
            q.push_back(rt->v);
        if (r <= L)
            query(rt->ch[0], l, r);
        else if (l > L + 1) query(rt->ch[1], l - L - 1, r - L - 1);
        else
        {
            if (l <= L) query(rt->ch[0], l, L);
            if (r > L + 1)query(rt->ch[1], 1, r - L - 1);
        }
    }
    inline int Query(int L, int R, int k)
    {
        query(root, L, R);
        k--;
        int l = 0, r = 70000, n = h.size(), m = q.size();
        while (l < r)
        {
            int mid = l + r >> 1, sum = 0;
            // for (int i = 0; i < m; i++) cerr << q[i] << " ";
            for (int i = 0; i < n; i++)
            {
                if (h[i]) sum += Size(h[i]->ch[0]);
            }
            for (int i = 0; i < m; i++) if (q[i] >= l && q[i] <= mid) sum++;
            if (k < sum)
            {
                for (int i = 0; i < n; i++) if (h[i]) h[i] = h[i]->ch[0];
                r = mid;
            }
            else
            {
                for (int i = 0; i < n; i++) if (h[i]) h[i] = h[i]->ch[1];
                l = mid + 1, k = k - sum;
            }
        }
        h.clear(), q.clear();
        return l;
    }
    void print(Node *rt)
    {
        if (rt == NULL) return;
        print(rt->ch[0]);
        cerr << rt->v << " ";
        print(rt->ch[1]);
    }
    void print()
    {
        print(root);
    }
}root;
int main()
{
    int n = read();
    for (int i = 1; i <= n; i++)
        a[i] = read();
    root.Build(1, n);
    int q = read();
    int lastans = 0;
    char s[10];
    while (q--)
    {
        scanf ("%s", s);
        if (s[0] == 'Q')
        {
            int x = read() ^ lastans, y = read() ^ lastans, k = read() ^ lastans;
            // root.print();
            printf ("%d\n", lastans = root.Query(x, y, k));
        }
        else if (s[0] == 'M')
        {
            int x = read() ^ lastans, val = read() ^ lastans;
            root.Change(x, val);
        }
        else
        {
            int x = read() ^ lastans, val = read() ^ lastans;
            root.insert(x - 1, val);
        }
    }
    // while (1);;
}