#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
unsigned int base = 31;
unsigned int bin[100005];
struct Treap
{
    struct Node
    {
        Node *ch[2];
        int size, key, c;
        unsigned int Hash;
        Node(unsigned int x)
        {
            c = x; Hash = x;
            key = rand(), size = 1;
            ch[0] = ch[1] = NULL;
        }
#define size(_) ((_) ? (_)->size : 0)
#define Hash(_) ((_) ? (_)->Hash : 0)
        void PushUp()
        {
            size = size(ch[0]) + size(ch[1]) + 1;
            Hash = Hash(ch[0]) * bin[size(ch[1]) + 1] + c * bin[size(ch[1])] + Hash(ch[1]);
        }
    } * root;
    Node *Merge(Node *A, Node *B)
    {
        if (!A)
            return B;
        if (!B)
            return A;
        if (A->key < B->key)
        {
            A->ch[1] = Merge(A->ch[1], B);
            A->PushUp();
            return A;
        }
        else
        {
            B->ch[0] = Merge(A, B->ch[0]);
            B->PushUp();
            return B;
        }
    }
    typedef pair<Node *, Node *> DNode;
    DNode Split(Node *rt, int k)
    {
        if (!rt)
            return DNode(NULL, NULL);
        DNode o;
        if (size(rt->ch[0]) >= k)
        {
            o = Split(rt->ch[0], k);
            rt->ch[0] = o.second;
            rt->PushUp();
            o.second = rt;
        }
        else
        {
            o = Split(rt->ch[1], k - size(rt->ch[0]) - 1);
            rt->ch[1] = o.first;
            rt->PushUp();
            o.first = rt;
        }
        return o;
    }
    void Insert(char s, int k)
    {
        DNode x = Split(root, k);
        Node *n = new Node((int)s);
        root = Merge(Merge(x.first, n), x.second);
    }
    void dfs(Node *rt)
    {
        if(rt)
        {
            dfs(rt->ch[0]);
            printf("%c", rt->c);
            dfs(rt->ch[1]);
            // rt->PushUp();
        }
    }
    void print()
    {
        dfs(root);
    }
} root;
bool Judge(int a, int b, int mid)
{
    if(!mid) return 1;
    Treap::DNode x = root.Split(root.root, a);
    if (mid > size(x.second))
    { 
        root.root = root.Merge(x.first, x.second);
        return 0;
    }
    Treap::DNode y = root.Split(x.second, mid);
    // printf("1: ");
    // root.dfs(y.first);
    // printf("\n");
    unsigned int Hash1 = y.first->Hash;
    // printf("%u\n", Hash1);
    root.root = root.Merge(x.first, root.Merge(y.first, y.second));
    x = root.Split(root.root, b);
    if (mid > size(x.second)) 
    {
        root.root = root.Merge(x.first, x.second);
        return 0;
    }
    y = root.Split(x.second, mid);
    // printf("2: ");
    // root.dfs(y.first);
    // printf("\n");
    unsigned int Hash2 = y.first->Hash;
    // printf("%u\n", Hash2);
    root.root = root.Merge(x.first, root.Merge(y.first, y.second));
    return Hash1 == Hash2;
}
void Get_ans(int a, int b)
{
    int l = 0, r = 100005;
    int ans = 0;
    while (l < r)
    {
        int mid = l + r >> 1;
        if (Judge(a, b, mid))
            ans = mid, l = mid + 1;
        else
            r = mid;
    }
    printf("%d\n", ans);
}
int main()
{
    static char s[100005];
    bin[0] = 1;
    for (int i = 1; i <= 100000; i++)
        bin[i] = bin[i - 1] * base;
    scanf("%s", s);
    int n = strlen(s);
    for (int i = 0; i < n; i++)
        root.Insert(s[i], i);
    // root.print();
    // while(1);
    int m;
    scanf("%d", &m);
    char c[10], ch[10];
    for (int i = 1; i <= m; i++)
    {
        scanf("%s", c);
        if (c[0] == 'Q')
        {
            int l, r;
            scanf("%d%d", &l, &r);
            l--,r--;
            Get_ans(l, r);
        }
        else if (c[0] == 'R')
        {
            int l;
            scanf("%d%s", &l, ch);
            l--;
            Treap::DNode x = root.Split(root.root, l);
            Treap::DNode y = root.Split(x.second, 1);
            y.first->c = (int)ch[0];
            y.first->Hash = ch[0];
            root.root = root.Merge(x.first, root.Merge(y.first, y.second));
            //root.print();
        }
        else
        {
            int l;
            scanf("%d%s", &l, ch);
            Treap::DNode x = root.Split(root.root, l);
            Treap::Node *n = new Treap::Node(ch[0]);
            root.root = root.Merge(x.first, root.Merge(n, x.second));
        }
    }
}