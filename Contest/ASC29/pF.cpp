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
#define REP(i,x) for(int i=0;i<(x);i++)
#define REP1(i,a,b) for (int i=(a);i<=(b);i++)
// Let's Fight!

typedef long long ll;
const int MXN = 200005;
const ll H = 222557;
const ll MOD = 999991231;
//const ll H = 100;
//const ll MOD = 1000000;

ll curh,tarh,pw[MXN];
int N,M,lstapp[MXN],prv[MXN],nxt[MXN];
char s1[MXN], s2[MXN];

void normalize(ll &h) {
	h %= MOD;
	if (h < 0) h += MOD;
}
int main() {
	pw[0] = 1;
	REP1(i,1,MXN-1) {
		pw[i] = pw[i-1]*H%MOD;
	}
	FILEIO("substring");
	gets(s1);
	gets(s2);
	N = strlen(s1);
	M = strlen(s2);

	tarh = 0;
	FMO(lstapp);
	REP(i,M) {
		int c = s2[i];
		if (lstapp[c] != -1) {
			tarh = tarh * H + (i - lstapp[c]);
		} else {
			tarh = tarh * H + (H - 1);
		}
		normalize(tarh);
		lstapp[c] = i;
	}

	FMO(lstapp);
	REP(i,N) {
		int c = s1[i];
		if (lstapp[c] != -1) nxt[lstapp[c]] = i;
		prv[i] = lstapp[c];
		nxt[i] = MXN*3;
		lstapp[c] = i;
	}

	curh = 0;
	FMO(lstapp);
	REP(i,M) {
		if (prv[i] != -1) {
			curh = curh * H + (i - prv[i]); 
		} else {
			curh = curh * H + (H - 1);
		}
		normalize(curh);
	}

	vector<int> ans;
	if (curh == tarh) ans.PB(0);
	REP1(i,M,N-1) {
		int st = i - M + 1;
		curh = curh * H - (H - 1) * pw[M];
		normalize(curh);
		if (nxt[st-1] < i) {
			int j = nxt[st-1] - st;
			curh -= (j + 1) * pw[M-(j+1)];
			normalize(curh);
			curh += (H - 1) * pw[M-(j+1)];
			normalize(curh);
		}
		if (prv[i] >= st) {
			curh += (i - prv[i]);
		} else {
			curh += H - 1;
		}
		normalize(curh);
		//cout << curh << endl;
		if (curh == tarh) ans.PB(st);
	}
	cout << SZ(ans) << endl;
	for (auto it:ans) cout << it+1 << " ";
	cout << endl;


	return 0;
}
