//bcw0x1bd2 {{{
#include<bits/stdc++.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define MC(n,m) memcpy((n),(m),sizeof(n))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define FOR(x,y) for(__typeof(y.begin())x=y.begin();x!=y.end();x++)
#define IOS ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
  freopen(name".in", "r", stdin); \
  freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif

void RI() {}

template<typename... T>
void RI( int& head, T&... tail ) {
	    scanf("%d",&head);
			    RI(tail...);
}

mt19937 rng(0x5EED);
int randint(int lb, int ub) {
    return uniform_int_distribution<int>(lb, ub)(rng);
}
// Let's Fight! }}}

typedef long long i64;
const i64 MD = 998244353;
i64 trans[4][4] = {
	{ 1, 1, 1, 0 }, 
	{ 1, 2, 2, 0 },
	{ 0, 0, 1, 1 },
	{ 0, 1, 2, 1 },
};
int N;
i64 ans[4];

void mulmm(i64 t[4][4], i64 m1[4][4], i64 m2[4][4]) {
	for(int i=0; i<4; i++) 
		for(int j=0; j<4; j++)  t[i][j] = 0;

	for(int i=0; i<4; i++) {
		for(int j=0; j<4; j++) {
			for(int k=0; k<4; k++) {
				t[i][j] += m1[i][k] * m2[k][j] % MD;
				t[i][j] %= MD;
			}
		}
	}
}

void matcp(i64 m1[4][4], i64 m2[4][4]) {
	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++) m1[i][j] = m2[i][j];
}

void fastpow(i64 t[4][4], i64 mat[4][4], i64 b) {
	i64 tp1[4][4], tp2[4][4];
	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++) tp1[i][j] = 0;
	for(int i=0; i<4; i++) tp1[i][i] = 1;
	matcp(tp2, mat);

	i64 temp[4][4];
	while(b) {
		if(b&1LL) {
			mulmm(temp, tp1, tp2);
			matcp(tp1, temp);
		}
		mulmm(temp, tp2, tp2);
		matcp(tp2, temp);
		b >>= 1;
	}

	matcp(t, tp1);
}

void mulmv(i64 t[], i64 mat[4][4], i64 v[]) {
	for(int i=0; i<4; i++) {
		t[i] = 0;
		for(int j=0; j<4; j++) {
			t[i] += mat[i][j] * v[j];
		}
	}
}

int main(){
	FILEIO("figure");
	IOS;
	while(cin >> N && N) {
		i64 t[4][4];
		fastpow(t, trans, N);
		i64 a[4];
		for(int i=0; i<4; i++) a[i] = 0;
		ans[0] = 1;
		mulmv(a, t, ans);
		cout << a[0] << endl;
	}
	return 0;
}

