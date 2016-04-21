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

int B,S,N;

using pii=pair<int,int>;
using arr=array<array<int, 14>, 14>;

int remSize[15],color[15];
vector<int> vecSize;
int counter;
arr varSm[9555];
int varFs[9555];
const int INF = 1ll<<60;
int ans = INF;
vector<string> ip;

int solve(int a, int f) {
	//auto &z = varSm[f];
	/*
	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) cout << z[i][j] << ' ';
		cout << endl;
	}*/
	int res = (varFs[f] == -1 ? 0 : 2);
	//cout << "FS = " << varFs[f] << endl;
	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
			int u = color[i], v = color[j];
			if (u == a or v == a) continue;

			if (u == v) res += varSm[f][i][j];
			else res += 2*varSm[f][i][j];
		}

		if (color[i] == a) {
			res += varSm[f][i][i];
		}
	}
	return res;
}

void solve() {


	int cmax = 0;
	for (int i=0; i<N; i++) {
		cmax = max(cmax, color[i]);
	}
	for (int i=0; i<=cmax; i++) {
		int flag = 0;
		for (int j=0; j<N; j++) {
			if (color[j] == i) flag |= (1<<j);
		}
		ans = min(solve(i, flag), ans);
	}
}
void DFS2(int cur) {
	if (cur >= N) {
		counter++;
		solve();
		return;
	}
	REP(i,SZ(vecSize)) {
		if (!remSize[i]) continue;
		if (remSize[i] != vecSize[i]) {
			color[cur] = i;
			remSize[i]--;
			DFS2(cur+1);
			remSize[i]++;
		} else {
			int ok = 1;
			for (int j=i-1; j>=0; j--) {
				if (vecSize[j] != vecSize[i]) break;
				if (remSize[j] == vecSize[i]) {
					ok = 0;
					break;
				}
			}
			if (!ok) continue;
			color[cur] = i;
			remSize[i]--;
			DFS2(cur+1);
			remSize[i]++;
		}
	}
}
void DFS(int curB, int rem, int lstCnt) {
	if (curB >= 2 and vecSize[0] + vecSize[1] <= S) return;
	if (rem == 0) {
		REP(i,SZ(vecSize)) remSize[i] = vecSize[i];
		DFS2(0);
		return;
	}
	if (curB >= B) return;
	REP1(i,lstCnt,rem) {
		if (i > S) return;
		vecSize.PB(i);
		DFS(curB+1,rem-i,i);
		vecSize.pop_back();
	}
}
struct Data {
	pii p;
	arr a;
};

int geti(string s) {
	int t = 0;
	for (auto c: s) {
		t*=10;
		t+=c-'0';
	}
	return t;
}

int pid;
int pflag;
Data parse() {
	int fs = -1;
	int ls = -1;
	arr a = {};
	auto udp = [&](int x, int y) {
		assert(x != -1 and y != -1);
		if (ls != -1) a[ls][x] ++;
		ls = y;
		if (fs == -1) fs = x;
	};
	while (pid < SZ(ip)) {
		string s = ip[pid];
		pid++;
		if (s[0] == 'E') {
			//cout << fs << ' ' << ls << endl;
			return {{fs, ls}, a};
		} else if (s[0] == 'R') {
			int t = geti(s.substr(1));
			auto p = parse();
			for (int i=0; i<N; i++) {
				for (int j=0; j<N; j++) {
					a[i][j] += p.a[i][j] * t;
				}
			}
			if (p.p.F != -1) {
				a[p.p.S][p.p.F] += t-1;
				udp(p.p.F, p.p.S);
			}
		} else {
			int t = geti(s.substr(1))-1;
			//cout << "T = " << t << endl;
			if ((1<<t) & pflag) a[t][t] ++;
			else udp(t, t);
		}
	}
	return {{fs, ls}, a};
}

int32_t main() {
	IOS;
	cin >> B >> S;
	N = min(B*S,13ll);
	string s;
	while (cin >> s) {
		ip.PB(s);
	}
	for (int i=0; i<(1<<N); i++) {
		pid = 0;
		pflag = i;
		//cout << "flag = " << pflag << endl;
		auto x = parse();
		varSm[i] = x.a;
		varFs[i] = x.p.F;
	}


	// end input

	DFS(0,N,1);
//	cout << counter << endl;
	cout << ans << endl;

	return 0;
}

