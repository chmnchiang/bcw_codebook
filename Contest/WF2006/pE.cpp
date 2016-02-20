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
// Let's Fight!
#include <sys/resource.h>
void increase_stack_size() {
  const rlim_t ks = 64*1024*1024;
  struct rlimit rl;
  int res=getrlimit(RLIMIT_STACK, &rl);
  if(res==0){
    if(rl.rlim_cur<ks){
      rl.rlim_cur=ks;
      res=setrlimit(RLIMIT_STACK, &rl);
    }
  }
}

const int MX = 16*1024*8 + 20;
const int MB = 40 + 5;
const int INF = 1029384756;

int L, N;
string ip;
int len;
bool visit[MB][MX][MB];
char mem[MB][MX][MB];

int getNum(int i, int j) {
	int t = 0;
	for (int x=i; x<j; x++) {
		t <<= 1;
		t += ip[x]-'0';

		if (t > MX) return INF;
	}
	return t;
}

int dp(int pos, int l, int zero) {
	if (pos == 0) {
		if (l == 0 and zero == 0)
			return 1;
		return 0;
	}

	if (l < 0 or zero < 0) return 0;

	if (visit[pos][l][zero]) return mem[pos][l][zero];

	visit[pos][l][zero] = true;

	int ans = 0;
	for (int i=0; i<pos; i++) {
		if (ip[i] == '0') continue;
		if (i and ip[i-1] == '1') continue;
		if (pos != L and ip[pos] == '1') continue;
		int t = getNum(i, pos);
		if (t <= 2) continue;
		int nl = l - t;
		if (nl < 0) continue;


		ans = min(2, ans + dp(i, nl, zero));
	}

	if (ip[pos-1] == '0' and zero)
		ans = min(2, ans + dp(pos-1, l-1, zero-1));

	if (ip[pos-1] == '1' and (pos == 1 or ip[pos-2] == '0'))
		ans = min(2, ans + dp(pos-1, l-1, zero));

	if (pos >= 2 and ip[pos-1] == '1' and ip[pos-2] == '1' and (pos == 2 or ip[pos-3] == '0'))
		ans = min(2, ans + dp(pos-2, l-2, zero));

	return (mem[pos][l][zero] = ans);
}

void solve() {


	int zeros = L - N;
	if (zeros > len or L > MX) {
		cout << "NO\n";
		return;
	}

	for (int i=0; i<MB; i++) {
		for (int j=0; j<=L+5; j++) {
			for (int k=0; k<MB; k++) {
				mem[i][j][k] = visit[i][j][k] = 0;
			}
		}
	}

	int t = dp(len, L, zeros); 

	if (t >= 2) {
		cout << "NOT UNIQUE\n";
	} else if (t == 1) {
		cout << "YES\n";
	} else cout << "NO\n";
}

int main() {
	IOS;
	increase_stack_size();

	int cas = 0;
	while (true) {
		cin >> L >> N;
		if (not N and not L) break;
		cin >> ip;
		len = ip.length();

		cas++;
		cout << "Case #" << cas << ": ";
		solve();
	}

    return 0;
}


