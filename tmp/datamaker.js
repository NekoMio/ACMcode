
function isprime(x) {
  for (let i = 2; i * i <= x; i++) {
    if (x % i == 0) return 0;
  }
  return 1;
}
var t = 3;
var n = 100000, m = 100000;
var MOD = 1000000;
while (t--) {
  s = "";
  for (let i = 1; i <= n; i++) s = s + " " + Math.random() % MOD + 1;
  console.log(s);
  s = "";
  for (var i = 1; i <= m; i++) {
    var l = Math.random() % n + 1, r = Math.random() % n + 1;
    if (l > r) {
      tmp = l;
      l = r;
      r = tmp;
    }
    console.log(`${l} ${r} ${Math.random() % MOD + 1} ${Math.min(r - l + 1, 169)}`);
  }
}