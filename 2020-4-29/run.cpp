#include <bits/stdc++.h>
using namespace std;
int main() {
  while (1) {
    system("maker >I.in");
    system("II <I.in >I.out");
    if (system("judger <I.out >err.out")) {
      printf ("error\n");
      break;
    } else {
      printf ("OK\n");
    }
  }
}