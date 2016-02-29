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

const int MXN = 100005;

struct Lisan {
	vector<int> seq;
	void add(int x) { seq.PB(x); }
	void build() {
		sort(ALL(seq));
		seq.resize(unique(ALL(seq))-begin(seq));
	}
	int id(int x) {
		return lower_bound(ALL(seq),x)-begin(seq)+1;
	}
}lisan;

struct BIT {
	int bit[MXN];
	void init() {
		FZ(bit);
	}
	int lb(int a) { return a & -a; }
	void update(int st, int v) {
		for (int i=st; i<MXN; i+=lb(i))
			bit[i] += v;
	}
	int query(int st) {
		int res=0;
		for (int i=st; i>0; i-=lb(i))
			res += bit[i];
		return res;
	}
}bit1,bit2;

int N,ip[MXN],ID[MXN],at[MXN];
int bpos;



int main() {
	IOS;
	FILEIO("mtf");
	cin >> N;
	REP(i,N) {
		cin >> ip[i];
		lisan.add(ip[i]);
	}
	lisan.build();
	REP(i,N) {
		ID[i] = lisan.id(ip[i]);
	}
	bpos = MXN-1;
	bit1.init();
	bit2.init();
	REP1(i,1,MXN-1) {
		bit2.update(i,1);
	}

	vector<int> ans;
	FZ(at);
	REP(i,N) {
		int id = ID[i];
		int res = 0;
		if (at[id] == 0) {
			res = bit1.query(MXN-1);
			res += ip[i] - (id-bit2.query(id));
			at[id] = bpos--;
			bit1.update(at[id], 1);
			bit2.update(id, -1);
		} else {
			res = bit1.query(at[id]);
			bit1.update(at[id], -1);
			at[id] = bpos--;
			bit1.update(at[id], 1);
		}
		ans.PB(res);
	}
	for (auto it:ans) cout << it << " ";
	cout << endl;


	return 0;
}

