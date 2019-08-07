#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<map>
#define N 2005
using namespace std;
int T,n;
struct nd{
	int x,y;
	long long da;
}nod[N];
bool cmp(const nd &a,const nd &b)
{
	if(a.y==b.y)return a.x<b.x;
	return a.y<b.y;
}
int zz;
int B[N];
map<int,int> dl;
struct no{
	int left,right,mid;
	long long sum,lmx,rmx;
}node[N*4];
void build(int left,int right,int x)
{
	node[x].left=left,node[x].right=right;
	node[x].sum=node[x].lmx=node[x].rmx=0;
	if(left==right)return;
	int mid=(left+right)>>1;
	node[x].mid=mid;
	build(left,mid,x<<1);
	build(mid+1,right,x<<1|1);
}
void insert(int to,int x,int da)
{
	if(node[x].left==node[x].right)
	{
		node[x].sum+=da;
		node[x].rmx+=da;
		node[x].lmx+=da;
		return;
	}
	int mid=node[x].mid;
	if(to>mid) insert(to,x<<1|1,da);
	else insert(to,x<<1,da);
	node[x].sum=node[x<<1].sum+node[x<<1|1].sum;
	
	if(node[x<<1].lmx>node[x<<1].sum+node[x<<1|1].lmx) node[x].lmx=node[x<<1].lmx;
	else node[x].lmx=node[x<<1].sum+node[x<<1|1].lmx;
	
	if(node[x<<1|1].rmx>node[x<<1|1].sum+node[x<<1].rmx) node[x].rmx=node[x<<1|1].rmx;
	else node[x].lmx=node[x<<1|1].sum+node[x<<1].rmx;
}
long long get_lmx(int x,long long sum,int fr)
{
	long long ans=0;
	if(fr==1)
		ans=sum+node[x<<1].lmx;
	else if(fr==-1) ans=sum;
	if(x!=1)
	{
		long long ans1=0;
		if(fr==1)
			ans1=get_lmx(x>>1,sum+node[x<<1].sum,x&1);
		else ans1=get_lmx(x>>1,sum,x&1);
		if(ans1>ans) ans=ans1;
	}
	return ans;
}

long long get_rmx(int x,long long sum,int fr)
{
	long long ans=0;
	if(fr==0)
		ans=sum+node[x<<1|1].rmx;
	else if(fr==-1) ans=sum;
	if(x!=1)
	{
		long long ans1=0;
		if(fr==0)
			ans1=get_rmx(x>>1,sum+node[x<<1|1].sum,x&1);
		else ans1=get_rmx(x>>1,sum,x&1);
		if(ans1>ans) ans=ans1;
	}
	return ans;
}

long long find(int to,int x,int op)
{
	if(node[x].left==node[x].right)
	{
		if(op==0)
			return get_lmx(x,node[x].sum,-1);
		else return get_rmx(x,node[x].sum,-1);
	}
	int mid=node[x].mid;
	if(to>mid)  return find(to,x<<1|1,op);
	else return find(to,x<<1,op);
}
long long get_sum(int left,int right,int x)
{
	if(node[x].left==left&&node[x].right==right)return node[x].sum;
	int mid=node[x].mid;
	if(left>mid)return get_sum(left,right,x<<1|1);
	else if(right<=mid)return get_sum(left,right,x<<1);
	else return get_sum(left,mid,x<<1)+get_sum(mid+1,right,x<<1|1);
}
int main()
{
	// freopen("test.in","r",stdin);
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d",&n);
		dl.clear();
		for(int i=1;i<=n;i++)
			scanf("%d%d%lld",&nod[i].x,&nod[i].y,&nod[i].da);
		sort(nod+1,nod+1+n,cmp);
		zz=0;
		for(int i=1;i<=n;i++)
		{
			if(nod[i].x!=nod[i-1].x||nod[i].y!=nod[i-1].y||i==1) zz++;
			if(nod[i].x==nod[i-1].x&&nod[i].y==nod[i-1].y) nod[zz].da+=nod[i].da;
			else nod[zz]=nod[i];
		}
		n=zz;
		zz=0;
		for(int i=1;i<=n;i++)
		{
			zz++;
			B[zz]=nod[i].x;
		}
		sort(B+1,B+zz+1);
		zz=0;
		for(int i=1;i<=n;i++)
		{
			if(B[i]!=B[i-1]||i==1) zz++;
			B[zz]=B[i];
			dl[B[i]]=zz;
		}
		for(int i=1;i<=n;i++) nod[i].x=dl[nod[i].x];
		long long ans=0;
		for(int i=1;i<=n;i++)
		{
			if(nod[i].da>ans) ans=nod[i].da;
			long long sum=nod[i].da,sum2=nod[i].da;
			build(1,zz,1);
			insert(nod[i].x,1,nod[i].da);
			for(int j=i-1;j;j--)
			{
				if(nod[i].y==nod[j].y)
				{
					insert(nod[j].x,1,nod[j].da);
				}
				else break;
			}
			for(int j=i+1;j<=n;j++)
			{
				if(nod[j].x==nod[i].x) sum2+=nod[j].da;
				if(nod[j].y==nod[i].y)
				{
					sum+=nod[j].da;
					if(sum>ans) ans=nod[i].da;
				}
				if(nod[j].y!=nod[j-1].y||j==i+1)
				{
					for(int k=j;k<=n;k++)
					{
						if(nod[k].y==nod[j].y)
						{
							insert(nod[k].x,1,nod[k].da);
						}
						else break;
					}
				}
				long long a,b,c=0;
				if(nod[j].x<nod[i].x)
				{
					a=find(nod[j].x,1,0);
					b=find(nod[i].x,1,1);
					if(nod[i].x-nod[j].x>=2)
						c=get_sum(nod[j].x+1,nod[i].x-1,1);
					else c=0;
				}
				else 
				{
					a=find(nod[j].x,1,1);
					b=find(nod[i].x,1,0);
					if(nod[j].x-nod[i].x>=2)
						c=get_sum(nod[i].x+1,nod[j].x-1,1);
					else c=0;
				}
				if(nod[i].x==nod[j].x) c-=sum2;
				if(a+b+c>ans) ans=a+b+c;
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
/*
2
4
1 1 50
2 1 50
1 2 50
2 2 -500
2 
-1 1 5
-1 1 1

1
4
0 1 10
0 2 -10
0 4 20
0 5 20

3
5
0 0 -10
1 1 -9
1 -1 -9
-1 1 -10
-1 -1 -10


4
1 1 50
2 1 50
1 2 50
2 2 -500
2 
-1 1 5
-1 1 1
*/
