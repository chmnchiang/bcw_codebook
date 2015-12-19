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

const int MX = 5555;
typedef pair<short, short> pii;
struct PQ {
	vector<short> ls[MX];
	int val[MX];
	int cur_min = 0;
	int k;

	void init(int _k) {
		k = _k;
		for (int i=0; i<MX; i++) {
			ls[i].clear();
		}
		for (int i=1; i<=k; i++) {
			val[i] = 0;
			ls[0].PB(i);
		}
		cur_min = 0;
	}

	pii get_min() {
		while (! ls[cur_min].size()) {
			cur_min ++;
		}

		vector<short> &l = ls[cur_min];
		while (l.size()) {
			if (val[l.back()] != cur_min)
				l.pop_back();
			else break;
		}
		if (! ls[cur_min].size()) return get_min();
		return {cur_min, l.back()};
	}

	void change(int _k, int n) {
//		if (val[_k] <= n) return;
		val[_k] = n;
		ls[n].PB(_k);
	}

} pq, pq1;


int K;
int L1, L2;
int S1[MX], S2[MX];
int J1[MX], J2[MX];
short dp[MX][MX];
pii bk[MX][MX];
short bbk[MX][MX];

int main() {
	FILEIO("robots");
	IOS;

	cin >> K;
	cin >> L1;
	for (int i=0; i<L1; i++) {
		cin >> S1[i];
	}
	cin >> L2;
	for (int i=0; i<L2; i++) {
		cin >> S2[i];
	}

	pq.init(K);
	for (int i=1; i<=K; i++) {
		J1[i] = L1;
	}
	for (int i=L1-1; i>=0; i--) {
		int m, k;
		tie(m, k) = pq.get_min();
		dp[i][L2] = m + 1;
		bk[i][L2] = {J1[k], L2};
		bbk[i][L2] = k;

		int t = S1[i];
		J1[t] = i;
		pq.change(t, m+1);
	}

	pq.init(K);
	for (int i=1; i<=K; i++) {
		J2[i] = L2;
	}
	for (int i=L2-1; i>=0; i--) {
		int m, k;
		tie(m, k) = pq.get_min();
		dp[L1][i] = m + 1;
		bk[L1][i] = {L1, J2[k]};
		bbk[L1][i] = k;

		int t = S2[i];
		J2[t] = i;
		pq.change(t, m+1);
	}

	for (int i=1; i<=K; i++) {
		J1[i] = L1;
		J2[i] = L2;
	}
	for (int i=L1-1; i>=0; i--) {
		int s1 = S1[i];
		pq.init(K);
		for (int k=1; k<=K; k++) {
			int pos = J1[k];
			int d = dp[pos][L2];
			pq.change(k, d);
			//cout << i << ' ' << k << ' ' << d << endl;
			J2[k] = L2;
		}
		for (int j=L2-1; j>=0; j--) {
			
			int s2 = S2[j];
			if (s1 == s2) {
				int m, k;
				tie(m, k) = pq.get_min();
			//	cout << "min = " << m << endl;
				dp[i][j] = m + 1;
				bk[i][j] = {J1[k], J2[k]};
				bbk[i][j] = k;
			}

			int pos = J1[s2];
			int d = dp[pos][j];
			pq.change(s2, d);
			//cout << "pos = " << pos << endl;
			//cout << "Ch = " << s2 << ' ' << d << endl;
			J2[s2] = j;
		}
		J1[s1] = i;
		pq1.change(s1, dp[i][L2]);
	}

	int mn = 10293847;
	int mnk = -1;
	pii curp = {-1, -1};
	for (int k=1; k<=K; k++) {
		int p1 = J1[k], p2 = J2[k];
		int d = dp[p1][p2];
		if (mn > d) {
			mn = d;
			curp = {p1, p2};
			mnk = k;
		}
	}

	/*
	cout << curp.F << ' ' << curp.S << endl;
	for (int i=0; i<=L1; i++) {
		for (int j=0; j<=L2; j++) {
			cout << dp[i][j] << ' ';
		}
		cout << endl;
	}*/

	cout << dp[curp.F][curp.S]+1 << endl;
	cout << mnk;
	while (curp != pii{L1, L2}) {
		int k = 0;
		int p1, p2;
		tie(p1, p2) = curp;
		if (p1 == L1) {
			k = S2[p2];
		} else {
			k = S1[p1];
		}
		curp = bk[p1][p2];
		cout << ' ' << bbk[p1][p2];
	}
	cout << endl;
	


    return 0;
}
