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
#define loop(i, a, b) for (auto (i)=(a); (i) != (b); (i) += ((b) < (a) ? -1 : 1))

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pll;

const int MAXN = 101010;

pll operator+(pll a, pll b){return {a.F+b.F, a.S+b.S};}
pll operator-(pll a, pll b){return {a.F-b.F, a.S-b.S};}
ll dot(pll a, pll b){return a.F*b.F+a.S*b.S;}
ll cross(pll a, pll b){return a.F*b.S-a.S*b.F;}
ld angle(pll a){return atan2l(a.S, a.F);}

int N, M;
vector<pll> poly[MAXN];
vector<ld> theta[MAXN];
int ord[MAXN];
ll area[MAXN], darea[MAXN];
pll query[MAXN];
bool used[MAXN];

bool cmp(int a, int b){return area[a] < area[b];}

bool in_poly(vector<pll> &vec, vector<ld> &vth, pll pt)
{
	int K = vec.size();
	ld th = angle(pt);
	int idx = lower_bound(ALL(vth), th) - vth.begin();
	if(idx == 0) idx = K;

	pll p1 = vec[idx-1], p2 = vec[idx%K];
	return cross(p2-p1, pt-p1) >= 0;
}

bool check_in(pll pt, int m)
{
	if(m == N) return true;
	return in_poly(poly[ord[m]], theta[ord[m]], pt);
}

ll calc()
{
	for(int i=0; i<N; i++)
	{
		int k = poly[i].size();
		area[i] = 0;
		for(int j=0; j<k; j++)
		{
			int y = (j+1) % k;
			area[i] += cross(poly[i][j], poly[i][y]);
		}

		ld minth = 1E3;
		int minidx = -1;
		for(int j=0; j<k; j++)
		{
			ld th = angle(poly[i][j]);
			theta[i].PB(th);
			if(th < minth)
			{
				minth = th;
				minidx = j;
			}
		}

		vector<pll> npoly;
		vector<ld> ntheta;
		for(int j=minidx; j<k; j++)
		{
			npoly.PB(poly[i][j]);
			ntheta.PB(theta[i][j]);
		}
		for(int j=0; j<minidx; j++)
		{
			npoly.PB(poly[i][j]);
			ntheta.PB(theta[i][j]);
		}
		poly[i] = npoly;
		theta[i] = ntheta;
//		cout<<npoly<<endl;		cout<<ntheta<<endl;
	}

	for(int i=0; i<N; i++)
		ord[i] = i;
	sort(ord, ord+N, cmp);

	darea[0] = area[ord[0]];
	for(int i=1; i<N; i++)
		darea[i] = area[ord[i]] - area[ord[i-1]];

	for(int i=0; i<M; i++)
	{
		int lb = 0, rb = N;
		while(lb < rb)
		{
			int mb = (lb + rb) / 2;
			if(check_in(query[i], mb))
				rb = mb;
			else
				lb = mb + 1;
		}

//		cout<<query[i]<<" : "<<lb<<endl;
		if(lb < N)
			used[lb] = true;
	}

	ll ans = 0;
	for(int i=0; i<N; i++)
		if(used[i])
			ans += darea[i];

	return ans;
}

int main() {
	IOS;
	FILEIO("castle");

	cin>>N;
	for(int i=0; i<N; i++)
	{
		int k;
		cin>>k;
		poly[i].resize(k);
		for(int j=0; j<k; j++)
			cin>>poly[i][j].F>>poly[i][j].S;
	}
	cin>>M;
	for(int i=0; i<M; i++)
		cin>>query[i].F>>query[i].S;

	ll ans = calc();
	ld rans = ans / 2.l;
	cout<<fixed<<setprecision(10)<<rans<<endl;

	return 0;
}
