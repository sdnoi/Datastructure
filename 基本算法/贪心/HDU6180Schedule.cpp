/*
题意：给你n个项目的开始时间和结束时间，问至少需要多少个机器能做完所有的项目。
每个机器在某一个时刻被启动后只能运行到某一个时刻停止且停止后不能再次启动。还问用这最少个数的机器做完所有的这些项目所需最少时间是多少。

思路：

1.贪心。将每个安排分成两个：起始（标号为0）和终止（标号为1）。按照时间顺序排序，
每次遇到一个起始事件时，num++（代表当前机器不能满足条件，需要一台新的机器）；每次遇到一个终止事件时，num--（代表当前机器运行结束）。
则机器个数=max{num}（代表同时运行的机器个数）。
2.时间计算。时间=完成工作的时间+等待时间。工作时间可通过输入时累加，等待时间可通过用一栈记录当前完成工作的结束时间。
当遇到一起始事件时，等待时间=起始事件时间-当前最后工作的完成时间（即栈顶元素），同时出栈。当遇到一终止事件时，将该事件的时间入栈。
3.若起始时间与终止时间相同时，应先按照终止时间排序（可以理解为将所有终止时间往左移动了一个极小（大于0）的距离）。


*/

#include<stack>
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
#define debug
using namespace std;
typedef long long LL;
const int maxn=200000+50;
struct Node
{
    LL x;
    int id;
    Node() {}
    Node(LL x,int id):x(x),id(id) {}
};
LL sum;;
stack<LL> s;
Node a[maxn];
int ans,n,num,cnt;
int cmp(Node a,Node b)
{
    if(a.x==b.x) return a.id>b.id;
    else return a.x<b.x;
}
void init()
{
    ans=0,sum=0,num=0,cnt=0;
    while(!s.empty()) s.pop();
}
int main()
{
#ifdef debu
    freopen("1010.in","r",stdin);
#endif // debug
    int t;
    scanf("%d",&t);
    while(t--)
    {
        init();
        scanf("%d",&n);
        for(int i=0; i<n; i++)
        {
            LL l,r;
            scanf("%lld%lld",&l,&r);
            a[cnt++]=Node(l,0);
            a[cnt++]=Node(r,1);
            sum+=r-l;
        }
        sort(a,a+cnt,cmp);
        for(int i=0; i<cnt; i++)
        {
            if(a[i].id==0)//遇到项目的开始时间
            {
                num++;
                if(!s.empty()) //选一个离自己最近的已结束项目，且这个项目所使用的机器还没被用于其它项目
                {
                    LL pre=s.top(); //栈顶就是满足这个要求的项目
                    s.pop();//本项目使用了栈顶项目的同一台机器，那么这台机器就被使用了
                    sum+=a[i].x-pre;
                }
            }
            else//遇到项目的结束时间
            {
                num--;
                s.push(a[i].x);//释放机器，入栈，准备给其它项目使用
            }
            ans=max(ans,num);
        }
        printf("%d %lld\n",ans,sum);
    }
    return 0;
}
/*
1
6
1 3
2 5
4 6
4 10
7 12
8 11
*/
