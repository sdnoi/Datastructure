//Author:XuHt
#include <cstring>
#include <iostream>
using namespace std;
const int N = 6;
int a[N], ans, aa[N];
char s[N];

void dj(int x, int y) {
    aa[x] ^= (1 << y);//第y位取反
    if (x != 1) aa[x-1] ^= (1 << y);//上
    if (x != 5) aa[x+1] ^= (1 << y);//下
    if (y != 0) aa[x] ^= (1 << (y - 1));//右
    if (y != 4) aa[x] ^= (1 << (y + 1));//左
}

void pd(int p) {
    int k = 0;
    memcpy(aa, a, sizeof(a));
    for (int i = 0; i < 5; i++)//先处理第1行在受到P方案的影响后的状态
        if (!((p >> i) & 1)) {//点击方案的第i位为0,表示要按开关
            dj(1, i);//点击第1行第i位
            ++k;
           // if (++k >= ans) return;
        }
    for (int x = 1; x < 5; x++)
        for (int y = 0; y < 5; y++)
            if (!((aa[x] >> y) & 1)) {//第x行的第y位为0
                dj(x + 1, y);//按第x+1行的第y位开关
                ++k;
               // if (++k >= ans) return;
            }
    if (aa[5] == 31) ans = k;//第5行下面没有第6行了，要看之前对它的影响后是不是全1
}

void abc() {
    memset(a, 0, sizeof(a));//a存储灯的状态
    for (int i = 1; i <= 5; i++) {//5行
        cin >> (s + 1);
        for (int j = 1; j <= 5; j++)
          a[i] = a[i] * 2 + (s[j] - '0');//转换为一个二进制数
    }
    ans = 7;
    for (int p = 0; p < (1 << 5); p++)//枚举第一行2^5种点击方案
      pd(p);
    if (ans == 7) cout << "-1" << endl;
    else cout << ans << endl;
}

int main() {
    int n;
    cin >> n;
    while (n--) abc();
    return 0;
}
