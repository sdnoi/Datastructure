#include <queue>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
const int N = 50006;
int head[N], Edge[N<<1], Leng[N<<1], Next[N<<1], tot;
int n, m, t, a[N], b[N], g[N], fa[N][16], sh[N];
ll c[N], d[N], f[N], dis[N][16], sum;
vector<ll> arv[N];
queue<int> q;
bool v[N], w[N];

void add(int x, int y, int z) {
	Edge[++tot] = y;
	Leng[tot] = z;
	Next[tot] = head[x];
	head[x] = tot;
}

void bfs() {
	v[1] = 1;
	for (int i = head[1]; i; i = Next[i]) {
		int y = Edge[i];
		q.push(y);
		v[y] = 1;
		b[sh[y]=++t] = i;//给根的儿子节点编号sh[y]，以及存储本节点与父亲的边属于哪条边
	}
	while (q.size()) {
		int x = q.front();
		q.pop();
		for (int i = head[x]; i; i = Next[i]) {
			int y = Edge[i];
			if (v[y]) continue;
			q.push(y);
			v[y] = 1;
			fa[y][0] = x;
			dis[y][0] = Leng[i];
			for (int j = 1; j < 16; j++) {
				fa[y][j] = fa[fa[y][j-1]][j-1];
				dis[y][j] = dis[y][j-1] + dis[fa[y][j-1]][j-1];
			}
		}
	}
}

bool dfs(int x) {
	v[x] = 1;
	if (!sh[x] && w[x]) return 1; //此处不是根的儿子且有军队驻扎，就不用往下走了
	bool flag = 0;
	for (int i = head[x]; i; i = Next[i]) {
		int y = Edge[i];
		if (v[y]) continue;
		flag = 1;
		if (!dfs(Edge[i])) return 0;
	}
	return flag;//如果x是叶子节点，则返回0
}

bool work(ll now) {
	for (int i = 1; i <= t; i++) arv[i].clear();
	memset(v, 0, sizeof(v));
	memset(w, 0, sizeof(w));
	v[1] = 1;
	for (int i = 1; i <= m; i++) {
		g[i] = a[i];//第i只军队现在驻扎的城市
		d[i] = 0;
		for (int j = 15; j >= 0; j--)
			if (fa[g[i]][j] && d[i] + dis[g[i]][j] <= now) { //i不走到根，且在now的范围内最远能到达的城市
				d[i] += dis[g[i]][j];
				g[i] = fa[g[i]][j];
			}
		w[g[i]] = 1;// g[i]处有军队
		int j = sh[g[i]]; //g[i]节点是根的第几个儿子，如果是0则表示不是根的儿子
		if (j) {//到达了根的第j个儿子处
			arv[j].push_back(now - d[i]);//第i支军队剩余可走的距离
			if (arv[j].size() > 1 && now - d[i] > arv[j][arv[j].size()-2])//始终让最小的在尾巴上
				swap(arv[j][arv[j].size()-1], arv[j][arv[j].size()-2]);
		}
	}

	int p = 0, q = 0;
	for (int i = 1; i <= t; i++) {
		if (!dfs(Edge[b[i]])) {//在忽略根儿子军队的情况下，有叶子没有被管辖
			if (arv[i].size() && arv[i][arv[i].size()-1] < (Leng[b[i]] << 1)) //本根儿子的军队就在原地不动
				arv[i].pop_back();
			else   // 可以由其它儿子调动军队到此处
        f[++q] = Leng[b[i]]; //到此处需要走的距离
		}
		for (unsigned int j = 0; j < arv[i].size(); j++)
			if (arv[i][j] >= Leng[b[i]]) //如果要将本军队调动到其它儿子处，本军队还能走多远
				c[++p] = arv[i][j] - Leng[b[i]];
	}
	sort(c + 1, c + p + 1);
	sort(f + 1, f + q + 1);
	if (p < q) return 0;
	for (int i = q, j = p; i; i--, j--)
		if (c[j] < f[i]) return 0;
	return 1;
}

int main() {
	cin >> n;
	for (int i = 1; i < n; i++) {
		int x, y, z;
		scanf("%d %d %d", &x, &y, &z);
		add(x, y, z);
		add(y, x, z);
		sum += z;
	}
	cin >> m;
	for (int i = 1; i <= m; i++) scanf("%d", &a[i]);
	bfs();
	ll l = 0, r = sum + 1;
	while (l < r) {
		int mid = (l + r) >> 1;
		if (work(mid)) r = mid;
		else l = mid + 1;
	}
	if (l > sum) puts("-1");
	else cout << l << endl;
	return 0;
}
