
/*
题意：给一个数字串s和正整数d, 统计s有多少种不同的排列能被d整除（可以有前导0）。例如123434有90种排列能被2整除，其中末位为2的有30种，末位为4的有60种。
*/
#include <bits/stdc++.h>

using namespace std;

int T,d,len,cnt[15],dupli[15],dp[1200][1010];
char s[15];

int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s %d",s,&d);len=strlen(s);
        for(int i=0;i<15;i++)
         dupli[i]=1;
        memset(cnt,0,sizeof(cnt));
        memset(dp,0,sizeof(dp));

        for(int i=0;i<len;i++)
            cnt[s[i]-'0']++,dupli[s[i]-'0']*=cnt[s[i]-'0'];

        dp[0][0]=1; //用二进制表示每个位置选了没有,dp[i][j]表示当前选的数集合为i,除d的余数为j的方案数
        for(int i=0;i<(1<<len);i++)
            for(int j=0;j<d;j++)
                if(dp[i][j])
                    for(int k=0;k<len;k++)
                        if(!(i&(1<<k)))
                            dp[i|(1<<k)][(j*10+(s[k]-'0'))%d]+=dp[i][j];

        for(int i=0;i<=9;i++)
          dp[(1<<len)-1][0]/=dupli[i];
        printf("%d\n",dp[(1<<len)-1][0]);
    }
    return 0;
}
