#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <list>
#include <queue>
using namespace std;
// class Node
// {
//   public:
//     int s, key, v;
//     Node *ch[2];
//     Node(int x)
//     {
//         v = x;
//         key = rand();
//         s = 1;
//         ch[0] = ch[1] = NULL;
//     }
// #define Size(_) ((_) ? (_)->s : 0)
//     void Pushup()
//     {
//         s = Size(ch[0]) + Size(ch[1]) + 1;
//     }
// };
// Node *Merge(Node *A, Node *B)
// {
//     if (!A)
//         return B;
//     if (!B)
//         return A;
//     if (A->key > B->key)
//     {
//         A->ch[1] = Merge(A->ch[1], B);
//         A->Pushup();
//         return A;
//     }
//     else
//     {
//         B->ch[0] = Merge(A, B->ch[0]);
//         B->Pushup();
//         return B;
//     }
// }
// Node *rt[100005];
struct edge
{
    int END, next;
} v[2000005 << 1];
bool unable[100005];
// int father[100005];
// int find(int x)
// {
//     if (father[x] != x)
//         father[x] = find(father[x]);
//     return father[x];
// }
int first[100005], p;
void add(int a, int b)
{
    v[p].END = b;
    v[p].next = first[a];
    first[a] = p++;
}
// int comp(Node *A, Node *B)
// {
//     return Size(A) < Size(B);
// }
// class list_node
// {
//   public:
//     list_node *next, *last;
//     int v;
//     list_node(int i)
//     {
//         v = i;
//         last = NULL;
//     }
// } * head;
// void insert(list_node *hd, int i){
//     while(hd->last) hd=hd->last;
//     hd->last=new list_node(i);
//     hd->last->next=hd;
// }
list<int> ls;
bool vis[100005];
int in[100005],n;
int ans = 0, size[100005];
void bfs(int x)
{
    queue<int> Q;
    Q.push(x);
    in[x]=ans;
    //size[ans]=1;
    while (!Q.empty())
    {
        int k = Q.front();
        Q.pop();
       // in[k] = ans;
        //size[ans]++;
        memset(vis, 1, sizeof(vis[0]) * n + 1);
        for (int i = first[k]; i != -1; i = v[i].next)
        {
            vis[v[i].END] = 0;
        }
        list<int>::iterator s;
        for (list<int>::iterator it = ls.begin(); it != ls.end(); it=s)
        {
            s=it;
            s++;
            if (vis[*it])
            {
                Q.push(*it);
                in[*it] = ans;
                ls.erase(it);
                size[ans]++;
            }
        }
    }
}
// vector<Node *> ans;
int main()
{
    // freopen("biu.in", "r", stdin);
    // freopen("biu.out", "w", stdout);
    srand(0);
    int m;
    memset(first, -1, sizeof(first));
    scanf("%d%d", &n, &m);
    // for (int i = 1; i <= n; i++)
    //     rt[i] = new Node(i);
    // for (int i = 1; i <= n; i++)
    //     father[i] = i;
    int a, b;
    while (m--)
    {
        scanf("%d%d", &a, &b);
        add(a, b);
        add(b, a);
    }
    for (int i = 1; i <= n; i++)
    {
        ls.push_back(i);
    }
    for (int i = 1; i <= n; i++)
    {
        if (in[i])
            continue;
        ans++;
        bfs(i);
    }
    printf("%d\n", ans);
    sort(size + 1, size + ans + 1);
    for (int i = 1; i <= ans; i++)
        printf("%d ", size[i]);
    // for (int i = 1; i <= n; i++)
    // {
    //     memset(vis, 0, sizeof(vis[0]) * n + 1);
    //     for (int j = first[i]; j != -1; j = v[j].next)
    //     {
    //         vis[v[j].END] = 1;
    //     }
    //     for (int j = 1; j <= n; j++)
    //     {
    //         if (!vis[j])
    //         {
    //             if (find(i) != find(j))
    //             {
    //                 rt[find(i)] = Merge(rt[find(i)], rt[find(j)]);
    //                 unable[find(j)] = 1;
    //                 father[find(j)] = i;
    //             }
    //         }
    //     }
    // }
    // for (int i = 1; i <= n; i++)
    // {
    //     if (!unable[i])
    //         ans.push_back(rt[i]);
    // }
    // printf("%d\n", ans.size());
    // sort(ans.begin(), ans.end(), comp);
    // for (vector<Node *>::iterator i = ans.begin(); i != ans.end(); i++)
    // {
    //     printf("%d ", Size((*i)));
    // }
    //while(1);
}
