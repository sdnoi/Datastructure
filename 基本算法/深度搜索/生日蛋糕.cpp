#include <cmath>
#include <iostream>
#include <algorithm>
using namespace std;
const int INF = 0x7fffffff;
int n, m, minv[30], mins[30], ans = INF;
int h[30], r[30], s = 0, v = 0;

void dfs(int dep) {
	if (!dep) {
		if (v == n) ans = min(ans, s);
		return;
	}
	for (r[dep] = min((int)sqrt(n - v), r[dep + 1] - 1); r[dep] >= dep; r[dep]--)//倒序枚举本层半径
		for (h[dep] = min((int)((double)(n-v) / r[dep] / r[dep]), h[dep+1] - 1); h[dep] >= dep; h[dep]--)//倒序枚举高
		 {
			if (v + minv[dep-1] > n) continue;//剪枝3：可行性剪枝
			if (s + mins[dep-1] > ans) continue;//剪枝4：最优性剪枝一
			if (s + (double)2 * (n - v) / r[dep] > ans) continue;//剪枝5：最优性剪枝二
			if (dep == m) //所有层蛋糕的“上表面”露在外面的面积之和等于最底层的圆面积
        s += r[dep] * r[dep];
			s += 2 * r[dep] * h[dep];//累加本层的侧面积
			v += r[dep] * r[dep] * h[dep];//累加本层的体积
			dfs(dep - 1);//继续搜索上一层

			if (dep == m) s -= r[dep] * r[dep];//还原
			s -= 2 * r[dep] * h[dep];//还原
			v -= r[dep] * r[dep] * h[dep];//还原
		}
}

int main() {
	cin >> n >> m;
	minv[0] = mins[0] = 0;
	for (int i = 1; i <= m; i++) {//1~i层的最小体积和面积
		minv[i] = minv[i-1] + i * i * i;
		mins[i] = mins[i-1] + i * i;
	}
	h[m+1] = r[m+1] = INF;
	dfs(m);
	cout << ans << endl;
	return 0;
}
