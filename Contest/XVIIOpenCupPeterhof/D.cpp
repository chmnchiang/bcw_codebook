#pragma GCC optimize ("O2")
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

const int MX = 500;
int E[MX][MX];

void check(int u, int v) {
	assert(u != v and E[u][v]);
	E[u][v] = E[v][u] = 0;
}

int main() {
	IOS;

	
	int N;
	cin >> N;


		cout << "Yes" << endl;
	for (int i=0; i<=N; i++)
		for (int j=0; j<=N; j++) {
			E[i][j] = 1;
		}

	int M = N/2;
	for (int i=0; i<M; i++) {
		vector<int> vec;
		int s = i;
		for (int j=0; j<N-1; j++) {
			vec.PB(s);
			if (j&1) (s += j+1) %= (N-1);
			else (s += N-1-j-1) %= (N-1);
		}
		for (auto x: vec) cout << x+1 << ' ';
		cout << N << endl;

		
		/*
		for (int j=0; j<N-1; j++) {
			int u = j ? vec[j-1] : N-1;
			int v = vec[j];
			check(u, v);
		}
		check(vec.back(), N-1);
		*/
		
	}

	return 0;
}

