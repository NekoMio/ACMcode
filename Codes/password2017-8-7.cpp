#include<cstdio>
#include<cstring>
using namespace std;
char s[2000005];
unsigned long long base = 31;
unsigned long long has[2000005];
unsigned long long Pow(unsigned long long b,int i)
{
    unsigned long long ans = 1;
    while(i)
    {
        if(i & 1)
            ans = ans * b;
        i >>= 1;
        b = b * b;
    }
    return ans;
}
int main()
{
    freopen("fool.in","r",stdin);
    freopen("fool.out","w",stdout);
    int q;
    scanf("%d",&q);
    while(q--){
        scanf("%s", s + 1);
        int len = strlen(s + 1);
        for (int i = 1; i <= len; i++)
        {
            has[i] = has[i - 1] * base + s[i];
        }
        int ans = 0;
        for (int i = 1; i <= len; i++)
        {
            unsigned long long T = Pow(base, i); 
            if( has[i] == has[len] - has[len - i] * T)
            {
                for(int j = 2; j < len - i; j++)
                {
                    if(has[j + i] - has[j] * T == has[i])
                    {
                        ans = i;
                        break;
                    }
                }
                if(ans != i)
                    break;
            }
        }
        if(ans)
        {
            for(int i = 1; i <= ans; i++)
            {
                printf("%c", s[i]);
            }
            printf("\n");
        }
        else 
            puts("---\n");
    }
}
