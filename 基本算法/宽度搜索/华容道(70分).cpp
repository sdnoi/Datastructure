#include <bits/stdc++.h>
using namespace std;

const int Max=31;
const int fx[5]={0,1,0,-1,0};
const int fy[5]={0,0,1,0,-1};
int n,m,ans,q;
int sx,sy,tx,ty,x,y;
int num[Max][Max],vis[Max][Max][Max][Max];
struct shu{int x,y,sx,sy,step;};
shu p[5000001];

inline int get_int()
{
	int x=0,f=1;
	char c;
	for(c=getchar();(!isdigit(c))&&(c!='-');c=getchar());
	if(c=='-') f=-1,c=getchar();
	for(;isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+c-'0';
	return x*f;
}

inline int bfs()
{
	int head=0,tail=1;
	p[1].x=x,p[1].y=y,p[1].sx=sx,p[1].sy=sy;
	while(head<tail)
	{
	  int x=p[++head].x,y=p[head].y;//当前的空白格子 
	  for(int i=1;i<=4;i++)
	  {
	  	int x1=x+fx[i],y1=y+fy[i]; //移动空白格子 
	  	int xx=p[head].sx,yy=p[head].sy;//当前起始棋子 的坐标 
	  	if(x1==xx&&y1==yy)//空白走到了起始棋子当前的位置
            xx=x,yy=y; //更新起始棋子的坐标 
	  	if(x1<1||x1>n||y1<1||y1>m||!num[x1][y1]||vis[x1][y1][xx][yy]) //空白越界或当前移动到的位置有障碍或已访问过 
            continue;
	  	tail++;
	  	p[tail].sx=xx,p[tail].sy=yy,	p[tail].x=x1,p[tail].y=y1,p[tail].step=p[head].step+1; //扩展一个新状态
		vis[x1][y1][xx][yy]=1;
	  	if(p[tail].sx==tx&&p[tail].sy==ty) //起始棋子到达终点 
	  	return p[tail].step;
	  }
	}
	return -1;
}

int main()
{
	n=get_int(),m=get_int(),q=get_int();
	for(int i=1;i<=n;i++)
	  for(int j=1;j<=m;j++)
	    num[i][j]=get_int();
	while(q--)
	{
	  memset(vis,0,sizeof(vis));
	  x=get_int(),y=get_int(),sx=get_int(),sy=get_int(),tx=get_int(),ty=get_int();
	  if(sx==tx&&sy==ty) cout<<"0\n";
	  else
	  {
	    ans=bfs();
	    cout<<ans<<"\n";
	  }
	}
	return 0;

}
