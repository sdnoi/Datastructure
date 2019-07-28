/*
直接暴力做前缀和，再暴力枚举右下节点即可，注意常数。
这道题有一个坑，就是边界上的点不算，所以我们要求 边长为R-1的矩形.
*/
##include<stdio.h>
#include<iostream>
#include<math.h>
using namespace std;
int map[5005][5005]={0};
//int dp[5005][5005]={0};
int main()
{
	int N,R;
	int x,y,w;
	cin>>N>>R;
	int n = R,m = R;
	for(int i=0;i<N;i++)
	{
		cin>>x>>y>>w;
		x++; y++;
		map[x][y]+=w;
		n = max(n,x);
		m = max(m,y);
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			map[i][j] +=map[i-1][j]+map[i][j-1]-map[i-1][j-1];
		}
	}
	int ans = 0;
	for(int i=R;i<=n;i++)
	{
		for(int j=R;j<=m;j++)
		{
			int tmp = map[i][j]-map[i-R][j]-map[i][j-R]+map[i-R][j-R];
			ans = max(ans,tmp);
		}
	}
	cout<<ans<<endl;
 }


