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
typedef pair<long long, long long> pll;

// n < 4,759,123,141        3 :  2, 7, 61
// n < 1,122,004,669,633    4 :  2, 13, 23, 1662803
// n < 3,474,749,660,383          6 :  pirmes <= 13
// n < 2^64                       7 :
// 2, 325, 9375, 28178, 450775, 9780504, 1795265022
// Make sure testing integer is in range [2, n−2] if
// you want to use magic.
inline long long modit(long long x,long long mod) {
	if(x>=mod) x-=mod;
	//if(x<0) x+=mod;
	return x;
}
inline long long mult(long long x,long long y,long long mod) {
	if (y < 0) y = (y%mod+mod)%mod;
	long long s=0,m=x%mod;
	while(y) {
		if(y&1) s=modit(s+m,mod);
		y>>=1;
		m=modit(m+m,mod);
	}
	return s;
}
long long power(long long x,long long p,long long mod){
	long long s=1,m=x;
	while(p) {
		if(p&1) s=mult(s,m,mod);
		p>>=1;
		m=mult(m,m,mod);
	}
	return s;
}
bool witness(long long a,long long n,long long u,int t){
	long long x=power(a,u,n);
	for(int i=0;i<t;i++) {
		long long nx=mult(x,x,n);
		if(nx==1&&x!=1&&x!=n-1) return 1;
		x=nx;
	}
	return x!=1;
}
bool miller_rabin(long long n) {
	// iterate s times of witness on n
	// return 1 if prime, 0 otherwise
	if(n<2) return 0;
	if(!(n&1)) return n==2;
	long long u=n-1;
	int t=0;
	// n-1 = u*2^t
	while(!(u&1)) {
		u>>=1;
		t++;
	}
	long long arr[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
	REP(i,7) {
		if (arr[i] >= n-1) break;
		if(witness(arr[i],n,u,t)) return 0;
	}
	return 1;
}
long long f(long long x,long long mod) {
	return modit(mult(x,x,mod)+1,mod);
}
long long pollard_rho(long long n) {
	if (miller_rabin(n)) return n;
	if(!(n&1)) return 2;
	while (true) {
		long long y=2, x=rand()%(n-1)+1, res=1;
		for (int sz=2; res==1; sz*=2) {
			for (int i=0; i<sz && res<=1; i++) {
				x = f(x, n);
				res = __gcd(abs(x-y), n);
			}
			y = x;
		}
		if (res!=0 && res!=n) return res;
	}
}
vector<pll> factorint(long long x) {
	vector<pll> res;
	while (x > 1) {
		long long fac = pollard_rho(x);
		while (!miller_rabin(fac))
			fac = pollard_rho(fac);
		int c = 0;
		while (x % fac == 0) {
			c++;
			x /= fac;
		}
		res.PB({fac,c});
	}
	sort(ALL(res));
	return res;
}

int phi(int x) {
	auto res = factorint(x);
	int t = x;
	for (auto p: res){
		t /= p.F;
		t *= p.F-1;
	}
	return t;
}

const int MX = 5010;
int N, M;
int A[MX], B[MX];
int tA[MX], tB[MX];

typedef pair<int, int> pii;

inline pii gcd(int a, int b){
	if(b == 0) return make_pair(1, 0);
	else{
		int p = a / b;
		pii q = gcd(b, a % b);
		return make_pair(q.second, q.first - q.second * p);
	}
}

inline int rev(int a, int p) {
	auto r = gcd(a, p);
	return r.F%p;
}

int calc(int x) {
	int ans = 1;

	for (int i=0; i<N; i++) {
		tA[i] = A[i];
	}
	for (int i=0; i<M; i++) {
		tB[i] = B[i];
	}

	auto res = factorint(x);
	vector<int> prime;
	for (auto y: res) prime.PB(y.F);
	map<int, int> mp;

	for (int i=0; i<N; i++) {
		for (auto p: prime) {
			while (tA[i]%p == 0) {
				//cout << p << "++" << endl;
				mp[p]++;
				tA[i]/=p;
			}
		}
	}
	for (int i=0; i<M; i++) {
		for (auto p: prime) {
			while (tB[i]%p == 0) {
				//cout << p << "--" << endl;
				mp[p]--;
				tB[i]/=p;
			}
		}
	}

	for (auto y: mp) {
		int p = y.F, v = y.S;
		if (v < 0) return -1;
		if (!v) continue;
		ans = mult(ans, power(p, v, x), x);
	}
	//cout << "ANS = " << ans << endl;


	for (int i=0; i<M; i++) {
		ans = mult(ans, rev(tB[i], x), x);
	}

	for (int i=0; i<N; i++) {
		ans = mult(ans, tA[i], x);
	}

	return ans;
}
int32_t main() {
	IOS;
	//cout << factorint(1000000016000000063) << endl;
	cin >> N >> M;
	for (int i=0; i<N; i++)
		cin >> A[i];
	for (int i=0; i<M; i++)
		cin >> B[i];

	/*
	for (int i=0; i<N; i++) {
		for (int j=0; j<M; j++) {
			int g = __gcd(A[i], B[j]);
			A[i] /= g; B[j] /= g;
			if (A[i] == 1) break;
		}
	}*/

	/*
	for (int i=0; i<N; i++)
		cout << A[i] << ' ';

	for (int i=0; i<M; i++)
		cout << B[i] << ' ';
		*/
	int Q; cin >> Q;
	for (int i=0; i<Q; i++) {
		int z; cin >> z;
		int t = calc(z);
		if (t == -1) cout << "DIVISION BY ZERO" << endl;
		else cout << t << endl;
	}


	return 0;
}
