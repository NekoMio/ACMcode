#include <bits/stdc++.h>
using namespace std;
inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
char A[505], B[505];
const int MOD = 1024523;
int f[505][505][505];
int main() {
    // freopen ("ballb.in", "r", stdin);
    // freopen ("ballb.out", "w", stdout);
    int n = read(), m = read();
    scanf ("%s", A + 1);
    scanf ("%s", B + 1);
    f[0][0][0] = 1;
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            for (int k = 0; k <= m; ++k) if (f[i][k][j]) {
                int l = i + k - j;
                if (A[i + 1] == A[j + 1]) {
                    f[i + 1][k][j + 1] = (f[i + 1][k][j + 1] + f[i][k][j]) % MOD;
                }
                if (A[i + 1] == B[l + 1]) {
                    f[i + 1][k][j] = (f[i + 1][k][j] + f[i][k][j]) % MOD;
                }
                if (B[k + 1] == A[j + 1]) {
                    f[i][k + 1][j + 1] = (f[i][k + 1][j + 1] + f[i][k][j]) % MOD;
                }
                if (B[k + 1] == B[l + 1]) {
                    f[i][k + 1][j] = (f[i][k + 1][j] + f[i][k][j]) % MOD;
                }
            }
        }
    }
    printf ("%d\n", f[n][m][n]);
}