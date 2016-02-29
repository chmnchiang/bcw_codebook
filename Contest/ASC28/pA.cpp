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

const int MX = 202020;

int T;
int N, K;
int _ord[MX*2];
int *ord = _ord + MX;
int curc[MX];
int ip[MX];
int op[MX];

int minl = -1;

const int INF = 1029384756;
void fillmin(int j) {
	stack<int> st;
	int lc = 0;
	for (int i=0; i<j; i++) {
		int t = op[i];
		if (t > 0) {
			st.push(-op[i]);
			lc++;
		} else st.pop();
	}

	for (int i=j; i<2*N; i++) {
		int ol = ord[minl];
		int r=INF, _or = INF;
		if (SZ(st)) {
			r = st.top();
			_or = ord[r];
		}
		if (ol < _or and lc < N) {
			op[i] = minl;
			lc ++;
			st.push(-minl);
		} else {
			assert(r != INF);
			op[i] = r;
			st.pop();
		}
	}

	for (int i=0; i<N*2; i++) {
		cout << op[i] << (i == N*2-1 ? "\n" : " ");
	}
}

typedef pair<int, int> pii;
void solve() {
	cin >> N >> K;
	int M = max(N, K);
	fill(curc, curc+M*2+5, 0);
	fill(_ord, _ord+M*2+5, 0);
	fill(ip, ip+M*2+5, 0);
	fill(op, op+M*2+5, 0);
	minl = -1;

	vector<pii> ss;
	for (int i=0; i<K*2; i++) {
		int t; cin >> t;
		ord[t] = i;
		if (minl == -1 and t > 0) {
			minl = t;
		}
		if (t > 0) {
			ss.PB({i, t});
		}
	}

	auto next_big = [&] (int t) {
		int o = ord[t];
		auto it = lower_bound(ALL(ss), pii{o, INF});
		if (it == ss.end()) return 0;
		return it->S;
	};
	//cout << ss << endl;


	stack<int> st;
	for (int i=0; i<N*2; i++) {
		int t; cin >> t;
		ip[i] = t;
		if (st.size()) {
			curc[i] = st.top();
		}

		if (t > 0) {
			st.push(-t);
		} else {
			st.pop();
		}
	}

	int lc = N;
	for (int i=2*N-1; i>=0; i--) {
		int t = ip[i];

		int xt = 0, xo = INF;
		//cout << "i = " << i << endl;
		if (ip[i] > 0) lc --;
		if (curc[i] and ord[curc[i]] > ord[t]) {
			if (xo > ord[curc[i]]) {
				xt = curc[i];
				xo = ord[curc[i]];
			}
		}
		if (lc != N) {
			int n = next_big(t);
			if (n and ord[n] > ord[t]) {
				if (xo > ord[n]) {
					xt = n;
					xo = ord[n];
				}
			}
		}

		if (xt) {
			for (int j=0; j<i; j++) {
				op[j] = ip[j];
			}
			op[i] = xt;
			/*
			for (int j=0; j<=i; j++) {
				cout << op[j] << ' ';
			} cout << endl;
			*/
			fillmin(i+1);
			return;
		}

	}
	//cout << "OK" << endl;
	fillmin(0);
}

int main() {
	IOS;
	FILEIO("brackets");

	cin >> T;

	while (T--) {
		solve();
	}

    return 0;
}

