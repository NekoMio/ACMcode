#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
int f[100005], a[100005];
vector<int> ch[100005];
int S;
void DFS(int x,int D)
{
    if(D&1) S^=a[x];
    for(auto i:ch[x])
    {
        DFS(i,D+1);
    }
}
int main(int argc, char const *argv[])
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            ch[i].clear();
        for (int i = 1; i <= n - 1; i++)
        {
            scanf("%d", &f[i]);
            ch[f[i]].push_back(i);
        }
        for (int i = 0; i <= n - 1; i++)
        {
            scanf("%d", &a[i]);
        }
        S = 0;
        DFS(0,0);
        if(S)
            printf("win\n");
        else 
            printf("lose\n");
    }
    //while(1);
    return 0;
}
