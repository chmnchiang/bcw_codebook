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

typedef long long ll;

const int MAXN = 1010;

ll N, D;
ll M;

ll num[MAXN];

void calc()
{
	ll alpha = (M-N) / D;
	ll beta = (N+D-1) / D;
	ll r = beta * D - N;

	ll p = alpha % N;
	ll g = __gcd(beta, N);
	ll ng = N / g;
	ll c = beta * ng;
	ll k = alpha / c;

	for(int i=0; i<N; i++)
		num[i] = 1;
	num[p] += M - alpha * D - N;

	alpha %= c;
	alpha /= beta;

	for(int i=0; i<N; i++)
		num[i] += ng * k;
	for(int i=0; i<ng; i++)
		num[(p+i*g)%N] += r * k;

	for(int i=0; i<alpha; i++)
	{
		p = (p + N - beta) % N;
		for(int j=0; j<N; j++)
			num[j] += 1;
		num[p] += r;
	}
}

int main() {
	FILEIO("coins");
	IOS;

	cin>>N>>M>>D;

	calc();
	for(int i=0; i<N; i++)
		cout<<num[i]<<(i==N-1 ? "\n" : " ");

    return 0;
}
