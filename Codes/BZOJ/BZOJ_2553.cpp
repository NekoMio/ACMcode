#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
int alphabet, Idx;
struct Trie_Node
{
    bool flag;
    int Id;
    Trie_Node *ch[27], *fail;
    Trie_Node()
    {
        flag = 0;
        Id = ++Idx;
        fail = NULL;
        memset(ch, 0, sizeof(ch));
    }
} * root, *point[100];
struct Matrix
{
    int n;
    long double a[100][100];
    Matrix(int b = 0)
    {
        n = b;
        memset(a, 0, sizeof(a));
    }
    Matrix operator*(const Matrix &b) const
    {
        Matrix ans(n);
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                for (int k = 1; k <= n; k++)
                    ans.a[i][j] += a[i][k] * b.a[k][j];
        return ans;
    }
    Matrix operator^(const int &k) const
    {
        Matrix a = *this, ans(n);
        for (int i = 1; i <= n; i++)
            ans.a[i][i] = 1;
        int b = k;
        while (b)
        {
            if (b & 1)
                ans = a * ans;
            b >>= 1;
            a = a * a;
        }
        return ans;
    }
};
void Insert(const char *s)
{
    Trie_Node *rt = root;
    int len = strlen(s);
    for (int i = 0; i < len; i++)
    {
        if (rt->ch[s[i] - 'a'] == NULL)
        {
            rt->ch[s[i] - 'a'] = new Trie_Node();
            point[Idx] = rt->ch[s[i] - 'a'];
        }
        else if (rt->ch[s[i] - 'a']->flag)
            return;
        rt = rt->ch[s[i] - 'a'];
    }
    rt->flag = 1;
}
queue<Trie_Node *> Q;
void Get_fail()
{
    for (int i = 0; i < alphabet; i++)
    {
        if (root->ch[i] != NULL)
        {
            root->ch[i]->fail = root;
            Q.push(root->ch[i]);
        }
    }
    while (!Q.empty())
    {
        Trie_Node *rt = Q.front();
        Q.pop();
        Trie_Node *p = NULL;
        for (int i = 0; i < alphabet; i++)
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
                Q.push(rt->ch[i]);
            }
            if (rt->ch[i] == NULL)
                rt->ch[i] = rt->fail->ch[i];
        }
    }
}
Matrix A;
long double P;
void Build()
{
    for (int i = 1; i <= Idx; i++)
        if (!point[i]->flag)
            for (int j = 0; j < alphabet; j++)
                if (point[i]->ch[j])
                    if (point[i]->ch[j]->flag)
                        A.a[i][Idx + 1] += P, A.a[i][1] += P;
                    else
                        A.a[i][point[i]->ch[j]->Id] += P;
                else
                    A.a[i][1] += P;
    A.a[Idx + 1][Idx + 1] = 1;
}
int main()
{
    root = new Trie_Node();
    point[1] = root;
    static char s[20];
    int n, len;
    scanf("%d%d%d", &n, &len, &alphabet);
    P = 1. / alphabet;
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", s);
        Insert(s);
    }
    Get_fail();
    //printf("1\n");
    A.n = Idx + 1;
    Build();
    A = A ^ len;
    printf("%.9lf", (double)A.a[1][Idx + 1]);
    //while (1);
}
