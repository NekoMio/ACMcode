#include<cstdio>

long long a,b,c,d,e,f,g,h,i,m,n;
long long xa[200000]={0},xb[1600000]={0},xc[1600000]={0};
const int y=1000000007;
bool z[2000000]={0};

long long zh(long long j,long long k)
{
return xb[j]*xc[j-k]%y*xc[k]%y;
}

long long km(long long j,long long k)
{
if(j==0) return 1;
if(j==1) return k;
long long l=km(j/2,k);
l=l*l%y;
if(j&1) l=l*k%y;
return l;
}

int main()
{
int t=0;
for(int r=2;(r<=1500000)&&(t<=100000);r++)
{
	if(z[r]==0)
	{
		t++;
		xa[t]=(long long)r;
	}
	for(int s=1;(s<=t)&&(r*xa[s]<=1500000);s++)
	{
		z[r*xa[s]]=1;
		if(r%xa[s]==0) s=t+10;
	}
}
xb[0]=1;
xb[1]=1;
xc[0]=1;
xc[1]=1;
for(i=2;i<=1500000;i++)
{
	xb[i]=xb[i-1]*i%y;
	xc[i]=(y-y/i)*xc[y%i]%y;
}
for(i=2;i<=1500000;i++)
{
	xc[i]=xc[i-1]*xc[i]%y;
}
scanf("%lld",&a);
for(int r=1;r<=a;r++)
{
	scanf("%lld%lld%lld",&b,&c,&d);
	b=xa[b];
	e=0;
	for(i=1;i<=d;i++)
	{
		f=zh(b+i,b-1);
		if(f==0) e+=c;
		else e+=(km(c+1,f)+y-f)*km(y-2,f-1)%y;
		e%=y;
	}
	printf("%lld\n",e);
}
}