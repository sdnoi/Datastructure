/*
直接暴力做前缀和，再暴力枚举右下节点即可，注意常数。
*/
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;
 
int a[5010][5010]={0};
int main(){
	int n,r;
	scanf("%d%d",&n,&r);
	int i,j,ans=0;
	for (i=1; i<=n; i++){
		int u,v,c; scanf("%d%d%d",&u,&v,&c);
		a[u+1][v+1]+=c;
	}
	for (i=1; i<=5001; i++)
		for (j=1; j<=5001; j++) a[i][j]+=a[i-1][j];
	for (i=1; i<=5001; i++)
		for (j=1; j<=5001; j++) a[i][j]+=a[i][j-1];
	for (i=r; i<=5001; i++)
      for (j=r; j<=5001; j++)
        ans=max(ans,a[i][j]+a[i-r][j-r]-a[i][j-r]-a[i-r][j]);
    printf("%d",ans);
	return 0;

