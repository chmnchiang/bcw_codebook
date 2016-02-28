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
#define endl "\n"
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

#define int long long
const int MX = 12;
const int MP = 1<<22;
const int MMP = 59500;
const int ERR = MP-1;
const int INF = 1e18 + 100;
int flag[MX];

int conv[1<<20];

int N, A, B, Q;

int update(int s, int j, int typ) {
	int t = s & flag[j];
	t >>= (2*j);
	if (t == 0 and typ == 1) {
		s += (1<<(2*j));
		return s;
	} else if (t == 1 and typ == 0) {
		s += (1<<(2*j));
		return s;
	} else if (t == 2 and typ == 1) {
		return ERR;
	}
	return s;
}

int convert(int a) {
	int t = 0;
	for (int i=0; i<10; i++) {
		t *= 3;
		t += a % 4;
		a >>= 2;
	}
	return t;
}

int mem[11][MX/3][MMP][MX];
int dp(int i, int j, int st, int cnt) {
	if (st == ERR) return 0;
	if (cnt > B) return 0;

	if (j == N) {
		if (cnt > B or cnt < A) return 0;
		return dp(i+1, 0, st, 0);
	}

	if (i == N) {
		for (int k=0; k<N; k++) {
			if (not (st & flag[k])) {
				return 0;
			}
		}
		return 1;
	}

	if (j%3 == 0) {
		int cst = conv[st];
		if (mem[i][j/3][cst][cnt] != -1) {
			return mem[i][j/3][cst][cnt];
		}
	}

	int st0 = update(st, j, 0);
	int st1 = update(st, j, 1);

	int ans = dp(i, j+1, st0, cnt) + dp(i, j+1, st1, cnt+1);
	/*
	if (i ==4 and j == 4 and convert(st) == 41 and cnt == 3) {
		cout << st << ' ' << convert(st) << endl;
		cout << st0 << ' ' << st1 << endl;
	}*/
	ans = min(ans, INF);

	if (j%3 == 0) {
		int cst = conv[st];
		mem[i][j/3][cst][cnt] = ans;
	}
	//cout << i << ' ' << j << ' ' << st << ' ' << cnt << ": " << ans << endl;
	return ans;
}

int32_t main() {
	IOS;
	//cout << convert(ERR) << endl;

	memset(mem, -1, sizeof(mem));
	for (int i=0; i<(1<<20); i++) {
		conv[i] = convert(i);
	}

	flag[0] = 3;
	for (int i=1; i<=10; i++) {
		flag[i] = flag[i-1] << 2;
	}

	cin >> N >> A >> B >> Q;
	int all = dp(0, 0, 0, 0);
	//cout << all << endl;

	static int ans[MX][MX];

	for (int qq=0; qq<Q; qq++) {
		if (qq) cout << endl;
		int c; cin >> c;
		c--;
		if (c >= all) {
			cout << "No such matrix." << endl;
			continue;
		}
		int st = 0;
		for (int i=0; i<N; i++) {
			int cnt = 0;
			for (int j=0; j<N; j++) {
				// Try one word
				int xst = update(st, j, 0);
				int way = dp(i, j+1, xst, cnt);
				if (c < way) {
					ans[i][j] = 0;
					st = update(st, j, 0);
				} else {
					ans[i][j] = 1;
					cnt ++;
					c -= way;
					st = update(st, j, 1);
				}
			}
		}

		for (int i=0; i<N; i++) {
			for (int j=0; j<N; j++) {
				cout << ans[i][j];
			}
			cout << endl;
		}
	}
	
	
	return 0;
}

