#include <cstdio>

using namespace std;

const int MAXN = 1025;

char map[MAXN][MAXN*2];
int N, Len;

void Init()
{
	scanf("%d", &N);
	Len = 1 << N;
	for (int i = 1; i <= Len; i ++)
		for (int j = 1; j <= Len*2; j ++)
			map[i][j] = ' ';
}

void Draw(int x, int y, int N)
{
	if (N == 1){
		map[x][y] = '/'; map[x][y+1] = 92;
		map[x+1][y-1] = '/';
		map[x+1][y] = map[x+1][y+1] = '_'; map[x+1][y+2] = 92;
		return;
	}
	Draw(x, y, N - 1);
	int len = 1 << (N - 1);
	Draw(x + len, y - len, N - 1);
	Draw(x + len, y + len, N - 1);
}

void Print()
{
	for (int i = 1; i <= Len; i ++){
		for (int j = 1; j <= Len*2; j ++) printf("%c", map[i][j]);
		puts("");
	}
}

int main()
{
//	freopen("pattern.in", "r", stdin);
//	freopen("pattern.out", "w", stdout);
	Init();
	Draw(1, Len, N);
	Print();
	return 0;
}
