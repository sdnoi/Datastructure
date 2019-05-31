#include <cmath>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int N = 10006, M = 100006;
int n, m, q, t, cnt;
int d[N], dep[N], dfn[N], pos[N], f[N][14], s[N], a[N], b[N];
int Head[N], Next[M], Edge[M], Leng[M], tot = 1;
bool v[N], w[M];
 
inline void add(int x, int y, int z) {
    Edge[++tot] = y;
    Leng[tot] = z;
    Next[tot] = Head[x];
    Head[x] = tot;
}
 
void spfa() {
    memset(d, 0x3f, sizeof(d));
    queue<int> q;
    q.push(1);
    d[1] = 0;
    while (q.size()) {
        int x = q.front();
        q.pop();
        v[x] = 0;
        for (int i = Head[x]; i; i = Next[i])
            if (d[Edge[i]] > d[x] + Leng[i]) {
                d[Edge[i]] = d[x] + Leng[i];
                if (!v[Edge[i]]) {
                    v[Edge[i]] = 1;
                    q.push(Edge[i]);
                }
            }
    }
}
 
void work(int x, int y) {
    if (x == y) return;
    pos[x] = cnt;//点x在编号为cnt的环上
    add(y, x, 0);//将x直接连到环顶
    w[a[x]] = w[a[x]^1] = 1;
    s[cnt] += Leng[a[x]];
    work(Edge[a[x]^1], y);
}
 
void dfs1(int x) {
    dfn[x] = ++t;
    for (int i = Head[x]; i; i = Next[i])
        if (i != (a[x] ^ 1) && i <= (m << 1 | 1)) {//i不为树边的反向边即不为指向父亲的边，且i小于等于2*m+1
            if (!dfn[Edge[i]]) {//如果Edge[i]还没被访问
                b[Edge[i]] = b[x] + Leng[i];//树中点到根的距离，不一定等于原图中点到根的最短路，因为经过树（n-1条边）比图（m条边）减少了的那些边的距离可能更短
                a[Edge[i]] = i;//树边
                dfs1(Edge[i]);
            } else if (dfn[Edge[i]] < dfn[x]) {//找到环了
                s[++cnt] = Leng[i]; //cnt为环的编号，s存储环的周长
                work(x, Edge[i]); //edge[i]为环顶
            }
        }
}
 
void dfs2(int x) {
    for (int i = Head[x]; i; i = Next[i])
        if (!w[i] && !dep[Edge[i]]) {
            f[Edge[i]][0] = x;
            dep[Edge[i]] = dep[x] + 1;
            dfs2(Edge[i]);
        }
}
 
int ask(int x, int y) {
    if (dep[x] < dep[y]) swap(x, y);
    int o = x, p = y;
    for (int i = 13; i >= 0; i--)
        if(dep[f[x][i]] >= dep[y]) x = f[x][i];
    if (x == y)
        return d[o] - d[p];//在同一条链上,树上两点之间的距离不一定是原图中两点之间的最近距离，因此不能用b[o]-b[p]
 
    for (int i = 13; i >= 0; i--)
        if (f[x][i] != f[y][i]) {
            x = f[x][i];
            y = f[y][i];
        }
    if (pos[x] && pos[x] == pos[y]) {//在同一环上
        int now = abs(b[x] - b[y]);//采用树上两点之间的距离，而不是图上两点的最短路的差值，
        //因为图上两点的最短路可能在原图这个环中走的方向不一样
        //int now = abs(d[x] - d[y]);//
        return d[o] - d[x] + d[p] - d[y] + min(now, s[pos[x]] - now);
    }
     return d[o] + d[p] - 2 * d[f[x][0]];//
    //return b[o] + b[p] - 2 * b[f[x][0]];//树上两点之间的距离走的不一定是原图中的最短的距离
}
 
int main() {
    cin >> n >> m >> q;
    for (int i = 1; i <= m; i++) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        add(x, y, z);
        add(y, x, z);
    }
    spfa();//求出1号点到其它点的最短路
    dfs1(1);//找环，且将环上各点直接连到环顶
    dep[1] = 1;
    dfs2(1);//求出各点的深度（在dfs1时新加了边，深度就与dfs1时不一样了），同一个环中的点（除环顶外）深度相同，相当于把一个环看作了一个点
    for (int j = 1; j < 14; j++)
        for (int i = 1; i <= n; i++)
            f[i][j] = f[f[i][j-1]][j-1];
    while (q--) {
        int x, y;
        scanf("%d %d", &x, &y);
        printf("%d\n", ask(x, y));
    }
    return 0;
}
