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

struct Isap{
  static const int MXN = 10000;
  struct Edge{ int v,f,re,eid; };
  int n,s,t,h[MXN],gap[MXN];
  vector<Edge> E[MXN];
  void init(int _n, int _s, int _t){
    n = _n; s = _s; t = _t;
    for (int i=0; i<n; i++) E[i].clear();
  }
  void add_edge(int u, int v, int f, int eid){
    E[u].PB({v,f,SZ(E[v]),eid});
    E[v].PB({u,0,SZ(E[u])-1,-1});
  }
  int DFS(int u, int nf, int res=0){
    if (u == t) return nf;
    for (auto &it : E[u]){
      if (h[u]==h[it.v]+1 && it.f>0){
        int tf = DFS(it.v,min(nf,it.f));
        res += tf; nf -= tf; it.f -= tf;
        E[it.v][it.re].f += tf;
        if (nf == 0) return res;
      }
    }
    if (nf){
      if (--gap[h[u]] == 0) h[s]=n;
      gap[++h[u]]++;
    }
    return res;
  }
  int flow(int res=0){
    FZ(h); FZ(gap);
    gap[0] = n;
    while (h[s] < n) res += DFS(s,2147483647);
    return res;
  }
  vector<int> get_eid(int l, int r) {
	  vector<int> res;
	  REP(i,n) {
		  for (auto it:E[i]) {
			  if (it.f == 0 and l <= it.eid and it.eid <= r)
				  res.PB(it.eid);
		  }
	  }
	  return res;
  }
}flow;

const int MXN = 514;

struct Lisan {
	vector<int> seq;
	void build(int n) {
		seq.clear();
		REP1(i,1,n) {
			seq.PB(-i);
			seq.PB(i);
		}
		sort(ALL(seq));
	}
	int qry(int x) {
		return lower_bound(ALL(seq),x)-begin(seq);
	}
}lisan;

typedef pair<int,int> pii;
struct Edge {
	int u,v,c;
}edge[MXN*MXN];

int N,M,K,V,S,T;
int idx1[MXN][5],idx2[MXN][5],in[MXN],out[MXN];
int vst[MXN],ons[MXN];
vector<int> stk;
vector<int> E[MXN];
vector<int> vec;

bool DFS(int u, int f) {
	vst[u] = 1;
	ons[u] = 1;
	stk.PB(u);
	for (auto v:E[u]) {
		if (v == f) continue;
		if (!vst[v]) {
			if (DFS(v,u)) return true;
		} else if (ons[v]) {
			while (stk.back() != v) {
				vec.PB(stk.back());
				stk.pop_back();
			}
			vec.PB(v);
			return true;
		}
	}
	ons[u] = 0;
	stk.pop_back();
	return false;
}
int main() {
	IOS;
	FILEIO("colorful");
	cin >> N >> M >> K;
	lisan.build(N);
	V = 0;
	REP(i,2*N) {
		REP(j,K) idx1[i][j] = V++;
		REP(j,K) idx2[i][j] = V++;
	}
	REP(i,2*N) {
		in[i] = V++;
		out[i] = V++;
	}
	S = V++;
	T = V++;
	flow.init(V,S,T);
	REP(i,2*N) {
		flow.add_edge(S,in[i],2,M);
		flow.add_edge(out[i],T,2,M);
		REP(j,K) {
			flow.add_edge(in[i],idx1[i][j],1,M);
			flow.add_edge(idx2[i][j],out[i],1,M);
		}
	}
	REP(i,M) {
		int u,v,c;
		cin >> u >> v >> c;
		u = lisan.qry(u);
		v = lisan.qry(v);
		c--;
		edge[i] = {u,v,c};
		flow.add_edge(idx1[u][c],idx2[v][c],1,i);
	}
	int f = flow.flow();
	if (f != 2*N) {
		cout << "NO" << endl;
	} else {
		cout << "YES" << endl;
		vector<vector<int>> ans;
		vector<int> eid = flow.get_eid(0,M-1);
		int cnt = 0;
		for (auto it:eid) {
			int u = edge[it].u, v = edge[it].v;
			E[u].PB(v);
			E[v].PB(u);
			cnt++;
		}
		while (cnt) {
			vec.clear();
			REP(i,2*N) {
				vst[i] = 0;
				ons[i] = 0;
			}
			stk.clear();
			REP(i,2*N) {
				if (!vst[i]) {
					if (DFS(i,-1)) break;
				}
			}
			assert(!vec.empty());
			int sz = SZ(vec);
			vector<int> v2;
			vec.PB(vec[0]);
			REP(i,sz) {
				int v = vec[i];
				v2.PB(lisan.seq[v]);
				int u = vec[i+1];
				REP(j,SZ(E[u])) {
					if (E[u][j] == v) {
						swap(E[u][j], E[u].back());
						E[u].pop_back();
						break;
					}
				}
				REP(j,SZ(E[v])) {
					if (E[v][j] == u) {
						swap(E[v][j], E[v].back());
						E[v].pop_back();
						break;
					}
				}
			}
			ans.PB(v2);
			cnt -= sz;
			assert(cnt >= 0);
		}
		cout << SZ(ans) << endl;
		for (auto it:ans) {
			cout << SZ(it);
			for (auto v:it) cout << " " << v;
			cout << endl;
		}
	}

	return 0;
}


