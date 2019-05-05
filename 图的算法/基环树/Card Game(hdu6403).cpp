#include<bits/stdc++.h>
using namespace std;
#define RG register

const int N = 2e5 + 10, mod = 998244353;
vector < pair < int, int > > e[N];
vector < int > Q;
int st, nxt, dir, n, siz, edg, T;
int d[N], dp[N];
bool vis[N];

void check(int u) {                  //判断该连通块是否有环
	vis[u] = true;siz++; //size为点的数量
	for (RG int i = 0; i < e[u].size(); i++) {
		edg++; //边的数量
		if (vis[e[u][i].first] == false) check(e[u][i].first);
	}
}

void dfs(int u, int fa) {           //求出以 i 为根时的需反向边的dp值
	vis[u] = true;
	d[u] = 0;
	for (RG int i = 0; i < e[u].size(); i++) {
		pair < int, int > v = e[u][i];
		if (vis[v.first] == false) {
			dfs(v.first, u);
			d[u] += d[v.first] + ((v.second % 2) ^ 1);
			//偶数编号，表示u是正面v是反面，又因为u是父亲，但实际上u指向的v，所以要反向，即+1
			//奇数编号，表示u是反面v是正面，又因为u是父亲，实际上也是v指向u，所以不反向，即+0
		} else if (v.first != fa) {
			st = u;//环尾
			nxt = v.first;//环首
			dir = v.second;//尾和首相连的边
		}
	}
}

void calc(int u, pair < int, int > pre) {  //求出以其他点为根的dp值
	Q.push_back(dp[u]);
	for (RG int i = 0; i < e[u].size(); i++) {
		pair < int, int > v = e[u][i];
		if (v == pre) continue;//如果是父亲，则跳过
		if (v.second == dir || v.second == (dir ^ 1)) continue;//如果是基环树，暂不考虑环上这条首尾相连的边，则基环树被当着一棵树
		dp[v.first] = dp[u] + ((v.second % 2 == 0) ? -1 : 1);//v.second为偶数时，表示实际u指向v,现在v作为根，
		//则u指向v是我们希望的，但之前在u作为根时，因为希望v指向u,就翻转了一次，所以现在要减去这一次
		calc(v.first, {u, v.second ^ 1});
	}
}

int main() {
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		for (RG int i = 1; i <= n * 2; i++) e[i].clear();
		for (RG int i = 1; i <= n; i++) {
			int x, y;
			scanf("%d%d", &x, &y);//建立从正面指向反面的边
        //最终让所有点的出度为1是翻牌的目标，即目标是让树上的儿子都指向父亲
			e[y].push_back(make_pair(x, 2 * i - 1));//子指向父的边编号为奇数
			e[x].push_back(make_pair(y, 2 * i - 2));//父指向子的边编号为偶数
		}
		memset(vis, false, sizeof(vis));
		int fl = 1;
		for (RG int i = 1; i <= 2 * n; i++) {
			if (vis[i]) continue;//如果点i所在的连通块处理过，就跳过
			siz = 0;edg = 0;
			check(i);
			if (edg / 2 > siz) {//点小于边的数量
				fl = 0;
				break;
			}
		}
		if (fl == 0) puts("-1 -1");
		else {
			memset(vis, false, sizeof(vis));
			int ans = 0, tot = 1;
			for (RG int i = 1; i <= n * 2; i++) {
				if (vis[i]) continue;
				st = dir = nxt = -1;//环相关变量的初始状态
				dfs(i, 0);//对于一棵树，我们让每一个点都指向他的父亲，统计翻转的数量
				dp[i] = d[i];
				Q.clear();
				calc(i, {0, 0});
				int cnt = 0;
				if (st == -1) {         //若没有环
					sort(Q.begin(), Q.end());//排序找最小翻转次数
					for (int i = 0; i < Q.size(); i++)
						if (Q[i] == Q[0]) cnt++; //统计方案数
					ans += Q[0];
				} else {               //有环（方案数只有可能是1或2）
					dir %= 2;
					if (dp[st] + dir == dp[nxt] + (dir ^ 1)) cnt = 2;//如果环上顺时针与逆时针得到的答案相同，则有两种方案
					else cnt = 1;
					ans += min(dp[st] + dir, dp[nxt] + (dir ^ 1));
				}
				tot = 1LL * tot * cnt % mod;// 所有连通块的方案数之积即为最终的方案数
			}
			printf("%d %d\n", ans, tot);
		}
	}
	return 0;
}
