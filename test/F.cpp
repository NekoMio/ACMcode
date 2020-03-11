#include <bits/stdc++.h>
using namespace std;
char s[10005];
int type[10005], len;
int Type(char x) {
  if (x >= 'a' && x <= 'z') {
    return 1;
  } else if (x == '(') {
    return 2;
  } else if (x == ')') {
    return 3;
  } else {
    return 0;
  }
}
// int a;
// int x = a + () + a; 
bool Judge1() {
  int pre = 0;
  int num2 = 0, num3 = 0;
  for (int i = 1; i <= len; i++) type[i] = Type(s[i]);
  for (int i = 1; i <= len; i++) {
    if (type[i] != 2 && type[i] != 3) {
      if (type[i] == pre) 
        return 0;
      pre = type[i];
    }
    if (type[i] == 2) {
      num2++;
      if (type[i + 1] == 0 || type[i + 1] == 3) return 0;
      if (type[i - 1] == 1 || type[i - 1] == 3) return 0;
    }
    if (type[i] == 3) {
      num3++;
      if (type[i - 1] == 0 || type[i - 1] == 2) return 0;
      if (type[i + 1] == 1 || type[i + 1] == 2) return 0;
    }
    // printf ("%d %d\n", num2, num3);
    if (num3 > num2) return 0;
  }
  if (pre == 0) return 0;
  if (num2 != num3) return 0;
  return 1;
}
int st[10005], num[10005];
bool Judge2() {
  int top = 0;
  type[0] = 2, type[len] = 3;
  for (int i = 0; i <= len; i++) {
    if (type[i] == 2) {
      top++;
    }
    if (type[i] == 0) {
      st[top]++;
    }
    if (type[i] == 3) {
      if (st[top] != 1) return 0;
      st[top] = 0;
      top--;
    }
  }
  return 1;
}
int main() {
  fgets(s + 1, 1002, stdin);
  len = strlen(s + 1);
  s[len] = '\0';
  len--;
  int j = 1;
  for (int i = 1; i <= len; i++) {
    if (s[i] != ' ') {
      s[j] = s[i];
      j++;
    }
  }
  s[j] = '\0';
  len = j - 1;
  if (!Judge1()) {
    printf ("error\n");
  } else { 
    len++;
    s[len] = ')';
    s[0] = '(';
    if (Judge2()) {
      printf ("proper\n");
    } else {
      printf ("improper\n");
    }
  }
} 