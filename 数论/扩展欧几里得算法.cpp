#include<cstdio>
using namespace std;

int exgcd(int a, int b, int &x, int &y)
{
    if(b == 0)
    {//推理1，终止条件
        x = 1;
        y = 0;
        return a;
    }
    int r = exgcd(b, a%b, x, y);
    //先得到更底层的x2,y2,再根据计算好的x2,y2计算x1，y1。
    //推理2，递推关系
    int t = y;
    y = x - (a/b) * y;
    x = t;
    return r;
}

int exgcd1(int a, int b, int &x, int &y)//我写的函数
{
    if(b == 0)
    {//推理1，终止条件
        x = 1;
        y = 0;
        return a;
    }
    int x2,y2;   //局部变量x2,y2
    int r = exgcd(b, a%b, x2, y2);
    //先得到更底层的x2,y2,再根据计算好的x2,y2计算x1，y1。
    //推理2，递推关系
    x=y2;
    y=x2-a/b*y2;
    return r;
}
int main() {
   int a,b,x,y,x1,y1;
   scanf("%d%d",&a,&b);
   //如果有解,则继续
    exgcd(a,b,x,y);
    printf("%d %d\n",x,y);
    exgcd1(a,b,x1,y1);
    printf("%d %d\n",x1,y1);
    return 0;
}
