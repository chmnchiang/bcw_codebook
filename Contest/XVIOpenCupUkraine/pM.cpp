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


#define int long long
using Poly = array<int, 8>;
vector<Poly> ip;
int N;
const int INF = 1e17+10;
const double Z = 5e17;
using pii = pair<int, int>;
priority_queue<pii> pq;
const int MX = 2e5;
int zid[MX];

int pow(int a, int b, int c) {

	int res = 1;
	double x = 1.0;
	for (int i=0; i<b; i++) {
		res *= a;
		x *= a;
		if (x*c > 3.0*INF) return INF;
	}
	return res * c;
}

int eval(Poly p, int n) {
	int res = 0;
	for (int i=0; i<=7; i++) {
		res += pow(n, i, p[i]);
		if (res > INF) res = INF;
	}
	return res;
}

int32_t main() {
	IOS;
	cin>>N;
	ip.resize(N);
	for (int i=0; i<N; i++) {
		for (int j=7; j>=0; j--) {
			cin>>ip[i][j];
		}
		pq.push({-eval(ip[i], 1), i});
		zid[i] = 1;
	}

	
	int M; cin >> M;
	for (int i=0; i<M-1; i++) {
		int t = pq.top().S;
		pq.pop();
		int q = ++zid[t];
		pq.push({-eval(ip[t], q), t});
	}
	cout << -pq.top().F << endl;


	return 0; 
}

