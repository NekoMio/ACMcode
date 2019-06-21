#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
const int MOD = 1e9 + 7;
int Index;
long long pow_mod(long long a, int b)
{
    long long ans = 1;
    while (b)
    {
        if (b & 1) ans = ans * a % MOD;
        b >>= 1;
        a = a * a % MOD;
    }
    return ans;
}
long long a[200][200];
void gauss(int n)
{
    for (int i = 1; i <= n; i++)
    {
        int t = pow_mod(a[i][i], MOD - 2);
        for (int j = 1; j <= n + 1; j++)
            a[i][j] = a[i][j] * t % MOD;
        for (int j = 1; j <= n; j++)
        {
            if (j != i)
            {
                int t = a[j][i];
                for (int k = i; k <= n + 1; k++)
                    a[j][k] = (a[j][k] - a[i][k] * t % MOD + MOD) % MOD;
            }
        }
    }
}
const int MAXN = 20;
bool vis[200];
struct Trie
{
    struct Node
    {
        Node *ch[26], *fail;
        int id;
        Node()
        {
            memset (ch, 0, sizeof (ch));
            fail = NULL;
            id = ++Index;
        }
    }*root, *END, *Q[205];
    Trie()
    {
        root = new Node();
        Q[root->id] = root;
        END = new Node();
        Q[END->id]  = END;
    }
    void reset()
    {
        Index = 0;
        root = new Node();
        Q[root->id] = root;
        END = new Node();
        Q[END->id] = END;
    }
    void Insert(char *s, int m)
    {
        Node *rt = root;
        for (int i = 1; i < m; i++)
        {
            if (rt->ch[s[i] - 'a'] == NULL)
            {
                rt->ch[s[i] - 'a'] = new Node();
                Q[rt->ch[s[i] - 'a']->id] = rt->ch[s[i] - 'a'];
                // du[rt->ch[s[i] - 'a']->id] = 1;
            }
            if (rt->ch[s[i] - 'a'] == END) return; 
            rt = rt->ch[s[i] - 'a'];
        }
        rt->ch[s[m] - 'a'] = END;
    }
    void Get_fail()
    {
        queue<Node*> Q;
        for (int i = 0; i < 26; i++)
        {
            if (root->ch[i] != NULL)
            {
                root->ch[i]->fail = root;
                Q.push(root->ch[i]);
                vis[root->ch[i]->id] = 1;
            }
            else
                root->ch[i] = root;
        }
        while (!Q.empty())
        {
            Node *rt = Q.front(); Q.pop();
            // if (rt == END) continue;
            Node *p = NULL;
            for (int i = 0; i < 26; i++)
            {
                if (rt->ch[i] != NULL)
                {
                    p = rt->fail;
                    while (p != NULL)
                    {
                        if (p->ch[i] != NULL)
                        {
                            rt->ch[i]->fail = p->ch[i];
                            break;
                        }
                        p = p->fail;
                    }
                    if (p == NULL)
                        rt->ch[i]->fail = root;
                    if (!vis[rt->ch[i]->id])
                    {
                        Q.push(rt->ch[i]);
                        vis[rt->ch[i]->id] = 1;
                    }
                }
                if (rt->ch[i] == NULL)
                    rt->ch[i] = rt->fail->ch[i];
            }
        }
    }
}root;
char s[MAXN];
int main()
{
    int T = read();
    while (T--)
    {
        memset (a, 0, sizeof (a));
        root.reset();
        int n = read();
        memset (vis, 0, sizeof (vis));
        for (int i = 1; i <= n; i++)
        {
            scanf ("%s", s + 1);
            root.Insert(s, strlen(s + 1));
        }
        root.Get_fail();
        long long Inv = pow_mod(26, MOD - 2);
        // a[1][Index + 1] = MOD - 1;
        for (int i = 1; i <= Index; i++)
        {
            a[i][i] += 1;
            if (i != 2) a[i][Index + 1] = 1;
            for (int j = 0; j < 26; j++)
            {
                if (root.Q[i]->ch[j]->id == 2) continue;
                a[i][root.Q[i]->ch[j]->id] = (a[i][root.Q[i]->ch[j]->id] - Inv + MOD) % MOD;
                // a[i][Index + 1] = (a[i][Index + 1] - Inv + MOD) % MOD;
            }
        }
        gauss(Index);
        printf ("%d\n", a[1][Index + 1]);
    }
}