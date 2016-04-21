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

#define int long long
const int MD = 1000000007;
int K, M, H, L, R;
int N;
int A, B, C;
int ans;
const int MX = (1<<16) + 3;
int lookup[MX];

int _rev(int a) {
	int b = 0;
	for (int i=0; i<((K+1)/2); i++) {
		b<<=1; b|=(a&1);
		a>>=1;
	}
	return b;
}

void pre() {
	for (int i=0; i<MX; i++) lookup[i] = _rev(i);
}

int rev(int a) {
	int kf = (K+1)/2;
	int z = (1<<kf)-1;
	int a1 = (a&(z<<kf)) >> kf;
	int a2 = (a&z);
	int v = (lookup[a2]<<kf) + lookup[a1];
	if (K%2) v>>=1;
	return v;
}

void nextHash() {
	H = ((L^R^H^ans)+C)%MD;
	L = ((L^A^H) % (N+1))%N;
	R = ((R^B^H) % (N-L))+L;
}

int getN(int a) {
	int b = a/2;
	int v = rev(b);
	if (a&1) {
		return N-v-1;
	} else return v;
}

void calc() {
	for (int i=0; i<M; i++) {
		int len = R - L + 1;
		if (L%2 == 0) {
			int lf = len/2;
			int v = (lf%2 ? N-1 : 0);
			if (len % 2) {
				v ^= getN(R);
			}
			ans = v;
		} else {
			int lf = (len-1)/2;
			int v = (N-1) * lf;
			v += getN(L);
			if (len % 2 == 0) v += getN(R);
			ans = v;
		}
		nextHash();
	}
}

int32_t main() {
	IOS;
	cin>>K>>M>>L>>R>>A>>B>>C;
	N = 1<<K;
	pre();
//	for (int i=0; i<N; i++) cout<<getN(i)<<' '; cout << endl;
	//for (int i=0; i<N; i++) cout << rev(i) << endl;
	calc();

	cout << H << endl;

	return 0;
}
