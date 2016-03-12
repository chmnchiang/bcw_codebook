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
    freopen(name".in", "r", stdin);
//    freopen(name".out", "w", stdout);
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

int N,M,S,T;
int curfar;
int vst[MXN],pid[MXN],fa[MXN],prefar[MXN],ban[MXN];
vector<int> E[MXN];

vector<int> gen_path() {
	FZ(fa);
	queue<int> que;
	que.push(S);
	fa[S] = S;
	while (!que.empty()) {
		int u=que.front();
		que.pop();
		for (auto v:E[u]) {
			if (fa[v]) continue;
			fa[v] = u;
			que.push(v);
		}
	}
	vector<int> vec;
	for (int v=T; v!=S; v=fa[v]) {
		vec.PB(v);
	}
	vec.PB(S);
	reverse(ALL(vec));

	return vec;
}
int main() {
	IOS;
	FILEIO("assassination");
	cin >> N >> M >> S >> T;
	REP(i,M) {
		int u,v;
		cin >> u >> v;
		E[u].PB(v);
	}
	vector<int> path;
	path = gen_path();

	FZ(ban);
	FZ(pid);
	REP(i,SZ(path)) {
		pid[path[i]] = i+1;
		ban[path[i]] = 1;
	}

//	cout << path << endl;
	FZ(prefar);
	FZ(vst);
	curfar = 0;
	REP(i,SZ(path)) {
		curfar = max(curfar, pid[path[i]]);
		ban[path[i]] = 0;

		//cout << "BFS " << path[i] << endl;
		queue<int> que;
		que.push(path[i]);
		vst[path[i]] = 1;
		while (!que.empty()) {
			int u = que.front();
			que.pop();
			for (auto v:E[u]) {
				if (vst[v]) continue;
				if (ban[v]) {
					curfar = max(curfar,pid[v]);
				} else {
					vst[v] = 1;
					que.push(v);
				}
			}
		}
		prefar[i] = curfar;
	}
	vector<int> ans;
	REP1(i,1,SZ(path)-2) {
		if (prefar[i-1] <= pid[path[i]]) {
			ans.PB(path[i]);
		}
	}
	sort(ALL(ans));
	cout << SZ(ans) << endl;
	for (auto it:ans) cout << it << " ";
	cout << endl;


	return 0;
}

