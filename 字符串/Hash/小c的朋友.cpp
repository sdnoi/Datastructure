/*
对于一个点xx我们搞出与这个点相邻的点的集合Adj(x)Adj(x) 
那么如果(x,y)(x,y)之间没有边那么点对(x,y)(x,y)满足条件等价于Adj(x)=Adj(y)Adj(x)=Adj(y) 
如果(x,y)(x,y)之间有边那么点对(x,y)(x,y)满足条件等价于Adj(x)−y=Adj(y)−xAdj(x)−y=Adj(y)−x
怎么表示一个集合呢？我们给一个点赋予一个64位的整数，然后一个集合用集合内所有的点的异或值来代替就行了 
然后一个集合就变成了一个数，没有边的排序处理，有边的枚举边就行了 
时间复杂度O(nlogn+m)
 
*/
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define M 1001001
using namespace std;
struct edge{
    int x,y;
}edges[M];
int n,m;
long long a[M],b[M],ans;
int main()
{
    srand(19980402);
    int i,x,y;
    cin>>n>>m;
    for(i=1;i<=n;i++)
        a[i]=(long long)rand()*rand()+rand();
    for(i=1;i<=m;i++)
    {
        scanf("%d%d",&x,&y);
        edges[i].x=x;
        edges[i].y=y;
        b[x]^=a[y];//x的邻接点集合
        b[y]^=a[x];//y的邻接点集合
    }
    for(i=1;i<=m;i++)//x与y之间有边相连
    {
        x=edges[i].x;
        y=edges[i].y;
        if( (b[x]^a[y])==(b[y]^a[x]) )//这里的异或操作相当于去掉点y，想想用异或加密与解密的原理
            ++ans;
    }
    sort(b+1,b+n+1);
    int cnt=0;
    for(i=1;i<=n;i++)
    {
        ++cnt;//统计边集相同的点的数量
        if(i==n||b[i]!=b[i+1]) //已经到达最后一个点或两个点的边集不相同了则停止计数
            ans+=(long long)cnt*(cnt-1)>>1,cnt=0;//这些点形成的点对的数量为（cnt*(cnt-1)）/2
    }
    cout<<ans<<endl;
    return 0;
}
