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
typedef pair<ld, ld> pdd;

const ld PI = acosl(-1);
const ld INF = 1E20;
const ld EPS = 1E-12;

pdd operator+(pdd a, pdd b){return {a.F+b.F, a.S+b.S};}
pdd operator-(pdd a, pdd b){return {a.F-b.F, a.S-b.S};}
pdd operator*(pdd a, ld b){return {a.F*b, a.S*b};}
ld dot(pdd a, pdd b){return a.F*b.F+a.S*b.S;}
ld cross(pdd a, pdd b){return a.F*b.S-a.S*b.F;}
ld abs(pdd a){return sqrtl(dot(a, a));}
ld theta(pdd a){return atan2l(a.S, a.F);}
ld delta(ld a, ld b)
{
	ld d = fabsl(a - b);
	while(d >= PI) d -= 2*PI;
	return fabsl(d);
}

pdd P, Q, O;
ld R;

ld eval(pdd x)
{
	ld r = abs(x);
	if(r < R) return INF;
	return abs(x-P) + abs(x-Q) + r - R;
}

ld randf()
{
	ld r = rand() / (ld)RAND_MAX;
	return 2 * r - 1;
}

pdd rp()
{
	return {randf(), randf()};
}

ld calc()
{
	P = P - O;
	Q = Q - O;

	pdd d = Q - P;
	ld da = abs(d);
	pdd dh = d * (1 / da);
	ld t = fabsl(cross(P, dh));
	ld pa = abs(P), qa = abs(Q);

	if(t >= R || dot(d, P) * dot(d, Q) > 0)
	{
		pdd cur = P;
		ld curcost = eval(cur);
		ld step = 1E6;
		while(step > EPS)
		{
			pdd np = cur + rp() * step;
			ld nc = eval(np);
			if(nc < curcost)
			{
				curcost = nc;
				cur = np;
			}
			step *= 0.99999;
		}

//		cout<<cur<<endl;
		return curcost;
	}

	ld ans = 0;

	ld pth = theta(P), qth = theta(Q);
	ld fp = sqrtl(pa * pa - R * R), fq = sqrtl(qa * qa - R * R);
	ld phip = acosl(R / pa), phiq = acosl(R / qa);
	ld pp = pth + phip, pm = pth - phip;
	ld qp = qth + phiq, qm = qth - phiq;
	ld tdis = 2*PI;
	tdis = min(tdis, delta(pp, qp));
	tdis = min(tdis, delta(pp, qm));
	tdis = min(tdis, delta(pm, qp));
	tdis = min(tdis, delta(pm, qm));
	ld arc = tdis * R;

	ans = fp + arc + fq;

	return ans;
}

int main() {
	IOS;
	cin>>P.F>>P.S>>Q.F>>Q.S>>O.F>>O.S>>R;

	ld ans = calc();
	cout<<fixed<<setprecision(10)<<ans<<endl;

	return 0;
}

