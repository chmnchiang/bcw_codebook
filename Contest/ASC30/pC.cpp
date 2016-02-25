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
#define REP(i,n) for (int i=0; i<(n); i++)
#define REP1(i,a,b) for (int i=(a); i<=(b); i++)
// Let's Fight!

typedef pair<int,int> pii;
const int MXN = 105;

int N,M,edge[MXN][MXN],isbye[MXN*MXN];
vector<int> bye;
vector<int> E[MXN];

void solve(vector<int> V) {
	if (SZ(V) <= 2) return;
	int cen = V[0];
	vector<int> v1,v2,v3;
	vector<int> e1c,ec2,e23,e31;
	for (auto it:V) {
		if (edge[it][cen]) {
			v1.PB(it);
			e1c.PB(edge[it][cen]);
		} else if (edge[cen][it]) {
			v2.PB(it);
			ec2.PB(edge[cen][it]);
		} else if (it != cen) {
			v3.PB(it);
		}
	}
	sort(ALL(v1));
	v1.resize(unique(ALL(v1))-begin(v1));
	sort(ALL(v2));
	v2.resize(unique(ALL(v2))-begin(v2));
	sort(ALL(v3));
	v3.resize(unique(ALL(v3))-begin(v3));
	/*
	cout << "=================\n";
	cout << V << endl;
	cout << v1 << endl;
	cout << v2 << endl;
	cout << v3 << endl;
	*/
	assert(SZ(V) == 1 + SZ(v1) + SZ(v2) + SZ(v3));

	for (auto i:v2) for (auto j:v1)
		if (edge[i][j]) while(1);

	for (auto i:v2) for (auto j:v3)
		if (edge[i][j]) e23.PB(edge[i][j]);
	for (auto i:v3) for (auto j:v1)
		if (edge[i][j]) e31.PB(edge[i][j]);
	int mn = 1e9;
	mn = min(mn, SZ(e1c));
	mn = min(mn, SZ(ec2));
	mn = min(mn, SZ(e23));
	mn = min(mn, SZ(e31));
	if (mn == SZ(e1c)) {
		bye.insert(bye.end(), ALL(e1c));
	} else if (mn == SZ(ec2)) {
		bye.insert(bye.end(), ALL(ec2));
	} else if (mn == SZ(e23)) {
		bye.insert(bye.end(), ALL(e23));
	} else {
		bye.insert(bye.end(), ALL(e31));
	}

	vector<int> nxtV;
	nxtV.insert(nxtV.end(), ALL(v1));
	nxtV.insert(nxtV.end(), ALL(v2));
	nxtV.insert(nxtV.end(), ALL(v3));
	solve(nxtV);
//	solve(v1);
//	solve(v2);
//	solve(v3);
}


int vst[MXN],onstk[MXN],fail;
void DFS(int u) {
	onstk[u] = 1;
	vst[u] = 1;
	for (auto v:E[u]) {
		if (!vst[v]) DFS(v);
		else if (onstk[v]) {
			fail = 1;
		}
	}
	onstk[u] = 0;
}

void check() {
	for (auto it:bye) isbye[it] = 1;
	REP1(i,1,N) {
		vst[i] = 0;
		REP1(j,1,N) {
			if (!isbye[edge[i][j]] and edge[i][j])
				E[i].PB(j);
		}
	}
	fail = 0;
	REP1(i,1,N) {
		if (!vst[i]) DFS(i);
	}
	if (fail) while(true);
}

int main() {
	IOS;
	FILEIO("electricity");
	cin >> N >> M;
	REP1(i,1,M) {
		int u,v;
		cin >> u >> v;
		edge[u][v] = i;
	}
	vector<int> vec;
	REP1(i,1,N) vec.PB(i);
	solve(vec);
	int K = N * (N-1) / 2 - M;
	sort(ALL(bye));
	bye.resize(unique(ALL(bye)) - begin(bye));

	assert(SZ(bye) <= K);
	cout << SZ(bye) << endl;
	for (auto it:bye) cout << it << " ";
	cout << endl;
	check();



    return 0;
}
