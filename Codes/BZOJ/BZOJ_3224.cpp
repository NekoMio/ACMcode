#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

namespace Scapegoat_Tree
{
    const int MAXN = 1e6 + 10;
    const double alpha = 0.756;
    struct Node
    {
        Node *ch[2];
        int key, s, cover;
        bool exist;
        void Pushup()
        {
            s = ch[0]->s + ch[1]->s + exist;
            cover = ch[0]->cover + ch[1]->cover + 1;
        }
        bool isBad()
        {
            return ((ch[0]->cover > cover * alpha + 5) || (ch[1]->cover > cover * alpha + 5));
        }
    };
    struct Stree 
    {
        Node mem_poor[MAXN];
        Node *tail, *root, *null, *ls[MAXN];
        Node *bc[MAXN]; int bc_top, top;
        Node *NewNode(int key)
        {
            Node *o = bc_top ? bc[--bc_top] : tail++;
            o->ch[0] = o->ch[1] = null;
            o->s = o->cover = o->exist = 1;
            o->key = key;
            return o;
        }
        void Travel(Node *rt)
        {
            if (rt == null) return;
            Travel(rt->ch[0]);
            if (rt->exist) ls[++top] = rt;
            else bc[bc_top++] = rt;
            Travel(rt->ch[1]);
        }
        Node *Divide(int l, int r)
        {
            if (l > r) return null;
            int mid = (l + r) >> 1;
            Node *o = ls[mid];
            o->ch[0] = Divide(l, mid - 1);
            o->ch[1] = Divide(mid + 1, r);
            o->Pushup();
            return o;
        }
        void ReBuild(Node *&rt)
        {
            top = 0;
            Travel(rt);
            rt = Divide(1, top);
        }
        Node ** Insert(Node *&rt, int val)
        {
            if (rt == null) 
            {
                rt = NewNode(val);
                return &null;
            }
            else
            {
                Node **res = Insert(rt->ch[val >= rt->key], val);
                rt->Pushup();
                if (rt->isBad()) res = &rt;
                return res;
            }
        }
        void erase(Node *rt, int id)
        {
            rt->s--;
            int offset = rt->ch[0]->s + rt->exist;
            if (rt->exist && id == offset)
            {
                rt->exist = false;
                return;
            }
            else
            {
                if (id <= offset) erase(rt->ch[0], id);
                else erase(rt->ch[1], id - offset);
            }
        }
        Stree()
        {
            tail = mem_poor;
            null = tail++;
            null->ch[0] = null->ch[1] = null;
            null->cover = null->s = null->key = 0;
            root = null; bc_top = 0;
        }
        void Insert(int val)
        {
            Node **rt = Insert(root, val);
            if (*rt != null) ReBuild(*rt);
        }
        int Rank(int val)
        {
            Node *rt = root;
            int ans = 1;
            while (rt != null)
            {
                if (rt->key >= val) rt = rt->ch[0];
                else
                {
                    ans += rt->ch[0]->s + rt->exist;
                    rt = rt->ch[1];
                }
            }
            return ans;
        }
        int Kth(int k)
        {
            Node *rt = root;
            while (rt != null)
            {
                if (rt->ch[0]->s + 1 == k && rt->exist) return rt->key;
                else if (rt->ch[0]->s >= k) rt = rt->ch[0];
                else k -= rt->ch[0]->s + rt->exist, rt = rt->ch[1];
            }
        }
        void erase(int k)
        {
            erase(root, Rank(k));
            if (root->s < alpha * root->cover) ReBuild(root);
        }
    };
}

using namespace Scapegoat_Tree;

Stree rt;

int main()
{
    // freopen("phs.in", "r", stdin);
    // freopen("phs.out", "w", stdout);
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        int op, x;
        scanf("%d%d", &op, &x);
        switch (op)
        {
        case 1:
            rt.Insert(x);
            break;
        case 2:
            rt.erase(x);
            break;
        case 3:
            printf("%d\n", rt.Rank(x));
            break;
        case 4:
            printf("%d\n", rt.Kth(x));
            break;
        case 5:
            printf("%d\n", rt.Kth(rt.Rank(x) - 1));
            break;
        case 6:
            printf("%d\n", rt.Kth(rt.Rank(x + 1)));
        }
    }
}