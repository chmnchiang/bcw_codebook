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

typedef long long ll;
typedef double ld;
typedef complex<ld> cplx;

const ld PI = acosl(-1);
const cplx I(0, 1);
const ll MOD = 1000000007;
const int MAXN = 32768;

cplx omega[MAXN+1];
void pre_fft()
{
  for(int i=0; i<=MAXN; i++)
    omega[i] = exp(i * 2 * PI / MAXN * I);
}
void fft(int n, cplx a[], bool inv=false)
{
  int basic = MAXN / n;
  int theta = basic;
  for (int m = n; m >= 2; m >>= 1) {
    int mh = m >> 1;
    for (int i = 0; i < mh; i++) {
      cplx w = omega[inv ? MAXN-(i*theta%MAXN) : i*theta%MAXN];
      for (int j = i; j < n; j += m) {
        int k = j + mh;
        cplx x = a[j] - a[k];
        a[j] += a[k];
        a[k] = w * x;
      }
    }
    theta = (theta * 2) % MAXN;
  }
  int i = 0;
  for (int j = 1; j < n - 1; j++) {
    for (int k = n >> 1; k > (i ^= k); k >>= 1);
    if (j < i) swap(a[i], a[j]);
  }
  if (inv)
    for (i = 0; i < n; i++)
      a[i] /= n;
}

ll N;
int M, P, G, NN;
int coin[MAXN];
ll lcur[MAXN], lret[MAXN];
cplx ca[MAXN], cb[MAXN];
ll D[MAXN];
bool dp[MAXN];
ll aa[MAXN], bb[MAXN], cc[MAXN], dd[MAXN], tmp[MAXN];

ll lpow(ll a, ll p)
{
	ll ret = 1, cur = a % MOD;
	while(p)
	{
		if(p&1LL)
			ret = ret * cur % MOD;
		cur = cur * cur % MOD;
		p >>= 1;
	}
	return ret;
}

ll linv(ll a)
{
	return lpow(a, MOD-2);
}

void _mult(ll a[], ll b[], ll c[])
{
	for(int i=0; i<NN; i++)
	{
		if(i < G)
		{
			ca[i] = a[i];
			cb[i] = b[i];
		}
		else
			ca[i] = cb[i] = 0;
	}
	fft(NN, ca);
	fft(NN, cb);
	for(int i=0; i<NN; i++)
		ca[i] *= cb[i];
	fft(NN, ca, true);
	for(int i=0; i<G; i++)
	{
		c[i] = (ca[i] + ca[i+G]).real() + 0.5;
		c[i] %= MOD;
	}
}

void mult(ll a[], ll b[])
{
	for(int i=0; i<G; i++)
	{
		bb[i] = a[i] & 32767LL;
		dd[i] = b[i] & 32767LL;
		aa[i] = (a[i] >> 15);
		cc[i] = (b[i] >> 15);
	}

	_mult(bb, dd, a);
	_mult(aa, dd, tmp);
	for(int i=0; i<G; i++)
		a[i] = (a[i] + tmp[i] * 32768LL) % MOD;
	_mult(bb, cc, tmp);
	for(int i=0; i<G; i++)
		a[i] = (a[i] + tmp[i] * 32768LL) % MOD;
	_mult(aa, cc, tmp);
	for(int i=0; i<G; i++)
		a[i] = (a[i] + tmp[i] * (1LL<<30)) % MOD;
}

void pre()
{
	for(int i=0; i<MAXN; i++)
		D[i] = 0;
	D[0] = 1;
	for(int i=1; i<MAXN and i<=N; i++)
	{
		D[i] = D[i-1] * (N-i+1) % MOD;
		D[i] = D[i] * linv(i) % MOD;
	}
	for(int i=0; i<MAXN and i<=N; i++)
	{
		D[i] = D[i] * lpow(P, i) % MOD;
		D[i] = D[i] * lpow(100-P, N-i) % MOD;
	}

	for(int i=0; i<MAXN; i++)
		dp[i] = false;
	dp[0] = true;

	for(int i=0; i<M; i++)
	{
		int c = coin[i];
		for(int j=0; j+c<MAXN; j++)
			dp[j+c] |= dp[j];
	}
}

ll calc()
{
	pre();

	G = coin[0];
	for(int i=1; i<M; i++)
		G = __gcd(G, coin[i]);
	NN = (4 << __lg(G));
//	cout<<"G = "<<G<<", NN = "<<NN<<endl;

	for(int i=0; i<G; i++)
		lret[i] = lcur[i] = 0;

	lret[0] = 1;
	lcur[0] = 100-P;
	lcur[1] = P;

	int n = N;
	while(n)
	{
		if(n&1)
			mult(lret, lcur);
		mult(lcur, lcur);
		n >>= 1;
	}

	ll ans = 0;
	for(int i=1; i<G; i++)
	{
		ans += (G-i) * lret[i];
		ans %= MOD;
	}

	int lastok = MAXN;
	while(lastok % G != 0) lastok++;
	for(int i=MAXN-1; i>=0; i--)
	{
		if(dp[i])
			lastok = i;
		ll dif = (lastok - i) - ((i%G==0) ? 0 : G-(i%G));
		ans = (ans + dif * D[i]) % MOD;
	}

	/*ans = 0;
	lastok = MAXN;
	for(int i=MAXN-1; i>=0; i--)
	{
		if(dp[i])
			lastok = i;
		ll extra = lastok - i;
		ans += extra * D[i];
	}*/

	ans %= MOD;
	if(ans < 0) ans += MOD;

	return ans;
}

int main() {
	IOS;

	pre_fft();

	int T;
	cin>>T;
	for(int t=1; t<=T; t++)
	{
		cin>>N>>M>>P;
		for(int i=0; i<M; i++)
			cin>>coin[i];

		ll ans = calc();
		cout<<"Case #"<<t<<": "<<ans<<endl;
	}

	return 0;
}

