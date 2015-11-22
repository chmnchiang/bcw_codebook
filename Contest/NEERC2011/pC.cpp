#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define MC(n,m) memcpy((n),(m),sizeof(n))
#define F first
#define S second
#define MP make_pair
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
// Let's Fight!
const int MX = 33;

int M, N, K, Smin, Smax;
vector<char> chars;
map<char, int> charMap;
char font[MX][MX][MX];
char mp[MX][2020];
string ip, op;
int l1, l2;

int mem[MX+MX][2020];
int bs[MX+MX][2020];
int sm[2020];
int cost[MX][2020];
const int INF = 1029384756;

int dp(int idx, int pos) {

	if (pos < 0) return INF;
	if (mem[idx][pos] != -1) return mem[idx][pos];

	int ans = INF;
	int best = -1;
	if (idx == 0) {
		ans = sm[pos];
	} else if (idx == l2 * 2) {
		for (int i=0; i<=pos; i++) {
			int temp = dp(idx-1, i) + sm[pos] - sm[i];
			if (ans > temp) {
				ans = temp;
				best = i;
			}
		}
	} else if (idx & 1) {
		if (pos - K >= 0) {
			int i = idx / 2;
			int t = charMap[op[i]];
			ans = dp(idx-1, pos-K) + cost[t][pos-K];
			best = pos-K;
		}

	} else {
		for (int i=Smin; i<=min(Smax, pos); i++) {
			int temp = dp(idx-1, pos-i) + sm[pos] - sm[pos-i];
			if (ans > temp) {
				ans = temp;
				best = pos-i;
			}
		}
	}
	mem[idx][pos] = ans;
	bs[idx][pos] = best;
	return ans;
}


int main() {
	FILEIO("caption");
	cin >> M >> N >> K >> Smin >> Smax;
	getchar();
	for (int i=0; i<M; i++) {
		int t = 0;
		while (true) {
			char c = getchar();

			if (not i) {
				charMap[c] = chars.size();
				chars.PB(c);
			}
			getchar();
			for (int j=0; j<K; j++) {
				font[t][i][j] = getchar();
			}
			c = getchar();
			if (c == '\n') break;

			t ++;
		}
	}
	{
		int t = charMap[' '] = chars.size();
		chars.PB(' ');
		for (int i=0; i<M; i++) {
			for (int j=0; j<K; j++) {
				font[t][i][j] = '.';
			}
		}
	}
	getline(cin, ip);
	l1 = ip.length();
	int pos = 0;
	for (int j=0; j<M; j++) {
		for (int i=0; i<N; i++) {
			mp[j][i] = '.';
		}
	}
	for (int i=0; i<l1; i++) {
		int a; cin >> a; pos += a;
		int cid = charMap[ip[i]];
		for (int j=0; j<M; j++) {
			for (int k=0; k<K; k++) {
				mp[j][pos+k] = font[cid][j][k];
			}
		}
		pos += K;
	}
	
	getchar();

	getline(cin, op);
	l2 = op.length();

	for (int i=0; i<N; i++) {
		int t = 0;
		for (int j=0; j<M; j++) {
			t += (mp[j][i] == '*');
		}
		sm[i+1] = sm[i] + t;
	}

	for (int i=0; i<SZ(chars); i++) {
		for (int ii=0; ii<M; ii++) {
			for (int j=0; j<=N-K; j++) {
				for (int k=0; k<K; k++) {
					cost[i][j] += (font[i][ii][k] != mp[ii][j+k]);
				}
			}
		}
	}


	memset(mem, -1, sizeof(mem));
	dp(l2*2, N);

	int idx = l2*2;
	pos = N;
	vector<int> ans;

	while (idx) {
		int bk = bs[idx][pos];
		ans.PB(pos - bk);
		//assert(pos-bk >= 0);
		idx --;
		pos = bk;
	}
	ans.PB(pos);
	//assert(pos >= 0);

	reverse(ALL(ans));
	for (int i=0; i<l2; i++) {
		cout << ans[i*2] << " \n"[i == l2-1];
	}

    return 0;
}
