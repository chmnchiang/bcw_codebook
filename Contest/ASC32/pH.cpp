#include<bits/stdc++.h>/*{{{*/
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
}/*}}}*/
// Let's Fight!

const int MXN = 505;

struct Edge {
	int u, v;
}edge[MXN*MXN];

struct Setting {
	int u, v, c;
};

int N, M, K, D;
int deg[MXN], mark[MXN][MXN];
int colorUsed[MXN][MXN];
vector<Setting> setting;

void setColor(int u, int v, int c) {
	mark[u][v] = mark[v][u] = c;
	colorUsed[u][c] = v;
	colorUsed[v][c] = u;
}
void setSetting() {
  vector<Setting> vec;
  for (auto it : setting) {
    int u = it.u;
    int v = it.v;
    int old = mark[u][v];
    vec.PB({u, v, old});
    vec.PB({v, u, old});
  }
  for (auto it :vec) {
    colorUsed[it.u][it.c] = colorUsed[it.v][it.c] = 0;
  }
  for (auto it : setting) {
    setColor(it.u, it.v, it.c);
  }
  setting.clear();
}

bool DFS(int v, int c1, int c2, int tar) {
	if (v == tar) return true;
	int nxt = colorUsed[v][c1];
	if (nxt == 0) return false;

	bool flag = DFS(nxt, c2, c1, tar);
	setting.PB({v, nxt, c2});
	return flag;
}

void addEdge(int x, int v) {
	if (deg[x] == K || deg[v] == K) {
		++K;
		setColor(x, v, K+1);
		deg[x]++;
		deg[v]++;
		return ;
	}
	deg[x]++;
	deg[v]++;
  
	for (int i=1; i<=K+1; i++) {
		if (!colorUsed[x][i] && !colorUsed[v][i]) {
			setColor(x, v, i);
			return ;
		}
	}
 

	int a = 0;
	for (int i=1; i<=K+1; i++) {
		if (!colorUsed[x][i]) {
			a = i;
			break;
		}
	}
	int b = 0;
	for (int i=1; i<=K+1; i++) {
		if (!colorUsed[v][i]) {
			b = i;
			break;
		}

	}

	int sb = 0;
	vector<int> y, beta;
	set<int> st;
	while (true) {
		y.PB(v);
		int nv = colorUsed[x][b];
		if (nv == 0) {
			int len = SZ(y);
      setting.clear();
			for (int i=0; i<len-1; i++)
        setting.PB({x, y[i], mark[x][y[i+1]]});
      setting.PB({x, y[len-1], b});
      setSetting();
			return;
		}
		sb = b;
		if (st.count(b)) break;
		beta.PB(b);
		st.insert(b);
		
		v = nv;
		b = 0;
		for (int i=1; i<=K+1; i++) {
			if (!colorUsed[v][i]) {
				b = i;
				break;
			}
		}
	}
/*
  cout << "y : " << y << endl;
  cout << "b : " << beta << endl;
  cout << "a = " << a << endl;
  cout << "SB = " << sb << endl;
  */
	for (int i=0; i<SZ(beta); i++) {
		if (sb == beta[i]) {
//      cout << "i = " << i << endl;
			int s = y.back();
			setting.clear();
      for (int j=0; j<SZ(y)-1; j++)
        setting.PB({x, y[j], mark[x][y[j+1]]});
      int old = mark[x][y.back()];
      colorUsed[x][old] = 0;
      colorUsed[y.back()][old] = 0;
      mark[x][y.back()] = mark[y.back()][x] = 0;
      setSetting();

			bool flag = DFS(s, a, sb, x);
//      cout << (flag ? "True" : "False") << endl;
			if (!flag) {
        setSetting();
        setting.PB({x, y.back(), a});
			} else {
        for (int j=i; j<SZ(y)-1; j++)
          setting.PB({x, y[j+1], mark[x][y[j]]});
			}
      setSetting();
			return ;
		}
	}

}


int colorCnt[MXN][MXN];
void check(int m) {
	FZ(colorCnt);
	for (int i=1; i<=m; i++) {
		int u = edge[i].u;
		int v = edge[i].v;
		int c = mark[u][v];
		//assert(c > 0);
		if (colorCnt[u][c]) {
//			cout << "FAILED! " << u << " " << v << " " << colorCnt[u][c] << endl;
			assert(false);
		}
		if (colorCnt[v][c]) {
//			cout << "FAILED! " << u << " " << v << " " << colorCnt[v][c] << endl;
			assert(false);
		}
		colorCnt[u][c] = v;
		colorCnt[v][c] = u;
	}
  cout << "CHECK " << m << " : HAO123" << endl;

}

int main() {
	IOS;
	FILEIO("roadsigns");
	cin >> N >> M >> D;
	K = 0;
	FZ(deg);
	FZ(mark);
	FZ(colorUsed);
	for (int i=1, u, v; i<=M; i++) {
		cin >> u >> v;
		edge[i].u = u;
		edge[i].v = v;
		assert(!mark[u][v]);
		addEdge(u, v);
	}

	for (int i=1; i<=M; i++) {
		int u = edge[i].u;
		int v = edge[i].v;
		cout << mark[u][v] << " \n"[i==M];
	}
//	check(M);

    return 0;
}

