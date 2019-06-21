#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
	int x=0,f=1;char ch=getchar();
	while (ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while (ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
const int MOD = 1e9 + 7;
const int MAXN = 1e6 + 5;
char s[MAXN];
struct PAM
{
    int len[MAXN], fail[MAXN], tr[MAXN][26], Cnt[MAXN], Sum[MAXN];
    int cnt, now, Maxlen;
    PAM() {cnt = 1, fail[0] = fail[1] = 1, len[1] = -1; Maxlen = 0;}
    void clear()
    {
    	memset (len, 0, sizeof (len));
    	memset (fail, 0, sizeof (fail));
    	memset (tr, 0, sizeof (tr));
    	memset (Cnt, 0, sizeof (Cnt));
    	memset (Sum, 0, sizeof (Sum));
    	cnt = 1, fail[0] = fail[1] = 1, len[1] = -1; Maxlen = 0;
    }
    int extend(int c, int pos)
    {
        int p = now;
        while (s[pos - len[p] - 1] != s[pos]) p = fail[p];
        if (!tr[p][c])
        {
            int np = ++cnt, q = fail[p];
            len[np] = len[p] + 2;
            Maxlen = max(Maxlen, len[np]);
            while (s[pos - len[q] - 1] != s[pos]) q = fail[q];
            fail[np] = tr[q][c];
            Cnt[np] = (Cnt[fail[np]] + 1);
            Sum[np] = (Sum[fail[np]] + len[np]);
            tr[p][c] = np;
        }
        now = tr[p][c];
    	return now;
    }
}pam, pram;

int L[MAXN], R[MAXN], id[MAXN];
int main()
{
	int T = read();
	while (T--)
	{
		scanf ("%s", s + 1);
		pam.clear(), pram.clear();
		int n = strlen(s + 1);
		for (int i = 1; i <= n; i++)
			id[i] = pam.extend(s[i], i);
		for (int i = 1; i <= n; i++)
		{
			L[i] = (1ll * pam.Cnt[id[i]] * (i + 1) % MOD - pam.Sum[id[i]]) % MOD;
			
		}
		reverse(s + 1, s + n + 1);
		for (int i = 1; i <= n; i++)
			id[i] = pam.extend(s[i], i);
		for (int i = 1; i <= n; i++)
		{
			R[i] = (1ll * pam.Cnt[id[i]] * (n - i) % MOD + pam.Sum[id[i]]) % MOD;
			// printf ("%d\n", R[i]);
		}
		reverse(R + 1, R + n + 1);
		// for (int i = 1; i <= n; i++)
			// R[i] = n - R[i] + 1;
		int ans = 0;
		for (int i = 1; i < n; i++)
		{
			ans = (ans + 1ll * L[i] * R[i + 1] % MOD) % MOD;
			// printf ("%d %d\n", L[i], R[i + 1]);
		}
		printf ("%d\n", ans);
	}
}
