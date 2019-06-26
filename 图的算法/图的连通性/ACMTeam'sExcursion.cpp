#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn=3e5+10,maxm=2e5+5;
const ll inf=0x7fffffff;
const ll mod=1e9+7;
template<typename T>inline void read(T &x)
{
	x=0;
	T f=1,ch=getchar();
	while (!isdigit(ch) && ch^'-') ch=getchar();
	if (ch=='-') f=-1, ch=getchar();
	while (isdigit(ch)) x=(x<<1)+(x<<3)+(ch^48), ch=getchar();
	x*=f;
}
ll spot[maxm<<1],ver[maxm<<1],edge[maxm<<1],Next[maxm<<1],head[maxn],Out[maxn],len;
inline void add(ll x,ll y,ll z)
{
	spot[++len]=x,ver[len]=y,edge[len]=z,Next[len]=head[x],head[x]=len,++Out[y];
}
ll vc[maxm<<1],ec[maxm<<1],Nc[maxm<<1],hc[maxn],Otc[maxn],lc;
inline void addc(ll x,ll y,ll z)
{
	vc[++lc]=y,ec[lc]=z,Nc[lc]=hc[x],hc[x]=lc,++Otc[y];
}
ll n,m,s,t,q;
ll deg[maxn],fs[maxn];
inline void topsort1()
{
	memcpy(deg,Out,sizeof(Out));
	queue<ll>q;
	fs[s]=1;
	for (ll i=1;i<=n;++i)
		if (!deg[i])
			q.push(i);
	while (!q.empty())
	{
		ll x=q.front();
		q.pop();
		for (ll i=head[x];i;i=Next[i])
		{
			ll y=ver[i];
			fs[y]+=fs[x];//到y的路径条数
			fs[y]%=mod;
			if (!--deg[y]) q.push(y);
		}
	}
}
ll ft[maxn];
inline void topsort2()
{
	queue<ll>q;
	ft[t]=1;
	for (ll i=1;i<=n;++i)
		if (!Otc[i])
			q.push(i);
	while (!q.empty())
	{
		ll x=q.front();
		q.pop();
		for (ll i=hc[x];i;i=Nc[i])
		{
			ll y=vc[i];
			ft[y]+=ft[x];
			ft[y]%=mod;
			if (!--Otc[y]) q.push(y);
		}
	}
}
ll dist[maxn],pre[maxn];
inline void topsort3()
{
	queue<ll>q;
	for (ll i=1;i<=n;++i)
		if (!Out[i])//入度为0的点入队
			q.push(i);
	while (!q.empty())
	{
		ll x=q.front();
		q.pop();
		for (ll i=head[x];i;i=Next[i])
		{
			ll y=ver[i],z=edge[i];
			if (dist[y]>dist[x]+z)
			{
				dist[y]=dist[x]+z;
				pre[y]=x;
			}
			if (!--Out[y]) q.push(y);
		}
	}
}
ll f[maxn],path[maxn],sum[maxn],cnt;
bool flag1[maxn];
inline void solve1()
{
	ll cur=1;
	for (ll i=1;i<=cnt;++i)
	{
		while (dist[path[i]]-dist[path[cur]]>q)//离path[i]的距离不能超过q
			++cur;
		f[i]=f[i-1];
		ll temp=sum[path[i]]-sum[path[cur]];//此段路径内必经边的距离
		if (flag1[path[cur]])
			temp+=q-(dist[path[i]]-dist[path[cur]]);//cur之前也是必经边，因此把必经边上的这一段也要算上
		f[i]=max(f[i],temp);
	}
}
ll g[maxn];
bool flag2[maxn];
inline void solve2()
{
	ll cur=cnt;
	for (ll i=cnt;i>=1;--i)
	{
		while (dist[path[cur]]-dist[path[i]]>q)
			--cur;
		g[i]=g[i+1];
		ll temp=sum[path[cur]]-sum[path[i]];
		if (flag2[path[cur]])
			temp+=q-(dist[path[cur]]-dist[path[i]]);
		g[i]=max(g[i],temp);
	}
}
inline void Clear()
{
	for (ll i=1;i<=n;++i)
		dist[i]=inf;//初始化距离为无穷大
	memset(fs,0,sizeof(fs));//s出发到各节点的路径条数初始化为0
	memset(ft,0,sizeof(ft));
	memset(flag1,0,sizeof(flag1));
	memset(flag2,0,sizeof(flag2));
	memset(sum,0,sizeof(sum));
	memset(f,0,sizeof(f));
	memset(g,0,sizeof(g));
	memset(head,0,sizeof(head));
	memset(hc,0,sizeof(hc));
	len=lc=0;
}
int main()
{
	int T;read(T);
	while (T--)
	{
		read(n);read(m);read(s);read(t);read(q);
		++s,++t;
		Clear();
		for (ll i=1;i<=m;++i)// 加边
		{
			ll x,y,z;
			read(x);read(y);read(z);
			++x,++y;
			add(x,y,z);
			addc(y,x,z);//建反图
		}
		topsort1();//求起点s到每个点的路径条数fs[x]
		topsort2();//在反图上求每个点x到终点t的路径条数ft[x]
		for (ll i=1;i<=len;++i)//枚举每条边
		{
			ll x=spot[i],y=ver[i];
			if (fs[x]*ft[y]%mod==fs[t])//必经边
			{
				sum[y]=edge[i];//以y为入点的必经边的边长
				flag1[y]=flag2[x]=1;//必经点，flag2的反图上的必经点
			}
		}
		dist[s]=0;
		topsort3();//求最短路
		if (dist[t]==inf)//there is no route from s to t
			puts("-1");
		else
		{
			cnt=0;//从s到t经过的节点数量
			ll p=t;
			do
			{
				path[++cnt]=p; // 从t到s的路径
				p=pre[p];
			} while (p!=s);
			path[++cnt]=s;
			reverse(path+1,path+cnt+1);// 翻转后变成从s到t的路径
			for (ll i=1;i<=cnt;++i)
				sum[path[i]]+=sum[path[i-1]]; //从起点到i的路径上必经边的距离和
			solve1();//求f[i],从s节点到i节点只搭一次车的最大危险程度
			solve2();//求g[i],从i节点到t节点只搭一次车的最大危险程度
			ll temp=sum[path[cnt]],ans=inf;//temp为整个路径上必经边的长度之和
			for (ll i=1;i<=cnt;++i)
				ans=min(ans,temp-(f[i]+g[i]));
			printf("%lld\n",ans);
		}
	}
	return 0;
}
