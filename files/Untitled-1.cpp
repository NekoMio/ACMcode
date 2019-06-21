#define MAXN 800010UL
#define MAXL 2000010UL
 
#include <stdio.h>
#include <algorithm>
 
struct Pair{int x,y,val,pos,id,opt;};
Pair Ask[MAXN],tmp[MAXN];
int n,m,tree[MAXL],Ans[MAXN];
 
inline bool comp(Pair a,Pair b){
	if(a.x==b.x&&a.y==b.y) return a.opt<b.opt;
	return a.x==b.x?a.y<b.y:a.x<b.x;
}
 
inline int lowbit(int x){
	return x&(-x);
}
 
inline void Update(int i,int val){
	for(;i<=n;i+=lowbit(i)) tree[i]+=val;
	return;
}
 
inline int Query(int i){
	int temp_ans=0;
	for(;i;i-=lowbit(i)) temp_ans+=tree[i];
	return temp_ans;
}
 
inline int in(){
	int x=0,c=getchar();
	while(c<'0'||c>'9') c=getchar();
	for(;c>='0'&&c<='9';c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	return x;
}
 
inline void Add(){
	int x1,x2,y1,y2;
	x1=in();y1=in();x2=in();y2=in();++Ans[0];
	Ask[++m].pos=Ans[0];Ask[m].x=x1-1;Ask[m].y=y1-1;Ask[m].val= 1;Ask[m].opt=1;
	Ask[++m].pos=Ans[0];Ask[m].x=  x2;Ask[m].y=  y2;Ask[m].val= 1;Ask[m].opt=1;
	Ask[++m].pos=Ans[0];Ask[m].x=x1-1;Ask[m].y=  y2;Ask[m].val=-1;Ask[m].opt=1;
	Ask[++m].pos=Ans[0];Ask[m].x=  x2;Ask[m].y=y1-1;Ask[m].val=-1;Ask[m].opt=1;
	return;
}
 
inline void CDQ(int l,int r){
	if(l==r) return;
	int mid=(l+r)>>1,l1=l,l2=mid+1;
	for(int i=l;i<=r;i++){
		if(Ask[i].id<=mid&&!Ask[i].opt) Update(Ask[i].y,Ask[i].val);
		if(Ask[i].id>mid&&Ask[i].opt) Ans[Ask[i].pos]+=Ask[i].val*Query(Ask[i].y);
	}
	for(int i=l;i<=r;i++) if(Ask[i].id<=mid&&!Ask[i].opt) Update(Ask[i].y,-Ask[i].val);
	for(int i=l;i<=r;i++){
		if(Ask[i].id<=mid) tmp[l1++]=Ask[i];
		else tmp[l2++]=Ask[i];
	}
	for(int i=l;i<=r;i++) Ask[i]=tmp[i];
	CDQ(l,mid);CDQ(mid+1,r);
	return;
}
 
int main(){
	freopen("mokia.in","r",stdin);
	freopen("mokia.out","w",stdout);
	n=in();n=in();
	while(true){
		int op=in();
		if(op==1) ++m,Ask[m].x=in(),Ask[m].y=in(),Ask[m].val=in();
		else if(op==2) Add();
		else break;
	}
	for(int i=1;i<=m;i++) Ask[i].id=i;
	std::sort(Ask+1,Ask+m+1,comp);
	CDQ(1,m);
	for(int i=1;i<=Ans[0];i++) printf("%d\n",Ans[i]);
	return 0;
}