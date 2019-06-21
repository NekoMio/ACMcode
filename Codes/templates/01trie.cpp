#include <cstdio>
using namespace std;
const int full = 24, fix = 1e7;
class Node
{
  public:
    int size;
    Node *ch[2];
    Node()
    {
        ch[0] = ch[1] = NULL;
        size = 0;
    }
#define size(_) ((_) ? (_)->size : 0)
    void* operator new(size_t size);
} * root,*C,*num;
void* Node::operator new(size_t size){
    if(C==num){
        C=new Node[1<<5];
        num=C+(1<<5);
    }
    return C++;
}
void Insert(int x, int add)
{
    x += fix;
    Node *rt = root;
    for (int i = full; i >= 0; i--)
    {
        bool next = x >> i & 1;
        if (!rt->ch[next])
            rt->ch[next] = new Node;
        rt = rt->ch[next];
        rt->size += add;
    }
}
int rank(int x)
{
    x += fix;
    int res = 0;
    Node *rt = root;
    for (int i = full; i >= 0; i--)
    {
        bool next = x >> i & 1;
        if (next)
            res += size(rt->ch[0]);
        if (!rt->ch[next])
            break;
        rt = rt->ch[next];
    }
    return res;
}
int kth(int k)
{
    int res = 0;
    Node *rt = root;
    for (int i = full; i >= 0; i--)
    {
        if (k > size(rt->ch[0]))
        {
            k -= size(rt->ch[0]);
            res |= 1 << i;
            if (!rt->ch[1])
                break;
            rt = rt->ch[1];
        }
        else

            rt = rt->ch[0];
    }
    return res - fix;
}
int main()
{
    // freopen("phs.in", "r", stdin);
    // freopen("phs.out", "w", stdout);
    root=new Node();
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        int op, x;
        scanf("%d%d", &op, &x);
        switch (op)
        {
        case 1:
            Insert(x, 1);
            break;
        case 2:
            Insert(x, -1);
            break;
        case 3:
            printf("%d\n", rank(x) + 1);
            break;
        case 4:
            printf("%d\n", kth(x));
            break;
        case 5:
            printf("%d\n", kth(rank(x)));
            break;
        case 6:
            printf("%d\n", kth(rank(x + 1) + 1));
        }
    }
}