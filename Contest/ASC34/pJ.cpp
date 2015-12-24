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

typedef long double ld;
typedef pair<ld, ld> pdd;
typedef pair<ld, int> pdi;

pdd operator+(pdd a, pdd b) {return {a.F+b.F, a.S+b.S};}
pdd operator-(pdd a, pdd b) {return {a.F-b.F, a.S-b.S};}
pdd operator*(pdd a, ld b) {return {a.F*b, a.S*b};}
ld cross(pdd a, pdd b) {return a.F*b.S-a.S*b.F;}
ld dot(pdd a, pdd b) {return a.F*b.F+a.S*b.S;}
ld abs(pdd a)	{return sqrtl(dot(a, a));}

const int MAXN = 128;
const ld INF = 1E20;
const ld EPS = 1E-14;
const ld TEPS = 1E-9;
const ld PI = acosl(-1);

int N, M;
pdd pr[MAXN], pb[MAXN];

bool has_ans = false;
pdd C;
ld R;

ld reg(ld th)
{
	while(th >= PI) th -= 2*PI;
	while(th < -PI) th += 2*PI;
	return th;
}

ld getth(pdd p1, pdd p2, pdd x)
{
	ld th1 = atan2l(p2.S-x.S, p2.F-x.F);
	ld th2 = atan2l(p1.S-x.S, p1.F-x.F);
	return reg(th2 - th1);
}

void calc()
{
	for(int i=0; i<N; i++)
	{
		for(int j=i+1; j<N; j++)
		{
			pdd p1 = pr[i], p2 = pr[j];

			ld rmin = 0, rmax = 0;
			ld blmax = -INF, brmin = INF;
			bool fail = false;
			for(int k=0; k<N; k++)
			{
				if(k == i || k == j) continue;
				ld th = getth(p1, p2, pr[k]);
				if(abs(th) < TEPS) fail = true;
				th = reg(th + PI);
				rmin = min(rmin, th);
				rmax = max(rmax, th);
			}
			if(fail) continue;
			for(int k=0; k<M; k++)
			{
				ld th = getth(p1, p2, pb[k]);
				if(abs(th) < TEPS) continue;
				th = reg(th + PI);
//				cout<<k<<" TH "<<th<<endl;
				if(th <= TEPS)
					blmax = max(blmax, th);
				if(th >= -TEPS)
					brmin = min(brmin, th);
			}

			if(blmax > rmin + TEPS) continue;
			if(brmin < rmax - TEPS) continue;
			if(brmin - blmax < PI - TEPS) continue;
			if(rmax - rmin > PI + TEPS) continue;
			if(has_ans) continue;

//			cout<<i<<" "<<j<<endl;
//			cout<<blmax<<"/"<<rmin<<" ~ "<<rmax<<"/"<<brmin<<endl;
			ld thl = max(blmax, rmax-PI);
			ld thr = min(brmin, rmin+PI);
			ld thc = (thl + thr) / 2;
//			cout<<thc<<endl;
			pdd d = p2 - p1;
			ld dl = abs(d);
			d = d * (1. / dl);
			pdd t = {-d.S, d.F};
			pdd cen = (p1 + p2) * 0.5;
			C = cen + t * (dl * 0.5 * tanl(thc));
			R = dl * 0.5 / cosl(thc);

//			cout<<"C "<<C<<" R "<<R<<endl;

//			for(int k=0; k<N; k++)
//				assert(abs(pr[k]-C) < R + TEPS);
//			for(int k=0; k<M; k++)
//				assert(abs(pb[k]-C) > R - TEPS);

			has_ans = true;
		}
	}
}

int main() {
	IOS;
	FILEIO("wall");

	while(cin>>N>>M)
	{
		has_ans = false;
		for(int i=0; i<N; i++)
			cin>>pr[i].F>>pr[i].S;
		for(int i=0; i<M; i++)
			cin>>pb[i].F>>pb[i].S;

		calc();
//		cout<<"SW"<<endl;
		swap(N, M);
		swap(pr, pb);
		calc();

		if(has_ans)
		{
			cout<<"YES"<<endl;
			cout<<fixed<<setprecision(12)<<C.F<<" "<<C.S<<" "<<R<<endl;
		}
		else
		{
			cout<<"NO"<<endl;
		}
	}

    return 0;
}
