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
#define endl "\n"
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

const int MX = 202020;
int N;
typedef pair<int, int> pii;
vector<pii> ip;
priority_queue<pii> pq;
int bk[MX];

void sol(int s) {
	static bool us[MX];
	fill(us, us+N+1, false);
	int t = N-1;
	bool st = true;
	while (true) {
		for (int i=s+1; i<=t; i++) us[i] = st;
		st = !st;
		if (s == -1) break;
		t = s;
		s = bk[s+1];
	}

	//for (int i=0; i<N; i++) cout << us[i] << ' ';
	//cout << endl;
	cout << "yes" << endl;
	for (int i=0; i<N; i++) {
		if (not us[i]) {
			cout << ip[i].F << ' ' << ip[i].S << endl;
		}
	}
	
	for (int i=N-1; i>=0; i--) {
		if (us[i]) {
			cout << ip[i].S << ' ' << ip[i].F << endl;
		}
	}
}

void solve() {
	cin >> N;
	ip.resize(N);
	for (int i=0; i<N; i++) {
		cin >> ip[i].F >> ip[i].S;
		if (ip[i].S < ip[i].F) swap(ip[i].S, ip[i].F); 
	}
	if (N == 1) {
		cout << "yes" << endl;
		cout << ip[0].F << ' ' << ip[0].S << endl;
		return;
	}

	sort(ALL(ip), [](pii p1, pii p2) { p1.S *= -1; p2.S *= -1; return p1 < p2; });
	//cout << ip << endl;

	const int INF = 1029384756;
	pq = priority_queue<pii>();
	pq.push({INF, -1});

	for (int i=0; i<N; i++) {
		bool ok1 = false, ok2 = false;
		if (SZ(pq)) {
			auto p = pq.top();
			//cout << p << endl;
			if (p.F >= ip[i].S) {
				ok1 = true;
				bk[i] = p.S;
			}
		}
		if (i) {
			int j = i-1;
			if (ip[j].S >= ip[i].S) {
				ok2 = true;
				//bk[i] = i-1;
			}
		} else ok2 = true;
		//cout << bk[i] << endl;
		//cout << ok1 << ' ' << ok2 << endl;

		if (not ok1 and not ok2) {
			cout << "no" << endl;
			return;
		}

		if (not ok2) {
			pq = priority_queue<pii>();
		}

		if (i and ok1) pq.push({ip[i-1].S, i-1});
	}

	pii lst = ip.back();
	while (SZ(pq)) {
		pii p = pq.top();
		pii t = ip[p.S];
		//cout << t << endl;

		if (lst.F <= t.S and lst.S >= t.F) {
//			cout << "Sol = " << p.S << endl;
			sol(p.S);
			return;
		} else pq.pop();
	}
	cout << "no" << endl;
}

int main() {
	IOS;

	int T;
	cin >> T;
	while (T--) {
		solve();
	}

	return 0;
}
