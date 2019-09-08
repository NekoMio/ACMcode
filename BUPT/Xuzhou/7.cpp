#include <bits/stdc++.h>
using namespace std;
const int MAXN = 3e5 + 5;
struct PAM
{
    int len[MAXN], fail[MAXN], tr[MAXN][26];
    int cnt, now, Maxlen;
    PAM() {cnt = 1, fail[0] = fail[1] = 1, len[1] = -1; Maxlen = 0;}
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
            tr[p][c] = np;
        }
        now = tr[p][c];
        return pos - len[now];
    }
}pam;
int main() {

}