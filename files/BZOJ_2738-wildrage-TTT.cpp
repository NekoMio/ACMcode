#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int full = 31;
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
    void insert(int x, int add)
    {
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
        return res;
    }
} root;
int a[505][505];
int in[505][505], block = 20, m, n, q;
struct Query
{
    int x1, y1, x2, y2, k, ID;
    bool operator < (const Query &b) const
    {
        return in[x1][y1] == in[b.x1][b.y1] ? x2 * n + y2 > b.x2 * n + b.y2 : in[x1][y1] < in[b.x1][b.y1];
    } 
}Q[60006];
void Remove1(int x_1, int y_1, int y_2)
{
    for (int i = y_1; i <= y_2; i++)
        root.insert(a[x_1][i], -1);
}
void Remove2(int y_1, int x_1, int x_2)
{
    for (int i = x_1; i <= x_2; i++)
        root.insert(a[i][y_1], -1);
}
void Add1(int x_1, int y_1, int y_2)
{
    for (int i = y_1; i <= y_2; i++)
        root.insert(a[x_1][i], 1);
}
void Add2(int y_1, int x_1, int x_2)
{
    for (int i = x_1; i <= x_2; i++)
        root.insert(a[i][y_1], 1);
}
int ans[60005];
int main()
{
    scanf("%d%d", &n, &q);
    m = n / block + 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            scanf("%d", &a[i][j]);
            root.insert(a[i][j], 1);
            in[i][j] = ((i - 1) / block + 1) * m + (j - 1) / block + 1;
        }
    }
    for (int i = 1; i <= q; i++)
        scanf("%d%d%d%d%d", &Q[i].x1, &Q[i].y1, &Q[i].x2, &Q[i].y2, &Q[i].k), Q[i].ID = i;
    sort(Q + 1, Q + q + 1);
    int x_1 = 1, x_2 = n, y_1 = 1, y_2 = n;
    for (int i = 1; i <= q; i++)
    {
        while (x_1 < Q[i].x1) {Remove1(x_1, y_1, y_2), x_1++;}
        while (x_1 > Q[i].x1) {x_1--; Add1(x_1, y_1, y_2);}
        while (x_2 > Q[i].x2) {Remove1(x_2, y_1, y_2), x_2--;}
        while (x_2 < Q[i].x2) {x_2++; Add1(x_2, y_1, y_2);}
        while (y_1 < Q[i].y1) {Remove2(y_1, x_1, x_2), y_1++;}
        while (y_1 > Q[i].y1) {y_1--; Add2(y_1, x_1, x_2);}
        while (y_2 > Q[i].y2) {Remove2(y_2, x_1, x_2), y_2--;}
        while (y_2 < Q[i].y2) {y_2++; Add2(y_2, x_1, x_2);}
        ans[Q[i].ID] = root.kth(Q[i].k);
    }
    for (int i = 1; i <= q; i++)
        printf("%d\n", ans[i]);
    // while(1);
}