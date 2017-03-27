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


using BT = bitset<30>;
using ll = long long;

int N,M;
int hao[1<<22];
ll T,A[34],B[34];
BT edge1[34], edge2[34];

vector<ll> calc(int n, ll x[], BT edge[]) {
	vector<ll> res;
	FZ(hao);
	hao[0] = 1;
	REP(i,1<<n) {
		ll cost = 0;
		hao[i] = 1;
		BT a34;
		REP(j,n) {
			if (i & (1<<j)) {
				cost += x[j];
				a34 |= edge[j];
				if (!hao[i^(1<<j)]) {
					hao[i] = 0;
					break;
				}
			}
		}
		if (hao[i] and a34.count() >= __builtin_popcount(i)) {
			res.PB(cost);
		} else {
			hao[i] = 0;
		}
	}



	return res;
}
int main() {
	IOS;
	cin>>N>>M;
	REP(i,N) {
		string s;
		cin>>s;
		REP(j,M) {
			edge1[i][j] = edge2[j][i] = (s[j] == '0') ? 0 : 1;
		}
	}
	REP(i,N) cin>>A[i];
	REP(i,M) cin>>B[i];
	cin>>T;

	vector<ll> vecA = calc(N,A,edge1);
	vector<ll> vecB = calc(M,B,edge2);

	sort(ALL(vecA));
	sort(ALL(vecB));

	ll ans = 0;
	int j = SZ(vecB) - 1;
	REP(i,SZ(vecA)) {
		while (j >= 0 and vecA[i] + vecB[j] >= T) {
			j--;
		}
		ans += SZ(vecB) - (j + 1);
	}

	cout<<ans<<endl;

	return 0;
}

