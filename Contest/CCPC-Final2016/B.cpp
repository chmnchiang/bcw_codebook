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

typedef long long ll;
typedef pair<ll, ll> pll;

const int MAXN = 101010;

int N, M, L;
ll w[MAXN], d[MAXN];

ll calc()
{
	priority_queue<pll, vector<pll>, greater<pll>> pq;
	for(int i=0; i<N; i++)
		pq.push({w[i], i});

	vector<ll> vw;
	while(SZ(vw) < L)
	{
		pll p = pq.top();
		pq.pop();
		vw.PB(p.F);
		pq.push({p.F+w[p.S], p.S});
	}

	while(!pq.empty()) pq.pop();

	for(int i=0; i<M; i++)
		pq.push({d[i], i});

	vector<ll> vd;
	while(SZ(vd) < L)
	{
		pll p = pq.top();
		pq.pop();
		vd.PB(p.F);
		pq.push({p.F+d[p.S], p.S});
	}

	ll ans = 0;
	for(int i=0; i<L; i++)
		ans = max(ans, vw[i] + vd[L-i-1]);

	return ans;
}

int main() {
	IOS;

	int T;
	cin>>T;
	for(int t=1; t<=T; t++)
	{
		cin>>L>>N>>M;
		for(int i=0; i<N; i++)
			cin>>w[i];
		for(int i=0; i<M; i++)
			cin>>d[i];

		ll ans = calc();
		cout<<"Case #"<<t<<": "<<ans<<endl;
	}

	return 0;
}

