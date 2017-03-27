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


const int MAXN = 100005;

int N;
int X[MAXN], Y[MAXN], isleaf[MAXN];

int bye(int x) {
	int res = 0;
	while (X[x]) {
		int y = X[x];
		X[x] = 0;
		res++;
		x = y;
	}
	return res;
}

int main() {
	IOS;
	cin>>N;
	REP1(i,1,N) cin>>X[i];
	REP1(i,1,N) cin>>Y[i];

	REP1(i,1,N) isleaf[i] = 1;

	REP1(i,1,N) {
		isleaf[Y[i]] = 0;
	}

	int ans = 0;

	REP1(i,1,N) {
		if (!isleaf[i]) continue;
		int a = i;
		while (a and Y[a] == X[a]) a = Y[a];
		if (!a) continue;
		while (a) {
			ans += bye(a);
			a = Y[a];
		}
	}

	int z1 = 0;
	int z2 = 0;
	REP1(i,1,N) {
		if (!X[i]) z1++;
		if (!Y[i]) z2++;
	}
	assert(z1 >= z2);
	ans += z1 - z2;

	cout<<ans<<endl;

	return 0;
}

