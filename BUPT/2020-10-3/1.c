#include <stdio.h>
#include <string.h>
// using namespace std;
char Map[1001][1001], tmp[1004];
int main() {
  int n;
  scanf ("%d", &n);
  getchar();
  gets(tmp);
  int len = strlen(tmp);
  int cnt = 1;
  for (int i = 0, j = 1; i < len; i++) {
    Map[cnt][j] = tmp[i];
    if (i == len - 1) break; 
    j++;
    if (j == n + 1) j = 1, cnt++;
  }
  for (int j = 1; j <= n; j++) {
    for (int i = cnt; i >= 1; i--) {
      printf ("%c", Map[i][j] ? Map[i][j] : ' ');
    }
    printf ("\n");
  }
}