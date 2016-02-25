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

const int MXN = 505;

int N,M,col[MXN],isn[MXN],vst[MXN];
int edge[MXN][MXN];
int permu[MXN];

void gen_order() {
	memset(vst, 0, sizeof(vst));
	int step = 1;
	REP1(i,1,N) {
		if (vst[i]) continue;
		queue<int> que;
		que.push(i);
		permu[step++] = i;
		while (!que.empty()) {
			int u = que.front(); que.pop();
			REP1(v,1,N) {
				if (edge[u][v] and !vst[v]) {
					vst[v] = 1;
					que.push(v);
					permu[step++] = v;
				}
			}
		}
	}

}
void setc(int u, int c) {
	col[u] = c;
	//cout << "SET " << u << " : " << c << endl;
}
int main() {
	IOS;
	FILEIO("mayors");
	cin >> N >> M;
	REP1(i,1,M) {
		int u,v;
		cin >> u >> v;
		edge[u][v] = edge[v][u] = 1;
	}

	gen_order();

	memset(col, -1, sizeof(col));
	int fail = 0;
	REP1(ii,1,N) {
		int i = permu[ii];
		if (col[i] == -1) setc(i, 0);
		REP1(j,1,N) {
			vst[j] = 0;
		}
		vector<int> vec;
		REP1(j,1,N) {
			if (edge[i][j]) {
				vec.PB(j);
			}
		}
		if (vec.empty()) continue;
		queue<int> que;
		for (auto v:vec) {
			if (col[v] != -1) {
				que.push(v);
				vst[v] = 1;
			}
		}
		if (que.empty()) {
			setc(vec[0], 1);
			que.push(vec[0]);
			vst[vec[0]] = 1;
		}
		while (!fail && !que.empty()) {
			int u = que.front(); que.pop();
			for (auto v:vec) {
				if (!edge[u][v]) continue;
				if (col[v] == -1) setc(v, 3 - col[u] - col[i]);
				if (!vst[v]) {
					vst[v] = 1;
					que.push(v);
				}
			}
		}
		if (fail) break;
	}
	REP1(i,1,N) {
		REP1(j,1,N) {
			if (edge[i][j] and col[i] == col[j]) fail = 1;
		}
	}
	if (fail) {
		cout << "Plan failed" << endl;
	} else {
		cout << "Plan OK" << endl;
		REP1(i,1,N) {
			if (col[i] == 0) cout << "R";
			if (col[i] == 1) cout << "G";
			if (col[i] == 2) cout << "B";
		}
		cout << endl;
	}


    return 0;
}
