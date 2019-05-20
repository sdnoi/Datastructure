#include<bits/stdc++.h>
using namespace std;
const int N=5000;
set< pair< int,int > > lnk[N+5];
int n,m,del;
int ans[N+5],res[N+5]; //ans为最终答案，res为当前贪心得到的答案
bool Prefer(){ //判断ans和res谁更优
    for(int i=1;i<=n;i++){
        if(ans[i]<res[i]) return false;
        if(ans[i]>res[i]) return true;
    }
    return false;
}
int vis[N+5],tag;
void DFS(int u){
    vis[u]=tag;
    res[++res[0]]=u;
    if(res[0]==n && Prefer())
        memcpy(ans,res,sizeof res);
    for(set< pair< int,int > >::iterator it=lnk[u].begin();it!=lnk[u].end();it++){
        int v=it->first,id=it->second;
        if(vis[v]==tag || id==del) continue; //如果是访问过的点或者经过了删除了的边
        DFS(v);
    }
}
int cir[N+5],beg,ok;
void Circle(int u,int pre){
    vis[u]=tag;
    for(set< pair< int,int > >::iterator it=lnk[u].begin();it!=lnk[u].end();it++){
        int v=it->first,id=it->second;
        if(v==pre || id==cir[1]) continue; //如果是父亲，或者是环的末端
        if(vis[v]==tag){
            beg=v,ok=true,cir[++cir[0]]=id; //找到环，退出
            break;
        }
        Circle(v,u);
        if(ok) cir[++cir[0]]=id; //存储环
        if(u==beg) ok=false; //完成整个环的搜索，结束存储
    }
}
int main(){
    ans[1]=(1<<29); //将ans的字典序初始化为最大
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++){
        int u,v;scanf("%d%d",&u,&v);
        lnk[u].insert(make_pair(v,i)); //用set存储，用pair的first存储相邻点，second存储边的编号
        lnk[v].insert(make_pair(u,i)); //这样就可以直接给邻接表排序
    }
    if(n==m){
        tag=-1; //一个简单的vis标记，只要vis[u]!=tag，那么u在这次搜索中就没有被访问过（每次用一个不同的值代表访问标记，就可以省去memset）
        Circle(1,-1); //找环
        for(int i=1;i<=cir[0];i++){ //枚举删边
            del=cir[i];tag=i;res[0]=0; //注意清空res
            DFS(1);
        }
    }
    else{
        del=-1;tag=1; //不删除任何点
        DFS(1);
    }
    for(int i=1;i<=n;i++)
        printf("%d%c",ans[i],i==n?'\n':' ');
    return 0;
}
