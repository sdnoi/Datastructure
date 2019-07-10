#include <cstring>
#include <iostream>
using namespace std;
char s[81];
int cnt[1<<9], f[1<<9];
int x[9], y[9], z[9], X[81], Y[81];
int gx, gy, gz;

inline void get(int i) {
	gx = X[i];//行号
	gy = Y[i];//列号
	gz = gx / 3 * 3 + gy / 3;//9宫格编号
}

void work(int i, int k) {//i表示在表格的第几个位置， k表示该位置上的数字
	get(i);
	x[gx] ^= (1 << k); //将第k位上取反，如果原来这个位置上是1，现在则为0，表示k位上所代表的这个数已经有了
	y[gy] ^= (1 << k);////二进制位与1异或相当于取反
	z[gz] ^= (1 << k);
}

bool dfs(int ans) {
	if (!ans) return 1;//没空位置
	int k = 10, t;
	for (int i = 0; i < 81; i++)
		if (s[i] == '.') {
			get(i);
			int w = x[gx] & y[gy] & z[gz]; //i所处于的行、列、9空格做与运算
			if (cnt[w] < k) { //优化：能填的合法数字最少的
				k = cnt[w];//k表示当前可填的数最少的值
				t = i;//这个值所处的位置
			}
		}
	get(t);//选定的这个位置上求出行、列、九空格编号
	int w = x[gx] & y[gy] & z[gz];
	while (w) {
		int now = f[w&-w];//最低位1所处于二进制中的位置，表示取哪个数(0-8)
		s[t] = now + '1';
		work(t, now); //把这个数在行、列、九宫格中做好记录
		if (dfs(ans - 1)) return 1;
		work(t, now);//把这个数在行、列、九宫格中的记录中还原
		s[t] = '.';
		w -= w & -w; //去掉刚才取得数，准备取下个可能的数字
	}
	return 0;
}

void Sudoku() {
	for (int i = 0; i < 9; i++)
        x[i] = y[i] = z[i] = (1 << 9) - 1;//初始为二进制： 111111111
	int ans = 0;//需要填数的位置的个数
	for (int i = 0; i < 81; i++)
		if (s[i] != '.')
            work(i, s[i] - '1');
		else
            ++ans;
	if (dfs(ans))
        for (int i = 0; i < 81; i++)
            cout << s[i];
	cout << endl;
}

int get_cnt(int i) {
	int ans = 0;
	while (i) {
		++ans;
		i -= (i & -i);
	}
	return ans;
}

int main() {
	for (int i = 0; i < (1 << 9); i++)
        cnt[i] = get_cnt(i);//i的二进制表示中1的个数
	for (int i = 0; i < 9; i++)
        f[1<<i] = i;//该2^i用于表示数字i
    for (int i = 0; i < 81; i++) {
		X[i] = i / 9; //所在行
		Y[i] = i % 9; //所在列
	}
	while (cin >> s && s[0] != 'e') //多组数据
        Sudoku();
	return 0;
}
