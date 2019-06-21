/*
 * @Author: WildRage 
 * @Date: 2017-07-29 08:42:54 
 * @Last Modified by: WildRage
 * @Last Modified time: 2017-07-29 09:57:54
 */
#include <cstdio>
#include <cstring>
using namespace std;
int SG[2025];
int Get_SG(int x)
{
    if (x < 0)
        return 0;
    if (SG[x] != -1)
        return SG[x];
    int h[2025];
    memset(h, 0, sizeof(h));
    for (int i = 1; i <= x; i++)
    {
        int H = Get_SG(i - 3) ^ Get_SG(x - i - 2);
        h[H] = 1;
    }
    int i;
    for (i = 0; h[i]; ++i)
        ;
    return SG[x] = i;
}
int main()
{
    memset(SG, -1, sizeof(SG));
    SG[0] = 0, SG[1] = 1, SG[2] = 1, SG[3] = 1;
    int n;
    //printf("%d\n",Get_SG(100));
    while (scanf("%d", &n) != EOF)
    {
        printf("%d\n",Get_SG(n)?1:2);  
    }
    return 0;
}
