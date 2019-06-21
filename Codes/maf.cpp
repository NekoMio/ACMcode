#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
int a[1000005], Maxn, t, Min, Max;
int times[1000005];
bool die[1000005], nodie[1000005];
int Q[1000005];
int main()
{
    //freopen("maf.in", "r", stdin);
    //freopen("maf.out", "w", stdout);
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        times[a[i]]++;
    }
    //Q.resize(1000001);
    for (int i = 1; i <= n; i++)
    {
        if (!times[i])
        {
            Max++;
            Q[++Min] = i;
        }
    }
    //printf("%d\n",Max);

    //for (vector<int>::iterator it = Q.begin(); it != Q.end(); it++)
    for (int i = 1; i <= Min; i++)
    {
        //printf("%d---------%d=======\n",it-Q.begin(),*it);
        int k = a[Q[i]];
        if (die[k])
            continue;
        die[k] = 1;
        nodie[a[k]] = 1;
        --times[a[k]];
        if (!times[a[k]])
        {
            Q[++Min]=a[k]; 
        }
    }
    int sum;
    bool All_NoDied;
    for (int i = 1; i <= n; i++)
    {
        if (times[i] && !die[i])
        {
            sum = 0;
            All_NoDied = 0;
            for (int j = i; !die[j]; j = a[j])
            {
                die[j] = 1;
                sum++;
                All_NoDied |= nodie[j];
            }
            if (!All_NoDied && sum > 1)
                Max++;
            Min += sum / 2;
        }
    }
    printf("%d %d\n", n - Min, n - Max);
}