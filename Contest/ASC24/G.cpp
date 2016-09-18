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

typedef pair<int,int> pii;
const int MXN = 50005;
const int INF = 1029384756;

struct Lisan {
	vector<int> seq;
	void add(int x) { seq.PB(x); }
	void make() {
		sort(ALL(seq));
		seq.resize(unique(ALL(seq))-begin(seq));
	}
	int qry(int x) { return lower_bound(ALL(seq),x)-begin(seq); }
}lx,ly,lxy1,lxy2;

int N;
int dp[MXN];
int at[MXN];
pii frm[MXN];
pii pt[MXN];
vector<pii> vec[MXN];
set<pii> st[3][MXN];
vector<int> to[MXN];
pii bestPrev[MXN], bestSuf[MXN];

void solve(vector<pii> vvv) {
	int n = SZ(vvv);

	for (int i=0; i<n; i++) {
		int id = vvv[i].S;
		bestPrev[i] = {dp[id],i};
		if (i > 0) { 
			bestPrev[i] = max(bestPrev[i-1], bestPrev[i]);
		}
	}
	for (int i=n-1; i>=0; i--) {
		int id = vvv[i].S;
		bestSuf[i] = {dp[id],i};
		if (i != n-1) {
			bestSuf[i] = max(bestSuf[i+1], bestSuf[i]);
		}
	}

	REP(i,n) {
		int bv = dp[vvv[i].S];
		int b = i;
		if (i > 0 and bestPrev[i-1].F + i > bv) {
			bv = bestPrev[i-1].F + i;
			b = bestPrev[i-1].S;
		}
		/*
		for (int j=0; j<i; j++) {
			int id = vvv[j].S;
			if (dp[id] + i > bv) {
				bv = dp[id] + i;
				b = j;
			}
		}
		*/

		if (i < n-1 and bestSuf[i+1].F - 1 + (n - i) > bv) {
			bv = bestSuf[i+1].F - 1 + (n - i);
			b = bestSuf[i+1].S;
		}
		/*
		for (int j=i+1; j<n; j++) {
			int id = vvv[j].S;
			if (dp[id] - 1 + (n - i) > bv) {
				bv = dp[id] - 1 + (n - i);
				b = j;
			}

		}
		*/

		for (auto nxt:to[vvv[i].S]) {
			if (dp[nxt] < 1+bv) {
				dp[nxt] = 1+bv;
				frm[nxt] = {vvv[i].S,vvv[b].S}; // b -> i -> nxt
			}
		}
	}
}
int main() {
	IOS;
	FILEIO("queen");
	cin >> N;
	pt[0] = {0,0};
	REP1(i,1,N) {
		cin >> pt[i].F >> pt[i].S;
	}
	REP1(i,0,N) {
		lx.add(pt[i].F);
		ly.add(pt[i].S);
		lxy1.add(pt[i].F+pt[i].S);
		lxy2.add(pt[i].F-pt[i].S);
	}
	lx.make();
	ly.make();
	lxy1.make();
	lxy2.make();
	REP1(i,0,N) {
		int x;
		int y = pt[i].S;
		x = lx.qry(pt[i].F);
		st[0][x].insert({y,i});

		x = lxy1.qry(pt[i].F+pt[i].S);
		st[1][x].insert({y,i});

		x = lxy2.qry(pt[i].F-pt[i].S);
		st[2][x].insert({y,i});
	}

	REP1(i,0,N) {
		int x;
		int y = pt[i].S;
		{
			x = lx.qry(pt[i].F);
			auto it = st[0][x].upper_bound({y,i});
			if (it != end(st[0][x])) {
				to[i].PB(it->S);
			}
		}
		{
			x = lxy1.qry(pt[i].F+pt[i].S);
			auto it = st[1][x].upper_bound({y,i});
			if (it != end(st[1][x])) {
				to[i].PB(it->S);
			}
		}
		{
			x = lxy2.qry(pt[i].F-pt[i].S);
			auto it = st[2][x].upper_bound({y,i});
			if (it != end(st[2][x])) {
				to[i].PB(it->S);
			}
		}
	}

	REP1(i,0,N) {
		dp[i] = -INF;
		int id = ly.qry(pt[i].S);
		vec[id].PB({pt[i].F,i});
	}

	REP1(i,0,N) {
		sort(ALL(vec[i]));
		REP(j,SZ(vec[i])) {
			int k = vec[i][j].S;
			at[k] = j;
		}
	}

	dp[0] = 0;
	REP1(i,0,N) {
		solve(vec[i]);
	}

	int ans = -1;
	int best = -1;
	REP1(i,0,N) {
		int id = ly.qry(pt[i].S);
		if (dp[i] - 1 + SZ(vec[id]) > ans) {
			ans = dp[i] - 1 + SZ(vec[id]);
			best = i;
		}
//		cout << i << " " << dp[i] << endl;
	}
	
	vector<int> v;
	int lv = ly.qry(pt[best].S);

	for (int i=0; i<at[best]; i++)
		v.PB(vec[lv][i].S);
	for (int i=SZ(vec[lv])-1; i>=at[best]; i--)
		v.PB(vec[lv][i].S);

	int cur = best;
	while (cur != 0) {
		int x2 = frm[cur].F;
		int x1 = frm[cur].S;
		lv = ly.qry(pt[x1].S);

		if (x1 == x2) {
			v.PB(x1);
		} else if (at[x1] < at[x2]) {
			for (int i = at[x2]; i>at[x1]; i--)
				v.PB(vec[lv][i].S);
			for (int i=0; i<=at[x1]; i++)
				v.PB(vec[lv][i].S);
		} else {
			for (int i = at[x2]; i<at[x1]; i++)
				v.PB(vec[lv][i].S);
			for (int i=SZ(vec[lv])-1; i>=at[x1]; i--)
				v.PB(vec[lv][i].S);
		}

		cur = x1;
	}

	assert(SZ(v) >= 1);
	v.pop_back();
	reverse(ALL(v));
	cout << SZ(v) << endl;
	for (auto it:v) cout << it << " ";
	cout << endl;
	assert(SZ(v) == ans);

	return 0;
}

