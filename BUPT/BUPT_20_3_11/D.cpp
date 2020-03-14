#include <cstdio>
#include <cstring>
int a, b, c, d, e, f, g, i, m, n;
char x[10000] = {0};

int cl() {
  if (x[b - 1] == 'a') {
    printf("%ss\n", x);
    return 0;
  }
  if (x[b - 1] == 'i') {
    printf("%sos\n", x);
    return 0;
  }
  if (x[b - 1] == 'y') {
    x[b - 1] = 'i';
    printf("%sos\n", x);
    return 0;
  }
  if (x[b - 1] == 'l') {
    printf("%ses\n", x);
    return 0;
  }
  if (x[b - 1] == 'n') {
    x[b - 1] = 'a';
    printf("%snes\n", x);
    return 0;
  }
  if ((x[b - 2] == 'n') && (x[b - 1] == 'e')) {
    x[b - 2] = 'a';
    x[b - 1] = 'n';
    printf("%ses\n", x);
    return 0;
  }
  if (x[b - 1] == 'o') {
    printf("%ss\n", x);
    return 0;
  }
  if (x[b - 1] == 'r') {
    printf("%ses\n", x);
    return 0;
  }
  if (x[b - 1] == 't') {
    printf("%sas\n", x);
    return 0;
  }
  if (x[b - 1] == 'u') {
    printf("%ss\n", x);
    return 0;
  }
  if (x[b - 1] == 'v') {
    printf("%ses\n", x);
    return 0;
  }
  if (x[b - 1] == 'w') {
    printf("%sas\n", x);
    return 0;
  }
  printf("%sus\n", x);
}

int main() {
  scanf("%d", &a);
  for (i = 1; i <= a; i++) {
    scanf("%s", &x);
    b = strlen(x);
    cl();
  }
}