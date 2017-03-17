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
#ifdef BCW
#define FILEIO(name)
#else
#define FILEIO(name) \
    freopen(name".in", "r", stdin); \
    freopen(name".out", "w", stdout);
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
const int MS = 4444;
const int MP = 888;

int dig[MS];
int isp[MS];
vector<int> primes;

using Arr = array<int, 3>;
const int INF = 2e18;
const int INF2 = 5e17;

int digit(int n) {
	int s = 0;
	while (n) {
		s++;
		n /= 10;
	}
	return s;
}

void init() {
	fill(isp, isp+MS, 1);
	isp[0] = isp[1] = 0;
	for (int i=2; i<MS; i++) {
		if (isp[i]) {
			primes.PB(i);
			for (int j=i+i; j<MS; j+=i) {
				isp[j] = 0;
			}
		}
	}

	for (int i=0; i<MS; i++) dig[i] = digit(i);
}

Arr norm(Arr a) {
	return Arr{
		min(a[0], INF2),
		min(a[1], INF),
		min(a[2], INF)
	};
}

ostream& operator << (ostream &o, const Arr &a) {
	return o << '(' << a[0] << ' ' << a[1] << ' ' << a[2] << ')';
}

bool us[MS][MP];
Arr mem[MS][MP];
int sm[MS];

Arr dp(int s, int pid) {
	if (s < 0) return Arr{0, 0, 0};
	if (s == 0) return Arr{1, 0, 0};
	if (pid >= SZ(primes) || primes[pid] > s) return Arr{0, 0, 0};

	if (us[s][pid]) return mem[s][pid];

	us[s][pid] = 1;
	int p = primes[pid];

	auto a1 = dp(s - p, pid+1), a2 = dp(s, pid+1);
	Arr a;
	a[0] = a1[0] + a2[0];
	a[1] = a1[1] + a1[0] + a2[1];
	a[2] = a1[2] + min(a1[0] * dig[p], INF) + a2[2];

	a = norm(a);
	mem[s][pid] = a;

	return a;
}

int Z(const Arr &a) {
	if (!a[0]) return 0;
	return min(a[0]*2 + a[1]*2 + a[2], INF);
}

const int HAO = 3000;
int L, R;
const int HAHA = 2e5;
char _ans[3*HAHA], *ans = _ans + HAHA;
int aid = 0;

vector<int> curs;
int tdg;

void print(int st) {
//	cout << st << ' ' << curs << endl;
	ans[st++] = '[';
	int n = SZ(curs);
	for (int i=0; i<n; i++) {
		int x = curs[i];
		if (i) {
			ans[st++] = ',';
			ans[st++] = ' ';
		}
		sprintf(ans+st, "%lld", x);
		st += dig[x];
		if (st >= HAHA) return;
	}
	ans[st++] = ']';
	ans[st++] = ',';
	ans[st++] = ' ';
}

int mult(int a, int b) {
	if (!a) return 0;
	if (INF / a < b) return INF;
	return a*b;
}

void go(int s, int pid, int l) {
	if (s == 0) {
		print(l);
		return;
	}
	int p = primes[pid];

	Arr a = dp(s-p, pid+1);
	a[1] = a[1] + mult(a[0], (1 + SZ(curs)));
	a[2] = a[2] + min(mult(a[0], dig[p] + tdg), INF);
	a = norm(a);
	int pre = Z(a);
	if (pre and pre + l > 0) {
		curs.PB(p);
		tdg += dig[p];
		go(s-p, pid+1, l);
		tdg -= dig[p];
		curs.pop_back();
	}
	l += pre;

	if (l > HAHA) {
		return;
	}

	a = dp(s, pid+1);
	a[1] = a[1] + mult(a[0], (SZ(curs)));
	a[2] = a[2] + min(mult(a[0], tdg), INF);
	a = norm(a);
	int post = Z(a);
	if (post and post > -l) {
		go(s, pid+1, l);
	}
}


void trace() {
	for (int i=1; i<HAO; i++) {
		go(i, 0, sm[i-1] - L);
		//cout << sm[i] << endl;
		if (sm[i] > R+10) break;
	}

	ans[R - L] = 0;
	for (int i=0; i<R-L; i++) cout << ans[i];
	cout << endl;
//	cout << ans << endl;
}

void calc() {
	cin >> L >> R;
	L--;
	trace();
}
	
int32_t main() {
	FILEIO("list");
	IOS;

	init();

	sm[0] = 0;
	for (int i=1; i<3000; i++) {
		Arr a = dp(i, 0);
		sm[i] = sm[i-1] + Z(a);
		sm[i] = min(sm[i], INF);
	}

	calc();

	return 0;
}

