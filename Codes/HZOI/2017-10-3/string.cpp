#pragma GCC optimize("O3")
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
char s[500005];
int now[500005];
int t[500005], idx;
struct Node{
	int v,key,size,rev;
	Node *ch[2];
	Node(){;}
	Node(int x){
		v=x;key=rand();size=1;rev=0;
		ch[0]=ch[1]=NULL;
	}
	#define size(_) ((_)?(_)->size:(0))
	void Pushup(){
		size=1+size(ch[1])+size(ch[0]);
	}
	void reverse(){
		if(!this)return;
		swap(ch[0],ch[1]);
		rev^=1;
	}
	void Pushdown(){
		if(!this)return;
		if(rev){
			ch[0]->reverse();
			ch[1]->reverse();
			rev=0;
		}
	}
	void *operator new (size_t size);
}*root,*C,*num;
void* Node::operator new (size_t size){
	if(C==num){
		C=new Node[1<<15];
		memset(C,0,sizeof(Node)*(1<<15));
		num=C+(1<<15);
	}
	return C++;
}
typedef pair<Node*,Node*> DNode;
Node *Merge(Node *A,Node *B){
	if(!A)return B;
	if(!B)return A;
	if(A->key<B->key){
		A->Pushdown();
		A->ch[1]=Merge(A->ch[1],B);
		A->Pushup();
		return A;
	}else{
		B->Pushdown();
		B->ch[0]=Merge(A,B->ch[0]);
		B->Pushup();
		return B;
	}
}
DNode Split(Node *rt,int k){
	if(!rt)return DNode(NULL,NULL);
	DNode o;
	rt->Pushdown();
	if(size(rt->ch[0])>=k){
		o=Split(rt->ch[0],k);
		rt->ch[0]=o.second;
		rt->Pushup();
		o.second=rt;
	}else{
		o=Split(rt->ch[1],k-size(rt->ch[0])-1);
		rt->ch[1]=o.first;
		rt->Pushup();
		o.first=rt;
	}
	return o;
}
Node *kth(int k){
	DNode x=Split(root,k-1);
	DNode y=Split(x.second,1);
	Node *ans=y.first;
	root=Merge(Merge(x.first,ans),y.second);
	return ans;
}
int Rank(Node* rt,int x){
	if(!rt)return 0;
	return x<=rt->v ? Rank(rt->ch[0],x):Rank(rt->ch[1],x)+size(rt->ch[0])+1;
}
void Insert(int x){
	int k=Rank(root,x);
	DNode y=Split(root,k);
	Node *n=new Node(x);
	root=Merge(Merge(y.first,n),y.second);
}
void remove(int x){
	int k=Rank(root,x);
	DNode a=Split(root,k);
	DNode b=Split(a.second,1);
	root=Merge(a.first,b.second);
}
void dfs(Node* rt){
	if(rt){
		rt->Pushdown();
		dfs(rt->ch[0]);
		now[++idx] = rt->v;
		dfs(rt->ch[1]);
	}
}
Node *st[4000005];
Node *build(int m)
{
    //memset(st, 0, sizeof(st));
    Node *x, *last;
    int p = 0;
    for (int i = 1; i <= m; i++)
    {
        x = new Node(i);
        last = NULL;
        while (p && st[p]->key > x->key)
        {
            st[p]->Pushup();
            last = st[p];
            st[p--] = NULL;
        }
        if (p)
            st[p]->ch[1] = x;
        x->ch[0] = last;
        st[++p] = x;
    }
    while (p)
        st[p--]->Pushup();
    return st[1];
}
void Swap(int l, int r)
{
    DNode x=Split(root,l-1);
    DNode y=Split(x.second,r-l+1);
    y.first->reverse();
    root=Merge(x.first,Merge(y.first,y.second));
}
int fa[500005], a[500005];
char L[500005];
bool flag[500005];
int find(int x)
{
	if(fa[x] != x) fa[x] = find(fa[x]);
	return fa[x];
}
int main()
{
	int n, m;
	long long k;
    scanf("%d%d%lld", &n, &m ,&k);
    scanf("%s", s + 1);
    int c, b;
    root = build(n);
    for (int i = 1; i <= m; i++)
    {
		scanf("%d %d", &c, &b);
		if (c > b) swap(b, c);
        Swap(c, b);
	}
	dfs(root);
    for (int i = 1; i <= n; i++)
        fa[i] = i, L[i] = s[i];
    for (int i = 1; i <= n; i++)
    {
        if(find(i) != find(now[i]))
        {
            if(L[find(i)] != '?')
                L[find(now[i])] = L[find(i)];
            fa[find(i)] = find(now[i]);
        }
    }
    int cnt = 0;
    for (int i = 1; i <= n; i++)
        if(L[find(i)] == '?' && !flag[find(i)]) 
            t[++cnt] = i, flag[find(i)] = 1;
    int pos = 0;
    k--;
    while(k)
    {
        a[++pos] = k % 26;
        k /= 26;
    }
	for (int i = cnt, j = 1; i >= 1; i--, j++) L[find(t[i])] = a[j] + 'a';
	for (int i = 1; i <= n; i++)
	{
		printf("%c", L[find(i)]);
	}
	// while(1);
}