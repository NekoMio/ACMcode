/*
 * @Author: WildRage 
 * @Date: 2017-06-25 15:42:08 
 * @Last Modified by: WildRage
 * @Last Modified time: 2017-06-25 16:28:13
 */
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
namespace WorkSpace
{
class Floyd
{
    int n;
    int a[305][305];

  public:
    void GetMinDis()
    {
        for (int i = 1; i <= n; i++)
            a[i][i] = 0;
        for (int k = 1; k <= n; k++)
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    a[i][j] = std::min(a[i][j], a[i][k] + a[k][j]);
    }
    void GetMap(int Number = 0, int m = 0)
    {
        n = Number;
        memset(a, 0x3f, sizeof(a));
        int s, e, v;
        for (int i = 1; i <= m; i++)
        {
            scanf("%d%d%d", &s, &e, &v);
            a[s][e] = std::min(v, a[s][e]);
            a[e][s] = std::min(v, a[s][e]);
        }
    }
    int MinDis(int s = 0, int e = 0)
    {
        return a[s][e];
    }
} Map;
struct Input
{
    int n, m, v, e;
} Read;
int ClassroomC[2005], ClassroomD[2005];
double ChangeProbability[2005], FailedToChange[2005];
class Init
{
    void OpenFile()
    {
        freopen("classrooma.in", "r", stdin);
        freopen("classrooma.out", "w", stdout);
    }
    void ReadInput()
    {
        scanf("%d%d%d%d", &Read.n, &Read.m, &Read.v, &Read.e);
        for (int i = 1; i <= Read.n; i++)
            scanf("%d", &ClassroomC[i]);
        for (int i = 1; i <= Read.n; i++)
            scanf("%d", &ClassroomD[i]);
        for (int i = 1; i <= Read.n; i++)
            scanf("%lf", &ChangeProbability[i]), FailedToChange[i] = 1 - ChangeProbability[i];
        Map.GetMap(Read.v, Read.e);
    }

  public:
    Init()
    {
#ifdef MineWorkSpace
        OpenFile();
#endif
        ReadInput();
        Map.GetMinDis();
    }
};
class DP
{
    double MinExpectation[2010][2010][2];

  public:
#define n Read.n
#define m Read.m
    DP()
    {
        memset(MinExpectation, 0x43, sizeof(MinExpectation));
        MinExpectation[1][0][0] = 0;
        MinExpectation[1][1][1] = 0;
        for (int i = 2; i <= n; i++)
        {
            for (int j = 0; j <= m; j++)
            {
                MinExpectation[i][j][0] = std::min(MinExpectation[i - 1][j][0] + Map.MinDis(ClassroomC[i - 1], ClassroomC[i]), MinExpectation[i - 1][j][1] + (double)Map.MinDis(ClassroomD[i - 1], ClassroomC[i]) * ChangeProbability[i - 1] + (double)Map.MinDis(ClassroomC[i - 1], ClassroomC[i]) * FailedToChange[i - 1]);
                if (j > 0)
                    MinExpectation[i][j][1] = std::min(MinExpectation[i - 1][j - 1][0] + (double)Map.MinDis(ClassroomC[i - 1], ClassroomD[i]) * ChangeProbability[i] + (double)Map.MinDis(ClassroomC[i - 1], ClassroomC[i]) * FailedToChange[i], MinExpectation[i - 1][j - 1][1] + (double)Map.MinDis(ClassroomC[i - 1], ClassroomC[i]) * FailedToChange[i - 1] * FailedToChange[i] + (double)Map.MinDis(ClassroomC[i - 1], ClassroomD[i]) * FailedToChange[i - 1] * ChangeProbability[i] + (double)Map.MinDis(ClassroomD[i - 1], ClassroomC[i]) * ChangeProbability[i - 1] * FailedToChange[i] + Map.MinDis(ClassroomD[i - 1], ClassroomD[i]) * ChangeProbability[i - 1] * ChangeProbability[i]);
            }
        }
        double ans = 1e16;
        for (int i = 0; i <= m; i++)
        {
            ans = std::min(MinExpectation[n][i][0], ans);
            ans = std::min(MinExpectation[n][i][1], ans);
        }
        printf("%.2lf", ans);
    }
};
class Main
{
  public:
    Main()
    {
        new Init();
        new DP();
        //while(1);
    }
} Run;
}
int main() { ; }