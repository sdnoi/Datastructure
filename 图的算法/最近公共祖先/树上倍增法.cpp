#include<bits/stdc++.h>
using namespace std;
const int SIZE = 500010;
int head[SIZE],ver[SIZE*2],Next[SIZE*2],edge[SIZE*2];
int fa[SIZE],f[SIZE],d[SIZE],a[SIZE];
int n,s,m,tot,l,r,x,y,z,temp,ans;
bool vis[SIZE];
int fat[SIZE][22];
void add(int x,int y,int z) {
	ver[++tot]=y,Next[tot]=head[x],edge[tot]=z,head[x]=tot;
}


void dfs(int x){

   for(int i=head[x];i;i=Next[i]){
     int v=ver[i];
     if(vis[v]) continue;
     vis[v]=1;
     fat[v][0]=x;
     for(int j=1;j<20;++j){
        fat[v][j]=fat[fat[v][j-1]][j-1];
    }
    dfs(v);
   }
}



int main(){
	scanf("%d",&n);
	for(int i=1;i<=n-1;i++){
		scanf("%d%d",&x,&y);
		add(x,y,1);add(y,x,1);
	}
	for(int i=1;i<=n;++i){
       printf("%d:",i);
       for(int j=head[i];j;j=Next[j]) {
         int v=ver[j];
         printf("%d ",v);

       }
       printf("\n");

	}
   vis[1]=1;//设置根节点已访问标志
    dfs(1);
	for(int i=1;i<n+1;++i){
        for(int j=0;j<4;++j)
            printf("f[%d][%d]=%d ",i,j,fat[i][j]);
    printf("\n");
	}

	return 0;
}
