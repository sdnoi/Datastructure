#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define fo(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
#define N 12100
using namespace std;
int deep[N],fa[N],hzj[N],last[N*10],next[N*10],to[N*10],n,data[N*10],f[N][14],g[N][14],las2[N*10],nex2[N*10],t2[N*10],dat2[N*10],tot=1,totot=1,ttt=0,tt=0,m,ans,a[N][3],s[N][2],sy[N][4],ss=0,yj,lb[N][3],dfn[N*10],jy;
bool bz[N*10];
void putin(int x,int y,int z)
{
    next[++tot]=last[x];last[x]=tot;to[tot]=y;data[tot]=z;
    next[++tot]=last[y];last[y]=tot;to[tot]=x;data[tot]=z;
}
void link(int x,int y,int z)
{
    nex2[++totot]=las2[x];las2[x]=totot;t2[totot]=y;dat2[totot]=z;
    nex2[++totot]=las2[y];las2[y]=totot;t2[totot]=x;dat2[totot]=z;
}
void zh(int x,int y,int fa)
{
    dfn[x]=++ttt;
    for(int i=last[x];i;i=next[i])
    {
        int k=to[i];
        if (k==fa && i==(y^1)) continue;
        if (dfn[k]<dfn[x] && dfn[k]!=0) //k到x构成一个环，k为环顶
        {
            int jy=data[i];tt++;//jy存储环的周长，tt表示环的编号
            for(int l=ss;s[l][0]!=k;l--)//绕环一圈，算周长
              jy+=s[l][1];
            sy[x][0]=tt;sy[x][1]=k;sy[x][2]=data[i];sy[x][3]=jy-data[i];
            link(k,x,min(sy[x][2],sy[x][3]));
            for(int l=ss-1;s[l][0]!=k;l--) //环上其它点连到环顶
            {
                int z=s[l][0];
                sy[z][0]=tt;//所在环的编号
                sy[z][1]=k;//所在环的环顶
                sy[z][2]=sy[s[l+1][0]][2]+s[l+1][1];//到环顶的距离
                sy[z][3]=jy-sy[z][2];//从另一个方向到环顶的距离
                link(k,z,min(sy[z][2],sy[z][3]));
            }
            continue;
        }
        if (dfn[to[i]]!=0) continue;
        s[++ss][0]=k;s[ss][1]=data[i];//s栈：存储当前的路径上的点及边长
        zh(k,i,x);
    }
    ss--;//本节点访问完毕，"出栈"
}
void dfs3(int x)
{
    for(int i=las2[x];i;i=nex2[i])
    {
        if (t2[i]==fa[x]) continue;
        fa[t2[i]]=x;
        hzj[t2[i]]=dat2[i];
        deep[t2[i]]=deep[x]+1;
        dfs3(t2[i]);
    }
}
int lca(int x,int y)
{
    int an=0;
    //将x与y移动到同一层，并计算移动的距离
    fd(i,13,0) if (deep[f[x][i]]>=deep[y]) an+=g[x][i],x=f[x][i];
    fd(i,13,0) if (deep[f[y][i]]>=deep[x]) an+=g[y][i],y=f[y][i];

    fd(i,13,0)
      if (f[x][i]!=f[y][i]) {
        an=an+g[x][i]+g[y][i];x=f[x][i];y=f[y][i];
        }
    if (x==y) //x与y在同一条链中
     return an;
    if (x!=y && sy[x][0]==sy[y][0] && sy[x][0]!=0)//x,y在同一个环中，
    //x经过环顶到y：min(sy[x][2]+sy[y][3],(sy[x][3]+sy[y][2]))
    //x不经过环顶到y：abs(sy[x][2]-sy[y][2])
      an+=min(sy[x][2]+sy[y][3],min(sy[x][3]+sy[y][2],abs(sy[x][2]-sy[y][2])));
    else
      an+=g[x][0]+g[y][0];
    return an;
}

int main()
{
    int nm;
    scanf("%d%d%d",&n,&m,&nm);
    fo(i,1,m)
    {
        int x,y,z;scanf("%d%d%d",&x,&y,&z);
        putin(x,y,z);
        lb[i][1]=x;lb[i][2]=y;lb[i][0]=z;
    }
    fo(i,1,nm) scanf("%d%d",&a[i][1],&a[i][2]);
    ss=1;s[1][0]=1;s[1][1]=0;
    zh(1,-1,0);//找环，并将环上点直接连到环顶
    fo(i,1,m)//将非环上的边加到新建的图中
    {
        int x=lb[i][1],y=lb[i][2],z=lb[i][0];
        if ((sy[x][0]!=sy[y][0]|| sy[x][0]==0 || sy[x][0]==0) && sy[x][1]!=y && sy[y][1]!=x)
        //如果x,y不在同一个环，或x不在环上 且
          link(x,y,z);
    }
    deep[1]=1;
    dfs3(1);//找出新图中各点的深度、父亲
    fo(i,1,n)
      f[i][0]=fa[i],g[i][0]=hzj[i];
    fo(j,1,13)//lca倍增的预处理
        fo(i,1,n)
        {
            f[i][j]=f[f[i][j-1]][j-1];
            if (f[i][j]) g[i][j]=g[i][j-1]+g[f[i][j-1]][j-1];
        }
    fo(i,1,nm)
    {
        int x=a[i][1],y=a[i][2];
        ans=lca(x,y);
        printf("%d\n",ans);
    }
}

/*
输入: 
13 16 4 
1 2 1 
2 4 1 
1 3 1 
3 4 4 
3 12 1 
12 13 1 
13 3 3 
3 10 1 
3 11 1 
10 11 1 
4 6 3 
4 5 1 
5 6 1 
6 8 1 
8 7 1 
8 9 1 
12 13 
9 13 
11 4 
13 11 

输出： 
1 
9 
4 
3

*/
