#include <bits/stdc++.h>
using namespace std;
char s[100];
int main() {
  for (int i = 1; i <= 15; ++i) {
    for (int j = 2; j <= 10; ++j) {
      sprintf (s, "echo \"%d %d \\c\" >>1.txt && echo %d %d |./string-run.out >>1.txt", i, j, i, j);
      system(s);
    }
  }
}
