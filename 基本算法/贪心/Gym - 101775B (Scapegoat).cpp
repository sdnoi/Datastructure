/*
题意：有n个事件，每个事件有一个严重程度，m个人（m>=n），你要让m个人去背锅，每个人只能背一个事件的锅，
但是一个事件可以由很多人背。让你使得这m个人所承受的严重程度的方差最小化。
题解：
考虑到平均值是一定的，所以我们就是要尽量的使得，所有的人的值都在平均值上下。
巧妙之处： 我们考虑如果多了一个人，给了这个组，那么我们看看方差会降低多少，然后取那个降得最多的

优先队列： 提供了一个有序的选择器，每次都可以找到最好的，并且不断的调整。
贪心，对于每一个替罪羊，要分配到使得 （罪恶值-平均数）^2，下降最多的个trouble上。
对于第二个样例，一开始先给每个问题分配一个替罪羊，此时这5个羊的罪恶值为56789，计算他们的对答案的贡献，即（罪恶值-平均数）^2
然后计算增加一个羊的话，下降了多少，贪心的取最大的即可。

考虑一开始n个人各背一个事件，记录下该初始状态下的ans。然后分配剩下的m-n个人。
堆里存储每个事件的严重程度x和当前背锅人数y，按照x*x/y-x*x/(y+1.0)
（这个值是该事件当前提供的方差*n-给当前的事件多分配一个人所能提供的方差*n，即给它多分配一个人所能给方差带来的改进量，很容易推出来）
从大到小排序，然后依次从堆顶取出元素，把一个人分给这个事件，再放回堆即可，然后对初始状态的ans减去这个值，直到堆顶元素的这个值小于零。
*/

#include<cstdio>
#include<queue>
using namespace std;
const double EPS=0.00000001;
double ave;
struct data{
    double x,y,val;
    data(const double &x,const double &y){
        this->x=x;
        this->y=y;
        val=x*x/y-x*x/(y+1.0);
    }
    data(){}
};
bool operator < (const data &a,const data &b){
    return a.val<b.val;
}
priority_queue<data>Heap;
int a[200005];
double sqr(const double &x){
    return x*x;
}
int T,n,m;
int main(){
    //freopen("b.in","r",stdin);
    scanf("%d",&T);
    for(int zu=1;zu<=T;++zu){
        while(!Heap.empty()){
            Heap.pop();
        }
        scanf("%d%d",&n,&m);
        ave=0;
        for(int i=1;i<=n;++i){
            scanf("%d",&a[i]);
            ave+=(double)a[i];
        }
        ave/=(double)m;
        double tt=0;
        for(int i=1;i<=n;++i){
            tt+=sqr((double)a[i]-ave);
        }
        double ans=tt+sqr(ave)*(double)(m-n);
        for(int i=1;i<=n;++i){
            Heap.push(data((double)a[i],1.0));
        }
        for(int i=1;i<=m-n;++i){
            data t=Heap.top(); Heap.pop();
            if(t.val<EPS){
                break;
            }
            Heap.push(data(t.x,t.y+1.0));
            ans-=t.val;
        }
        printf("Case #%d: %.12f\n",zu,ans/(double)m);
    }
    return 0;
}
