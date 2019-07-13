#include <cmath>
#include <cstdio>
#include <vector>
#include <cstring>
#include <iostream>
#define pii pair<int, int>
#define x first
#define y second
using namespace std;
const int N = 56, M = 2506;
const double eps = 1e-8;
int n, m, t, t2, V, f[M];
double t1;
bool v[M];
pii a[N], b[N];
pair<int, double> c[M];//
vector<int> e[N];

inline double S(pii a, pii b) {
	int dx = a.x - b.x, dy = a.y - b.y;
	return sqrt(dx * dx + dy * dy);
}

bool dfs(int x) {
	for (unsigned int i = 0; i < e[x].size(); i++) {
		int y = e[x][i];
		if (v[y]) continue;
		v[y] = 1;
		if (!f[y] || dfs(f[y])) {
			f[y] = x;
			return 1;
		}
	}
	return 0;
}

inline bool pd(double mid) {
	memset(f, 0, sizeof(f));
	for (int i = 1; i <= m; i++) {
		e[i].clear();
		for (int j = 1; j <= t; j++)//左部点与每个右部点的每次发射是否可以连边
			if (c[j].y + S(a[i], b[c[j].x]) / V <= mid)//如果右部点这次发射出的时刻加上路上跑的时间小于等于猜测的时刻
				e[i].push_back(j);
	}
	for (int i = 1; i <= m; i++) {
		memset(v, 0, sizeof(v));
		if (!dfs(i)) return 0;
	}
	return 1;
}

int main() {
	cin >> n >> m >> t1 >> t2 >> V;
	t = n * m;
	t1 /= 60;
	for (int i = 1; i <= m; i++)
		scanf("%d %d", &a[i].x, &a[i].y);
	for (int i = 1; i <= n; i++)
		scanf("%d %d", &b[i].x, &b[i].y);

//初始化，先记录下每座塔发射第i发导弹的时刻（每个塔发m发）
	for (int i = 1; i <= m; i++)//每个导弹发射m次
		for (int j = 1; j <= n; j++) {
			int k = (i - 1) * n + j;//现在是总第k次发射
			c[k].x = j;//这是第j座塔在发射
			c[k].y = (i - 1) * (t1 + t2) + t1;//从开始到发射出第i发导弹的时长
		}
	double l = t1, r = 100000;
	while (l + eps < r) {
		double mid = (l + r) / 2;
		if (pd(mid)) r = mid;
		else l = mid;
	}
	printf("%.6f\n", l);
	return 0;
}
