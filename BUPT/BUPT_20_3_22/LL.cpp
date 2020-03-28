
#pragma comment(linker, "/STACK:102400000,102400000")
#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<cassert>
#include<string>
#include<cstdio>
#include<bitset>
#include<vector>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
#include<deque>
#include<list>
#include<set>
#include<map>
using namespace std;
#define debug test
#define mst(ss,b) memset((ss),(b),sizeof(ss))
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
#define ll long long
#define ull unsigned long long
#define pb push_back
#define mp make_pair
#define inf 0x3f3f3f3f
#define eps 1e-10
#define PI acos(-1.0)
typedef pair<int,int> PII;
const ll mod = 1e9+7;
const int N = 1e6+10;
 
ll gcd(ll p,ll q){return q==0?p:gcd(q,p%q);}
ll qp(ll a,ll b) {ll res=1;a%=mod; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
int to[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
 
int t,aa,bb,xx,yy;
double a,b,x,y;
 
int main() {
    // ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>t;
    while(t--) {
        cin>>aa>>bb>>xx>>yy;
        xx=-xx;
        a=aa,b=bb,x=xx,y=yy;
        ///垂直于斜面方向上
        double th=atan(b/a);///斜面角度
        double h=y-x*tan(th);///从下落处到第一次碰撞点的垂直高度
        double g=9.8;///重力加速度
        double v=sqrt(2*g*h);///第一次碰撞时的速度
        double t=2*v/g;///小球在垂直斜面方向上运动的周期
        ///平行于斜面方向上LL
        double X=x/cos(th);///小球在斜面上的位移
        double vx=v*sin(th);///小球平行于斜面的分速度
        double A=g*sin(th);///小球平行于斜面的加速度(重力加速度的分速度)
        double T=(sqrt(4*vx*vx+8*A*X)-2*vx)/(2*A);///小球在斜面上运动的总时间
        printf ("%lf %lf\n", T, t / 2);
        cout<<(ll)(T/t)+1<<endl;///碰撞次数为总时间除以碰撞周期+1(第一次碰撞)
    }
    return 0;
}