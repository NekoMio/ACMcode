#include <cstdio>
#include <cstring>

int a, b, c, d, e, f, g, i, m, n;
char x[1000];

int main() {
  // freopen("1.in","r",stdin);
  // freopen("1.out","w",stdout);
  scanf("%d", &a);
  for (n = 1; n <= a; n++) {
    scanf("%s", x);
    b = strlen(x);
    i = 0;
    while ((i < b) && (x[i] == 'y')) i++;
    if (x[i] == 'z') x[i] = 'b';
    printf("%s\n", x);
  }
}