#include <cstdio>
using namespace std;
const int full = 31, fix = 0x3f3f3f3f;
class Trie
{
  public:
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
    } * root;
    Trie()
    {
        root = new Node();
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
} root;
void Init()
{
    root.Insert(-0x3f3f3f3f, 1);
    root.Insert(+0x3f3f3f3f, 1);
}
int main()
{
    freopen("tb_kp.in", "r", stdin);
    freopen("tb_kp.out", "w", stdout);
    int n;
    scanf("%d", &n);
    Init();
    int t = 0;
    for (int i = 1; i <= n; i++)
    {
        int op, x;
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            scanf("%d", &x);
            t++;
            root.Insert(x, 1);
            break;
        case 2:
            scanf("%d", &x);
            t--;
            root.Insert(x, -1);
            break;
        case 3:
            scanf("%d", &x);
            printf("%d\n", root.rank(x));
            break;
        case 4:
            scanf("%d", &x);
            printf("%d\n", root.kth(x + 1));
            break;
        case 5:
            scanf("%d", &x);
            printf("%d\n", root.kth(root.rank(x)));
            break;
        case 6:
            scanf("%d", &x);
            printf("%d\n", root.kth(root.rank(x + 1) + 1));
            break;
        case 7:
            printf("%d\n", root.kth(2));
            break;
        case 8:
            printf("%d\n", root.kth(t + 1));
        }
    }
    //while(1);
}