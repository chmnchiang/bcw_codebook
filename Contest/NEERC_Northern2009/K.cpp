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


const int MX = 102030;
int N, M, K;
int typ[MX];
vector<int> el[MX], rel[MX];
int A, B;
bool isNotB[MX];

void buildB() {
	queue<int> qe;
	for (int i=1; i<=N; i++) {
		if (!(typ[i] & (1<<B))) {
			qe.push(i);
			isNotB[i] = 1;
		}
	}

	while (SZ(qe)) {
		int v = qe.front(); qe.pop();
		for (auto u: rel[v]) {
			if (!isNotB[u]) {
				isNotB[u] = 1;
				qe.push(u);
			}
		}
	}
}

bool isA[MX];
void buildA() {
	queue<int> qe;
	for (int i=1; i<=N; i++) {
		if (!isNotB[i]) {
			isA[i] = 1;
			qe.push(i);
		}
	}

	while (SZ(qe)) {
		int u = qe.front(); qe.pop();
		for (auto v: rel[u]) {
			if (!(typ[v] & (1<<A))) continue;
			if (!isA[v]) {
				isA[v] = 1;
				qe.push(v);
			}
		}
	}
}

int main() {
	FILEIO("kripke");
	IOS;
	cin >> N >> M >> K;
	for (int i=1; i<=N; i++) {
		int v;
		cin >> v;
		for (int j=0; j<v; j++) {
			char x; cin >> x;
			x -= 'a';
			typ[i] |= (1<<x);
		}
	}

	for (int i=0; i<M; i++) {
		int u, v; cin >> u >> v;
		el[u].PB(v);
		rel[v].PB(u);
	}

	string s; cin >> s;
	A = s[2] - 'a';
	B = s[7] - 'a';

	buildB();
	/*
	for (int i=1; i<=N; i++) if (!isNotB[i]) {
		cout << i << '\n';
	}
	*/
	//cout << "---" << endl;
	buildA();


	int ans = 0;
	for (int i=1; i<=N; i++) ans += (isA[i]);
	cout << ans << endl;
	for (int i=1; i<=N; i++) if (isA[i]) {
		cout << i << '\n';
	}
	return 0;
}
