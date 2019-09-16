#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int a,b,c,d,e,f,g,i,m,n;
int xa[5000000]={0},xb[5000000]={0},xc[5000000]={0},xd[5000000]={0};
int x[5000000]={0};
int w[20]={0};
char z[200000][20],za[20]={0};

bool sx(int j,int k)
{
if(xa[j]!=xa[k]) return xa[j]<xa[k];
if(xb[j]!=xb[k]) return xb[j]>xb[k];
if(xc[j]!=xc[k]) return xc[j]>xc[k];
if(xd[j]!=xd[k]) return xd[j]>xd[k];
if(strcmp(z[j],z[k])<0) return 1;
return 0; 
}

int main()
{
while(scanf("%d",&a)!=EOF)
{
	for(i=1;i<=a;i++)
	{
		scanf("%s",z[i]);
		scanf("%s",za);
		b=0;
		for(m=1;m<=5;m++)
		{
			if(za[b]=='J') w[m]=11;
			if(za[b]=='Q') w[m]=12;
			if(za[b]=='K') w[m]=13;
			if(za[b]=='A') w[m]=1;
			if(za[b]=='1') w[m]=10,b++;
			if(za[b]=='2') w[m]=2;
			if(za[b]=='3') w[m]=3;
			if(za[b]=='4') w[m]=4;
			if(za[b]=='5') w[m]=5;
			if(za[b]=='6') w[m]=6;
			if(za[b]=='7') w[m]=7;
			if(za[b]=='8') w[m]=8;
			if(za[b]=='9') w[m]=9;
			b++;
		}
		sort(w+1,w+6);
		xa[i]=xb[i]=xc[i]=xd[i]=0;
		x[i]=i;
		if((w[1]==1)&&(w[2]==10)&&(w[3]==11)&&(w[4]==12)&&(w[5]==13)) xa[i]=-1;
		if(xa[i]==0)
		{
			b=0;
			for(m=1;m<5;m++)
			{
				if(w[m]+1!=w[m+1]) b=1;
			}
			if(b==0)
			{
				xa[i]=1;
				xb[i]=w[5];
			}
		}
		if(xa[i]==0)
		{
			if((w[1]==w[2])&&(w[2]==w[3])&&(w[3]==w[4]))
			{
				xa[i]=2;
				xb[i]=w[1];
				xc[i]=w[5];
			}
			if((w[2]==w[3])&&(w[3]==w[4])&&(w[4]==w[5]))
			{
				xa[i]=2;
				xb[i]=w[5];
				xc[i]=w[1];
			}
		}
		if(xa[i]==0)
		{
			if((w[1]==w[2])&&(w[2]==w[3])&&(w[4]==w[5]))
			{
				xa[i]=3;
				xb[i]=w[1];
				xc[i]=w[5];
			}
			if((w[1]==w[2])&&(w[3]==w[4])&&(w[4]==w[5]))
			{
				xa[i]=3;
				xb[i]=w[5];
				xc[i]=w[1];
			}
		}
		if(xa[i]==0)
		{
			if((w[1]==w[2])&&(w[2]==w[3]))
			{
				xa[i]=4;
				xb[i]=w[1];
				xc[i]=w[4]+w[5];
			}
			if((w[2]==w[3])&&(w[3]==w[4]))
			{
				xa[i]=4;
				xb[i]=w[2];
				xc[i]=w[1]+w[5];
			}
			if((w[3]==w[4])&&(w[4]==w[5]))
			{
				xa[i]=4;
				xb[i]=w[3];
				xc[i]=w[1]+w[2];
			}
		}
		if(xa[i]==0)
		{
			if((w[1]==w[2])&&(w[3]==w[4]))
			{
				xa[i]=5;
				xb[i]=w[3];
				xc[i]=w[1];
				xd[i]=w[5];
			}
			if((w[1]==w[2])&&(w[4]==w[5]))
			{
				xa[i]=5;
				xb[i]=w[4];
				xc[i]=w[1];
				xd[i]=w[3];
			}
			if((w[2]==w[3])&&(w[4]==w[5]))
			{
				xa[i]=5;
				xb[i]=w[4];
				xc[i]=w[2];
				xd[i]=w[1];
			}
		}
		if(xa[i]==0)
		{
			if(w[1]==w[2])
			{
				xa[i]=6;
				xb[i]=w[1];
				xc[i]=w[3]+w[4]+w[5];
			}
			if(w[2]==w[3])
			{
				xa[i]=6;
				xb[i]=w[2];
				xc[i]=w[1]+w[4]+w[5];
			}
			if(w[3]==w[4])
			{
				xa[i]=6;
				xb[i]=w[3];
				xc[i]=w[1]+w[2]+w[5];
			}
			if(w[4]==w[5])
			{
				xa[i]=6;
				xb[i]=w[4];
				xc[i]=w[1]+w[2]+w[3];
			}
		}
		if(xa[i]==0)
		{
			xa[i]=7;
			xb[i]=w[1]+w[2]+w[3]+w[4]+w[5];
		}
	}
	sort(x+1,x+a+1,sx);
	for(i=1;i<=a;i++)
	{
		//printf("%d\n",x[i]);
		printf("%s\n",z[x[i]]);
	}
}
}