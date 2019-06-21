#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;
typedef long long LL;
const int N=1000010;
LL n,k,p,vis[N],f[N*6],ni[N],len[N];
bool ext[N];
void exgcd(LL a,LL b,LL&x,LL &y,LL &d)
{
	if(b==0)d=a,x=1,y=0;
	else exgcd(b,a%b,y,x,d),y-=x*(a/b);
}
inline LL inv(LL a,LL mod)
{
	LL d,x,y;exgcd(a,mod,x,y,d);
	return d==1?(x+mod)%mod:-1;
}
struct marx
{
	LL m[4][4];
	marx(){}
	inline LL *operator [](LL x){return m[x];}
	inline void clear(){memset(m,0,sizeof(m));}
	marx operator * (const marx &b) const
	{
		marx c;c.clear();
		for(int k=1;k<=3;k++)
			for(int i=1;i<=3;i++)
				for(int j=1;j<=3;j++)
					c.m[i][j]=(c.m[i][j]%p+m[i][k]%p*b.m[k][j]%p)%p;
		return c;
	}
}mat[N],A,B,C,ans;
inline marx poww(marx x,LL len)
{
	marx ret;ret.clear();
	ret[1][1]=ret[2][2]=ret[3][3]=1;
	while(len)
	{
		if(len&1)ret=ret*x;
		len>>=1;x=x*x;
	}
	return ret;
}
int main()
{
	freopen("rabbit17.in","r",stdin);
	freopen("rabbit.out","w",stdout);
	scanf("%lld%lld%lld",&n,&k,&p);
	f[1]=f[2]=1;
	for(int i=3;;i++)
	{
		f[i]=(f[i-1]+f[i-2])%k;
		if(!vis[f[i]])vis[f[i]]=i;
		if(f[i]==f[i-1]&&f[i]==1)break;
	}
	A[1][1]=A[1][2]=A[2][1]=A[3][3]=1;
	B[1][1]=B[2][2]=B[3][3]=1,B[3][1]=-1;
	ans[1][2]=ans[1][3]=1;
	LL x=1;bool flag=0;
	while(n)
	{
		if(!ni[x])ni[x]=inv(x,k);
		if(ni[x]==-1)
			{
				for(int i=1;i<=3;i++)
				{
					for(int j=1;j<=3;j++)
						printf("%lld ",ans[i][j]);
					printf("\n");
				}
				printf("No inv"),ans=ans*poww(A,n),n=0;
			}
		else
		{
			if(!ext[x]||flag)
			{
				ext[x]=1;
				if(!vis[ni[x]])
					printf("No vis"),ans=ans*poww(A,n),n=0;
				else
				{
					len[x]=vis[ni[x]];
					if(n>=len[x])
					{
						n-=len[x],mat[x]=poww(A,len[x])*B;
						ans=ans*mat[x],x=x*f[len[x]-1]%k;
					}
					else printf("No more len"),ans=ans*poww(A,n),n=0;
				}
			}
			else
			{
				LL cnt=0;
				C.clear();C[1][1]=C[2][2]=C[3][3]=1;
				for(LL i=x*f[len[x]-1]%k;i!=x;i=i*f[len[i]-1]%k)
					cnt+=len[i],C=C*mat[i];
                cnt+=len[x],C=mat[x]*C;
				printf("CNT============%d\n",cnt);
				ans=ans*poww(C,n/cnt);
				n%=cnt,flag=1;
			}
		}
	}
	printf("%lld",(ans[1][1]%p+p)%p);
}
