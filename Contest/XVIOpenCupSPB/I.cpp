#pragma GCC optimize ("O2")
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
#define REP(i,x) for (int i=0; i<(x); i++)
#define REP1(i,a,b) for (int i=(a); i<=(b); i++)
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
// Let's Fight!

using ll = long long;
using pll = pair<ll,ll>;
const int MXN = 200005;
const ll INF = 1LL<<60;

int N,ip[2][MXN];
int done[MXN];
ll dis[MXN];
vector<pll> E[MXN];


int main() {
	IOS;
	cin>>N;
	REP(i,N) {
		cin>>ip[0][i];
	}
	REP(i,N) {
		cin>>ip[1][i];
	}

	int S = 1;
	int T = 2*N-1;
	int V = 2*N;
	REP(i,V) dis[i] = INF;

	REP(i,N-1) {
		if (ip[1][i+1] >= ip[0][i] or
			ip[0][i+1] <= ip[1][i]) {
			cout<<"-1"<<endl;
			return 0;
		}
	}

	REP(i,N-1) {
		int a = 2 * i;
		int b = 2 * (i+1);
		if (ip[0][i] <= ip[0][i+1]) E[a].PB({b,0});
		if (ip[0][i+1] <= ip[0][i]) E[b].PB({a,0});

		a++;
		b++;
		if (ip[1][i] >= ip[1][i+1]) E[a].PB({b,0});
		if (ip[1][i+1] >= ip[1][i]) E[b].PB({a,0});
	}

	REP(i,N) {
		int a = 2*i;
		int b = 2*i+1;
		int w = abs(ip[0][i]-ip[1][i]);
		E[a].PB({b,w});
		E[b].PB({a,w});
	}

	priority_queue<pll> pq;
	dis[S] = 0;
	pq.push({-dis[S],S});
	while (!pq.empty()) {
		int u = pq.top().S;
		pq.pop();
		if (done[u]) continue;
		done[u] = 1;
		for (auto it:E[u]) {
			int v = it.F;
			ll w = it.S;
			if (dis[v] > dis[u] + w) {
				dis[v] = dis[u] + w;
				pq.push({-dis[v],v});
			}
		}
	}

	/*
	REP(i,N) cout<<dis[i*2]<<" ";
	cout<<endl;
	REP(i,N) cout<<dis[i*2+1]<<" ";
	cout<<endl;
	*/

	ll ans = dis[T];
	if (ans != INF) cout<<ans<<endl;
	else cout<<"-1"<<endl;

	return 0;
}

