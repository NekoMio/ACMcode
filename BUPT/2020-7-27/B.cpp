#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
const int mod = (ll)(1e9 + 7);
const int maxn = 2e7 + 10;
// O(1)快速乘
inline ll ksc(ll x, ll y, ll p) {
  ll z = (ld)x / p * y;
  ll res = (ull)x * y - (ull)z * p;
  return (res + p) % p;
}
// long long ksc(long long a, long long b, long long z) {
//   return (a * b - (long long)(((long double)a * b + 0.5) / (long double)z) * z + z) % z;
// }
// O(log)快速幂
inline ll ksm(ll x, ll y, ll p) {
  ll res = 1;
  while (y) {
    if (y & 1) res = ksc(res, x, p);
    x = ksc(x, x, p);
    y >>= 1;
  }
  return res;
}
int fz[maxn];
int fm[maxn];
int pow2[maxn];
int rec[maxn];
int n;
void solve() {
  // for(int i=1;i<=30;i++) memset(fz,0,sizeof(fz));
  // cout<<"JJ"<<endl;
  n = 2e7 + 10;
  fz[0] = 1;
  ll p = mod;
  ll tmp = 2;
  for (ll i = 1; i <= n; i++) {
    fz[i] = ksc(fz[i - 1], tmp - 1, p);
    tmp *= 2;
    tmp %= p;
    // fz[i]=pro;
    // fz[i]=ksc(ksm((ll)2,ksc(i,ksc((i-1),ksm(2,(p-2),p),p),p),p),pro,p);
  }
  //	for(int i=1;i<=n;i++) cout<<fz[i]<<" ";
  //	cout<<endl;
  ll tn = ksm((ll)2, p - 2, p);
  pow2[0] = 1;
  for (int i = 1; i <= n; i++) {
    pow2[i] = pow2[i - 1] * tn % p;
  }
  fm[0] = 1; 
  for (ll i = 1; i <= n; i++) {
    fm[i] = ksc(fm[i - 1], pow2[i * (i + 1) / 2 - i * (i - 1) / 2], p);
  }
  //	for(int i=1;i<=n;i++) cout<<fm[i]<<" ";
  //	cout<<endl;
  //	for(ll i=1;i<=n;i++){
  //		fm[i]=ksm(fm[i],p-2,p);
  //	}
  ll ans = 0;
  for (int i = 1; i <= n; i++) {
    ans ^= ksc(fz[i], fm[i], p);
    rec[i] = ans;
  }
  int t;
  // printf ("Ready");
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    printf("%d\n", rec[n]);
  }
}
int main() { solve(); }