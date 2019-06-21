#include <cstdio>
#include <algorithm>
#include <cstdlib>
using namespace std;
struct Node
{
    Node *ch[2];
    int s, id, key;
    Node(int x)
    {
        key = rand();
        id = x;
        s = 1;
        ch[0] = ch[1] = NULL;
    }
#define size(_) ((_) ? (_)->s : 0)
    void Update()
    {
        s = size(ch[1]) + size(ch[0]) + 1;
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
        A->Update();
        return A;
    }
    else
    {
        B->ch[0] = Merge(A, B->ch[0]);
        B->Update();
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
        rt->Update();
        o.second = rt;
    }
    else
    {
        o = Split(rt->ch[1], k - size(rt->ch[0]) - 1);
        rt->ch[1] = o.first;
        rt->Update();
        o.first = rt;
    }
    return o;
}
void Insert(int x, int k)
{
    DNode y = Split(root, k);
    Node *n = new Node(x);
    root = Merge(y.first, Merge(n, y.second));
}
int Ind = 0;
int a[100005];
void DFS(Node *rt)
{
    if (rt)
    {
        DFS(rt->ch[0]);
        a[rt->id] = ++Ind;
        DFS(rt->ch[1]);
    }
}
int main()
{
    int n;
    scanf("%d", &n);
    int c;
    Insert(1, 0);
    for (int i = 2; i <= n; i++)
    {
        scanf("%d", &c);
        Insert(i, c);
    }
    DFS(root);
    for (int i = 1; i <= n; i++)
    {
        printf("%d\n", a[i]);
    }
    //while(1);
}