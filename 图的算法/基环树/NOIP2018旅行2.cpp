#include <cstdio>
#include <algorithm>
const int maxn = 5123;
struct edge{ int v, nxt;
}e[maxn << 1]; int fir[maxn], num(1);
inline void add(int u, int v){
    e[++num].v = v; e[num].nxt = fir[u]; fir[u] = num;
}
int val[maxn][maxn], ans[maxn], cnts, tmp[maxn], n, m;
int in[maxn], q[maxn], cut; bool ontre[maxn];
inline void print(){
    for(int i(1); i < n; ++i){
        printf("%d ", ans[i]);
    }
    printf("%d\n", ans[n]);
}
bool solve(int now, int fr, bool &flag){
    tmp[++cnts] = now;
    if(!flag && tmp[cnts] > ans[cnts]) return false;
    if(tmp[cnts] < ans[cnts]) flag = true;
    int sons(0);
    for(int itr(fir[now]); itr; itr = e[itr].nxt){
        if(e[itr].v == fr || (itr >> 1) == cut) continue;
        val[now][++sons] = e[itr].v;
    }
    std::sort(val[now] + 1, val[now] + sons + 1);
    for(int i(1); i <= sons; ++i){
        if(!solve(val[now][i], now, flag)) return false;
    }
    return true;
}
inline void solve1(){
    int l(1), r(0);
    for(int i(1); i <= n; ++i){
        if(in[i] == 1)q[++r] = i;
        ans[i] = 5555;
    }
    while(l <= r){
        int now = q[l++];
        for(int itr(fir[now]); itr; itr = e[itr].nxt){
            if(in[e[itr].v] <= 1) continue;
            --in[e[itr].v];
            ontre[itr >> 1] = true;
            if(in[e[itr].v] == 1) q[++r] = e[itr].v;
        }
    }
    for(int i(1); i <= m; ++i){
        if(!ontre[i]){
            cut = i; //枚举删除的边
            cnts = 0; bool flag = false;
            if(solve(1, -1, flag)){
                for(int j(1); j <= n; ++j){
                    ans[j] = tmp[j];
                }
            }
        }
    }
}
void solve2(int now, int fr){
    ans[++cnts] = now;
    int sons(0);
    for(int itr(fir[now]); itr; itr = e[itr].nxt){
        if(e[itr].v == fr) continue;
        val[now][++sons] = e[itr].v;
    }
    std::sort(val[now] + 1, val[now] + sons + 1);//排序
    for(int i(1); i <= sons; ++i){
        solve2(val[now][i], now);
    }
}
int main(){
//  freopen("travel.in", "r", stdin);
//  freopen("travel.out", "w", stdout);
    scanf("%d%d", &n, &m);
    for(int i(1), u, v; i <= m; ++i){
        scanf("%d%d", &u, &v);
        add(u, v); add(v, u); ++in[u]; ++in[v];
    }
    if(n == m)  solve1();
    else  solve2(1, -1);
    print();
    return 0;
}
