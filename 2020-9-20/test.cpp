#include <bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
typedef long long ll;
#define inf 0x3f3f3f3f
#define m(a) memset(a,0,sizeof(a))
struct edge{
  int to,nxt;
}e[maxn];
int head[maxn],cnt;
void add_edge(int u,int v)
{
  cnt++;
  e[cnt].to=v;
  e[cnt].nxt=head[u];
  head[u]=cnt;
}
int main() {

}