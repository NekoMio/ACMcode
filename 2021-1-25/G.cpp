#include <bits/stdc++.h>
using namespace std;
char s[100];
int Map[100][100];
void printMap() {
  printf ("------\n");
  for (int i = 1; i <= 3; i++) {
    for (int j = 1; j <= 3; j++) {
      if (Map[i][j] == 0) {
        printf ("  ");
      }
      if (Map[i][j] == 1) {
        printf ("X ");
      }
      if (Map[i][j] == -1) {
        printf ("O ");
      }
    }
    printf ("\n");
  }
  printf ("------\n");
}
int out(int x, int y) {
  cout << x << " " << y << endl;
  Map[x][y] = 1;
  cout.flush();
  // printMap();
}
int lose() {
  for (int i = 1; i <= 3; i++) {
    int Sum = 0;
    for (int j = 1; j <= 3; j++) {
      Sum += Map[i][j];
    }
    if (Sum == -3) return 1;
  }
  for (int j = 1; j <= 3; j++) {
    int Sum = 0;
    for (int i = 1; i <= 3; i++) {
      Sum += Map[i][j];
    }
    if (Sum == -3) return 1;
  }
  int Sum = 0;
  for (int i = 1; i <= 3; i++) {
    Sum += Map[i][i];
  }
  if (Sum == -3) return 1;
  Sum = 0;
  for (int i = 1; i <= 3; i++) {
    Sum += Map[i][3 - i + 1];
  }
  if (Sum == -3) return 1;
  return 1;
}
int in(int &x, int &y) {
  cin >> x >> y;
  if (x <= 0 || x >= 4 || y <= 0 || y >= 4) {
    cin >> s;
    exit(0);
  }
  if (Map[x][y] != 0) {
    cin >> s;
    exit(0);
  }
  Map[x][y] = -1;
  if (lose()) {
    exit(0);
  }
  // printMap();
}
int findoo(int &x, int &y) {
  for (int i = 1; i <= 3; i++) {
    int Sum = 0;
    for (int j = 1; j <= 3; j++) {
      Sum += Map[i][j];
    }
    if (Sum == -2) {
      for (int j = 1; j <= 3; j++) {
        if (Map[i][j] == 0) {
          x = i, y = j;
          return 1;
        }
      }
    }
  }
  for (int j = 1; j <= 3; j++) {
    int Sum = 0;
    for (int i = 1; i <= 3; i++) {
      Sum += Map[i][j];
    }
    if (Sum == -2) {
      for (int i = 1; i <= 3; i++) {
        if (Map[i][j] == 0) {
          x = i, y = j;
          return 1;
        }
      }
    }
  }
  int Sum = 0;
  for (int i = 1; i <= 3; i++) {
    Sum += Map[i][i];
  }
  if (Sum == -2) {
    for (int i = 1; i <= 3; i++) {
      if (Map[i][i] == 0) {
        x = i, y = i;
        return 1;
      }
    }
  }
  Sum = 0;
  for (int i = 1; i <= 3; i++) {
    Sum += Map[i][3 - i + 1];
  }
  if (Sum == -2) {
    for (int i = 1; i <= 3; i++) {
      if (Map[i][3 - i + 1] == 0) {
        x = i, y = 3 - i + 1;
        return 1;
      }
    }
  }
  return 0;
}
int findxx(int &x, int &y) {
  for (int i = 1; i <= 3; i++) {
    int Sum = 0;
    for (int j = 1; j <= 3; j++) {
      Sum += Map[i][j];
    }
    if (Sum == 2) {
      for (int j = 1; j <= 3; j++) {
        if (Map[i][j] == 0) {
          x = i, y = j;
          return 1;
        }
      }
    }
  }
  for (int j = 1; j <= 3; j++) {
    int Sum = 0;
    for (int i = 1; i <= 3; i++) {
      Sum += Map[i][j];
    }
    if (Sum == 2) {
      for (int i = 1; i <= 3; i++) {
        if (Map[i][j] == 0) {
          x = i, y = j;
          return 1;
        }
      }
    }
  }
  int Sum = 0;
  for (int i = 1; i <= 3; i++) {
    Sum += Map[i][i];
  }
  if (Sum == 2) {
    for (int i = 1; i <= 3; i++) {
      if (Map[i][i] == 0) {
        x = i, y = i;
        return 1;
      }
    }
  }
  Sum = 0;
  for (int i = 1; i <= 3; i++) {
    Sum += Map[i][3 - i + 1];
  }
  if (Sum == 2) {
    for (int i = 1; i <= 3; i++) {
      if (Map[i][3 - i + 1] == 0) {
        x = i, y = 3 - i + 1;
        return 1;
      }
    }
  }
  return 0;
}
int findx__(int &x, int &y) {
  if (Map[1][1] == 1 && Map[1][2] == 0 && Map[1][3] == 0) {
    x = 1, y = 3;
    return 1;
  }
  if (Map[1][1] == 0 && Map[1][2] == 0 && Map[1][3] == 1) {
    x = 1, y = 1;
    return 1;
  }
  if (Map[3][1] == 1 && Map[3][2] == 0 && Map[3][3] == 0) {
    x = 3, y = 3;
    return 1;
  }
  if (Map[3][1] == 0 && Map[3][2] == 0 && Map[3][3] == 1) {
    x = 3, y = 1;
    return 1;
  }
  if (Map[1][1] == 1 && Map[2][1] == 0 && Map[3][1] == 0) {
    x = 3, y = 1;
    return 1;
  }
  if (Map[1][1] == 0 && Map[2][1] == 0 && Map[3][1] == 1) {
    x = 1, y = 1;
    return 1;
  }
  if (Map[1][3] == 1 && Map[2][3] == 0 && Map[3][3] == 0) {
    x = 3, y = 3;
    return 1;
  }
  if (Map[1][3] == 0 && Map[2][3] == 0 && Map[3][3] == 1) {
    x = 1, y = 3;
    return 1;
  }
  return 0;
}
int Inc(int x, int y) {
  if (x == 1 && y == 1) return 1;
  if (x == 3 && y == 3) return 1;
  if (x == 1 && y == 3) return 1;
  if (x == 3 && y == 1) return 1;
  return 0;
}
int findcor(int &x, int &y) {
  if (Map[1][1] == 0) {
    x = 1, y = 1;
    return 0;
  }
  if (Map[1][3] == 0) {
    x = 1, y = 3;
    return 0;
  }
  if (Map[3][1] == 0) {
    x = 3, y = 1;
    return 0;
  }
  if (Map[3][3] == 0) {
    x = 3, y = 3;
    return 0;
  }
  for (int i = 1; i <= 3; i++) {
    for (int j = 1; j <= 3; j++) {
      if (Map[i][j] == 0) {
        x = i, y = j;
        return 0;
      }
    }
  }
}
int main() {
  cin >> s;
  if (s[0] == 'X') {
    out(2, 2);
    int x, y;
    in(x, y);
    if (x == 2 || y == 2) {
      if (x == 2) {
        out(1, y);
      } else {
        out(x, 1);
      }
      in(x, y);
      if (findxx(x, y)) {
        out(x, y);
        cin >> s;
        return 0;
      } else if (findx__(x, y)) {
        out(x, y);
      } else {
        findcor(x, y);
        out(x, y);
      }
      in(x, y);
      findxx(x, y);
      out(x, y);
      cin >> s;
      return 0;
    } else {
      if (Map[1][1] == 0) {
        out(1, 1);
      } else {
        out(1, 3);
      }
      in(x, y);
      if (findxx(x, y)) {
        out(x, y);
        cin >> s;
        return 0;
      } else if (findoo(x, y)) {
        out(x, y);
      } else {
        findcor(x, y);
        out(x, y);
      }
      in(x, y);
      if (findxx(x, y)) {
        out(x, y);
        cin >> s;
        return 0;
      } else if (findoo(x, y)) {
        out(x, y);
      } else {
        findcor(x, y);
        out(x, y);
      }
      in(x, y);
      findcor(x, y);
      out(x, y);
      cin >> s;
    }
  } else {
    int x, y;
    in(x, y);
    if (Inc(x, y)) {
      out(2, 2);
      in(x, y);
      if (Map[1][1] == -1 && Map[3][3] == -1 || Map[1][3] == -1 && Map[3][1] == -1) {
        out(1, 2);
      } else {
        if (findoo(x, y)) {
          out(x, y);
        } else {
          findcor(x, y);
          out(x, y);
        }
      }
      in(x, y);
      if (findxx(x, y)) {
        out(x, y);
        cin >> s;
        return 0;
      } else if (findoo(x, y)) {
        out(x, y);
      } else {
        findcor(x, y);
        out(x, y);
      }
      in(x, y);
      if (findxx(x, y)) {
        out(x, y);
        cin >> s;
        return 0;
      } else if (findoo(x, y)) {
        out(x, y);
      } else {
        findcor(x, y);
        out(x, y);
      }
      in(x, y);
      cin >> s;
    }
    else if (x == 2 && y == 2) {
      out(1, 1);
      in(x, y);
      if (findoo(x, y)) {
        out(x, y);
      } else {
        findcor(x, y);
        out(x, y);
      }
      in(x, y);
      if (findxx(x, y)) {
        out(x, y);
        cin >> s;
        return 0;
      } else if (findoo(x, y)) {
        out(x, y);
      } else {
        findcor(x, y);
        out(x, y);
      }
      in(x, y);
      if (findxx(x, y)) {
        out(x, y);
        cin >> s;
        return 0;
      } else if (findoo(x, y)) {
        out(x, y);
      } else {
        findcor(x, y);
        out(x, y);
      }
      in(x, y);
      cin >> s;
    } else {
      out(2, 2);
      in(x, y);
      if (findoo(x, y)) {
        out(x, y);
      } else {
        findcor(x, y);
        out(x, y);
      }
      
      in(x, y);
      if (findxx(x, y)) {
        out(x, y);
        cin >> s;
        return 0;
      } else if (findoo(x, y)) {
        out(x, y);
      } else {
        findcor(x, y);
        out(x, y);
      }

      in(x, y);
      if (findxx(x, y)) {
        out(x, y);
        cin >> s;
        return 0;
      } else if (findoo(x, y)) {
        out(x, y);
      } else {
        findcor(x, y);
        out(x, y);
      }
      in(x, y);
      cin >> s;
    }
  }
}