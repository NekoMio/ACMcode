#include <cstdio>
int a, b, c, d, e, f, g, i, m, n;
int xa[200000] = {0}, xb[200000] = {0}, xc[200000] = {0};
// int wa[500000]={0},wb[500000]={0};

/*void sc(int j,int k)
{
int r,s;
if(k) c^=xa[j];
else d^=xa[j];
xc[j]=1;
r=xb[j];
s=wa[r];
while(r!=0)
{
        if(xc[s]==0) sc(s,k^1);
        r=wb[r];
        s=wa[r];
}
}*/

int main() {
  scanf("%d", &a);
  for (m = 1; m <= a; m++) {
    scanf("%d", &b);
    f = 0;
    for (i = 1; i <= b; i++) {
      scanf("%d", &xa[i]);
      f ^= xa[i];
      xb[i] = 0;
      xc[i] = 0;
    }
    for (i = 1; i < b; i++) {
      scanf("%d%d", &c, &d);
      /*wa[2*i-1]=d;
      wb[2*i-1]=xb[c];
      xb[c]=2*i-1;
      wa[2*i]=c;
      wb[2*i]=xb[d];
      xb[d]=2*i;*/
    }
    // sc(1,1);
    if (f == 0)
      printf("D\n");
    else
      printf("Q\n");
  }
}