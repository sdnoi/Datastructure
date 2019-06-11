#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 5;
template <typename T> void read(T &x) {
	x = 0; int f = 1;
	char ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = -f;
	for (; isdigit(ch); ch = getchar()) x = x * 10 + ch - '0';
	x *= f;
}
struct info {int ans, res; };//内部有ans条赛道，另外伸出来的长度是res连上父边
struct edge {int dest, len; };
vector <edge> a[MAXN];
int n, m, mid; info dp[MAXN];
info operator + (info a, int b) {
	a.res += b;//从a的儿子中冲出来的边的长度a.res与a的父边的边长b的和
	if (a.res >= mid) {  //如果满足答案，则构成一条赛道，就没有从此处冲出去的边，赋值为0
		a.ans++;
		a.res = 0;
	}
	return a;
}
int tot, len[MAXN], q[MAXN];
int top, fa[MAXN], s[MAXN];
void bfs(int from) {//fa:记录每个点的父亲,q记录广搜顺序
	memset(fa, -1, sizeof(fa));
	int l = 1, r = 1;
	fa[1] = 0; q[1] = from;
	while (l <= r) {
		int pos = q[l++];
		for (unsigned i = 0; i < a[pos].size(); i++)
			if (fa[a[pos][i].dest] == -1) {
				fa[a[pos][i].dest] = pos;
				q[++r] = a[pos][i].dest;
			}
	}
}
void work() {
	for (int p = n; p >= 1; p--) {
		int pos = q[p];
		tot = 0;
		dp[pos] = (info) {0, 0};
		for (unsigned i = 0; i < a[pos].size(); i++)
			if (a[pos][i].dest != fa[pos]) {
				info tmp = dp[a[pos][i].dest] + a[pos][i].len;//加法的含义见前面重载
				dp[pos].ans += tmp.ans;//赛道数量
				len[++tot] = tmp.res;//从底层向上到pos[i]的每个儿子再到pos[i]的路的长度
			}
		sort(len + 1, len + tot + 1);//排序之后好构造赛道，选一条不在赛道且最大的边冲出去
		top = 0;
		for (int i = 1, j = tot + 1; i <= tot; i++) {
			while (j - 1 > i && len[i] + len[j - 1] >= mid)//找一个可与len[i]搭配的len[j]
                s[++top] = --j;//所有满足条件的j存在s数组中
			if (i + 1 >= j) {//全部都满足要求，即任意两条都满足构成一个赛道的条件
				s[++top] = i;
				dp[pos].ans += top / 2;// 赛道增加数量
				if (top % 2 == 1) //计数条路，就还剩一条路没组成赛道，那么就选一条最大的突围出去
                    dp[pos].res = max(dp[pos].res, len[s[1]]);
				break;
			} else if (top != 0) //与len[i]搭配得最好的，即满足len[i]+len[j]>=mid 的最小值时取得的j
			    top--, dp[pos].ans++;
			else//没有与len[i]搭配的j，i就是突击队候补队员
			   dp[pos].res = max(dp[pos].res, len[i]);
		}
	}
}
int main() {
//	freopen("track.in", "r", stdin);
//	freopen("track.out", "w", stdout);
	read(n), read(m);
	for (int i = 1; i <= n - 1; i++) {
		int x, y, z; read(x), read(y), read(z);
		a[x].push_back((edge) {y, z});
		a[y].push_back((edge) {x, z});
	}
	bfs(1);
	int l = 1, r = 1e4 * n;
	while (l < r) {
		mid = (l + r + 1) / 2;
		work();
		if (dp[1].ans >= m) l = mid;
		else r = mid - 1;
	}
	printf("%d\n", l);
	return 0;
}
