CRT
#include <iostream>
#include <cstring>
#include <algorithm>
#include <stdio.h>
typedef long long ll;
const int MAXN = 1000005,P = 54184622;
int n,g,a[7],b[7]; ll Ans,fac[MAXN][6];
  
  
template<typename _t>
inline _t read(){
    _t x=0,f=1;
    char ch=getchar();
    for(;ch>'9'||ch<'0';ch=getchar())if(ch=='-')f=-f;
    for(;ch>='0'&&ch<='9';ch=getchar())x=x*10+(ch^48);
    return x*f;
}
 
inline int gcd(int x,int y){
    return !y?x:gcd(y,x%y);
}
 
inline ll qpow(ll x,ll k,ll mod) {
    ll Ans = 1;
    for (;k;k>>=1,x = x * x % mod) if (k & 1) Ans = Ans * x % mod;
    return Ans;
}
 
inline ll CRT(int *a,int *b,int n) {
    ll N = 1,tmp,ni,Ans = 0;
    for (int i = 1;i<=n;i++) N *= a[i];
    for (int i = 1;i<=n;i++) {
        tmp = N / a[i];
        ni = qpow(tmp,a[i] - 2,a[i]);
        (Ans += b[i] * ni % N * tmp % N) %= N;
    }
    return Ans;
}
 
inline ll C(int n,int m,int op){
    if (!m || n == m) return 1;
    if (n < m) return 0;
    return fac[n][op] * qpow(fac[n-m][op] * fac[m][op] % a[op],a[op]-2,a[op]) % a[op];
}
 
inline ll lucas(int n,int m,int op){
    if (!m||n == m) return 1;
    if (n<m) return 0;
    return lucas(n/a[op],m/a[op],op) * C(n%a[op],m%a[op],op) % a[op];
}
   
