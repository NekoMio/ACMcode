/*
根据我个人的理解,cdq分治的原理就和归并排序的一样
与普通分治不同的是,cdq把所有操作一视同仁 把修改和查询一起处理
和莫队有点像? 
再把左区间对右区间的影响统计的一下 
下面是一个简单的树状数组水题,不过可以作为cdq的引例 
哎呀看完之后觉得线段树的题也可以用cdq来水

给定一个N个元素的序列a，初始值全部为0，对这个序列进行以下两种操作：
操作1：格式为1 x k，把位置x的元素加上k（位置从1标号到N）。
操作2：格式为2 x y，求出区间[x,y]内所有元素的和。

我们把他转化成一个二维偏序问题，每个操作用一个有序对(a,b)表示，其中a表示操作到来的时间，b表示操作的位置，
时间是默认有序的，所以我们在合并子问题的过程中，就按照b从小到大的顺序合并。//时间作为默认顺序在很多巧妙的算法里都有使用
下面是关于"序"的一点摘抄: 
对于一个数据结构题而言（或者需要运用数据结构的地方），我们无非就是做两件操作，一是修改，二是查询 
对于修改而言，有插入，删除，变更（其实等价于删除再插入）这几种方式 
那么查询的本质是什么呢 
我们思考所遇到过的数据结构题，可以发现查询实际上就在做一件事情： 
"把符合本次查询的限制的修改对答案产生的效果合并起来" 
满足这种限制通常表现为一种序的要求，并且这种序是广义的，符合限制的操作往往是按某种序（或多种序）排序后的操作的前缀 
通常来说,查询一定有时间上的限制,也就是要求考虑发生在某个时刻之前的所有修改;
对于一个问题而言,假如所有查询要求的发生时刻相同,那这就是一个静态查询问题;
而如果要求发生的时刻随着查询而变,那这就是一个动态修改问题,动态修改问题较静态查询而言复杂很多,往往需要高级数据结构,可持久化等手段;
而静态查询简单很多,例如时间倒流,twopointers之类的方法都是很好的选择 ; 
CDQ分治算法的核心就在于:去掉时间的限制,将所有查询要求发生的时刻同化,化动态修改为静态查询
问题来了：如何表示修改与查询？
我们定义结构体Query包含3个元素：type，idx，val，其中idx表示操作的位置，type为1表示修改，val表示“加上的值”。
而对于查询，我们用前缀和的思想把他分解成两个操作：sum[1,y]-sum[1,x-1]，即分解成两次前缀和的查询。
在合并的过程中，type为2表示遇到了一个查询的左端点x-1，需要把该查询的结果减去当前“加上的值的前缀和”;
type为3表示遇到了一个查询的右端点y，需要把查询的结果加上当前“加上的值的前缀和”，val表示“是第几个查询”。
这样，我们就把每个操作转换成了带有附加信息的有序对(时间，位置)，然后对整个序列进行CDQ分治。
　　有几点需要注意：
 1.对于位置相同的操作，要先修改后查询。//这一点很重要,显然必须把所有修改进行完才能查询 
 2.代码中为了方便，使用左闭右开区间。
 3.合并问题的时候统计“加上的值的前缀和”，只能统计左边区间内的修改操作，改动查询结果的时候，只能修改右边区间内的查询结果。
   因为只有左边区间内的修改值对右边区间内的查询结果的影响还没有统计。
 4.代码中，给定的数组是有初始值的，可以把每个初始值变为一个修改操作。
 */
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cmath>
using namespace std;
typedef long long ll;
const int MAXN = 500001; // 原数组大小
const int MAXM = 500001; // 操作数量
const int MAXQ = (MAXM<<1)+MAXN;
int n,m;
struct Query {
    int type, idx; ll val;
    bool operator<( const Query &rhs ) const { // 按照位置从小到大排序，修改优先于查询
        return idx == rhs.idx ? type < rhs.type : idx < rhs.idx;
		//神奇重载,这样就实现了上面第一点注意的双关键字 
    }
}query[MAXQ];
int qidx = 0,aidx = 0;//qidx表示"是第几个操作",aidx表示"是第几个查询操作" 
ll ans[MAXQ]; // 答案数组
Query tmp[MAXQ]; // 归并用临时数组
void cdq( int L, int R ) {
    if( R-L <= 1 ) return;
    int M = (L+R)>>1;
	cdq(L,M); cdq(M,R);//先要递归处理子区间 
    ll sum = 0;
    int p = L, q = M, o = 0;
    while( p < M && q < R ) {//长得很像归并排序...... 
        if( query[p] < query[q] ) { // 只统计左边区间内的修改值
            if( query[p].type == 1 ) sum += query[p].val;//左边修改之和 
            tmp[o++] = query[p++];
        }
        else { // 只修改右边区间内的查询结果
            if( query[q].type == 2 ) ans[query[q].val] -= sum;
            else if( query[q].type == 3 ) ans[query[q].val] += sum;
            tmp[o++] = query[q++];
        }//为什么只统计左边的修改和右边的查询呢
		//因为,左边右边自己内部的查询&修改已经在之前的递归计算中完成了
		//现在只有"左边的修改对右边查询的影响"没有统计
		//所有只统计这一组 
    }
    while( p < M ) tmp[o++] = query[p++];
    while( q < R ) {
        if( query[q].type == 2 ) ans[query[q].val] -= sum;
        else if( query[q].type == 3 ) ans[query[q].val] += sum;
        tmp[o++] = query[q++];
    }
    for( int i = 0; i < o; ++i ) query[i+L] = tmp[i];//合并 
}
int main() {//本题的顺序就是时间序 
    scanf( "%d%d", &n, &m );
    for( int i = 1; i <= n; ++i ) {//把初始元素变为修改操作
        query[qidx].idx = i; query[qidx].type = 1;
        scanf( "%lld", &query[qidx].val ); ++qidx;
    }
    for( int i = 0; i < m; ++i ) {
        int type; scanf( "%d", &type );
        query[qidx].type = type;
        if( type == 1 ) scanf( "%d%lld", &query[qidx].idx, &query[qidx].val );
        else {//把查询操作分为两部分(也就是常用的前缀和思想) 
            int l,r; scanf( "%d%d", &l, &r );
            query[qidx].idx = l-1; query[qidx].val = aidx; ++qidx;
            query[qidx].type = 3; query[qidx].idx = r; query[qidx].val = aidx; ++aidx;
        }
        ++qidx;
    }
    cdq(0,qidx);
    for( int i = 0; i < aidx; ++i ) printf( "%lld\n", ans[i] );
    return 0;
}
/*
三维偏序对
给定N个有序三元组(a,b,c)，求对于每个三元组(a,b,c)，有多少个三元组(a2,b2,c2)满足a2<a且b2<b且c2<c。
我们发现,这里面没有一个天然的"序",所以我们考虑以a为关键字排序,制造一个序
然后按照b的顺序(可以看成平面坐标系的x轴)归并(把x的不同区间归到一起)
用一个(由于是归并,所以只用一个)树状数组,统计"c值小于目前查询的c值的三元组个数"(其实这里可以把c看成坐标系的y轴)
不过每次归并完,要给树状数组清零(显然的事情啊)
按照上面的思路,我们只需要维护"左面的修改对右面的查询的影响"
不过这里要把查询拆成四个,也就是(x2,y2)-(x2,y1)-(x1,y2)+(x1,y1)
然后水一水,就可以了; 
详细代码放在下面一道例题中. 
*/
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cctype>
using namespace std;
const int MAXN=500001; // 点的数量
const int MAXM=500001; // 询问数量
const int MAXQ=MAXN+(MAXM<<2);
const int MAXL=10000002; // 树状数组大小
int n,m,maxy=-1;
struct Query 
{
    int type, x, y, w, aid; // w表示对查询结果贡献(+还是-)，aid是“第几个查询”
    bool operator<( const Query &rhs ) const 
	{
        return x == rhs.x ? type < rhs.type : x < rhs.x; //这个重载很妙...... 
    }
}query[MAXQ];
int qidx = 0;
int ans[MAXM], aidx = 0;
namespace BIT 
{ // 树状数组相关
    int arr[MAXL];
    inline int lowbit( int num ) { return num&(-num); }
    void add( int idx, int val ) {
        while( idx <= maxy ) {
            arr[idx] += val;
            idx += lowbit(idx);
        }
    }
    int query( int idx ) {
        int ans = 0;
        while( idx ) {
            ans += arr[idx];
            idx -= lowbit(idx);
        }
        return ans;
    }
    void clear( int idx ){
        while( idx <= maxy ) {
            if( arr[idx] ) arr[idx] = 0; else break;
            idx += lowbit(idx);
        }
    }
}
Query tmp[MAXQ];
void cdq( int L, int R ) {
    if( R-L <= 1 ) return;
    int M = (L+R)>>1; cdq(L,M); cdq(M,R);
    int p = L, q = M, o = L;
    while( p < M && q < R ) {
        if( query[p] < query[q] ) {
            if( query[p].type == 0 ) BIT::add( query[p].y, 1 );
            tmp[o++] = query[p++];
        } else {
            if( query[q].type == 1 ) ans[query[q].aid] += query[q].w * BIT::query( query[q].y );
            tmp[o++] = query[q++];
        }
    }
    while( p < M ) tmp[o++] = query[p++];
    while( q < R ) {
        if( query[q].type == 1 ) ans[query[q].aid] += query[q].w * BIT::query( query[q].y );
        tmp[o++] = query[q++];
    }
    for( int i = L; i < R; ++i ) {
        BIT::clear( tmp[i].y ); // 清空树状数组
        query[i] = tmp[i];
    }
}
void addq( int type, int x, int y, int w, int aid ) {
    query[qidx++] = (Query){type,x,y,w,aid};
}
int main() {
    scanf("%d%d",&n,&m); 
    int x,y,x1,y1,x2,y2;
    while(n--)
	{
        scanf("%d%d",&x,&y);++x;++y;//为了方便，把坐标转化为[1,1e7+1]
        addq(0,x,y,0,0);maxy=max(maxy,y);//修改操作无附加信息
    }
    while(m--) 
	{
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);++x1;++y1;++x2;++y2;
        addq(1,x1-1,y1-1,1,aidx); addq(1,x1-1,y2,-1,aidx); addq(1,x2,y1-1,-1,aidx); addq(1,x2,y2,1,aidx); ++aidx;
        maxy=max(maxy,max(y1,y2));
    }
    cdq(0,qidx);
    for(int i=0;i<aidx;++i) printf("%d\n",ans[i]);
    return 0;
}
