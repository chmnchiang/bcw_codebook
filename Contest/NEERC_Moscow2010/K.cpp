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


using pii = pair<int, int>;


int main() {
	IOS;

	int N, M;
	cin >> N >> M;

	int Xm, XM, Ym, YM;
	Xm = XM = Ym = YM = 0;

	int nx = 0, ny = 0;
	for (int i=1; i<=N; i++) {
		for (int j=1; j<=M; j++) {
			if (i + Xm <= 0) continue;
			if (i + XM > N) continue;
			if (j + Ym <= 0) continue;
			if (j + YM > M) continue;
			int tx = i+nx, ty = j+ny;
			cout<<tx<<' '<<ty<<endl;
			string s; cin >> s;
			if (s == "DETECTED") exit(0);
			if (s == "L") ny--;
			if (s == "R") ny++;
			if (s == "U") nx--;
			if (s == "D") nx++;
			Xm = min(Xm, nx);
			XM = max(XM, nx);
			Ym = min(Ym, ny);
			YM = max(YM, ny);
		}
	}

	return 0;
}
