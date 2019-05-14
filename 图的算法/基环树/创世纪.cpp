/*
思路：
断开环上一边，跑两次 DFS。
第一次不考虑这条边的影响（当作不存在）。
第二次要专门考虑这条边的影响，但又不能真的把这条边加进来，因为加进来就变成环，跑不完。
那么就先把由这条边中一个端点对另一个端点造成的影响专门算出来，这种情况被认为必然发生，不需要把这条边加进去，然后再跑一次DFS，就可算出这种特定情况下的值。

*/
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1000006, INF = 0x3f3f3f3f;
int n, fa[N], t, k, f[N][2], s[N][2], ans;
int Head[N], Edge[N<<1], Next[N<<1], tot;

int get(int x) {
    if (x == fa[x]) return x;
    return fa[x] = get(fa[x]);
}

inline void add(int x, int y) {
    Edge[++tot] = y;
    Next[tot] = Head[x];
    Head[x] = tot;
}

void dfs(int x) {
    int num = INF;
    f[x][0] = 0;
    for (int i = Head[x]; i; i = Next[i]) {
        if (Edge[i]!= k)
          dfs(Edge[i]);
        f[x][0] += max(f[Edge[i]][0], f[Edge[i]][1]);//x不选时，它的每个孩子既可以选也可以不选
        num = min(num, max(f[Edge[i]][0], f[Edge[i]][1]) - f[Edge[i]][0]);
    }
    f[x][1] = f[x][0] + 1 - num;//假设y是用于控制x的儿子，即y就不能选，要让f[x][1]足够大，
                               //被减式不变，减式就要足够小：f[x][0]-(max(f[y][1],f[y][0])-f[y][0])
         //上式的含义：本来应该加上f[y][0],但是加上了max(f[y][1],f[y][0] ),所以要把多加的减去
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) fa[i] = i;
    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        int p = get(x), q = get(i);// i控制x
        if (p == q) { // x与i连边后，形成环（就找到了环上的一条边），因此建的图就没有连这条边
            s[++t][0] = x;
            s[t][1] = i;
        } else {
            add(x, i);//连边方式：x指向i
            fa[q] = p;
        }
    }
    for (int i = 1; i <= t; i++) {
        k = 0;
        dfs(s[i][0]);//以s[i][0]为根不含环上其它点的子树
            //由于断开了从s[i][0]到s[i][1]的边，即从s[i][0]走不到s[i][1]，所以事先把s[i][0]为根的这棵树算出来
        k = s[i][0];
        dfs(s[i][1]);
        int now = f[s[i][1]][1];//这里不取f[s[i][1]][0]的值，f[s[i][1]][0]的值在下一个dfs重新算出来
        f[s[i][0]][1] = f[s[i][0]][0] + 1;//对于s[i][0]要投放，因为指定用s[i][1]来控制s[i][0],则s[i][1]不能选
          //即在对s[i][0]的所有控制者中，指定了由s[i][1]来控制它，因此s[i][0]的其它控制者就没有任何约束
          //相当于s[i][0]不投放时其子树的投放数之和再加上1个自己
        dfs(s[i][1]);
        ans += max(now, f[s[i][1]][0]);
    }
    cout << ans << endl;
    return 0;
}
