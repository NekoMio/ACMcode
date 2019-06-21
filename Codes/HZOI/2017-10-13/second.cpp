#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
struct edge
{
    int END, next;
}v[200005];
int first[100005], p;
int size[100005];
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
bool notroot[100005];
void DFS(int rt)
{
    size[rt] = 1;
    for (int i = first[rt]; i != -1; i = v[i].next)
    {
        DFS(v[i].END);
        size[rt] += size[v[i].END];
    }
}
unsigned long long base = 31;
map<unsigned long long, int> Hash;
unsigned long long Get_Hash(int m)
{
    unsigned long long ans = 0;
    for (int i = 1; i <= m; i++)
        ans = ans * base + size[i];
    return ans;
}
int main()
{
    int n, m, q, a, b;
    scanf ("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n; i++)
    {
        memset(notroot, 0, sizeof (notroot[0]) * (m + 2));
        memset(first, -1, sizeof (first[0]) * (m + 2));
        memset(size, 0, sizeof (size[0]) * (m + 2));
        p = 0;
        for (int j = 1; j < m; j++)
        {
            scanf ("%d%d", &a, &b);
            add(a, b);
            notroot[b] = 1;
        }
        int root = 1;
        for (int j = 1; j <= m; j++)
            if (!notroot[j])
            { 
                root = j;
                break;  
            }
        DFS(root);
        sort(size + 1, size + m + 1);
        Hash[Get_Hash(m)]++;
    }
    while (q--)
    {
        memset(notroot, 0, sizeof (notroot[0]) * (m + 2));
        memset(first, -1, sizeof (first[0]) * (m + 2));
        memset(size, 0, sizeof (size[0]) * (m + 2));
        p = 0;
        for (int j = 1; j < m; j++)
        {
            scanf ("%d%d", &a, &b);
            add(a, b);
            notroot[b] = 1;
        }
        int root = 1;
        for (int j = 1; j <= m; j++)
            if (!notroot[j])
            { 
                root = j;
                break;  
            }
        DFS(root);
        sort(size + 1, size + m + 1);
        printf ("%d\n", Hash[Get_Hash(m)]);
    }
    // while (1);
}