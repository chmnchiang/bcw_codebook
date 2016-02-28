#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define F first
#define S second
#define PB push_back
#define ALL(x) begin(x),end(x)
#define SZ(x) ((int)(x).size())
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
freopen(name".in", "r", stdin); \
freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif
template<typename A, typename B>
ostream& operator <<(ostream &s, const pair<A,B> &p) {
return s<<"("<<p.first<<","<<p.second<<")";
}
template<typename T>
ostream& operator <<(ostream &s, const vector<T> &c) {
s<<"[ ";
for (auto it : c) s << it << " ";
s<<"]";
return s;
}
#define REP(i,x) for(int i=0;i<(x);i++)
#define REP1(i,a,b) for (int i=(a);i<=(b);i++)
// Let's Fight!

typedef long double ld;
typedef pair<int, ld> pid;
typedef pair<ld, int> pdi;

const int MAXN = 20101;
const ld EPS = 1E-12;
const ld INF = 1E20;

int N, M, L;
int eu[MAXN], ev[MAXN], el[MAXN];
ld rlen[MAXN];
bool used[MAXN];
vector<pid> edge[MAXN];
ld dis[MAXN];

bool test(ld x)
{
	for(int i=0; i<N; i++)
		edge[i].clear();
	for(int i=0; i<M; i++)
	{
		rlen[i] = (used[i] ? max(el[i]-x, 1.l) : el[i]+x);
		edge[eu[i]].PB({ev[i], rlen[i]});
		edge[ev[i]].PB({eu[i], rlen[i]});
	}

	for(int i=0; i<N; i++)
		dis[i] = INF;

	priority_queue<pdi, vector<pdi>, greater<pdi>> pq;
	pq.push({0, 0});
	while(!pq.empty())
	{
		pdi p = pq.top();
		pq.pop();
		ld c = p.F;
		int v = p.S;
		if(dis[v] != INF) continue;
		dis[v] = c;
		for(auto u: edge[v])
			pq.push({c+u.S, u.F});
	}

	ld splen = dis[N-1];
	ld tlen = 0;
	for(int i=0; i<M; i++)
		if(used[i])
			tlen += rlen[i];
	return tlen <= splen + EPS;
}

ld calc()
{
	ld lb = 0, rb = 1E5;
	for(int i=0; i<50; i++)
	{
		ld mb = (lb + rb) / 2;
		if(test(mb))
			rb = mb;
		else
			lb = mb;
	}

	return (lb + rb) / 2;
}

int main() {
	IOS;
	FILEIO("lateagain");

	cin>>N>>M;
	for(int i=0; i<M; i++)
	{
		cin>>eu[i]>>ev[i]>>el[i];
		eu[i]--;
		ev[i]--;
	}
	cin>>L;
	for(int i=0; i<L; i++)
	{
		int x;
		cin>>x;
		x--;
		used[x] = true;
	}

	ld res = calc();
	cout<<fixed<<setprecision(10)<<res<<endl;
	for(int i=0; i<M; i++)
		cout<<rlen[i]<<(i==M-1 ? "\n" : " ");

	return 0;
}
