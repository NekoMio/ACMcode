#include <cstring>
#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;
const int INF = 1000000000;
const int full = 30;
int n;
struct data
{
    int val, i;
    bool operator < (const data &a) const
    {
        return val > a.val;
    }
}a[50005];
struct Trie
{
    struct Node
    {
        int s;
        Node *ch[2];
        Node()
        {
            ch[0] = ch[1] = NULL;
            s = 0;
        }
    }*root[100005], *null;
    Trie()
    {
        null = new Node();
        null->ch[0] = null->ch[1] = null;
        root[0] = new Node();
        root[0]->ch[0] = root[0]->ch[1] = null;
    }
    Node *NewNode()
    {
        Node *rt = new Node();
        rt->ch[0] = rt->ch[1] = null;
        return rt;
    }
    void copy(Node *&a, Node *b)
    {
        if (b == null)
            a = null;
        else
            a = NewNode(), *a = *b;
    }
    void insert(int x, int cnt)
    {
        copy(root[cnt], root[cnt - 1]);
        Node *rt1 = root[cnt], *rt2 = root[cnt - 1];
        for (int i = full; i >= 0; i--)
        {
            int k = (x >> i) & 1;
            copy(rt1->ch[k], rt2->ch[k]);
            if (rt1->ch[k] == null)
                rt1->ch[k] = NewNode();
            rt1 = rt1->ch[k], rt2 = rt2->ch[k];
            rt1->s++;
        }
    }
    int Query(int val, int l, int r)
    {
        int res = 0;
        Node *rt1 = root[r], *rt2 = root[l - 1];
        for (int i = full; i >= 0; i--)
        {
            int next = (val >> i) & 1;
            if (rt1->ch[next ^ 1]->s - rt2->ch[next ^ 1]->s)
            {
                rt1 = rt1->ch[next ^ 1], rt2 = rt2->ch[next ^ 1];
                res |= (1 << i);
            }
            else
            {
                rt1 = rt1->ch[next], rt2 = rt2->ch[next];
            }
        }
        return res;
    }
}root;
set<int> st;
int main()
{
    scanf ("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf ("%d", &a[i].val);
        a[i].i = i;
        root.insert(a[i].val, i);
    }
    st.insert(-1), st.insert(INF), st.insert(-2), st.insert(INF + 1);
    sort(a + 1, a + n + 1);
    st.insert(a[1].i);
    int ans = 0;
    for (int i = 2; i <= n; i++)
    {
        int l = a[i].i, r = a[i].i;
        set<int>::iterator T, P;
        P = st.lower_bound(a[i].i);
        T = P;
        r = *T; T++;
        r = *T - 1;
        l = *--P; P--; l = *P + 1;
        l = max(1, l), r = min(r, n);
        if (l != r) ans = max(ans, root.Query(a[i].val, l, r));
        st.insert(a[i].i);
    }
    printf ("%d", ans);
}