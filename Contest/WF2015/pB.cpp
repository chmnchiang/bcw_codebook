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
typedef pair<ld, ld> pdd;

const int MAXN = 105;
const ld INF = 1E20;
const pdd BAD = {123456789, 382659382};
const ld EPS = 1E-9;

pdd operator+(pdd a, pdd b){return {a.F+b.F, a.S+b.S};}
pdd operator-(pdd a, pdd b){return {a.F-b.F, a.S-b.S};}
pdd operator*(pdd a, ld b){return {a.F*b, a.S*b};}
ld dot(pdd a, pdd b){return a.F*b.F+a.S*b.S;}
ld cross(pdd a, pdd b){return a.F*b.S-a.S*b.F;}
ld abs(pdd a){return sqrt(dot(a, a));}
pdd norm(pdd a){return a * (1.l / abs(a));}

int N, M;
pdd pt[MAXN], qt[MAXN];
pdd V;
ld Va;

pdd interPnt(pdd p1, pdd p2, pdd q1, pdd q2){
	double f1 = cross(p2 - p1, q1 - p1);
	double f2 = cross(p2 - p1, p1 - q2);
	double f = (f1 + f2);

	if(f < 0)
	{
		f = -f;
		f1 = -f1;
		f2 = -f2;
	}

	if(f < EPS) return BAD;

	if(f1 < -EPS or f2 < -EPS) return BAD;
	pdd res = q1 * (f2 / f) + q2 * (f1 / f);

	pdd d = p2 - p1;
	ld t = dot(res - p1, d) / dot(d, d);
	if(t < -EPS or t > 1+EPS) return BAD;

	return res;
}

ld area(vector<pdd> &poly)
{
	ld res = 0;
	int n = poly.size();
	for(int i=0; i<n; i++)
	{
		int ii = (i+1) % n;
		res += cross(poly[i], poly[ii]);
	}
	return res / 2;
}

bool inPoly(vector<pdd> &poly, pdd p)
{
	int n = poly.size();
	for(int i=0; i<n; i++)
	{
		pdd p1 = poly[i], p2 = poly[(i+1)%n];
		pdd d = p2 - p1;
		if(cross(d, p - p1) < -EPS)
			return false;
	}

	return true;
}
double cross(pdd o, pdd a, pdd b){
  return cross(a-o, b-o);
}
vector<pdd> convex_hull(vector<pdd> ppt){
  sort(ppt.begin(),ppt.end());
  int top=0;
  vector<pdd> stk(2*ppt.size());
  for (int i=0; i<(int)ppt.size(); i++){
    while (top >= 2 && cross(stk[top-2],stk[top-1],ppt[i]) <= 0)
      top--;
    stk[top++] = ppt[i];
  }
  for (int i=ppt.size()-2, t=top+1; i>=0; i--){
    while (top >= t && cross(stk[top-2],stk[top-1],ppt[i]) <= 0)
      top--;
    stk[top++] = ppt[i];
  }
  stk.resize(top-1);
  return stk;
}

ld interPoly(vector<pdd> &poly1, vector<pdd> &poly2)
{
	int n = poly1.size(), m = poly2.size();
	vector<pdd> vpt;

	for(int i=0; i<n; i++)
		vpt.PB(poly1[i]);
	for(int i=0; i<m; i++)
		vpt.PB(poly2[i]);

	for(int i=0; i<n; i++)
	{
		int ii = (i+1) % n;
		for(int j=0; j<m; j++)
		{
			int jj = (j + 1) % m;
			pdd ppt = interPnt(poly1[i], poly1[ii], poly2[j], poly2[jj]);
			if(ppt != BAD)
				vpt.PB(ppt);
		}
	}

	vector<pdd> vgood;
	for(auto p: vpt)
		if(inPoly(poly1, p) and inPoly(poly2, p))
			vgood.PB(p);

	sort(ALL(vgood));
	vector<pdd> cvx = convex_hull(vgood);
	ld a = area(cvx);
	return a;
}

ld eval(ld t)
{
	vector<pdd> v1, v2;
	for(int i=0; i<N; i++)
		v1.PB(pt[i]);
	for(int i=0; i<M; i++)
		v2.PB(qt[i] + V * t);

	return interPoly(v1, v2);
}

ld calc()
{
	Va = abs(V);
	V = V * (1. / Va);
	reverse(pt, pt+N);
	reverse(qt, qt+M);
	pt[N] = pt[0];
	qt[M] = qt[0];

	vector<ld> vt;

	for(int i=0; i<N; i++)
	{
		for(int j=0; j<M; j++)
		{
			pdd r = interPnt(qt[j], qt[j] + V * 1e5, pt[i], pt[i+1]);
			if(r != BAD)
			{
				ld t = dot(r - qt[j], V);
				vt.PB(t);
			}

			r = interPnt(pt[i], pt[i] - V * 1e5, qt[j], qt[j+1]);
			if(r != BAD)
			{
				ld t = dot(r - pt[i], V);
				vt.PB(-t);
			}
		}
	}

	sort(ALL(vt));

	ld ans = -INF, val = -1;

	for(auto x: vt)
	{
		ld ev = eval(x);
		if(ev > val + EPS)
		{
			val = ev;
			ans = x / Va;
		}
//		cout<<x/Va<<" : "<<eval(x)<<endl;
	}

	for(int i=0; i<SZ(vt)-1; i++)
	{
		ld lb = vt[i], rb = vt[i+1];
		ld lv = eval(lb), rv = eval(rb);
		for(int j=0; j<50; j++)
		{
			ld m1 = (2*lb+rb) / 3., m2 = (lb+2*rb) / 3.;
			ld m1v = eval(m1), m2v = eval(m2);
			if(m1v > m2v)
			{
				rb = m2;
				rv = m2v;
			}
			else
			{
				lb = m1;
				lv = m1v;
			}
		}
		if(lv > val + EPS)
		{
			val = lv;
			ans = lb / Va;
		}
	}

	return ans;
}

int main() {
	IOS;

	cin>>N;
	for(int i=0; i<N; i++)
		cin>>pt[i].F>>pt[i].S;
	ld vx, vy;
	cin>>vx>>vy;
	V.F -= vx;
	V.S -= vy;

	cin>>M;
	for(int i=0; i<M; i++)
		cin>>qt[i].F>>qt[i].S;
	cin>>vx>>vy;
	V.F += vx;
	V.S += vy;

	ld res = calc();
	if(res == -INF) cout<<"never"<<endl;
	else cout<<fixed<<setprecision(10)<<res<<endl;

	return 0;
}

