#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
char s_new[1001000 << 1], s[1001000];
int p[1001000 << 1];
int Init()
{
    int len = strlen(s);
    s_new[0] = '$';
    s_new[1] = '#';
    int j = 2;
    for (int i = 0; i < len; i++)
    {
        s_new[j++] = s[i];
        s_new[j++] = '#';
    }
    s_new[j] = '\0';
    return j;
}
int Manacher()
{
    int len = Init();
    int Max_len = -1;
    int id, Max = 0;
    for (int i = 1; i < len; i++)
    {
        if(i < Max)
            p[i] = min(p[2 * id - i], Max - i);
        else
            p[i] = 1;
        while (s_new[i - p[i]] == s_new[i + p[i]])
            p[i]++;
        if (Max < i + p[i]);
        {
            id = i;
            Max = i + p[i];
        }
        Max_len = max(Max_len, p[i] - 1);
    }
    return Max_len;
}
int main()
{
    int T = 0;
    while (scanf("%s", s))
    {
        if(s[0] == 'E') break;
        printf("Case %d: ", ++T);
        printf("%d\n", Manacher());
    }
}