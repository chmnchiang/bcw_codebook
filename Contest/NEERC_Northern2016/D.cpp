#pragma GCC optimize ("O2")
#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n)boolmemset((n),-1,sizeof(n))
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


ostream& operator << (ostream& o, array<int,3> a) {
	return o << "(" << a[0] << "," << a[1] << "," << a[2] << ")";
}

int N,ip[9][514];
int hao123[10][10][10];
int ws360[514];
int seg7[10][7];

void predef() {
	vector<int> vec = {0,1,2,4,5,6};
	for (auto i:vec) seg7[0][i] = 1;
	vec = {2,5};
	for (auto i:vec) seg7[1][i] = 1;
	vec = {0,2,3,4,6};
	for (auto i:vec) seg7[2][i] = 1;
	vec = {0,2,3,5,6};
	for (auto i:vec) seg7[3][i] = 1;
	vec = {1,2,3,5};
	for (auto i:vec) seg7[4][i] = 1;
	vec = {0,1,3,5,6};
	for (auto i:vec) seg7[5][i] = 1;
	vec = {0,1,3,4,5,6};
	for (auto i:vec) seg7[6][i] = 1;
	vec = {0,2,5};
	for (auto i:vec) seg7[7][i] = 1;
	vec = {0,1,2,3,4,5,6};
	for (auto i:vec) seg7[8][i] = 1;
	vec = {0,1,2,3,5,6};
	for (auto i:vec) seg7[9][i] = 1;

	auto gethash = [](int a, int b, int c) {
		auto A = seg7[a];
		auto B = seg7[b];
		auto C = seg7[c];
		int r = 0;
		REP1(i,0,2) r = r * 2 + A[i];
		REP1(i,0,2) r = r * 2 + (A[3+i] | B[i]);
		r = r * 2 + (A[6] | B[3] | C[0]);
		REP1(i,0,2) r = r * 2 + (C[1+i] | B[4+i]);
		REP1(i,4,6) r = r * 2 + C[i];
		return r;
	};

	REP(i,10) REP(j,10) REP(k,10) hao123[i][j][k] = gethash(i,j,k);

}

int jinfrom123(int t) {
	vector<int> vec = {11, 8, 5, 2, 12, 9, 6, 3, 0};
	int s = 0;
	for (int x: vec) {
		s *= 2; s += !!((1<<x) & t);
	}
	return s;
}

int shanfrom123(int t) {
	vector<int> vec = {10, 7, 4, 1};
	int s = 0;
	for (int x: vec) {
		s *= 2; s += !!((1<<x) & t);
	}
	return s;
}

void buildws() {
	for (int i=0; i<=N; i++) {
		int j = i*2, jj = j+1;
		for (int k=0; k<4; k++) {
			ws360[i] *= 2;
			ws360[i] += ip[k*2+1][j];
		}
		for (int k=0; k<5; k++) {
			ws360[i] *= 2;
			ws360[i] += ip[k*2][jj];
		}
	}
}

bool mem[111][80][2];
bool vt[111][80][2];
using pii = pair<int, int>;
pii duuba[111][80][2];
pii baidu[111][80][2];

bool dp(int i, int m, int p) {
//	cout << i << ' ' << m << ' ' << p << endl;
	if (i >= N) return p == 0 and (m << 5) == ws360[i];
	bool &res = mem[i][m][p];
	if (vt[i][m][p]) return res;
	vt[i][m][p] = 1;

	for (int a=0; a<=9; a++) {
		for (int b=0; b<=9; b++) {
			if (p) if (a + b < 10) continue;
			if (!p) if (a + b >= 10) continue;

			int c = (a+b)%10;
			int z = jinfrom123(hao123[a][b][c]);
			if ((z | (m << 5)) == ws360[i]) {
				int zzz = shanfrom123(hao123[a][b][c]);
				if (dp(i+1, zzz, 0)) {
					duuba[i][m][p] = {a, b};
					baidu[i][m][p] = {zzz, 0};
					res = 1;
					return true;
				}
			}
		}
	}

	for (int a=0; a<=9; a++) {
		for (int b=0; b<=9; b++) {
			if (p) if (a + b + 1 < 10) continue;
			if (!p) if (a + b + 1>= 10) continue;

			int c = (a+b+1)%10;
			int z = jinfrom123(hao123[a][b][c]);

			if ((z | (m << 5)) == ws360[i]) {
				int zzz = shanfrom123(hao123[a][b][c]);
				if (dp(i+1, zzz, 1)) {
					duuba[i][m][p] = {a, b};
					baidu[i][m][p] = {zzz, 1};
					res = 1;
					return true;
				}
			}
		}
	}

	return false;
}


int main() {
	IOS;
	FILEIO("digital");
	predef();

	cin >> N;
	REP(i,9) {
		if (i % 2 == 0) {
			for (int j=0,p=1; j<N; j++,p+=2) {
				cin >> ip[i][p];
			}
		} else {
			for (int j=0,p=0; j<N+1; j++,p+=2) {
				cin >> ip[i][p];
			}
		}
	}

	buildws();

	bool fg = dp(0, 0, 0);

	if (!fg) {
		cout << "NO" << endl;
	} else {
		string A, B, C;
		int i = 0, m = 0, p = 0;
		while (i < N) {
			int a, b, c;
			tie(a, b) = duuba[i][m][p];
			tie(m, p) = baidu[i][m][p];
			if (p) c = (a+b+1)%10;
			else c = (a+b)%10;
			A += '0'+a;
			B += '0'+b;
			C += '0'+c;
			i++;
		}
		cout << A << endl << B << endl << C << endl;
	}

	return 0;
}

