#include <cstdio>
#include <cstdlib>
#define maxm 200010
struct edge{int to,len,next;}E[maxm];
int cnt,last[maxm],fa[maxm],top[maxm],deep[maxm],siz[maxm],son[maxm],val[maxm];
void addedge(int a,int b,int len=0)
{
    E[++cnt]=(edge){b,len,last[a]},last[a]=cnt;
}
void dfs1(int x)
{
    deep[x]=deep[fa[x]]+1;siz[x]=1;
    for(int i=last[x];i;i=E[i].next)
    {
        int to=E[i].to;
        if(fa[x]!=to&&!fa[to]){
            val[to]=E[i].len;
            fa[to]=x;
            dfs1(to);
            siz[x]+=siz[to];
            if(siz[son[x]]<siz[to])son[x]=to;
        }
    }
}
void dfs2(int x)
{
    if(x==son[fa[x]])top[x]=top[fa[x]];
    else top[x]=x;
    for(int i=last[x];i;i=E[i].next)if(fa[E[i].to]==x)dfs2(E[i].to);
}
void init(int root){dfs1(root),dfs2(root);}
int query(int x,int y)
{
    for(;top[x]!=top[y];deep[top[x]]>deep[top[y]]?x=fa[top[x]]:y=fa[top[y]]);
    return deep[x]<deep[y]?x:y;
}
int n,m,x,y,v;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<n;i++)
    {
        scanf("%d%d",&x,&y);addedge(x,y,v);addedge(y,x,v);
    }
    init(1);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&x,&y);
        printf("%d\n",query(x,y));
    }
    return 0 ;
}
