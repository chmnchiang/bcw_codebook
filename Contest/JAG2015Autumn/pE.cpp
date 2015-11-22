#include<bits/stdc++.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define F first
#define S second
#define PB push_back
#define ALL(x) begin(x),end(x)
#define SZ(x) ((int)(x).size())
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
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

typedef long long LL;
typedef pair<int,int> pii;

const int MX = 105;
const int LOG = 31;

int N, L, a[MX][MX];
pii nxt[MX][MX], at[MX*MX];
pii stp[LOG][MX][MX];
string ip;

void _dump(int x[MX][MX]) {
	cout << "=== begin dump ===" << endl;
	for (int i=0; i<N; i++){
		for (int j=0; j<N; j++) {
			cout << x[i][j] << " ";
		}
		cout << endl;
	}
	cout << "=== end   dump ===" << endl;
}
void matcpy(int dst[MX][MX], int src[MX][MX]) {
	for (int i=0; i<N; i++)
		for (int j=0; j<N; j++)
			dst[i][j] = src[i][j];
}
void rotate(char op, LL t) {
	t--;
	if (op == 'L') {
		int zero = a[t][0];
		for (int i=0; i<N-1; i++)
			a[t][i] = a[t][i+1];
		a[t][N-1] = zero;
	}
	if (op == 'R') {
		int lst = a[t][N-1];
		for (int i=N-1; i>0; i--)
			a[t][i] = a[t][i-1];
		a[t][0] = lst;
	}
	if (op == 'U') {
		int zero = a[0][t];
		for (int i=0; i<N-1; i++)
			a[i][t] = a[i+1][t];
		a[N-1][t] = zero;
	}
	if (op == 'D') {
		int lst = a[N-1][t];
		for (int i=N-1; i>0; i--)
			a[i][t] = a[i-1][t];
		a[0][t] = lst;
	}
}

void buildNxt(int b[MX][MX]) {
	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
			at[a[i][j]] = {i, j};
		}
	}
	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
			nxt[i][j] = at[b[i][j]];
		}
	}
}

pii gogo(int x, int y, int t) {
	for (int i=0; t; i++) {
		if (t&1) {
			int nx = stp[i][x][y].F;
			int ny = stp[i][x][y].S;
			x = nx;
			y = ny;
		}
		t >>= 1;
	}
	return {x, y};
}
void rep(int b[MX][MX], int t) {
	for (int i=0; i<N; i++)
		for (int j=0; j<N; j++)
			stp[0][i][j] = nxt[i][j];
	for (int i=1; i<LOG; i++) {
		for (int j=0; j<N; j++) {
			for (int k=0; k<N; k++) {
				int nx = stp[i-1][j][k].F;
				int ny = stp[i-1][j][k].S;
				stp[i][j][k] = stp[i-1][nx][ny];
			}
		}
	}
//	int c[MX][MX];
	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
			pii tmp = gogo(i, j, t);
			a[tmp.F][tmp.S] = b[i][j];
		}
	}
//	matcpy(b, c);
}

int go(int cur) {
	if (ip[cur] == '(') {
		int b[MX][MX];
		matcpy(b, a);
		int p = cur+1;
		while (ip[p] != ')') {
			if (p > L) assert(false);
			p = go(p);
		}
		p++;
		LL t = 0;
		while (p<L && isdigit(ip[p])) {
			t = t * 10 + ip[p] - '0';
			p++;
		}
		buildNxt(b);
		rep(b, t);
		return p;
	} else {
		int p = cur+1;
		LL t = 0;
		while (p < L && isdigit(ip[p])) {
			t = t * 10 + ip[p] - '0';
			p++;
		}
		rotate(ip[cur], t);
		return p;
	}
}

int main() {
	IOS;
	while (cin >> N >> L) {
		cin >> ip;
		for (int i=0, s=1; i<N; i++) {
			for (int j=0; j<N; j++) {
				a[i][j] = s++;
			}
		}

		int p=0;
		while (p < L) {
			p = go(p);
		}
		for (int i=0; i<N; i++) {
			for (int j=0; j<N; j++) {
				cout << a[i][j];
				if (j == N-1) cout << endl;
				else cout << " ";
			}
		}
	}

	return 0;
}

