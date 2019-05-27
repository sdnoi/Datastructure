#include<set>
#include<map>
#include<stack>
#include<ctime>
#include<cstdio>
#include<queue>
#include<cmath>
#include<vector>
#include<cstring>
#include<climits>
#include<iostream>
#include<algorithm>
using namespace std;
#define LL long long
int read(){
    int f=1,x=0;char c=getchar();
    while(c<'0'||'9'<c){if(c=='-')f=-1;c=getchar();}
    while('0'<=c&&c<='9'){x=x*10+c-'0';c=getchar();}
    return f*x;
}
#define MAXN 100000
#define INF 214748364700ll
int n,m,p[MAXN+5];
vector<int> G[MAXN+5];
inline void Addedge(int u,int v){
    G[u].push_back(v);
    G[v].push_back(u);
    return ;
}
int dep[MAXN+5],fa[MAXN+5][20];
LL f[MAXN+5][20][2][2],g[MAXN+5][2];
void DFS(int u){//算出g数组，即没有任何条件要求时的值
    int siz=G[u].size();
    g[u][1]=p[u];
    dep[u]=dep[fa[u][0]]+1;
    for(int i=0;i<siz;i++){
        int v=G[u][i];
        if(v==fa[u][0]) continue;
        fa[v][0]=u;
        DFS(v);
        g[u][0]+=g[v][1];
        g[u][1]+=min(g[v][0],g[v][1]);
    }//!!
    return ;
}
void Prepare(){
    /*
    puts("");
    for(int i=1;i<=n;i++)
        printf("%lld %lld\n",g[i][0],g[i][1]);
    */
    for(int i=1;i<=n;i++){
        f[i][0][0][0]=INF;
        f[i][0][1][0]=g[fa[i][0]][0]-g[i][1];
        f[i][0][0][1]=f[i][0][1][1]=g[fa[i][0]][1]-min(g[i][0],g[i][1]);
        //printf("%lld %lld %lld %lld\n",f[i][j][0][0],f[i][j][0][1],f[i][j][1][0],f[i][j][1][1]);
    }
    for(int j=1;j<=int(log2(n));j++)
        for(int i=1;i<=n;i++){
            int k=fa[i][j-1];
            fa[i][j]=fa[fa[i][j-1]][j-1];  //倍增
            //因为f[i][j][][]的含义是不含i这棵子树，所以在合并时（即加法）就不会多算
            f[i][j][0][0]=min(f[i][j-1][0][0]+f[k][j-1][0][0],f[i][j-1][0][1]+f[k][j-1][1][0]);
            f[i][j][0][1]=min(f[i][j-1][0][0]+f[k][j-1][0][1],f[i][j-1][0][1]+f[k][j-1][1][1]);
            f[i][j][1][0]=min(f[i][j-1][1][0]+f[k][j-1][0][0],f[i][j-1][1][1]+f[k][j-1][1][0]);
            f[i][j][1][1]=min(f[i][j-1][1][0]+f[k][j-1][0][1],f[i][j-1][1][1]+f[k][j-1][1][1]);
        //  printf("%lld %lld %lld %lld\n",f[i][j][0][0],f[i][j][0][1],f[i][j][1][0],f[i][j][1][1]);
        }
    return ;
}
LL LCA(int u,int x,int v,int y){
    if(dep[u]<dep[v]) swap(u,v),swap(x,y);
    int d=dep[u]-dep[v];
    LL Lca,u0=INF,u1=INF,v0=INF,v1=INF,l0=INF,l1=INF;//u0表示u不选时的值，u1表时u要选时的值，其它变量含义类似
    !x?u0=g[u][0]:u1=g[u][1];//如果x为0（即不选），那么u0更新为g[u][0],u1不变（即认为无穷大）。反之，类似。
    !y?v0=g[v][0]:v1=g[v][1];
    //puts("");
    for(int j=0;j<=int(log2(d));j++)//爬到同一层
        if(d&(1<<j)){
            LL t0=u0,t1=u1;
            u0=min(t0+f[u][j][0][0],t1+f[u][j][1][0]);//u不选
            u1=min(t0+f[u][j][0][1],t1+f[u][j][1][1]);//u要选
            u=fa[u][j];
            //printf("%lld %lld\n",u0,u1);
        }
    //printf("%d %d*\n",u,v);
    if(u==v)
        Lca=u,!y?l0=u0:l1=u1;
    else{
        for(int j=int(log2(n));j>=0;j--)//!!
            if(fa[u][j]!=fa[v][j]){
                LL t0=u0,t1=u1;
                u0=min(t0+f[u][j][0][0],t1+f[u][j][1][0]);
                u1=min(t0+f[u][j][0][1],t1+f[u][j][1][1]);
                t0=v0,t1=v1;
                v0=min(t0+f[v][j][0][0],t1+f[v][j][1][0]);
                v1=min(t0+f[v][j][0][1],t1+f[v][j][1][1]);
                u=fa[u][j],v=fa[v][j];
            }
        Lca=fa[u][0];
        l0=g[Lca][0]-g[u][1]-g[v][1]+u1+v1;
        l1=g[Lca][1]-min(g[u][0],g[u][1])-min(g[v][0],g[v][1])+min(u0,u1)+min(v0,v1);
    }
    //printf("***%lld %lld %lld\n",Lca,l0,l1);
    d=dep[Lca]-dep[1];
    for(int j=0;j<=int(log2(d));j++)
        if(d&(1<<j)){
            LL t0=l0,t1=l1;
            l0=min(t0+f[Lca][j][0][0],t1+f[Lca][j][1][0]);
            l1=min(t0+f[Lca][j][0][1],t1+f[Lca][j][1][1]);
            Lca=fa[Lca][j];
        }
    LL ret=min(l0,l1);
    return ret>=INF?-1:ret;
}
int main(){
    char Re[5];
    n=read(),m=read(),scanf("%s",Re);
    for(int i=1;i<=n;i++)
        p[i]=read();
    for(int i=1;i<n;i++){
        int u=read(),v=read();
        Addedge(u,v);
    }
    DFS(1);
    Prepare();
    for(int i=1;i<=m;i++){
        int a=read(),x=read(),b=read(),y=read();
        printf("%lld\n",LCA(a,x,b,y));
    }
    return 0;
}
