#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
const int N = 1000006;
int Head[N], Edge[N<<1], Leng[N<<1], Next[N<<1], tot = 1;
int n, top, inst[N], q[N];
ll ans, d[N], f[N];
pair<int, ll> st[N];
vector<pair<int, ll> > s;//存储环
bool vis[N<<1], v[N], ins[N], w[N];

inline void add(int x, int y, int z) {
    Edge[++tot] = y;
    Leng[tot] = z;
    Next[tot] = Head[x];
    Head[x] = tot;
}

void dfs(int x) {
    for (int i = Head[x]; i; i = Next[i]) {
        int y = Edge[i];
        ll z = Leng[i];
        if (v[y]) {//点y被访问过
            if (!vis[i^1]) {//但边(y,x)没有访问过，即y并不是x的父亲，则找到一个环
                for (int j = inst[y] + 1; j <= top; j++) {
                    s.push_back(st[j]);
                    ins[st[j].first] = 1;//ins标记节点在环上
                }
                s.push_back(make_pair(y, z));
                ins[y] = vis[i] = 1;
            }
            continue;
        }
        v[y] = vis[i] = 1;//点y,边i设置为访问过
        st[++top] = make_pair(y, z);//st存储dfs序中的第++top个点及其到父亲的边权值
        inst[y] = top;//正在访问中还没结束访问的节点的顺序
        dfs(y);
        --top; //回溯时
    }
}

void dp(int x, ll &now) {
    w[x] = 1;
    for (int i = Head[x]; i; i = Next[i]) {
        int y = Edge[i];
        if (w[y] || ins[y]) continue;//是父节点或在在环上
        dp(y, now);
        ll z = Leng[i];
        now = max(now, d[x] + d[y] + z);
        d[x] = max(d[x], d[y] + z);
    }
}

int main() {
    cin >> n;
    for (int x = 1; x <= n; x++) {
        int y, z;
        scanf("%d %d", &y, &z);
        add(x, y, z);
        add(y, x, z);
    }
    for (int i = 1; i <= n; i++)
        if (!v[i]) {
            s.clear();
            v[i] = 1;
            st[1] = make_pair(i, 0);//根节点及其边取值
            inst[i] = top = 1;
            dfs(i);//跑一个连通块，找这个块中的环
            ll now = 0;//now为本块的最长直径
            for (unsigned int i = 0; i < s.size(); i++)
                dp(s[i].first, now);//先在去掉环中所有子树中去找最长的
            int sz = s.size();//环上节点的数量
            for (int i = 0; i < sz; i++)//环断开成链再复制一倍
                s.push_back(s[i]);
            int l = 0, r = 1;
            q[0] = 0;
            for (unsigned int i = 1; i < s.size(); i++) { //单调队列维护最优决策
                f[i] = f[i-1] + s[i].second;// 前缀和
                ll val = d[s[i].first] - f[i]; //
                if (l < r && q[r-1] - q[l] >= sz - 1) ++l;
                now = max(now, f[i] + d[s[i].first] + d[s[q[l]].first] - f[q[l]]);
                while (l < r && d[s[q[r-1]].first] - f[q[r-1]] <= val) --r;
                q[r++] = i;
            }
            ans += now;
        }
    cout << ans << endl;
    return 0;
}
/*
Wangyu
1、找环时判断边是否走过的数组的大小没有翻倍；平时写dfs时习惯了把bool数组的大小开为max；先想好每个数组的用途，再开对应的大小
2、进行树形dp时保存的直径和单调队列保存最大值使用的变量应该相同，但是这次用的是两个不同的变量；在写一个新的板块时没有想新的和旧的板块是不是有共用的变量；以后在写每个部分的时候先想好各部分之间共通的地方，再决定要新开的变量
*/
