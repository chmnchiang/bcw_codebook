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

const int MX = 202020;
int N;
vector<pair<string, int>> ip;
int _nx[MX], _pv[MX];
int *nx = _nx+1, *pv = _pv+1;
int hei[MX];
bool us[MX];
typedef array<int, 3> Data;
priority_queue<Data, vector<Data>> pq;

int cal(string &s1,string &s2) {
	int t = 0;
	while (t < SZ(s1) and t < SZ(s2) and s1[t] == s2[t]) {
		t++;
	}
	return t;
}

int main() {
	IOS;
	cin >> N;
	ip.resize(N);
	for (int i=0; i<N; i++) {
		cin >> ip[i].F;
		ip[i].S = i+1;
	}

	sort(ALL(ip));
	for (int i=1; i<N; i++) {
		hei[i] = cal(ip[i-1].F, ip[i].F);
	}


	nx[-1] = 0;
	for (int i=0; i<N; i++) {
		pv[i] = i-1;
		nx[i] = i+1;
	}
	pv[N] = N-1;

	for (int i=1; i<N; i++) {
		Data d = {hei[i], i-1, i};
		pq.push(d);
	}

	int n = N/2;
	int ans = 0;
	typedef pair<int, int> pii;
	vector<pii> ai;
	for (int i=0; i<n;) {
		auto bs = pq.top(); pq.pop();
		int v, a, b;
		v = bs[0]; a = bs[1]; b = bs[2];

		if (us[a] or us[b]) continue;

		ans += v;
		ai.PB({ip[a].S, ip[b].S});
		us[a] = us[b] = true;
		i++;

		int pa = pv[a], nb = nx[b];
		nx[pa] = nb;
		pv[nb] = pa;
		if (pa >= 0 and nb < N) {
			//v = min(v, hei[pa+1]);
			//v = min(v, hei[nb]);

			v = cal(ip[pa].F, ip[nb].F);

			Data d = {v, pa, nb};
			pq.push(d);
		}
	}

	cout << ans << endl;
	for (auto p: ai) {
		cout << p.F << ' ' << p.S << endl;
	}


	return 0;
}
