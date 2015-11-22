#include<bits/stdc++.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define F first
#define S second
#define PB push_back
#define ALL(x) begin(x),end(x)
#define SZ(x) ((int)(x).size())
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
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

const int INF = 102938475;
typedef pair<int, int> pii;
const int MX = 10101;
int N;
int A, B, C, E;
int cls[MX];
int hao[4];
vector<int> el[MX];
pii dis[4][MX];
bool inq[MX];

void build(int start, int id_) {
	queue<int> qe;
	qe.push(start);
	auto d = dis[id_];
	for (int i=0; i<=N; i++) {
		d[i] = {INF, INF};
		inq[i] = 0;
	}
	d[start] = {0, start};
	inq[start] = 1;
	while (qe.size()) {
		int u = qe.front();
		qe.pop();
		inq[u] = false;
		pii dn = d[u];
		for (auto v: el[u]) {
			pii dx = {dn.F+1, min(dn.S, v)};
			if (d[v] > dx) {
				d[v] = dx;
				if (not inq[v]) {
					qe.push(v);
					inq[v] = true;
				}
			}
		}
	}
}

int main() {
    IOS;
	cin >> N;
	cin >> A >> B >> C;
	hao[1] = hao[2] = hao[3] = 1029384756;
#define _magic(x, y) for (int i=0; i<x; i++) { \
		int a; cin >> a; \
		cls[a] = y; \
		hao[y] = min(hao[y], a); \
	} \

	_magic(A, 1);
	_magic(B, 2);
	_magic(C, 3);
	

	cin >> E;
	for (int i=0; i<E; i++) {
		int u, v; cin >> u >> v;
		if (cls[u]) {
			u = hao[cls[u]];
		}

		if (cls[v]) {
			v = hao[cls[v]];
		}
//		if (u == v) continue;
		el[u].PB(v);
		el[v].PB(u);
	}

	for (int i=1; i<=3; i++) {
		build(hao[i], i);
	}

	pii ans = {INF, INF};

	auto add = [](pii p1, pii p2) -> pii {
		return {p1.F+p2.F, min(p1.S, p2.S)};
	};

	for (int i=1; i<=N; i++) {
		pii z{0, INF};
		for (int j=1; j<=3; j++) {
			z = add(z, dis[j][i]);
		}
		ans = min(ans, z);
	}
	cout << ans.F << ' ' << ans.S << endl;


    return 0;
}

