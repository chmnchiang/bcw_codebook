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
// Let's Fight!

const int MX = 201010;
struct DJS {
	int par[MX];

	void init(int n) {
		for (int i=0; i<=n; i++) {
			par[i] = i;
		}
	}

	int ffa(int a) {
		return (par[a] == a ? a : (par[a] = ffa(par[a])));
	}

	void join(int a, int b) {
		int fa = ffa(a);
		int fb = ffa(b);
		if (fa > fb) swap(fa, fb);
		par[fb] = fa;
	}

	bool same(int a, int b) {
		return ffa(a) == ffa(b);
	}
} djs, djs2;

int main() {
	FILEIO("jackpot");
	IOS;

	int N, E;
	cin >> N >> E;
	int N2 = N + N;
	vector<int> el[MX];

	for (int i=0; i<E; i++) {
		int a, b; cin >> a >> b;
		if (a > b) swap(a, b);
		el[b].PB(a);
	}


	djs.init(N2);
	djs2.init(N);
#define EO(a) ((a)&1)
#define ME(a) ((a)*2)
#define NME(a) ((a)*2+1)
	auto ex = [](int z) {
		cout << ((not EO(z)) ? "Alice" : "Bob") << ' ' << z << endl;
		exit(0);
	};
	for (int i=1; i<=N; i++) {
		vector<int> vl;
		for (auto x: el[i]) {
			vl.PB(djs2.ffa(x));
		}

		sort(ALL(vl));
		vl.resize(unique(ALL(vl)) - vl.begin());
		//cout << vl << endl;

		for (int j=1; j<SZ(vl); j++) {
			int t = vl[j];
			if (EO(t) != EO(i)) {
				ex(i);
			}
		}

		for (auto x: el[i]) {
			djs.join(ME(i), NME(x));
			djs.join(ME(x), NME(i));
			djs2.join(x, i);
		}

		if (djs.same(ME(i), NME(i))) 
			ex(i);
	}

	cout << "Tie" << endl;
    return 0;
}
