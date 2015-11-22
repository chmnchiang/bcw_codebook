#include <bits/stdc++.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define MC(n,m) memcpy((n),(m),sizeof(n))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define FOR(x,y) for(__typeof(y.begin())x=y.begin();x!=y.end();x++)
#define ALL(x) (x).begin(), (x).end()
#define SZ(x) ((int)(x).size())
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
// Let's Fight!
const double EPS = 1e-8;
class Isap{
public:
	static const int MXN = 10000;
  class Edge{
  public:
    int v,re;
	double f;
    Edge (){ v=re=-1; f=0.0; }
    Edge (int _v, double _f, int _r){
      v = _v;
      f = _f;
      re = _r;
    }
  };
  int n,s,t,h[MXN],gap[MXN];
  vector<Edge> E[MXN];
  void init(int _n, int _s, int _t){
    n = _n;
    s = _s;
    t = _t;
    for (int i=0; i<n; i++)
      E[i].clear();
  }
  void add_edge(int u, int v, double f){
    E[u].PB(Edge(v,f,E[v].size()));
    E[v].PB(Edge(u,f,E[u].size()-1));
  }
  double DFS(int u, double nf, double res=0){
    if (u == t) return nf;
    for (auto &it : E[u]){
      if (h[u]==h[it.v]+1 && it.f>EPS){
        double tf = DFS(it.v,min(nf,it.f));
        res += tf;
        nf -= tf;
        it.f -= tf;
        E[it.v][it.re].f += tf;
        if (nf < EPS) return res;
      }
    }
    if (nf > EPS){
      if (--gap[h[u]] == 0) h[s]=n;
      gap[++h[u]]++;
    }
    return res;
  }
  double flow(double res=0){
    FZ(h);
    FZ(gap);
    gap[0] = n;
    while (h[s] < n)
      res += DFS(s,1e9);
	//cout << "RES = " << res << endl;
    return res;
  }
}flow;

const int MX = 121;
vector<int> vl;
vector<int> el[MX];
int N;
int deg[MX];

void aozora(int a) {
	vl.clear();
	for (int i=0; i<=a+2; i++) {
		el[i].clear();
		deg[i] = 0;
	}
}

bool test(double k) {
	double posSum = 0.0;
	int S = N, T = N+1, V = N+2;
	flow.init(V, S, T);
	for (int i=0; i<N; i++) {
		double c = deg[i] - 2 * k;
		//cout << i << ' ' << c << endl;
		if (c > 0) {
			posSum += c;
			flow.add_edge(S, i, c);
			//cout << 123 << endl;
		} else {
			flow.add_edge(i, T, -c);
		}
	}

	for (int i=0; i<N; i++) {
		for (auto x: el[i]) {
			flow.add_edge(i, x, 1.0);
		}
	}

	double f = flow.flow();
	//cout << "Pos = " << posSum << endl;
	double ans = posSum - f;
	return ans > 0;
}

int main() {
	IOS;
	int T; cin >> T;
	for (int _t=1; _t<=T; _t++) {
		cin >> N;
		aozora(N);
		for (int i=0; i<N; i++) {
			int a; cin >> a;
			vl.PB(a);
		}
		for (int i=0; i<SZ(vl); i++) {
			for (int j=0; j<i; j++) {
				if (vl[j] > vl[i]) {
					el[j].PB(i);
					deg[i] ++;
					deg[j] ++;
				}
			}
		}

		double l = 0.0, r = N*2.0;
		while (l < r - EPS) {
			double mid = (l+r)/2;
			if (test(mid)) {
				l = mid;
			} else {
				r = mid;
			}
		//	cout << mid << endl;
		}

		cout << "Case #" << _t << ": " << fixed << setprecision(15) << l << endl;
	}
	return 0;
}
