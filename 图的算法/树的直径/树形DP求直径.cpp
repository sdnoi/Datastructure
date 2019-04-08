#include <vector>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define INF 0x3f3f3f3f
#define N 10005
using namespace std;
int head[N],ver[N],edge[N],next[N];
int d[N],f[N];
int tot;
bool vis[N];
void add(int u,int v,int w) {

    ver[++tot]=v;
    edge[tot]=w;
    next[tot]=head[u];
    head[u]=tot;

}
void dfs(int x) {
    vis[x]=1;
    for(int i=head[x]; i; i=next[i]) {
        int  y=ver[i],w=edge[i];
        if(vis[y]) continue;
        dfs(y);

        if(f[x]<d[x]+d[y]+w)
            f[x]=d[x]+d[y]+w;
        if(d[x]<d[y]+w)
            d[x]=d[y]+w;
    }
    printf("%d ",x); //搜索完毕的点
}

void adj(int n) {
    for(int i=1; i<=n; ++i) {
      printf("%d->",i);
        for(int j=head[i]; j; j=next[j]) {
            int  v=ver[j],w=edge[j];
            printf("%d ",v);
        }
      printf("\n");
    }
}
int main() {
    int n,m;
    scanf("%d%d",&n,&m);
    int u,v;
    for(int i=0; i<m; ++i) {
        scanf("%d%d",&u,&v);
        add(u,v,1);
        add(v,u,1);
    }
    adj(n); //输出邻接表，检查图建对没有
    dfs(4);//以x为最初的根进行DFS搜索
    printf("\n");
    for(int i=1; i<=n; ++i) //每个F[i]的值代表以i为根的子树中的且经过i的最长链
        printf("%d ",f[i]);

    return 0;
}
/*
10 9
1 2
1 4
1 3
2 5
2 6
3 7
3 8
3 9
9 10
*/
