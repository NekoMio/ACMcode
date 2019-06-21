var isnprime = [];
var prime = [], cnt = 0;
const MAXN = 10000000;
for (var i = 1; i <= MAXN; ++i) isnprime[i] = 0;
isnprime[1] = 1;
for (var i = 2; i <= MAXN; ++i) {
  if (!isnprime[i]) prime[++cnt] = i;
  for (var j = 1; j <= cnt; ++j) {
    if (i * prime[j] > MAXN) break;
    isnprime[i * prime[j]] = 1;
    if (i % prime[j] == 0) break;
  }
}
for (var i in prime) {
  console.log(prime[i]);
}
