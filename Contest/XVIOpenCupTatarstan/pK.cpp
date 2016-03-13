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

const int MXN = 10005;

struct BIT {
	int bit[MXN];
	void init() {
		FZ(bit);
	}
	int lb(int x) { return x & -x; }
	void add(int x, int v) {
		for (int i=x; i<MXN; i+=lb(i))
			bit[i] += v;
	}
	int query(int x) {
		int res = 0;
		for (int i=x; i>0; i-=lb(i))
			res += bit[i];
		return res;
	}
};

string ip, op;
vector<int> l1, l2;
vector<int> s1, s2;
int N;
int M;
typedef pair<int, int> pii;
vector<pii> ans1, ans2;

void rotate(int l, int r) {
	ans1.PB({l+1, r});
}

void rotate2(int l, int r) {
	ans2.PB({l+1, r});
}

void cc(string s, vector<int> &v) {
	for (int i=0, t=0; i<N; i++) {
		if (s[i] == '0') {
			t++;
		} else {
			v.PB(t);
			t = 0;
		}
		if (i == N-1) v.PB(t);
	}
}



int main() {
	IOS;

	cin >> ip >> op;
	N = SZ(ip);
	if (SZ(op) != N) {
		cout << "NO" << endl;
		return 0;
	}
	//cout << "IP = " << ip << endl;
	cc(ip, l1);
	cc(op, l2);

	if (SZ(l1) != SZ(l2)) {
		cout << "NO" << endl;
		return 0;
	}
	M = SZ(l1);
	s1.resize(M+1);
	s1[0] = 0;
	s2.resize(M+1);
	s2[0] = 0;
	for (int i=0; i<M; i++) {
		s1[i+1] = s1[i] + l1[i];
		s2[i+1] = s2[i] + l2[i];
	}

	int t[2] = {};
	for (int i=0; i<M; i++) {
		t[i%2] += (l1[i] - l2[i]);
	}
	if (t[0] or t[1]) {
		cout << "NO" << endl;
		return 0;
	}

	for (int i=0; i<M-2; i++) {
		rotate(i, s1[i+2]+2+i);
	}

	for (int i=0; i<M-2; i++) {
		rotate2(i, s2[i+2]+2+i);
	}


	int z = SZ(ans1) + SZ(ans2);
	cout << "YES" << endl;
	assert(z <= 16*N);
	cout << z << endl;
	reverse(ALL(ans2));
	ans1.insert(ans1.end(), ALL(ans2));
	for (auto p: ans1) {
		cout << p.F << ' ' << p.S << endl;
		//reverse(ip.begin()+p.F, ip.begin()+p.S);
		//cout << ip << endl;
	}
	//assert(ip == op);

	return 0;
}


