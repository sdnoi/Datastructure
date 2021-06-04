#include <cstdio>
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
const int N = 1000006;
int Head[N], Edge[N<<1], Leng[N<<1], Next[N<<1], tot;
int n, du[N], c[N], q[N<<1];
ll f[N], d[N], a[N<<1], b[N<<1], ans;
bool v[N];

inline void add(int x, int y, int z) {
	Edge[++tot] = y;
	Leng[tot] = z;
	Next[tot] = Head[x];
	Head[x] = tot;
	++du[y];
}

void bfs(int s, int t) {
	int l = 1, r = 1;
	c[q[1]=s] = t;//点s属于连通块t
	while (l <= r) {
		for (int i = Head[q[l]]; i; i = Next[i])
			if (!c[Edge[i]]) c[q[++r]=Edge[i]] = t;
		++l;
	}
}

void topsort() {//从儿子到父亲向上一层层的搜索，最多到达环上点所在这层，由于环上这层的点是连通的，每个点至少有两度，因此环上的点进不了队列
//就不能通过环上的点再拓展到其它点，
//那么下面的过程就能求出从环上某点（不经过环上其它点）能到达的最远距离以及以这个点为根的子树（不含环上其它点）中的最长链
	int l = 1, r = 0;
	for (int i = 1; i <= n; i++)
		if (du[i] == 1) q[++r] = i;
	while (l <= r) {
		for (int i = Head[q[l]]; i; i = Next[i])
			if (du[Edge[i]] > 1) { //q[l]实际上是Edge[i]的儿子
				d[c[q[l]]] = max(d[c[q[l]]], f[q[l]] + f[Edge[i]] + Leng[i]);//目前找到的本块的最长链的值（不经过环上点）
				f[Edge[i]] = max(f[Edge[i]], f[q[l]] + Leng[i]);//edge[i]能走到的最远距离
				if (--du[Edge[i]] == 1) q[++r] = Edge[i];//环上的点进不了队
			}
		++l;
	}
}

void dp(int t, int x) {
	int m = 0, y = x, k, z = 0;
	do {
		a[++m] = f[y];//环上点(不经过环)能到达的最远距离存在a数组中，同时给环上的点编号
		du[y] = 1;
		for (k = Head[y]; k; k = Next[k])
			if (du[Edge[k]] > 1) {  //环上
				b[m+1] = b[m] + Leng[k];//前缀和
				y = Edge[k];//环上下一个点
				break;
			}
	} while (k);//当k为0，说明不是通过break跳出内层for循环的。即把环上的点都遍历了，x是环上第一个点，y是环上最后一个点
	if (m == 2) { //环上只有两个点
		for (int i = Head[y]; i; i = Next[i])
			if (Edge[i] == x) z = max(z, Leng[i]); //x到y之间最长的那条边
		d[t] = max(d[t], f[x] + f[y] + z);
		return;
	}
	for (int i = Head[y]; i; i = Next[i])
		if (Edge[i] == x) {
			b[m+1] = b[m] + Leng[i]; //b[m+1]环上一圈的长度
			break;
		}
	for (int i = 1; i < m; i++) { //把环延长一倍
		a[m+i] = a[i];
		b[m+i] = b[m+1] + b[i];
	}
	int l = 1, r = 1;
	q[1] = 1;
	for (int i = 2; i < (m << 1); i++) {
		if (l <= r && i - q[l] >= m) ++l;//不能超过一圈
		d[t] = max(d[t], a[i] + a[q[l]] + b[i] - b[q[l]]);//找本块最长链
		while (l <= r && a[q[r]] - b[q[r]] <= a[i] - b[i]) --r;//在单调队列中为i点找位置
		q[++r] = i;
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
	int t = 0;
	for (int i = 1; i <= n; i++)
	     if (!c[i])   bfs(i, ++t);//连通块
	topsort();
	for (int i = 1; i <= n; i++)
		if (du[i] > 1 && !v[c[i]]) { //度大于1的点是环上的点
			v[c[i]] = 1;
			dp(c[i], i);
			ans += d[c[i]];
		}
	cout << ans << endl;
	return 0;
}
