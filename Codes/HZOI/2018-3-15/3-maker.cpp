#include <bits/stdc++.h>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
char C[5] = "ATCG";
int main()
{    
    srand(time(NULL));
    int n = read();
    for (int i = 1; i <= n; i++)
        printf ("%c", C[rand() % 4]);
    printf ("\n");
    int m = read(), L = read();
    printf ("%d\n", m);
    for (int i = 1; i < m; i++)
    {
        int t = rand() % (L / 100);
        L -= t;
        for (int j = 1; j <= t; j++)
            printf("%c", C[rand() % 4]);
        printf ("\n");
    }
    for (int i = 1; i <= L; i++)
        printf ("%c", C[rand() % 4]);
    printf ("\n");
}