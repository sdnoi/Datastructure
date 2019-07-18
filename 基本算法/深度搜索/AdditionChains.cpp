//Author:XuHt
#include <cstring>
#include <iostream>
using namespace std;
const int N = 106;
int n, ans[N], dep;

bool dfs(int now) {
	if (now == dep) return ans[now] == n;
	bool v[N];
	memset(v, 0, sizeof(v));
	for (int i = now; i; i--)//优化搜索顺序
		for (int j = i; j; j--) {
			int num = ans[i] + ans[j];
			if (num <= n && num > ans[now] && !v[num]) {//num大于ans[now]保证了是递增的，以免冗余
				ans[now+1] = num;
				if (dfs(now + 1))
          return 1;
				else
          v[num] = 1;//标记num使用过了
			}
		}
	return 0;
}

int main() {
	ans[1] = 1;
	while (cin >> n && n) {
		dep = 1;//搜索深度
		while (!dfs(1))
      ++dep;
		for (int i = 1; i <= dep; i++)
      cout << ans[i] << " ";
		cout << endl;
	}
	return 0;
}
