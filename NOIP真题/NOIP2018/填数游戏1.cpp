/*
方法：搜索
*/
#include<bits/stdc++.h>
using namespace std;
const int N=100;int val[N][N],Rv[N],a[N][N],ans,no_ans,las;
int ok(int x,int y,int n,int m,int cur)//从（x,y)到（n,m) cur表示按照规则走到当前位置形成的01串
{
      if(no_ans) //不为0，就直接返回，不用再搜索了
             return 0;
       cur<<=1,cur|=a[x][y];//记录从（1,1）按规则走到当前的位置的路径的01串
       if(x==n&&y==m) //到达检测的位置
    	     return no_ans|=(cur<las),las=cur;//本次得到的路径要大于等于上次的路径才符合要求
                                 //只要有过一次cur<las，那么no_ans就会为1，只有cur都不小于las，no_ans才为0
	if(y==m)//到目标点的上方了，就只能往下走
   	  ok(x+1,y,n,m,cur);
	else if(x==n) //到目标点的左方了，就只能往右走
   	  ok(x,y+1,n,m,cur);
	else //先往右走，再往下走，由于按这个顺序，因此回溯时往下(即d)的先返回，往右（即r)的后返回
   	  ok(x,y+1,n,m,cur),ok(x+1,y,n,m,cur);
	return 0;
}
inline int can(int x,int y,int v) {

  a[x][y]=v,no_ans=0,las=0;
  ok(1,1,x,y,0);//检测(x,y)处可否放置a[x][y]
  return !no_ans; //no_ans为0表示可以
}
int dfs(int x,int y,int n,int m) //按行搜索
{
	if(x==n+1) return ++ans;
	for(int i=0;i<=1;i++)
	if(can(x,y,i))//i可以放在x,y处
	{
	 a[x][y]=i;//a数组记录（x,y)处存放的数字
	if(y>1)  //与上一个位置同一行
         val[x][y]=(val[x][y-1]<<1)|a[x][y];
	else    //在上一个位置的下一行 的第1个位置
         val[x][y]=(val[x-1][y]<<1)|a[x][y];
	if(y==m)//本行走完了，走下一行
          dfs(x+1,1,n,m);
	else//在本行继续向右走
          dfs(x,y+1,n,m);
	}
	return 0;
}
inline int calc(int n,int m) {
  return ans=0,dfs(1,1,n,m),ans;
}
int main()
{
	for(int n=2;n<=7;n++)
	{
		printf("ans(%d, %d) = %d\n",n,n,calc(n,n));
		printf("ans(%d, %d) = %d\n",n,n+1,calc(n,n+1));
//	printf("ans(%d, %d) = %d\n",n,n+2,calc(n,n+2));
//	printf("ans(%d, %d) = %d\n",n,n+3,calc(n,n+3));
	}
	return 0;
}
