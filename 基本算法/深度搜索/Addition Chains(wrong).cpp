/*
下面这个算法是错误的，找到的不一定是最小长度
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=150;
int s[N];
bool v[N];
int cnt;

void sequence(int n) {
    if (n==1) return ;
    int a=n>>1;
    if(!v[a]) {
        s[++cnt]=a;
        v[a]=1;
        sequence(a);
    }
    if(n%2 && !v[a+1]) {
        s[++cnt]=a+1;
        v[a+1]=1;
        sequence(a+1);
    }
}
int main() {
    int n;
    while(scanf("%d",&n)&&n) {
        s[0]=1;
        v[1]=1;
        sequence(n);
        sort(s,s+cnt+1);
        for(int i=0; i<=cnt; ++i)
            printf("%d ",s[i]);
        printf("%d\n",n);
    }
}
