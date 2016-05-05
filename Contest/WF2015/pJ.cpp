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

const int MAXN = 1048576;

typedef long double ld;
typedef complex<ld> cplx;
const ld PI = acosl(-1);
const cplx I(0, 1);

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

int N;
ll fact[MAXN];
cplx arr[MAXN];
ll num[MAXN];

void pre()
{
	for(int i=1; i<MAXN/2; i++)
	{
		for(int j=i; j<MAXN/2; j+=i)
			fact[j]++;
	}

	pre_fft();
	for(int i=0; i<MAXN/2; i++)
		arr[i] = fact[i];
	fft(MAXN, arr);
	for(int i=0; i<MAXN; i++)
		arr[i] *= arr[i];
	fft(MAXN, arr, true);

	for(int i=0; i<MAXN/2; i++)
		num[i] = arr[i].real() + 0.5;
}

int main() {
	IOS;

	pre();

	cin>>N;
	for(int i=0; i<N; i++)
	{
		int al, ar;
		cin>>al>>ar;
		int best = -1, val = -1;
		for(int j=al; j<=ar; j++)
		{
			if(num[j] > val)
			{
				val = num[j];
				best = j;
			}
		}
		cout<<best<<" "<<val<<"\n";
	}

	return 0;
}

