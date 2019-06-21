#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
int Index;
const int MOD = 1e9 + 7;
long long f[1505][1505][3];
struct Node
{
    Node *ch[10], *fail;
    bool flag;
    int ID;
    Node() 
    {
        ID = ++Index;
        flag = 0;
        memset (ch, 0, sizeof (ch));
        fail = NULL;
    }
}*root, *head[1505];
void Insert(char *s)
{
    int n = strlen(s);
    Node *rt = root;
    for (int i = 0; i < n; i++)
    {
        if (rt->ch[s[i] - '0'] == NULL)
            rt->ch[s[i] - '0'] = new Node(), head[Index] = rt->ch[s[i] - '0'];
        rt = rt->ch[s[i] - '0'];
    }
    rt->flag = 1;
}
void Get_fail()
{
    queue<Node*> Q;
    for (int i = 0; i <= 9; i++)
        if (root->ch[i])
        {
            Q.push(root->ch[i]);
            root->ch[i]->fail = root;
        }
    while (!Q.empty())
    {
        Node *rt = Q.front();
        rt->flag |= rt->fail->flag;
        Q.pop();
        Node *p = NULL;
        for (int i = 0; i <= 9; i++)
        {
            if(rt->ch[i] != NULL)
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
                Q.push(rt->ch[i]);
            }
            if(rt->ch[i] == NULL)
                rt->ch[i] = rt->fail->ch[i];
        }
    }
}
char N[1205], s[1505];
int m;
int main()
{
    root = new Node();
    head[Index] = root;
    scanf ("%s", N + 1);
    int n = strlen(N + 1);
    for (int i = 1; i <= n; i++)
        N[i] -= '0';
    scanf ("%d", &m);
    while (m--) 
    {
        scanf ("%s", s);
        Insert(s);
    }
    Get_fail();
    for (int i = 1; i <= 9; i++)
    {
        if (!root->ch[i]) root->ch[i] = root;
        if (!root->ch[i]->flag) 
            f[1][root->ch[i]->ID][0]++;
    }
    for (int i = 1; i <= n - 2; i++)
    {
        for (int j = 1; j <= Index; j++)
        {
            Node *rt = head[j];
            for (int k = 0; k <= 9; k++)
            {
                if (!rt->ch[k]) rt->ch[k] = root;
                if (!rt->ch[k]->flag) (f[i + 1][rt->ch[k]->ID][0] += f[i][j][0]) %= MOD;
            }
        }
    }
    long long ans = 0;
    for (int i = 1; i <= n - 1; i++)
        for (int j = 1; j <= Index; j++)
            (ans += f[i][j][0]) %= MOD;
    memset(f, 0, sizeof (f));
    for (int i = 1; i <= N[1]; i++)
    {
        if (!root->ch[i]) root->ch[i] = root;
        if (!root->ch[i]->flag) 
            f[1][root->ch[i]->ID][(N[1] == i)]++;
    }
    for (int i = 1; i <= n - 1; i++)
    {
        for (int j = 1; j <= Index; j++)
        {
            Node *rt = head[j];
            for (int k = 0; k <= 9; k++)
            {
                if (!rt->ch[k]) rt->ch[k] = root;
                if (rt->ch[k]->flag) continue;
                (f[i + 1][rt->ch[k]->ID][0] += f[i][j][0]) %= MOD;
                if (k < N[i + 1]) (f[i + 1][rt->ch[k]->ID][0] += f[i][j][1]) %= MOD;
                if (k == N[i + 1]) (f[i + 1][rt->ch[k]->ID][1] += f[i][j][1]) %= MOD;
            }
        }
    }
    for (int i = 1; i <= Index; i++) (ans += f[n][i][0]) %= MOD, (ans += f[n][i][1]) %= MOD;
    printf("%lld",ans);
    // while (1);
}