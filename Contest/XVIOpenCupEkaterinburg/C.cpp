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

const int MX = 3333;
int N, K;
int ip[2][MX];
int *me = ip[0], *he = ip[1];
using pii = pair<int, int>;
vector<pii> vec;

void calc(int n) {
	vec.clear();
	for (int i=1; i<n; i++) {
		vec.PB({me[i], -i});
	}
	sort(ALL(vec));

	int nd = (n-1)/2, k = 0;
	for (int i=0; i<nd; i++) {
		k += vec[i].F+1;
	}

	if (k > K) {
		for (int i=1; i<=n-1; i++) he[i] = me[i];
		he[n] = -1;
	} else {
		for (int i=1; i<=n; i++) he[i] = 0;
		for (int i=0; i<nd; i++) he[-vec[i].S] = vec[i].F+1;
		he[n] = K - k;
	}
	swap(me, he);
}

int main() {
	IOS;
	cin >> N >> K;
	
	me[1] = K;

	for (int i=2; i<=N; i++) {
		calc(i);
	}

	for (int i=N; i>=1; i--) {
		cout << me[i] << " \n"[i == 1];
	}


	return 0;
}

