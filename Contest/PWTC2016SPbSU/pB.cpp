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

typedef long double ld;
typedef long long ll;
typedef pair<ld, ld> pdd;

const int MAXN = 131072;
const ld PI = acosl(-1);

pdd operator+(pdd a, pdd b){return {a.F+b.F, a.S+b.S};}
pdd operator-(pdd a, pdd b){return {a.F-b.F, a.S-b.S};}
ld dot(pdd a, pdd b){return a.F*b.F+a.S*b.S;}
ld cross(pdd a, pdd b){return a.F*b.S-a.S*b.F;}
pdd unit(ld th){return {cosl(th), sinl(th)};}

int N;
pdd pt[MAXN];
ld prj[MAXN];
int ord[MAXN];
int BIT[MAXN];

void initBIT()
{
	FZ(BIT);
}

void addBIT(int pos, int val)
{
	pos++;
	while(pos < MAXN)
	{
		BIT[pos] += val;
		pos += pos&(-pos);
	}
}

int qryBIT(int pos)
{
	int res = 0;
	pos++;
	while(pos)
	{
		res += BIT[pos];
		pos -= pos&(-pos);
	}
	return res;
}

bool cmp(pdd a, pdd b)
{
	if(a.S == b.S) return a.F < b.F;
	return a.S < b.S;
}

bool cmp2(int a, int b)
{
	return prj[a] < prj[b];
}

ll count_less(ld th)
{
	pdd d = unit(th - PI/2);
	for(int i=0; i<N; i++)
		prj[i] = dot(d, pt[i]);
	sort(ord, ord+N, cmp2);

	initBIT();
	ll res = 0;
	for(int i=0; i<N; i++)
	{
		res += qryBIT(ord[i]);
		addBIT(ord[i], 1);
	}

	return res;
}

ld calc_kth(ll K)
{
	ld lb = 0, rb = PI;
	for(int i=0; i<80; i++)
	{
		ld mb = (lb + rb) / 2;
		if(count_less(mb) > K)
			rb = mb;
		else
			lb = mb;
	}
	return lb;
}

ld calc()
{
	for(int i=0; i<N; i++)
		ord[i] = i;
	sort(pt, pt+N, cmp);

	ll total = (ll)N * (N-1) / 2;
	ld ans = 0;
	if(total%2)
		ans = calc_kth(total/2);
	else
		ans = (calc_kth(total/2-1) + calc_kth(total/2)) / 2;

	return ans;
}

int main() {
	IOS;

	cin>>N;
	for(int i=0; i<N; i++)
		cin>>pt[i].F>>pt[i].S;

	ld ans = calc();
	cout<<fixed<<setprecision(12)<<ans<<endl;

	return 0;
}
