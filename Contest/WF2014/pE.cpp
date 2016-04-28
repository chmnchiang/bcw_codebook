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

typedef pair<int,int> pii;
const int MUL = 12721;
const int MOD = 1000512343LL;
const int MXN = 105;
const int MX = 100005;

struct Lisan {
	vector<int> seq;
	void init() { seq.clear(); }
	void add(int x) { seq.PB(x); }
	void make() {
		sort(ALL(seq));
		seq.resize(unique(ALL(seq))-begin(seq));
	}
	int qry(int x) { return lower_bound(ALL(seq),x)-begin(seq); }
}ls;
struct DisjointSet {
	int fa[MX];
	DisjointSet() { REP(i,MX) fa[i]=i; }
	int f(int x) { return x == fa[x] ? x : fa[x]=f(fa[x]); }
	void uni(int x, int y) {
		fa[f(y)] = f(x);
	}
}djs;

int N,K,id[MX],tmpid[MX];
pii id2uv[MX];
int start[MX];
int rev[MX];

map<pii,int> mp;
vector<int> E[MXN];
vector<int> eid[MXN];
vector<int> grp[MX];
vector<vector<int>> ans;

inline int get_hash(vector<int> &vec) {
	int h = 0;
	for (auto v:vec) h = (h * MUL + v) % MOD;
	return h;
}
void reid() {
	ls.init();
	REP(i,K) ls.add(id[i]);
	ls.make();
	REP(i,K) id[i] = ls.qry(id[i]);
}
bool checkOK(int x, int y) {
	if (SZ(E[x]) == 0 and SZ(E[y]) == 0) return true;
	vector<int> goal;
	REP(i,SZ(E[x])) {
		goal.PB(id[eid[x][i]]);
	}
	REP(st,SZ(E[y])) {
		vector<int> vec;
		REP1(j,st,SZ(E[y])-1) vec.PB(id[eid[y][j]]);
		REP1(j,0,st-1) vec.PB(id[eid[y][j]]);
		if (vec == goal) return true;
	}
	return false;
}
int32_t main() {
	IOS;
	cin >> N;
	K = 0;
	REP1(u,1,N) {
		int m,v;
		cin >> m;
		REP(j,m) {
			cin >> v;
			E[u].PB(v);
			eid[u].PB(K);
			mp[pii(u,v)] = K;
			start[K] = j;
			id2uv[K++] = {u,v};
		}
	}
	REP(i,K) {
		int u = id2uv[i].F;
		int v = id2uv[i].S;
		id[i] = SZ(E[u]);
		rev[i] = mp[pii(v,u)];
	}

	REP(_,N+5) {
		reid();
		REP(i,K) grp[i].clear();
		REP(i,K) {
			grp[id[i]].PB(i);
		}

		REP(i,K) {
			for (auto it:grp[i]) {
				vector<int> vec;
				vec.PB(i);
				int u = id2uv[it].F;
				int st = start[it];
				REP1(j,st,SZ(E[u])-1) {
					int rid = rev[eid[u][j]];
					vec.PB(id[rid]);
				}
				REP1(j,0,st-1) {
					int rid = rev[eid[u][j]];
					vec.PB(id[rid]);
				}
				tmpid[it] = get_hash(vec);
			}
		}
		REP(i,K) id[i] = tmpid[i];
	}
	
	reid();
	/*
	REP(i,K) {
		grp[id[i]].PB(i);
	}
	REP(i,K) {
		if (!grp[i].empty()) {
			for (auto it:grp[i])
				cout << id2uv[it] << endl;
			cout << endl;
		}
	}
	*/
	REP1(i,1,N) {
		REP1(j,i+1,N) {
			if (djs.f(j) != j) continue;
			if (checkOK(i,j)) {
				djs.uni(j,i);
			}
		}
	}
	REP(i,N+1) grp[i].clear();
	REP1(i,1,N) grp[djs.f(i)].PB(i);
	REP1(i,1,N) {
		sort(ALL(grp[i]));
		if (SZ(grp[i]) > 1) ans.PB(grp[i]);
	}
	if (ans.empty()) {
		cout << "none" << endl;
	} else {
		sort(ALL(ans));
		for (auto vec:ans) {
			int sz = SZ(vec);
			REP(i,sz) {
				cout << vec[i] << " \n"[i==sz-1];
			}
		}
	}

	return 0;
}