int main(){
    a[1] = 2;a[2] = 3;a[3] = 5;a[4] = 7;a[5] = 129011;
    fac[0][1] = fac[0][2] = fac[0][3] = fac[0][4] = fac[0][5] = 1;
    n = read<int>();g = read<int>();
    for (int i = 1;i<=g;i++) {
        fac[i][1] = fac[i-1][1] * i % a[1];
        fac[i][2] = fac[i-1][2] * i % a[2];
        fac[i][3] = fac[i-1][3] * i % a[3];
        fac[i][4] = fac[i-1][4] * i % a[4];
        fac[i][5] = fac[i-1][5] * i % a[5];
    }
    for (int i = 1;i<=n;i++)
        if (gcd(i,n) == 1)
            for (int j = 1;j<=5;j++)
                (b[j] += lucas(g,i,j)) %= a[j];
    ll Ans = CRT(a,b,5); 
    Ans += 27092310;
    Ans = qpow(n,Ans,P);
    printf("%lld\n",Ans);
    getchar(); getchar();
    return 0;
}
GS
#include<iostream>
#include<cstdio>
#include<cmath>
#define MAXN 20
using namespace std;
int n;
double a[MAXN][MAXN],b[MAXN],p[MAXN][MAXN],ans[MAXN];
void swap(double &x,double &y){double tmp=x;x=y;y=tmp;}
void work(int x,int y){
	double ans=0;
	for(int i=1;i<=n;i++){
		a[x][i]=2*(-p[x][i]+p[y][i]);
		ans+=p[x][i]*p[x][i]-p[y][i]*p[y][i];
	}
	b[x]=-ans;
}
void gs(){
	for(int k=1;k<=n;k++){
		int bj=k;
		for(int i=k+1;i<=n;i++)
			if(fabs(a[i][k])>fabs(a[bj][k]))bj=i;
		if(bj!=k){for(int i=k;i<=n;i++)swap(a[k][i],a[bj][i]);swap(b[k],b[bj]);}
		for(int i=k+1;i<=n;i++){
			double tmp=a[i][k]/a[k][k];
			for(int j=k;j<=n;j++)
				a[i][j]-=a[k][j]*tmp;
			b[i]-=b[k]*tmp;
		}
	}
	for(int i=n;i>=1;i--){
		for(int j=n;j>=i+1;j--)
			b[i]-=a[i][j]*ans[j];
		ans[i]=b[i]/a[i][i];
	}
}
int main(){
	freopen("bzoj_1013.in","r",stdin);
	freopen("bzoj_1013.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n+1;i++)
		for(int j=1;j<=n;j++)
			scanf("%lf",&p[i][j]);
	for(int i=1;i<=n;i++)
		work(i,i+1);
	gs();
	for(int i=1;i<=n;i++)
		printf("%.3lf ",ans[i]);
}
KMP
#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#define MAXN 1000005
using namespace std;
 
 
int next[MAXN];
char a[MAXN],b[MAXN];
int KMP(){
	
	memset(next,0,sizeof(next));
	
	int ans=0,fix=0,len=strlen(a);
	
	next[0]=0;
	
	for(int i=1;a[i];i++){
		
		while(fix && a[i]!=a[fix])
			fix=next[fix-1];
			
		if(a[fix] == a[i])
			fix++;
			
		next[i]=fix;
	}
	
	fix=0;
	
	for(int i=0;b[i];i++){
		
		while(fix&&a[fix]!=b[i])
			fix=next[fix-1];
			
		if(a[fix] == b[i])
			fix++;
			
		if(fix == len){
			fix=next[fix-1];
			ans++;
		}
		
	}
	return ans;
}
int main(){
	
	freopen("oulipo.in","r",stdin);
	
	freopen("oulipo.out","w",stdout);
	
	int m;
	
	scanf("%d",&m);
	
	while(m--){
		
		scanf("%s%s",a,b);
	
		printf("%d\n",KMP());
		
	}
}
bignum

#define BASE 10000
namespace BIGNUM{
    struct bignum{
        int a[10005],len;
        bignum(){memset(a,0,sizeof a); len = 0;}
        inline int& operator [] (const int &x){return a[x];}
        
        inline void operator = (const char *s){
            len = 0; int t = 1,k = 0;
            register int tmp = strlen(s);
            for (int i = tmp - 1; ~i; i--){
                k += t * (s[i] - '0'), t *= 10;
                if (t == BASE) t = 1, a[++len] = k, k = 0;
            }
            if (k) a[++len] = k;
        }
        
        inline bool operator == (const bignum &x)const{
            if (len != x.len) return false;
            for (int i = len; i; i--) 
                if (a[i] != x.a[i]) return false;
            return true;
        }

        inline bool operator != (const bignum &x)const{
            return *this == x?0:1;
        }

        inline bool operator < (const bignum &x)const{
            if (len != x.len) return len < x.len;
            for (int i = len; i; i--)
                if (a[i] != x.a[i])
                    return a[i] < x.a[i];
            return false;
        }

        inline bool operator > (const bignum &x)const{
            return x < (*this);
        }

        inline bool operator <= (const bignum &x)const{
            return *this < x || *this == x;
        }

        inline bool operator >= (const bignum &x)const{
            return *this > x || *this == x;
        }

        inline bignum operator + (const int &x){
            bignum Ans = *this;
            Ans.a[1] += x; Ans.len ++;
            for (int i = 1; i <= len; i++)
                Ans.a[i+1] += Ans.a[i] / BASE,Ans.a[i] %= BASE;
            while (Ans.a[Ans.len] == 0 && Ans.len > 1) Ans.len --;
            return Ans;
        }

        inline bignum operator + (const bignum &x){
            bignum Ans; Ans.len = std::max(len,x.len) + 1;
            for (int i = 1; i <= len || i <= x.len; i++)
                Ans.a[i] += (i<=len?a[i]:0) + (i<=x.len?x.a[i]:0),Ans.a[i+1] += Ans.a[i] / BASE,Ans.a[i] %= BASE;
            while (!Ans.a[Ans.len] && Ans.len > 1) Ans.len --;
            return Ans;
        }

        inline bignum operator / (const int &x){
            bignum Ans = *this;
            for (int i = len; i; i--)
                Ans.a[i-1] += Ans.a[i] % x * BASE,Ans.a[i] /= BASE;
            while (!Ans.a[Ans.len] && Ans.len > 1) Ans.len --;
            return Ans;
        }

        inline bignum operator * (const bignum &x){
            bignum Ans; int last;
            for (int i = 1; i <= len; i++){
                last = 0;
                for (int j = 1; j <= x.len; j++){
                    Ans[i+j-1] += a[i] * x.a[j] + last;
                    last = Ans[i+j-1] / BASE;
                    Ans[i+j-1] %= BASE;
                }
                Ans[i+x.len] = last;
            }
            Ans.len = len + x.len;
            while (!Ans[Ans.len] && Ans.len > 1) -- Ans.len;
            return Ans;
        }

        inline void operator += (const int &x){*this = *this + x;}
        inline void operator += (const bignum &x){*this = *this + x;}
        inline void operator /= (const int &x){*this = *this / x;}
        inline void operator *= (const bignum &x){*this = *this * x;} 
        inline void in(){char s[1005]; scanf("%s",s); *this = s;}
        inline void Print(){printf("%d",a[len]); for (int i = len - 1; i >= 1; i--) printf("%04d",a[i]); puts("");}
    };
}

AC自动机
#include <stdio.h>
#include <cstring>
#include <iostream>
#include <iomanip>
using namespace std;
int n,len,alphabet,sz;
const int MAXN = 150000;
const int maxn = 26;
char ch[MAXN];


struct node{
    node *ch[maxn],*fail;
    bool is;
    node(){
		memset(ch,0,sizeof(ch));
		fail=NULL;
		is=0;
	}
}*root,*q[MAXN],N[MAXN],*C=N;

void insert(char *s){
    int len =strlen(s);
    node *now=root;
    for(int i=0;i<len;i++){
        if(now -> ch[s[i]-'a']==NULL)now -> ch[s[i]-'a'] = C++;
        now = now -> ch[s[i]-'a'];
    }
    now -> is = 1;
}

void build_ac(){
    int l=0,r=0;
    for(int i=0;i<26;i++)
        if(root->ch[i]){
            root->ch[i]->fail=root;
            q[++r]=root->ch[i];
        }
        else    root->ch[i]=root;
    while(l!=r){
        node *now = q[++l];
        for(int i=0;i<26;i++){
            if(now -> ch[i]){
                q[++r]=now -> ch[i];
                now -> ch[i] -> fail = now -> fail -> ch[i];
                now -> ch[i] -> is |= now -> ch[i] -> fail -> is;
            }
            else now -> ch[i] = now -> fail -> ch[i];
        }
    }
}

struct matrix{
    long double m[85][85];
    matrix(){memset(m,0,sizeof(m));}
};

matrix operator * (matrix a,matrix b){
    matrix ans ;
    for(int i=0;i<=sz;i++)
        for(int j=0;j<=sz;j++)
            for(int k=0;k<=sz;k++)
                ans.m[i][j]+=a.m[i][k]*b.m[k][j];
    return ans;
}

matrix operator ^ (matrix a,int n){
    matrix ans;
    for(int i=0;i<=sz;i++)ans.m[i][i]=1;
    for(;n;n>>=1,a=a*a)
        if(n&1)
            ans=ans*a;
    return ans;
}

int main(){
	root = C++;
    scanf("%d%d%d",&n,&len,&alphabet);
    for(int i=1;i<=n;i++){
        scanf("%s",ch);
        insert(ch);
    }
    build_ac();
    matrix ans;
    sz=C-N;
    long double tmp = 1.0/alphabet;
    for(int i=0;i<sz;i++)
        for(int j=0;j<alphabet;j++){
            if(N[i].ch[j]->is){
                ans.m[i][0]+=tmp;
                ans.m[i][sz]+=tmp;
            }
            else ans.m[i][N[i].ch[j]-N]+=tmp;
        }
    ans.m[sz][sz]=1;
    ans=ans^len;
    cout<<fixed<<setprecision(10)<<ans.m[0][sz];
}


