#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define int long long
const int MOD = 19961993;
const int prime[60]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281};  
const int Inv[60]={9980997,13307996,7984798,11406854,14517814,18426456,9393880,5253157,16490343,8260136,2575742,18343454,3895024,17640832,1698894,3013132,7443456,4581442,9236147,18275065,6562848,2779519,7936697,4037258,6379607,19566707,13566404,4104336,3662752,13602421,16661192,1219054,13259427,9047523,3751248,8196316,14621843,1714528,12192356,11884887,8029406,13455046,17976246,13342473,14084859,15548287,10217514,9846724,5364237,3486812,1627803,14950615,1076789,12406658,19340609,8652728,7791857,7955334,1657495,8808852}; 
const int N = 100000;
long long Sum[(N + 5) << 2], bit[(N + 5) << 2];
#define lch l, m, rt << 1
#define rch m + 1, r, rt << 1 | 1
void Pushup(int rt)
{
    bit[rt] = bit[rt << 1] | bit[rt << 1 | 1];
    Sum[rt] = Sum[rt << 1] * Sum[rt << 1 | 1] % MOD;    
}
void BuildTree(int l, int r, int rt)
{
    if (l == r)
    {
        Sum[rt] = 3;
        bit[rt] |= 2;
        return;
    }
    int m = l + r >> 1;
    BuildTree(lch);
    BuildTree(rch);
    Pushup(rt);
}
void Update(int x, long long a, long long c, int l, int r, int rt)
{
    if (l == r)
    {
        bit[rt] = 0, Sum[rt] = c % MOD;
        for (int i = 0; i < 60; i++)
            if (c % prime[i] == 0)
                bit[rt] ^= (1ll << i);
        return;
    }
    int m = l + r >> 1;
    if (x <= m) Update(x, a, c, lch);
    else Update(x, a, c, rch);
    Pushup(rt);
}
long long ans, p;
void Query(int L, int R, int l, int r, int rt)
{
    if (L <= l && R >= r)
    {
        ans = ans * Sum[rt] % MOD;
        p |= bit[rt];
        return;
    }
    int m = l + r >> 1;
    if (L <= m) Query(L, R, lch);
    if (R > m) Query(L, R, rch);
}
int s[100005];
signed main()
{
    int n;
    for (int i = 1; i <= 100000; i++) s[i] = 3;
    scanf ("%lld", &n);
    BuildTree(1, 100000, 1);
    int a, b, c;
    while (n--)
    {
        scanf ("%lld%lld%lld", &a, &b, &c);
        if (a == 0)
        {
            ans = 1, p = 0;
            Query(b, c, 1, 100000, 1);
            // printf ("%lld : \n", ans);
            for (int i = 0; i < 60; i++)
                if (p & (1ll << i))
                    ans = ans * Inv[i] % MOD;
            printf ("%lld\n", ans);
        }
        else
            Update(b, s[b], c, 1, 100000, 1), s[b] = c;
    }
    // while(1);
}