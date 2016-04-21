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
const ll INF = 1LL << 60;

int A,B,N,M;
int lt[514],rt[514];
ll dep[514],ip[514][514],ans;


ll solve(ll x) {
//	cout << "SOLVE " << x << " : ";
//	REP(i,M) cout << dep[i] << " " ;
//	cout << endl;
	ll res = 0;
	stack<int> stk;
	REP(i,M) {
		while (!stk.empty() and dep[stk.top()] > dep[i]) {
			rt[stk.top()] = i;
			stk.pop();
		}
		stk.push(i);
	}
	while (!stk.empty()) {
		rt[stk.top()] = M;
		stk.pop();
	}

	for (int i=M-1; i>=0; i--) {
		while (!stk.empty() and dep[stk.top()] > dep[i]) {
			lt[stk.top()] = i;
			stk.pop();
		}
		stk.push(i);
	}
	while (!stk.empty()) {
		lt[stk.top()] = -1;
		stk.pop();
	}
//	REP(i,M) cout << "# " << i << " : " << lt[i] << " " << rt[i] << endl;

	REP(i,M) {
		int y = min(rt[i]-lt[i]-1,B);
		ll d = dep[i];
		ll V = 1LL * x * y * ((d*M*N-1) / (M*N-x*y));
		res = max(res, V);
	}

	return res;
}
void calc() {
	REP(i,N) {
		REP(j,M) dep[j] = INF;
		REP1(j,i,N-1) {
			if (j - i + 1 > A) break;
			REP(k,M) dep[k] = min(dep[k],ip[j][k]);
			ans = max(ans,solve(j-i+1));
		}
	}
}
int main() {
	IOS;
	cin >> A >> B >> N >> M;
	REP(i,N) {
		REP(j,M) cin >> ip[i][j];
	}
	ans = 0;
	calc();
	swap(A,B);
	calc();
	cout << ans << endl;

	return 0;
}

