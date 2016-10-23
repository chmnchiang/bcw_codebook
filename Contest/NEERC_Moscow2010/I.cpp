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


typedef pair<int,int> pii;
const int MXN = 200005;

struct ILog {
	int uid,cid,t,h;
	friend ostream& operator << (ostream &s, const ILog &he) {
		return s << "(" << he.uid << "," << he.cid << "," << he.t << "," << he.h << ")";
	}
}A[MXN];
struct ELog {
	int uid,cid,adv,t,c;
}B[MXN];

struct JLog {
	int uid,cid,ct,h,adv,st,c;
};

bool operator < (const ILog a, const ILog b) {
	return make_tuple(a.t,a.uid,a.cid,a.h) < make_tuple(b.t,b.uid,b.cid,b.h);
}

struct Lisan {
	vector<pii> seq;
	void add(pii a) { seq.PB(a); }
	void make() {
		sort(ALL(seq));
		seq.resize(unique(ALL(seq))-begin(seq));
	}
	int qry(pii a) { return lower_bound(ALL(seq),a)-begin(seq); }
}ls;

int N,M;
vector<ILog> vec[MXN];
//vector<pii> mx[MXN];

int main() {
	IOS;
	cin >> N >> M;
	REP(i,N) {
		cin >> A[i].uid >> A[i].cid >> A[i].t >> A[i].h;
		ls.add({A[i].uid,A[i].cid});
	}
	REP(i,M) {
		cin >> B[i].uid >> B[i].cid >> B[i].adv >> B[i].t >> B[i].c;
		ls.add({B[i].uid,B[i].cid});
	}
	ls.make();
	REP(i,N) {
		int id = ls.qry({A[i].uid,A[i].cid});
		vec[id].PB(A[i]);
	}
	REP(i,MXN) {
		sort(ALL(vec[i]));
	}

	vector<JLog> ans;
	REP(i,M) {
		int id = ls.qry({B[i].uid,B[i].cid});
		ILog tmp;
		tmp.uid = -2e9;
		tmp.cid = -2e9;
		tmp.t = B[i].t;
		tmp.h = -2e9;
		int j = lower_bound(ALL(vec[id]),tmp) - begin(vec[id]);

//		cout << i << " " << vec[id] << endl;
//		cout << "CHOOSE" << j-1 << endl;

		if (j == 0) continue;
		j--;
		ans.PB({B[i].uid,B[i].cid,vec[id][j].t,vec[id][j].h,B[i].adv,B[i].t,B[i].c});
	}
	sort(ALL(ans), [&](JLog a, JLog b) {
			return make_tuple(a.h,a.uid,a.cid,a.ct,a.adv,a.st) <
			make_tuple(b.h,b.uid,b.cid,b.ct,b.adv,b.st);
			});

	cout << SZ(ans) << endl;
	for (auto i:ans) {
		cout << i.uid << " " << i.cid << " " << i.ct << " " << i.h << " " << i.adv << " " << i.st << " " << i.c << "\n";
	}



	return 0;
}
