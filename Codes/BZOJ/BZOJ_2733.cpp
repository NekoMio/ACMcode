#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct Node{
    int v,key,size;
    Node *ch[2];
    Node(int x){
        v=x;key=rand();size=1;
        ch[0]=ch[1]=NULL;
    }
    #define size(_) ((_)?(_)->size:(0))
    void Pushup(){
        size=1+size(ch[1])+size(ch[0]);
    }
};
typedef pair<Node*,Node*> DNode;
Node *Merge(Node *A,Node *B){
    if(!A)return B;
    if(!B)return A;
    if(A->key<B->key){
        A->ch[1]=Merge(A->ch[1],B);
        A->Pushup();
        return A;
    }else{
        B->ch[0]=Merge(A,B->ch[0]);
        B->Pushup();
        return B;
    }
}
DNode Split(Node *rt,int k){
    if(!rt)return DNode(NULL,NULL);
    DNode o;
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
Node *kth(Node* rt,int k){
    DNode x=Split(rt,k-1);
    DNode y=Split(x.second,1);
    Node *ans=y.first;
    rt=Merge(Merge(x.first,ans),y.second);
    return ans;
}
int Rank(Node *rt,int x){
    if(!rt)return 0;
    return x<=rt->v?Rank(rt->ch[0],x):Rank(rt->ch[1],x)+size(rt->ch[0])+1;
}
Node* Insert(Node* rt,int x){
    int k=Rank(rt,x);
    DNode a=Split(rt,k);
    Node *n=new Node(x);
    return Merge(Merge(a.first,n),a.second);
}
Node* f[100005];
int father[100005];
int find(int x){
    if(x!=father[x])father[x]=find(father[x]);
    return father[x];
}
void dfs(Node *&root,Node *rt){
    if(rt){
        dfs(root,rt->ch[0]);
        root=Insert(root,rt->v);
        dfs(root,rt->ch[1]);
    }
}
int v[100005],s[100005];
int main()
{
    //freopen("bzoj_2733.in","r",stdin);
    //freopen("bzoj_2733.out","w",stdout);
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){scanf("%d",v+i);s[v[i]]=i;}
    for(int i=1;i<=n;i++){father[i]=i;f[i]=Insert(f[i],v[i]);}
    int a,b;
    for(int i=1;i<=m;i++){
        scanf("%d%d",&a,&b);
        int x=find(a),y=find(b);
        if(x!=y){
            if(size(f[x])<size(f[y]))swap(x,y);
            father[y]=x;
            dfs(f[x],f[y]);
        }
    }
    int Q;scanf("%d",&Q);
    char c[3];
    for(int i=1;i<=Q;i++){
        scanf("%s%d%d",c,&a,&b);
        if(c[0]=='Q'){
            Node *ans=kth(f[find(a)],b);
            if(ans==NULL)printf("-1\n");
            else printf("%d\n",s[ans->v]);
        }
        else{
            int x=find(a),y=find(b);
            if(x!=y){
                if(size(f[x])<size(f[y]))swap(x,y);
                father[y]=x;
                dfs(f[x],f[y]);
            }   
        }
    }
}