#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;

const int N=10005;
int dep[N],pre[N];
int head[N],ver[N],next[N];
bool vis[N];
int tot=1;
void add(int u,int v){
    next[++tot]=head[u];
    head[u]=tot;ver[tot]=v;
}

int bfs(int x){
    memset(dep,0,sizeof(dep));
    memset(vis,0,sizeof(vis));
    queue<int> q;
    q.push(x);
    vis[x]=1;dep[x]=0;pre[x]=-1;
    int maxdep=0,maxver=x;
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int i=head[u];i;i=next[i]){
            int v=ver[i];
             if(vis[v]) continue;
            vis[v]=1;
            dep[v]=dep[u]+1;
            pre[v]=u;
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
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;++i){
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v);add(v,u);

    }
    int u=bfs(1);
    int v=bfs(u);
    printf("%d,%d\n",u,v);
    while(v!=u){
        printf("%d ",v);
        v=pre[v];
    }
    printf("%d\n",u);
    return 0;
}
