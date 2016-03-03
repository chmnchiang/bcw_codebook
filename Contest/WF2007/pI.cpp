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

const int MAXN = 20;
const ld G = 0.097;

int N;
ld h[MAXN], f[MAXN], a[MAXN];
ld A, V, Pb;

ld solve(ld lim, ld alpha, ld beta, ld lb, ld rb)
{
	for(int i=0; i<100; i++)
	{
		ld mb = (lb + rb) / 2;
		ld p = G * min(lim, mb) + alpha / (beta - mb);
		if(p >= Pb)
			rb = mb;
		else
			lb = mb;
	}
	return (lb + rb) / 2;
}

ld calc()
{
	ld ans = h[0];
	Pb = 1 + G * h[0];
	V = 0;
	for(int i=1; i<N; i++)
		V += h[i];
	A = V - f[0];

	for(int i=1; i<N; i++)
	{
		if(i < N-1)
		{
			ld pfin = G * f[i] + A / (V - 2 * f[i]);
			if(pfin >= Pb)
			{
				ans += solve(f[i], A, V, f[i-1], 2*f[i]);
				break;
			}
			else
			{
				a[i] = A * (h[i] - f[i]) / (V - 2 * f[i]);
				A -= a[i];
				V -= h[i];
				ans += solve(h[i], a[i], h[i], f[i], h[i]);
			}
		}
		else
		{
			ans += solve(h[i], A, h[i], f[i-1], h[i]);
		}
	}

	return ans;
}

int main() {
    IOS;

	int t = 0;
	while(~scanf("%d", &N) && N)
	{
		t++;
		for(int i=0; i<N; i++)
			scanf("%lf", &h[i]);
		for(int i=0; i<N-1; i++)
			scanf("%lf", &f[i]);

		ld ans = calc();
		printf("Case %d: %.3f\n\n", t, ans);
	}

    return 0;
}

