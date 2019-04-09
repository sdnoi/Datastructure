#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;

const int N=10005;
int dep[N],pre[N],preedge[N];
int head[N],ver[N],next[N],edge[N];
bool vis[N];
int tot=1;
void add(int u,int v,int w){
    next[++tot]=head[u];
    head[u]=tot;ver[tot]=v;edge[tot]=w;
}

int bfs(int x){
    memset(dep,0,sizeof(dep));
    memset(vis,0,sizeof(vis));
    queue<int> q;
    q.push(x);
    vis[x]=1;dep[x]=0;pre[x]=-1;
    int maxdep=0xBFFFFFFF,maxver=x;
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int i=head[u];i;i=next[i]){
            int v=ver[i];
            if(vis[v]) continue;
            vis[v]=1;
            dep[v]=dep[u]+edge[i];
            pre[v]=u;preedge[v]=i;
            if(maxdep<dep[v])
            {
                maxdep=dep[v];maxver=v;
            }
            q.push(v);
        }
    }
    return maxver;
}
int main(){
    int n,k;
    scanf("%d%d",&n,&k);
    for(int i=1;i<n;++i){
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v,1);add(v,u,1);

    }
    int u=bfs(1);
    int v=bfs(u);
    int l1=dep[v];
    printf("%d,%d,%d\n",u,v,dep[v]);//直径的两个端点及长度
    while(v!=u){ //修改直径的边权
        int e=preedge[v];
        edge[e]=-1;edge[e^1]=-1;
        printf("%d ",v);
        v=pre[v];
    }
    printf("%d\n",u);

    for(int i=1;i<=n;++i){//检查边权修改对没
      printf("%4d:",i);
      for(int j=head[i];j;j=next[j]){
        int v=ver[j];
        printf("%d(%d),",v,edge[j]);
      }
      printf("\n");
    }
    u=bfs(1);v=bfs(u);//因为出现了负边权,两次bfs不适用了，要用树形DP
    printf("%d,%d,%d\n",u,v,dep[v]);//直径的两个端点及长度
    return 0;
}
