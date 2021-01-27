#include <bits/stdc++.h>
using namespace std;
double n, p1, v1, p2, v2;
double ans;
void solve1()
{
    ans = 2e60;
    double res;
    double t1 = (p2 - p1) / (v1 + v2);
    double npos = p1 + v1 * t1;
    double tt1 = npos / v1;
    double tt2 = (n - npos) / v2;
    double tat;
    if(v1 < v2){
        tat = (n + npos) / v2;
        if(tat < tt1) res = t1 + tat; // tt1
        else res = t1 + tt1; //tat
    }
    else{
        tat = (2 * n - npos) / v1;
        if(tat < tt2) res = t1 + tat; // tt2
        else res = t1 + tt2; //tat
    }
    ans = min(ans, res);
}
void solve2()
{
    double res;
    double t1 = (n + n - p1) / v1;
    double t2 = (n + n - p2) / v2;
    res = min(t1, t2);
    ans = min(ans, res);
}
void solve3()
{
    double res;
    double t1 = (n + p1) / v1;
    double t2 = (n + p2) / v2;
    res = min(t1, t2);
    ans = min(ans, res);
}
void solve4()
{
  double res;
  res = (p1 + n - p2 + n) / (v1 + v2);
  ans = min(ans, res);
}
int main()
{
    ios::sync_with_stdio(false);
    int t; cin>>t;
    while(t--){
        cin>>n>>p1>>v1>>p2>>v2;
        if(p1 > p2){
            swap(p1, p2);
            swap(v1, v2);
        }
        solve1();
        solve2();
        solve3();
        solve4();
        printf ("%.7f\n", ans);
    }
}