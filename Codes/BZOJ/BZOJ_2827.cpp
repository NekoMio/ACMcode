#pragma GCC optimize("O3")
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int Max_Morale[30005], Max_Solidarity[30005];
struct Point
{
    int x, y;
    Point(int a = 0, int b = 0)
    {
        x = a, y = b;
    }
    bool operator==(const Point &a) const
    {
        return x == a.x && y == a.y;
    }
};
struct data
{
    int x, ID;
    data(int a = 0, int b = 0)
    {
        x = a, ID = b;
    }
    bool operator>(const data &a) const
    {
        return x == a.x ? ID > a.ID : x > a.x;
    }
    bool operator<=(const data &a) const
    {
        return !(*this > a);
    }
};
struct Treap
{
    struct Node
    {
        int s, key, Max_Num, Max_Size;
        data x;
        Node *ch[2];
        Node(data sa)
        {
            ch[0] = ch[1] = NULL;
            s = 1, x = sa, key = rand();
            Max_Num = Max_Size = 0;
        }
#define size(_) ((_) ? (_)->s : 0)
        void Pushup()
        {
            s = size(ch[0]) + size(ch[1]) + 1;
        }
        void Pushdown()
        {
            if (ch[0])
            {
                ch[0]->Max_Num = max(ch[0]->Max_Num, Max_Num);
                ch[0]->Max_Size = max(ch[0]->Max_Size, Max_Size);
                Max_Morale[ch[0]->x.ID] = max(Max_Morale[ch[0]->x.ID], ch[0]->Max_Num);
                Max_Solidarity[ch[0]->x.ID] = max(Max_Solidarity[ch[0]->x.ID], ch[0]->Max_Size);
            }
            if (ch[1])
            {
                ch[1]->Max_Num = max(ch[1]->Max_Num, Max_Num);
                ch[1]->Max_Size = max(ch[1]->Max_Size, Max_Size);
                Max_Morale[ch[1]->x.ID] = max(Max_Morale[ch[1]->x.ID], ch[1]->Max_Num);
                Max_Solidarity[ch[1]->x.ID] = max(Max_Solidarity[ch[1]->x.ID], ch[1]->Max_Size);
            }
            Max_Num = Max_Size = 0;
        }
    } * root;
    Treap()
    {
        root = NULL;
    }
    Node *Merge(Node *A, Node *B)
    {
        if (!A)
            return B;
        if (!B)
            return A;
        if (A->key < B->key)
        {
            A->Pushdown();
            A->ch[1] = Merge(A->ch[1], B);
            A->Pushup();
            return A;
        }
        else
        {
            B->Pushdown();
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
        rt->Pushdown();
        if (size(rt->ch[0]) >= k)
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
    Node *kth(int k)
    {
        DNode x = Split(root, k - 1);
        DNode y = Split(x.second, 1);
        Node *ans = y.first;
        root = Merge(Merge(x.first, ans), y.second);
        return ans;
    }
    int Rank(Node *rt, data x)
    {
        if (!rt)
            return 0;
        return x <= rt->x ? Rank(rt->ch[0], x) : Rank(rt->ch[1], x) + size(rt->ch[0]) + 1;
    }
    void Insert(data x)
    {
        int k = Rank(root, x);
        if (root)
        {
            root->Max_Size = max(root->Max_Size, size(root));
            root->Max_Num = max(root->Max_Num, x.x);
            Max_Morale[root->x.ID] = max(root->Max_Num, Max_Morale[root->x.ID]);
            Max_Solidarity[root->x.ID] = max(root->Max_Size, Max_Solidarity[root->x.ID]);
        }
        DNode y = Split(root, k);
        Node *n = new Node(x);
        root = Merge(Merge(y.first, n), y.second);
    }
    void remove(data x)
    {
        int k = Rank(root, x);
        DNode a = Split(root, k);
        DNode b = Split(a.second, 1);
        delete b.first;
        root = Merge(a.first, b.second);
    }
};
#define Hash_MOD 76543
#define Hash_MOD_x 9991
#define Hash_MOD_y 7307
int p = 0;
struct Hash_Table
{
    int first[76545];
    struct Link
    {
        Treap *rt;
        Point t;
        int next;
    } v[400000];
    Hash_Table()
    {
        memset(first, -1, sizeof(first));
    }
    void Push(int u, Point now, Treap *x)
    {
        v[p].rt = x;
        v[p].t = now;
        v[p].next = first[u];
        first[u] = p++;
    }
    Treap *&operator[](Point x)
    {
        int Hash = (((x.x % Hash_MOD_x) + Hash_MOD_x) % Hash_MOD_x) * (((x.y % Hash_MOD_y) + Hash_MOD_y) % Hash_MOD_y) % Hash_MOD;
        for (int i = first[Hash]; i != -1; i = v[i].next)
            if (v[i].t == x)
                return v[i].rt;
        Push(Hash, x, new Treap);
        return v[first[Hash]].rt;
    }
} Hash;
#define X(_) ((_) ? (_)->x : 0)

Point bird[30005];
int Num[30005];
int main()
{
    int n;
    scanf("%d", &n);
    int a, b, c;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d%d%d", &a, &b, &c);
        Max_Morale[i] = max(Max_Morale[i], X(Hash[Point(b, c)]->kth(size(Hash[Point(b, c)]->root))).x);
        Max_Solidarity[i] = max(Max_Solidarity[i], size(Hash[Point(b, c)]->root));
        Hash[Point(b, c)]->Insert(data(a, i));
        bird[i] = Point(b, c);
        Num[i] = a;
    }
    int m;
    scanf("%d", &m);
    for (int i = 1; i <= m; i++)
    {
        scanf("%d%d%d", &a, &b, &c);
        Hash[bird[a]]->remove(data(Num[a], a));
        Max_Morale[a] = max(Max_Morale[a], X(Hash[Point(b, c)]->kth(size(Hash[Point(b, c)]->root))).x);
        Max_Solidarity[a] = max(Max_Solidarity[a], size(Hash[Point(b, c)]->root));
        Hash[Point(b, c)]->Insert(data(Num[a], a));
        bird[a] = Point(b, c);
    }
    for (int i = 1; i <= n; i++)
        Hash[bird[i]]->remove(data(Num[i],i));
    for (int i = 1; i <= n; i++)
        printf("%lld\n", (long long)Max_Morale[i] * Max_Solidarity[i]);
    // while(1);
}