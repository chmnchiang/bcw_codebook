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
const ld EPS = 1E-10;
const pdd BAD = {INF, INF};

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
ld reg(ld x)
{
	while(x < -PI) x += 2*PI;
	while(x >= PI) x -= 2*PI;
	return x;
}
pdd unit(ld x)
{
	return {cosl(x), sinl(x)};
}

pdd A, B, C;
ld TH1, TH2;

vector<pdd> interCircle(pdd o1, double r1, pdd o2, double r2) {
  ld d2 = dot(o1 - o2, o1 - o2);
  ld d = sqrt(d2);
	if (d > r1+r2) return {};
  pdd u = (o1+o2)*0.5 + (o1-o2)*((r2*r2-r1*r1)/(2*d2));
  double AX = sqrt((r1+r2+d) * (r1-r2+d) * (r1+r2-d) * (-r1+r2+d));
  pdd v = pdd(o1.S-o2.S, -o1.F+o2.F) * (AX / (2*d2));
  return {u+v, u-v};
}

void calc_O(pdd P, pdd Q, ld th, pdd &o1, pdd &o2)
{
	pdd d = Q - P;
	ld da = abs(d);
	pdd dh = d * (1 / da);
	pdd hh = {-dh.S, dh.F};

	pdd M = P + d * 0.5;
	ld ha = da / 2 * cosl(th) / sinl(th);
	pdd h = hh * ha;
	o1 = M + h;
	o2 = M - h;
}

bool check_pt(pdd x)
{
	if(abs(x-A) < EPS) return false;
	if(abs(x-B) < EPS) return false;
	if(abs(x-C) < EPS) return false;
	ld thA = theta(A-x);
	ld thB = theta(B-x);
	ld thC = theta(C-x);
	ld d1 = delta(thA, thB);
	ld d2 = delta(thB, thC);
	if(abs(d1 - TH1) > EPS) return false;
	if(abs(d2 - TH2) > EPS) return false;
	return true;
}

pdd check(pdd O1, pdd O2)
{
	ld R1 = abs(O1 - B);
	ld R2 = abs(O2 - B);

	if(abs(O1 - O2) < EPS)
	{
		if(abs(R1 - R2) < EPS)
		{
			vector<ld> vth;
			ld thA = theta(A-O1);
			ld thB = theta(B-O1);
			ld thC = theta(C-O1);
			vth.PB(thA);
			vth.PB(thB);
			vth.PB(thC);
			vth.PB(thA+2*PI);
			vth.PB(thB+2*PI);
			vth.PB(thC+2*PI);
			for(int i=0; i<6; i++)
				for(int j=i+1; j<6; j++)
					vth.PB((vth[i]+vth[j])/2);

			for(int i=0; i<(int)vth.size(); i++)
				vth[i] = reg(vth[i]);

			for(auto t: vth)
			{
				pdd q = O1 + unit(t) * R1;
				if(check_pt(q))
					return q;
			}
		}
	}
	else
	{
		vector<pdd> vec = interCircle(O1, R1, O2, R2);
		for(auto p: vec)
			if(check_pt(p))
				return p;
	}

	return BAD;
}

pdd calc()
{
	TH1 *= PI / 180;
	TH2 *= PI / 180;

	pdd O11, O12, O21, O22;
	calc_O(A, B, TH1, O11, O12);
	calc_O(B, C, TH2, O21, O22);

	pdd res = check(O11, O21);
	if(res != BAD) return res;
	res = check(O12, O21);
	if(res != BAD) return res;
	res = check(O11, O22);
	if(res != BAD) return res;
	res = check(O12, O22);
	if(res != BAD) return res;

	assert(false);
}

int main() {
	IOS;

	int T;
	cin>>T;
	while(T--)
	{
		cin>>A.F>>A.S>>B.F>>B.S>>C.F>>C.S>>TH1>>TH2;
		pdd ans = calc();
		cout<<fixed<<setprecision(12)<<ans.F<<" "<<ans.S<<"\n";
	}

	return 0;
}

