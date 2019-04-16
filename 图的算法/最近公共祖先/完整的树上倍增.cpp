#include<bits/stdc++.h>
using namespace std;
const int SIZE = 500010;
int head[SIZE],ver[SIZE*2],Next[SIZE*2],edge[SIZE*2];
int dep[SIZE];
int tot;
bool vis[SIZE];
int fat[SIZE][22];
void add(int x,int y,int z) {
	ver[++tot]=y,Next[tot]=head[x],edge[tot]=z,head[x]=tot;
}


void dfs(int x){//预处理

   for(int i=head[x];i;i=Next[i]){
     int v=ver[i];
     if(vis[v]) continue;
     vis[v]=1;
     dep[v]=dep[x]+1;
     fat[v][0]=x;
     for(int j=1;j<20;++j){
        fat[v][j]=fat[fat[v][j-1]][j-1];
    }
    dfs(v);
   }
}

int lca(int x,int y){
  if(dep[x]<dep[y]) swap(x,y);
  for(int i=19;dep[x]!=dep[y];--i){
    if(dep[fat[x][i]]>=dep[y]){
        x=fat[x][i];
    }
  }

 /* 跳深度的差值步*/
//  int d=dep[x]-dep[y];
//  int step=0;
//  while(d){
//    if(d&1)
//     x=fat[x][step];
//   step++;
//   d>>=1;
//  }
 //printf("%d %d\n",dep[x],dep[y]);

 if(x==y) return x;
 for(int i=19;i>=0;--i) //注意i>=0,i可以为0
  {
    if(fat[x][i]!=fat[y][i]){
     x=fat[x][i];
     y=fat[y][i];
    }
  }
  return fat[x][0];
}

int main(){
  int n,m;
	scanf("%d",&n);
	for(int i=1;i<=n-1;i++){
	  int x,y;
		scanf("%d%d",&x,&y);
		add(x,y,1);add(y,x,1);
	}
	for(int i=1;i<=n;++i){//测试代码
       printf("%d:",i);
       for(int j=head[i];j;j=Next[j]) {
         int v=ver[j];
         printf("%d ",v);

       }
       printf("\n");

	}

  vis[1]=1;//设置根节点已访问标志
  dfs(1);

	for(int i=1;i<n+1;++i){//测试代码
        for(int j=0;j<4;++j)
            printf("f[%d][%d]=%d ",i,j,fat[i][j]);
    printf("\n");
	}
  scanf("%d",&m);
	for(int i=0;i<m;++i){
	  int u,v;
	  scanf("%d%d",&u,&v);
    printf("%d\n",lca(u,v));
	}

	return 0;
}
