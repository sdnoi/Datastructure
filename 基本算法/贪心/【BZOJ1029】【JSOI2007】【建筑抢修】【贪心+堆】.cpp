

/*

题解：按完成时限排序，一个个修复。
并且按照结束时间排序 每次做的时候按照结束时间扫过去 然后记录一个我上一次做到的那个时间 
如果我这一次修理超过我的结束时间那么我就看一看我之前修理过的有没有耗时特别大的 
如果比我这次修理时间还大 那就把上次删除 加入这次 为什么可以这样 因为我可以看作把上次删除了之后把其他的修理时间都往前平移了 
因为根据规定我在队列里的都是确切可以修理的 那么往前平移也就没什么问题了 

*/
#include<cstdio>
#include<queue>
#include<algorithm>
using namespace std;
priority_queue<int,vector<int> >Heap;
struct Point{int x,y;};
bool cmp(const Point &a,const Point &b){return a.y<b.y;}
int n,v,used,ans=1;
Point a[150001];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)scanf("%d%d",&a[i].x,&a[i].y);
    sort(a+1,a+n+1,cmp);
    used=a[1].x;Heap.push(a[1].x);
    for(int i=2;i<=n;i++)
      {
          if(used+a[i].x<=a[i].y)//可以添加一个
            {
                Heap.push(a[i].x);
                used+=a[i].x;
                ans++;
                continue;
            }
          v=Heap.top();
          if(v>a[i].x)//换一个
            {
                Heap.pop();
                Heap.push(a[i].x);
                used+=(a[i].x-v);
            }
      }
    printf("%d\n",ans);
}
