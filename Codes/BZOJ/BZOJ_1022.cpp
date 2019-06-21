#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int a[55];
int main()
{
    int t = read();
    while (t--)
    {
        int n = read(), ans = 0;
        bool flag = 0;
        for (int i = 1; i <= n; i++)
        {
            a[i] = read();
            ans ^= a[i];
            if (a[i] != 1) flag = 1;
        }
        if (!flag)
        {
            if (n & 1) puts ("Brother");
            else puts ("John");
        }
        else
        {
            if (ans) puts("John");
            else puts("Brother");
        }
    }
}