

//二维前缀和
#include<bits/stdc++.h>
#define REP(i, a, b) for(register int i = (a); i < (b); i++)
#define _for(i, a, b) for(register int i = (a); i <= (b); i++)
using namespace std;

const int N = 100;
int a[N][N], n;

int main()
{
    scanf("%d", &n);
    _for(i, 1, n)
        _for(j, 1, n)
        {
            int x; scanf("%d", &x);
            a[i][j] = x + a[i-1][j] + a[i][j-1] - a[i-1][j-1];
        }
    
    int x1, y1, x2, y2;
    while(~scanf("%d%d%d%d", &x1, &y1, &x2, &y2))
        printf("%d\n", a[x2][y2] - a[x1-1][y2] - a[x2][y1-1] + a[x1-1][y1-1]);
 
    return 0;
}

//二维差分
#include<bits/stdc++.h>
#define REP(i, a, b) for(register int i = (a); i < (b); i++)
#define _for(i, a, b) for(register int i = (a); i <= (b); i++)
using namespace std;

const int N = 100;
int a[N][N], n, m;

int main()
{
    scanf("%d%d", &n, &m);
    _for(i, 1, m)
    {
        int x1, y1, x2, y2, p;
        scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &p);
        a[x1][y1] += p; a[x2+1][y2+1] += p;
        a[x2+1][y1] -= p; a[x1][y2+1] -= p;
    } 

    _for(i, 1, n)
        _for(j, 1, n)
            a[i][j] += a[i-1][j] + a[i][j-1] - a[i-1][j-1];
    
    _for(i, 1, n)
    {
        _for(j, 1, n)
            printf("%d ", a[i][j]);
        puts(""); 
    } 
        
    return 0;
}
