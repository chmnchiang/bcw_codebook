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
#define loop(i, a, b) for (auto (i)=(a); (i) != (b); (i) += ((b) < (a) ? -1 : 1))

#define int long long
const int MK = 111;
int N, K;
int E[MK];
int H[MK];
int D[MK];
int R[MK];

const int MX = 22;
struct creep {
	int h, d, e;
} Cr[MX];

#define exp eexxxppp

const int MM = 1<<MX;
int dp[MM];
int bk[MM];
int exp[MM];
int lev[MM];

const int INF = 1029384756;

int32_t main() {
	IOS;
	FILEIO("creeping");

	cin>>N>>K;
	loop (i, 0, K) {
		cin>>E[i]>>H[i]>>D[i]>>R[i];
	}

	loop (i, 0, N) {
		int h, d, e;cin>>h>>d>>e;
		Cr[i]={h, d, e};
	}

	dp[0] = H[0];
	int M = 1<<N;

	int ans = 0, bv = 0;
	loop (i, 1, M) {
		vector<int> cps;
		/*
		int t = i;
		while (t) {
			int z = t&(-t);
			int lg = __lg(z);
			cps.PB(lg);
			t-=z;
		}*/
		dp[i] = -INF;
		loop (j, 0, N) {
			if ((1<<j) & i) cps.PB(j);
		}

		for (auto x: cps)
			exp[i]+=Cr[x].e;
		lev[i] = upper_bound(E, E+K, exp[i]) - E - 1;

		for (auto x: cps) {
			int st = (i ^ (1<<x));
			int l = lev[st];
			int h = dp[st];
			int d = D[l];
			int r = R[l];
			if (h <= 0) continue;
			
			int eh = Cr[x].h;
			int ed = Cr[x].d - r;
			
			if (!d) continue;
			int edn = (eh+d-1) / d;

			int lh = min(h - edn * ed, H[l]);
//			if (ed < 0) lh = H[l];
			if (lh <= 0) continue;
			lh += H[lev[i]] - H[l];
			if (lh <= 0) continue;
			lh = H[lev[i]];
			if (lh > dp[i]) {
				dp[i] = lh;
				bk[i] = st;
			}
		}

		if (dp[i] > 0 and bv < exp[i]) {
			bv = exp[i];
			ans = i;
		}
	}

	cout << bv << endl;
	int st = ans;

	vector<int> aa;
	while (st) {
		int nst = bk[st];
		int c = __lg(st - nst);
		aa.PB(c);
		st = nst;
	}
	reverse(ALL(aa));
	cout<<SZ(aa)<<endl;
	for (int i=0; i<SZ(aa); i++) {
		cout << aa[i]+1 << " \n"[i==SZ(aa)-1];
	}


	return 0;
}
