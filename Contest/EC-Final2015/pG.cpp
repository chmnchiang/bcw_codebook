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


typedef double ld;
typedef complex<ld> cplx;
typedef long long ll;

const int MAXN = 65536;
const int MAXD = 204;
const ld PI = acosl(-1);
const cplx I(0, 1);
const ld EPS = 1E-9;

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

int N, Q, K, W;
vector<int> edge[MAXD];
int w[MAXD];
ld p[MAXD];
ld total_cnt;
cplx total_prob[MAXN];
ld cnt[MAXD];
cplx dp[MAXD][MAXN];
ld prob[MAXN], prob_sum[MAXN];
ld comb[MAXD][MAXD];
ld kase[MAXN];

void dfs(int v, int par)
{
	for(int i=0; i<MAXN; i++)
		dp[v][i] = (1 - p[v]) + p[v] * omega[((ll)i * w[v]) % MAXN];
	cnt[v] = 1;

	for(auto u: edge[v])
	{
		if(u == par) continue;
		dfs(u, v);

		cnt[v] *= cnt[u];
		for(int i=0; i<MAXN; i++)
			dp[v][i] *= dp[u][i];
	}

	total_cnt += cnt[v];
	for(int i=0; i<MAXN; i++)
		total_prob[i] += dp[v][i];

	cnt[v] += 1;
	for(int i=0; i<MAXN; i++)
		dp[v][i] += 1;
}

void pre()
{
	pre_fft();
	comb[0][0] = 1;
	for(int i=1; i<MAXD; i++)
	{
		comb[i][0] = comb[i][i] = 1;
		for(int j=1; j<i; j++)
			comb[i][j] = comb[i-1][j-1] + comb[i-1][j];
	}
}

ld calc()
{
	W = 0;
	for(int i=0; i<N; i++)
		W += w[i];

	total_cnt = 0;
	FZ(total_prob);
	dfs(0, 0);

	for(int i=0; i<MAXN; i++)
		total_prob[i] /= total_cnt;
	fft(MAXN, total_prob, true);

	prob_sum[0] = 0;
	for(int i=0; i<=W+1; i++)
	{
		prob[i] = total_prob[i].real();
		prob_sum[i+1] = prob_sum[i] + prob[i];
	}

	for(int x=0; x<=W+1; x++)
	{
		kase[x] = 0;
		ld P = prob_sum[x];
		ld p1 = 1, p2 = pow(1-P, Q);
		for(int i=0; i<=K-1; i++)
		{
			kase[x] += comb[Q][i] * p1 * p2;
			p1 *= P;
			if(1-P > EPS)
				p2 /= 1-P;
		}
	}

	ld ans = 0;
	for(int x=0; x<=W; x++)
		ans += x * (kase[x] - kase[x+1]);
	
	return ans;
}

int main() {
	IOS;

	pre();

	int T;
	cin>>T;
	for(int t=1; t<=T; t++)
	{
		cin>>N>>Q>>K;
		for(int i=0; i<N; i++)
			edge[i].clear();
		for(int i=0; i<N-1; i++)
		{
			int u, v;
			cin>>u>>v;
			u--; v--;
			edge[u].PB(v);
			edge[v].PB(u);
		}
		for(int i=0; i<N; i++)
			cin>>w[i];
		for(int i=0; i<N; i++)
		{
			cin>>p[i];
			p[i] /= 100.;
		}

		ld ans = calc();
		cout<<"Case #"<<t<<": "<<fixed<<setprecision(10)<<ans<<endl;
	}

	pre_fft();


	return 0;
}

