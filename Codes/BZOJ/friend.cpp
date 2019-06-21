/**
******************************************************************************
* @file	Wulala
* @author 	WildRage
* @version v 0.9
* @date 2017-8-10 10:58:12
* @brief 
******************************************************************************
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 100001, M = 301;
int a[N], in[N], n, m;
int Sum[500][305], Change[500];
int block;
int lp[500], rp[500];
int Query(int l, int r)
{
    int L = in[l], R = in[r];
    int ans = 0;
    bool flag = 0;
    if (L == R)
    {
        if (Change[L])
            return r - l;
        for (int i = l + 1; i <= r; i++)
        {
            if (a[i] == a[l])
                ans++;
            a[i] = a[l];
        }
        for (int i = lp[L]; i < l; i++)
            if (a[i] != a[l])
            {
                flag = 1;
                break;
            }
        if (flag == 1)
            return ans;
        for (int i = r + 1; i <= rp[R]; i++)
        {
            if (a[i] != a[l])
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
            Change[L] = a[l];
        return ans;
    }
    else
    {
        if (Change[L] == a[l])
            ans += (rp[L] - l);
        else
        {
            flag = 0;
            for (int i = l + 1; i <= rp[L]; i++)
            {
                if (a[i] == a[l])
                    ans++;
                a[i] = a[l];
            }
            for (int i = lp[L]; i < l; i++)
                if (a[i] != a[l])
                {
                    flag = 1;
                    break;
                }
            if (!flag)
                Change[L] = a[l];
        }
        if (Change[R])
        {
            if (Change[R] == a[l])
                ans += (r - lp[R] + 1);
            else
            {
                for (int i = lp[R]; i <= r; i++)
                    a[i] = a[l];
                Change[R] = 0;
            }
        }
        else
        {
            flag = 0;
            for (int i = lp[R]; i <= r; i++)
            {
                if (a[i] == a[l])
                    ans++;
                a[i] = a[l];
            }
            for (int i = r + 1; i <= rp[R]; i++)
                if (a[i] != a[l])
                {
                    flag = 1;
                    break;
                }
            if (!flag)
                Change[R] = a[l];
        }
        for (int i = L + 1; i < R; i++)
        {
            if (Change[i])
            {
                if (Change[i] == a[l])
                    ans += block;
                else
                {
                    for (int j = lp[i]; j <= rp[i]; j++)
                        a[j] = a[l];
                    Change[i] = a[l];
                }
            }
            else
            {
                for(int j = lp[i];j<=rp[i];j++)
                {
                    if(a[j]==a[l])
                        ans++;
                    a[j] = a[l];
                }
                Change[i] = a[l];
            }
        }
        return ans;
    }
}
int main()
{
    int c, b;
    scanf("%d%d", &n, &m);
    block = 316;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
        in[i] = (i - 1) / block + 1;
        Sum[in[i]][a[i]]++;
    }
    for (int i = 1; i <= in[n]; i++)
        lp[i] = (i - 1) * block + 1, rp[i] = min(n, i * block);
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &c, &b);
        int ans = Query(c, b);
        printf("%d\n", ans);
    }
}