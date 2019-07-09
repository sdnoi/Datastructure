#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
pair<LL,LL> calc(LL n, LL m){
    
	if(n == 0) return make_pair(0,0);
	LL len = 1ll << (n-1) , cnt = 1ll << (2*n - 2);

	//m%cnt表示当前编号m在n-1级格子里的编号(与道路走向的顺序来标号是吻合的）
	pair<LL,LL> pos = calc( n-1, m%cnt);//求出本编号在上一级中对应的坐标

	LL x = pos.first , y = pos.second;
	LL z = m / cnt;//z的值代表这n-1级的（x，y）在n级城市中的方位，然后就可由上一级的坐标推出本级的坐标
	if ( z == 0 ) return make_pair(y , x); //左上
	if ( z == 1 ) return make_pair(x, y + len);//右上
	if ( z == 2 ) return make_pair(x+len, y + len);//右下
	return make_pair(2*len-1-y, len - 1- x);// 左下
}
int main(){
	int T;
	cin >> T;
	while(T--){
		LL N,A,B;
		cin >> N >> A >> B;
		pair<LL,LL> s = calc(N, A - 1);
		pair<LL,LL> d = calc(N, B - 1);
		LL ax = s.first - d.first,ay = s.second - d.second;
		cout <<fixed << setprecision(0) << sqrt(ax * ax + ay * ay)*10<< endl;
	}
	return 0;
}
