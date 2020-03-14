#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
#define N 1005
using namespace std;
int n, m, C, H, M;
vector<int> q1[N][21];
bool Hum[N];
int B[N];
typedef pair<int, int> T;
queue<T> q;
bool fw[N][N];
int main() {
  scanf("%d%d%d%d%d", &n, &m, &C, &H, &M);
  for (int i = 1; i <= H; i++) {
    int x;
    scanf("%d", &x);
    x++;
    Hum[x] = 1;
  }
  for (int i = 1; i <= M; i++) {
    scanf("%d", &B[i]);
    B[i]++;
  }
  for (int i = 1; i <= m; i++) {
    int x, y, z;
    scanf("%d%d%d", &x, &z, &y);
    x++, y++;
    q1[y][z].push_back(x);
  }
  for (int i = 1; i <= M; i++) {
    for (int j = i; j <= M; j++) {
      if ((Hum[B[i]] && !Hum[B[j]]) || (!Hum[B[i]] && Hum[B[j]])) {
        printf("YES\n");
        exit(0);
      }
      q.push(make_pair(B[i], B[j]));
      fw[B[i]][B[j]] = fw[B[j]][B[i]] = 1;
    }
  }
  while (!q.empty()) {
    T X = q.front();
    q.pop();
    int x = X.first, y = X.second;
    for (int i = 1; i <= C; i++) {
      for (int j = 0; j < q1[x][i].size(); j++) {
        for (int k = 0; k < q1[y][i].size(); k++) {
          int xx = q1[x][i][j], yy = q1[y][i][k];
          if (!fw[xx][yy]) {
            fw[xx][yy] = fw[yy][xx] = 1;
            if (Hum[xx] && !Hum[yy]) {
              printf("YES\n");
              exit(0);
            }

            if (Hum[yy] && !Hum[xx]) {
              printf("YES\n");
              exit(0);
            }
            q.push(make_pair(xx, yy));
          }
        }
      }
    }
  }
  printf("NO\n");
  return 0;
}
/*
5 6
1 B 3 R 4 B
2 B 3 R 4 R
1 B 2 R 3 R
3 R 4 B 5 B
3 B 4 B 5 B
1 R 2 R 4 R
*/