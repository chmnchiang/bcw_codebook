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


const int MX = 2222;
const int INF = 1029384756;
int dp[2][MX][MX];
int N;
int ip[MX];
int ss[MX];

int main() {
	IOS;
	cin >> N;
	int S = 0;
	for (int i=0; i<N; i++) {
		cin >> ip[i];
		S += ip[i];
		ss[i] = ip[i];
	}

	for (int i=1; i<N; i++) {
		ss[i] += ss[i-1];
	}

	auto my = dp[0], he = dp[1];
	int Z = (S + N - 1) / N + (N+1)/2;


	for (int i=0; i<=Z; i++) {
		for (int j=0; j<=S; j++) my[i][j] = INF;
	}
	for (int i=0; i<=Z; i++)
		my[i][i] = 0;

	for (int n=1; n<N; n++) {
		for (int i=0; i<=Z; i++) {
			for (int j=0; j<=S; j++) he[i][j] = INF;
		}
		for (int a=0; a<=Z; a++) {
			for (int s=0; s<=S; s++) {
				{
					int ha = a;
					int hs = s + a;
					he[ha][hs] = min(he[ha][hs], my[a][s] + abs(ss[n-1] - s));
				}
				if (a < Z) {
					int ha = a + 1;
					int hs = s + a + 1;
					he[ha][hs] = min(he[ha][hs], my[a][s] + abs(ss[n-1] - s));
				}
				if (a) {
					int ha = a - 1;
					int hs = s + a - 1;
					he[ha][hs] = min(he[ha][hs], my[a][s] + abs(ss[n-1] - s));
				}
			}
		}
		swap(he, my);
		/*
		for (int a=0; a<=Z; a++) {
			for (int s=0; s<=S; s++) cout << my[a][s] << ' ';
			cout << endl;
		}
		cout << endl;
		*/
	}

	int ans = INF;
	for (int a=0; a<=Z; a++) {
		ans = min(ans, my[a][S]);
	}
	cout << ans << endl;

	return 0;
}
