#include<cstdio>
#include<algorithm>
using namespace std;

struct xl
{
long long r,s,t; 
};

long long a,b,c,d,e,f,g,i,m,n;
long long xa[500000]={0},xb[500000]={0};
xl w[500000];

bool sx(xl j,xl k)
{
if(j.s!=k.s) return j.s<k.s;
if(j.t!=k.t) return j.t>k.t;
return j.r<k.r;
}

long long qj(long long j,long long k,long long l)
{
long long p,q;
p=(w[j].s-w[l].s)*(w[k].t-w[l].t);
q=(w[k].s-w[l].s)*(w[j].t-w[l].t);
if(p==q) return w[j].r<w[k].r;
return p<q;
}

int main()
{
scanf("%lld",&a);
for(n=1;n<=a;n++)
{
	scanf("%lld",&b);
	f=0;
	for(i=1;i<=b;i++)
	{
		scanf("%lld%lld",&w[i].s,&w[i].t);
		w[i].r=i;
	}
	sort(w+1,w+b+1,sx);
	c=1;
	xa[1]=1;
	for(i=1;i<=b;i++)
	{
		if((w[i-1].s!=w[i].s)||(w[i-1].t!=w[i].t))
		{
			while((c>1)&&(qj(i,xa[c],xa[c-1]))) c--;
			c++;
			xa[c]=i;
		}
	}
	for(i=1;i<c;i++)
	{
		printf("%lld ",w[xa[i]].r);
	}
	printf("%lld\n",w[xa[c]].r);
}
}