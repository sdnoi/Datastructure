/*
仔细分析发现，答案满足单调性 因此可以二分答案ansans，然后O(m)验证。
于是我们要做的就是验证给出的一个答案是否合法。
如果所有路径中的最长路径mx≤ans则当前答案可行，并且如果两者差值mx−ans能够通过把一条边变为0来消去则答案也可行。
显然，由于只能改一条边，则这条边一定是所有超出ans的路径的一条公共边。
因此问题转化为寻找在那些超出ansans的路径中，是否存在一条公共边，并且其权值大于等于mx−ans。后者很容易判定，关键在于前者。如何验证公共边？
只需要验证每条边被经过的次数，如果等于路径数则为公共边。在树上求解每条边被经过次数，用树上差分即可

然后就是可怕的卡常了
想要优化常数，首先快读不能少，另外用链式前向星存图，尽量缩小二分答案的左右边界。这道题可以缩到多小？
由于只能弄掉一条边，因此左边界是给出路径中的最长的路径减去最长边权，右边界是最长路径，
当然如果你愿意，还可以记录dfs序然后逆序求解差分，不过没什么影响。
除此之外还有最重要的一点，由于一共只有M条路径，于是我们可以把M条路径的长度以及LCA求好，避免在judge时反复求解——这是一个大到可怕的优化

*/
#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>
#define  r  read()
#define  Max(a,b)  (((a)>(b)) ? (a) : (b))
#define  Min(a,b)  (((a)<(b)) ? (a) : (b))
using namespace std;
typedef long long ll;
const int MAXN = 300010;
const int MAXM = 600010;
const int INF = 1061109567;
inline int read(){
    int x = 0; int w = 1; register int c = getchar();
    while(c ^ '-' && (c < '0' || c > '9')) c = getchar();
    if(c == '-') w = -1, c = getchar();
    while(c >= '0' && c <= '9') x = (x<<3) + (x<<1) + c - '0', c = getchar();return x * w;
}
int N,M,x,y,z,L,R,Mid,Ans;
int first[MAXM],nxt[MAXM],to[MAXM],cost[MAXM],cnt,_mx;
int f[MAXN][30],dis[MAXN],dep[MAXN],a[MAXN],b[MAXN],cf[MAXN],cul[MAXN],lca[MAXN],dist[MAXN];
inline void add(int u, int v, int w){
    to[++cnt]=v, cost[cnt]=w, nxt[cnt]=first[u], first[u]=cnt;
}
void DFS_init(int u, int _f, int d){
    dep[u] = d, f[u][0] = _f;
    for(int i = 1; (1 << i) <= d; ++i){
        f[u][i] = f[f[u][i-1]][i-1];
    }
    int v;
    for(int i = first[u]; i; i = nxt[i]){
        if((v = to[i]) == _f) continue;
        dis[v] = dis[u] + cost[i];
        DFS_init(v, u, d+1);
    }
}
inline int LCA(int a, int b){
    if(dep[a] < dep[b]) swap(a, b);
    for(int i = 25; i >= 0; --i){
        if(dep[a] - (1<<i) >= dep[b]){
            a = f[a][i];
        }
    }
    if(a == b) return a;
    for(int i = 25; i >= 0; --i){
        if(f[a][i] == f[b][i]) continue;
        a = f[a][i], b = f[b][i];
    }
    return f[a][0];
}
void getCF(int u, int _f){
    int v;
    cul[u] = cf[u];
    for(int i = first[u]; i; i = nxt[i]){
        if((v = to[i]) == _f) continue;
        getCF(v, u);
        cul[u] += cul[v];
    }
}
bool DFS(int u, int _f, int k, int _cnt){
    int v;
    for(int i = first[u]; i; i = nxt[i]){
        if((v = to[i]) == _f) continue;
        if(cul[v] == _cnt && cost[i] >= k) return 1;//cost[i]要足够大，才能达到去掉这条边后，让路径足够小的效果
        if(DFS(v, u, k, _cnt)) return 1;
    }
    return 0;
}
inline bool judge(int k){
    int _cnt=0;
    if(_mx <= k) return 1;
    memset(cf,0,sizeof(cf));//cf是差分数组
    memset(cul,0,sizeof(cul));//前缀和
    for(int i = 1; i <= M; ++i){
        if(dist[i] > k){
            ++_cnt;
            cf[a[i]]++, cf[b[i]]++;
            cf[lca[i]] -= 2;
        }
    }
    getCF(1, 0);
    return DFS(1, 0, _mx-k, _cnt);
}
int main(){
    N=r, M=r;
    int tmp = 0;
    for(int i = 1; i < N; ++i){
        x=r, y=r, z=r;
        add(x, y, z);
        add(y, x, z);
        tmp = Max(tmp, z);
    }
    DFS_init(1, 0, 1);
    for(int i = 1; i <= M; ++i){
        a[i]=r, b[i]=r;
        lca[i] = LCA(a[i], b[i]);
        dist[i] = dis[a[i]] + dis[b[i]] - 2 * dis[lca[i]];
        _mx = Max(_mx, dist[i]);
    }
    L = _mx - tmp, R = _mx + 1;
    while(L <= R){
        Mid = (L + R) / 2;
        if(judge(Mid)){
            R = Mid - 1;
            Ans = Mid;
        }
        else{
            L = Mid + 1;
        }
    }
    printf("%d", Ans);
    return 0;
}
