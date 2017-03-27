#pragma GCC optimize ("O2")
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

int N,A,arr[514][514];
int vst[514][514];

void build1() {
	int p = 1;
	REP1(i,1,N) {
		if (i & 1) {
			REP1(j,1,N) arr[i][j] = p++;
		} else {
			for (int j=N; j>=1; j--) arr[i][j] = p++;
		}
	}
}
void build2() {
	int p = 1;
	REP1(j,1,N) {
		if (j & 1) {
			REP1(i,1,N) arr[i][j] = p++;
		} else {
			for (int i=N; i>=1; i--) arr[i][j] = p++;
		}
	}
}
int inr(int x, int y) {
	return (1 <= x and x <= N and 1 <= y and y <= N);
}
void build3() {
	const int dir[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};
	int x = 1;
	int y = 1;
	int d = 0;
	int p = 1;

	REP1(i,1,N*N) {
		arr[x][y] = p++;
		vst[x][y] = 1;

		int nx = x + dir[d][0];
		int ny = y + dir[d][1];

		if (!inr(nx,ny) or vst[nx][ny]) {
			d = (d + 1) % 4;
			nx = x + dir[d][0];
			ny = y + dir[d][1];
		}
		x = nx;
		y = ny;
	}
}
void build4() {
	const int dir[4][2] = {{1,0},{0,1},{-1,0},{0,-1}};
	int x = 1;
	int y = 1;
	int d = 0;
	int p = 1;

	REP1(i,1,N*N) {
		arr[x][y] = p++;
		vst[x][y] = 1;

		int nx = x + dir[d][0];
		int ny = y + dir[d][1];

		if (!inr(nx,ny) or vst[nx][ny]) {
			d = (d + 1) % 4;
			nx = x + dir[d][0];
			ny = y + dir[d][1];
		}
		x = nx;
		y = ny;
	}
}
int main() {
	IOS;
	cin>>N>>A;

	if (A == 1) build1();
	if (A == 2) build2();
	if (A == 3) build3();
	if (A == 4) build4();

	REP1(i,1,N) REP1(j,1,N) {
		cout<<arr[i][j]<<" \n"[j==N];
	}


	return 0;
}

