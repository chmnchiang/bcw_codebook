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
const int MX = 55;
int N, M;
int mem[MX][MX];
bool us[MX][MX];
int dp(int a, int b) {
	if (a == 0 or b == 0) return 0;
	if (us[a][b]) return mem[a][b];

	vector<int> sg;
	for (int i=0; i<a; i++) {
		for (int j=0; j<b; j++) {
			int q = dp(i, b) ^ dp(a, j) ^ dp(i, j);
			sg.PB(q);
		}
	}
	sort(ALL(sg));
	sg.resize(unique(ALL(sg)) - sg.begin());
	us[a][b] = true;
	for (int i=0; i<SZ(sg); i++) {
		if (i != sg[i]) {
			return (mem[a][b] = i);
		}
	}
	return (mem[a][b] = SZ(sg));
}

string mp[MX];

int main() {
	IOS;
	FILEIO("coins");

	cin >> M >> N;
	int sg = 0;
	for (int i=1; i<=M; i++) {
		string s; cin >> s;
		s = "?" + s;
		mp[i] = s;
		for (int j=1; j<=N; j++) {
			if (s[j] == '1') {
				sg ^= dp(i, j);
			}
		}
	}

	if (sg == 0) {
		cout << "Betty" << endl;
	} else {
		for (int i=1; i<=M; i++) {
			for (int j=1; j<=N; j++) {
				if (mp[i][j] == '0') continue;
				for (int ii=0; ii<i; ii++) {
					for (int jj=0; jj<j; jj++) {
						int ss = sg ^ dp(ii, jj) ^ dp(ii,j) ^ dp(i, jj) ^ dp(i, j);
						if (ss == 0) {
							cout << "Ann" << endl;
							cout << i << ' ' << j << endl;
							cout << ii << ' ' << jj << endl;
							return 0;
						}
					}
				}
			}
		}
	}

    return 0;
}
