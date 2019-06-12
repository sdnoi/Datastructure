#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 1000000007;
ll modpow(ll a, int b) {
    ll res = 1;
    for (; b; b >>= 1) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
    }
    return res;
}
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    if (n > m) swap(n, m);
    if (n == 1) return printf("%lld\n", modpow(2, m)) * 0;
    if (n == 2) return printf("%lld\n", modpow(3, m - 1) * 4 % mod) * 0;
    ll res = 2LL * modpow(4, n - 2) * modpow(3, m - n) % mod * modpow(2, n - 1) % mod;// a[1,2]=a[2,1]
    if (n == 3) {//n等于3，特判
        if (m == 3) {
            res += 12 + 6 + 6;//第3根斜线分别为000,001,011,111时对应的填法都是6，故有24种
            return printf("%lld\n", res * 2 % mod) * 0; //res乘以第一个格子的两种填法
        }
        res = (res + 32LL * modpow(3, m - 4)) % mod;
        res = (res + 48LL * (modpow(3, m - 4) - 1) % mod * (mod + 1) / 2 + 24) % mod;
        res = (res + 16LL * modpow(3, m - 4)) % mod;
        return printf("%lld\n", res * 2 % mod) * 0;
    }

    //第三条斜线为000,111的情况
    res = (res + 10LL * modpow(4, n - 4) % mod * modpow(3, m - n) % mod * modpow(2, n - 1)) % mod;

    //第三条斜线为110的情况，其中(modpow(4, n - 4) - 1) % mod * (mod + 1) / 3) % mod表示求4^0,4^1,4^2，...,4^(n-5)的和并取模
    res = (res + 20LL * modpow(3, m - n) % mod * modpow(2, n - 1) % mod * (modpow(4, n - 4) - 1) % mod * (mod + 1) / 3) % mod;
    if (n == m) //(4×3+2)*2^(n−2)
      res = (res + 15LL * modpow(2, n - 2)) % mod;
    else
      res = (res + 16LL * modpow(3, m - n - 1) % mod * modpow(2, n - 1) + 12LL * (modpow(2, n - 2) + modpow(2, n - 1) * (modpow(3, m - n - 1) - 1) % mod * (mod + 1) / 2 % mod)) % mod;

    //第三条斜线为100的情况,斜上为0
    res = (res + 20LL * modpow(3, m - n) % mod * modpow(2, n - 1) % mod * (modpow(4, n - 4) - 1) % mod * (mod + 1) / 3) % mod;
    if (n == m)
      res = (res + 15LL * modpow(2, n - 2)) % mod;
    else//(4*4+1*4）*3^(m-n-1)*2^(n-1)
      res = (res + 20LL * modpow(3, m - n - 1) % mod * modpow(2, n - 1)) % mod;

    return printf("%lld\n", res * 2 % mod) * 0; //res乘以第一个格子的两种填法
    return 0;
}
