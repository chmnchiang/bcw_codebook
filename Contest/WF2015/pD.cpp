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

const int MAXN = 10101;
const double PI = acos(-1);

int N, S;
double pr[MAXN], px[MAXN], py[MAXN], pz[MAXN];
double hei[MAXN], dif[MAXN];

double get_val(double h)
{
	double res = 0;

	for(int i=0; i<N; i++)
	{
		double dz = h - pz[i], r = pr[i];
		if(dz < -r) res += 0;
		else if(dz > r) res += 4. / 3. * PI * r * r * r;
		else res += PI * (2. / 3. * r * r * r + dz * r * r - dz * dz * dz / 3.);
	}

	return 1e4 * h - res;
}

void calc()
{
	double total_vol = 1e6;
	for(int i=0; i<N; i++)
		total_vol -= 4. / 3. * PI * pr[i] * pr[i] * pr[i];

	for(int i=1; i<=S; i++)
	{
		double v = total_vol * i / S;
		double lb = 0, rb = 100;
		for(int j=0; j<100; j++)
		{
			if(rb - lb < 1E-12) break;
			double mb = (lb + rb) / 2;
			double val = get_val(mb);
			if(val > v)
				rb = mb;
			else
				lb = mb;
		}
		hei[i] = rb;
		dif[i] = hei[i] - hei[i-1]; }
}

int main() {
	IOS;
	cin>>N>>S;
	for(int i=0; i<N; i++)
	{
		cin>>pr[i]>>px[i]>>py[i]>>pz[i];
		pr[i] /= 1e3;
		px[i] /= 1e3;
		py[i] /= 1e3;
		pz[i] /= 1e3;
	}

	calc();

	cout<<fixed<<setprecision(10);
	for(int i=1; i<=S; i++)
		cout<<dif[i]<<endl;

	return 0;
}

