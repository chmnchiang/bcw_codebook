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

const int MXN = 405;

struct Scc{
	int n, nScc, vst[MXN], bln[MXN], E[MXN][MXN];
	vector<int> vec;
	void init(int _n){
		n = _n;
		REP(i,n) REP(j,n) E[i][j] = 0;
	}
	void add_edge(int u, int v){
//		cout << "ADD EDGE " << u << " " << v << endl;
		E[u][v] = 1;
	}
	void DFS(int u){
		vst[u]=1;
		REP(v,n)
			if (E[u][v] and !vst[v]) DFS(v);
		vec.PB(u);
	}
	void rDFS(int u) {
		vst[u] = 1;
		bln[u] = nScc;
		REP(v,n)
			if (E[v][u] and !vst[v]) rDFS(v);
	}
	void solve(){
		nScc = 0;
		vec.clear();
		FZ(vst);
		for (int i=0; i<n; i++)
			if (!vst[i]) DFS(i);
		reverse(vec.begin(),vec.end());
		FZ(vst);
		for (auto v : vec){
			if (!vst[v]){
				rDFS(v);
				nScc++;
			}
		}
	}
}g;


int N,M,ip[MXN],own[2*MXN];
vector<int> board[2*MXN];
int ID[2*MXN];
vector<int> can[MXN];

int other(int x) {
	if (own[x] == -1) return -1;
	for (auto it:can[own[x]])
		if (it != x) return it;
	return x;
}
int ok(int i, int j) {
	REP(k,N) {
		if (board[i][k] == board[j][k])
			return false;
	}
	return true;
}
int main() {
	IOS;
	FILEIO("show");
	cin >> N;
	REP(i,N) cin >> ip[i];
	
	cin >> M;
	REP(i,M) {
		REP(j,N) {
			int v;
			cin >> v;
			board[i].PB(v);
		}
		ID[i] = i+1;
	}

	REP(i,M) {
		int cnt = 0;
		REP(j,N) {
			if (board[i][j] == ip[j]) cnt++;
		}
		if (cnt >= 2) {
			swap(board[i], board[M-1]);
			swap(ID[i], ID[M-1]);
			i--;
			M--;
		}
	}

	g.init(2*N);
	FMO(own);
	REP(i,M) {
		REP(j,N) {
			if (board[i][j] == ip[j]) {
				own[i] = j;
				can[j].PB(i);
			}
		}
	}
	REP(i,M) {
		REP(j,i) {
			int bye = 0;
			REP(k,N) {
				if (board[i][k] == board[j][k]) {
					bye = 1;
					break;
				}
			}
			if (bye and own[i] != own[j]) {
				int tmp = other(j);
				if (tmp != -1) g.add_edge(i, tmp);
				tmp = other(i);
				if (tmp != -1) g.add_edge(j, tmp);
			}
		}
	}
	REP(i,N) {
		 if (SZ(can[i]) == 1) {
			REP(j,M) {
				g.add_edge(j, can[i][0]);
			}
		}
	}

//	REP(i,N) cout << can[i] << endl;

	vector<int> ans;
	int fail = 0;
	g.solve();
	REP(i,N) {
		if (SZ(can[i]) == 2 and g.bln[can[i][0]] == g.bln[can[i][1]]) {
			fail = 1;
		}
		if (SZ(can[i]) == 1) {
			ans.PB(can[i][0]);
		} else if (SZ(can[i]) == 2) {
			if (g.bln[can[i][0]] > g.bln[can[i][1]]) ans.PB(can[i][0]);
			else ans.PB(can[i][1]);
		} else {
			fail = 1;
		}
	}
	for (auto i:ans) {
		for (auto j:ans)
			if (i != j && !ok(i, j)) fail = 1;
	}

	if (fail) {
		cout << "NO" << endl;
	} else {
		cout << "YES" << endl;
		for (auto it:ans) cout << ID[it] << " ";
		cout << endl;
	}

	return 0;
}

