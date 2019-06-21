#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
class Treap{
    class Node{
    public:
        int size,v,key;
        Node *ch[2];
        Node(int x){
            key=rand();v=x;size=1;
            ch[0]=ch[1]=NULL;
        }
        #define size(_) ((_)?(_)->size:0)
        void Pushup(){
            size=size(ch[0])+size(ch[1])+1;
        }
        void *operator new (size_t size);
    }*root;
    Node *Merge(Node *A,Node *B){
        if(!A)return B;
        if(!B)return A;
        if(A->key>B->key){
            A->ch[1]=Merge(A->ch[1],B);
            A->Pushup();
            return A;
        }
        else {
            B->ch[0]=Merge(A,B->ch[0]);
            B->Pushup();
            return B;
        }
    }
    typedef pair<Node*,Node*> DNode;
    DNode Split(Node *rt,int k){
        if(!rt)return DNode(NULL,NULL);
        DNode o;
        if(size(rt->ch[0])>=k){
            o=Split(rt->ch[0],k);
            rt->ch[0]=o.second;
            rt->Pushup();
            o.second=rt;
        }
        else{
            o=Split(rt->ch[1],k-size(rt->ch[0])-1);
            rt->ch[1]=o.first;
            rt->Pushup();
            o.first=rt;
        }
        return o;
    }
public:
    Treap(){
        root=NULL;
    }
    int kth(int k){
        DNode x=Split(root,k-1);
        DNode y=Split(x.second,1);
        Node *ans=y.first;
        root=Merge(x.first,Merge(y.first,y.second));
        return ans->v;
    }
    int rank(int x){
        return rank(root,x);
    }
    int rank(Node *rt,int x){
        if(!rt)return 0;
        return x<=rt->v?rank(rt->ch[0],x):rank(rt->ch[1],x)+size(rt->ch[0])+1;
    }
    void Insert(int x){
        int k=rank(root,x);
        DNode y=Split(root,k);
        Node *n=new Node(x);
        root=Merge(Merge(y.first,n),y.second);
    }
    void remove(int x){
        int k=rank(root,x);
        DNode a=Split(root,k);
        DNode b=Split(a.second,1);
        root=Merge(a.first,b.second);
    }
}root;
int main()
{
    freopen("tb_kp.in", "r", stdin);
    freopen("tb_kp.out", "w", stdout);
    srand(0);
	int n,op,x;
	scanf("%d",&n);
    root.Insert(-0x3f3f3f3f);
    root.Insert(+0x3f3f3f3f);
    int t=0;
	while(n--){
		scanf("%d",&op);
		switch(op){
			case 1:scanf("%d",&x);root.Insert(x);t++;break;
			case 2:scanf("%d",&x);root.remove(x);t--;break;
			case 3:scanf("%d",&x);printf("%d\n",root.rank(x));break;
			case 4:scanf("%d",&x);printf("%d\n",root.kth(x+1));break;
			case 5:scanf("%d",&x);printf("%d\n",root.kth(root.rank(x)));break;
			case 6:scanf("%d",&x);printf("%d\n",root.kth(root.rank(x+1)+1));break;
            case 7:printf("%d\n",root.kth(2));break;
            case 8:printf("%d\n",root.kth(t+1));
		}
	}
    //int n,m;
    //scanf("%d%d",&n,&m);
    //for(int i=1;i<=n;i++)scanf("%d",a[i]);
}