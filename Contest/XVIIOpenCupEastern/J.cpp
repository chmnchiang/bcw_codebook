#pragma GCC optimize ("O2")
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
typedef vector<pdd> Segs;

const int MAXN = 1010;
const ld PI = acosl(-1);
const ld EPS = 1E-14;

pdd operator+(pdd a, pdd b){return {a.F+b.F, a.S+b.S};}
pdd operator-(pdd a, pdd b){return {a.F-b.F, a.S-b.S};}
pdd operator*(pdd a, ld b){return {a.F*b, a.S*b};}
ld dot(pdd a, pdd b){return a.F*b.F+a.S*b.S;}
ld cross(pdd a, pdd b){return a.F*b.S-a.S*b.F;}
ld cross(pdd a, pdd b, pdd o){return cross(a-o, b-o);}
ld abs(pdd a){return sqrt(dot(a, a));}
ld ang(pdd a){return atan2(a.S, a.F);}
ld reg(ld th)
{
	while(th < -PI) th += 2*PI;
	while(th >= PI) th -= 2*PI;
	return th;
}

inline void AddSeg(Segs &vec, ld lb, ld rb)
{
	lb = reg(lb);
	rb = reg(rb);
	if(lb < rb) vec.PB({lb, rb});
	else
	{
		vec.PB({-PI, rb});
		vec.PB({lb, PI});
	}
}

Segs Reg(const Segs &vec)
{
	Segs ret;
	for(auto p: vec)
		if(p.S - p.F > EPS)
			ret.PB(p);
	sort(ALL(ret));
	return ret;
}

Segs Reverse(const Segs &vec)
{
	Segs ret;
	for(auto p: vec)
		ret.PB({-p.S, -p.F});
	reverse(ALL(ret));
	return ret;
}

Segs Rotate(const Segs &vec, ld th)
{
	Segs ret;
	for(auto p: vec)
	{
		if(p.S - p.F > 2 * PI - EPS)
			ret.PB(p);
		else
			AddSeg(ret, reg(p.F+th), reg(p.S+th));
	}
	return Reg(ret);
}

Segs Compl(const Segs &vec)
{
	int S = SZ(vec);
	Segs ret;
	if(S > 0)
	{
		ret.PB({-PI, vec[0].F});
		ret.PB({vec.back().S, PI});
		for(int i=0; i<S-1; i++)
			ret.PB({vec[i].S, vec[i+1].F});
		return Reg(ret);
	}
	else
	{
		return {{-PI, PI}};
	}
}

Segs Union(const vector<Segs> &vv)
{
	Segs ss, ret;
	for(auto x: vv)
		for(auto y: x)
			ss.PB(y);
	sort(ALL(ss));

	ld rb = -10;
	for(auto p: ss)
	{
		if(p.F > rb)
			ret.PB(p);
		else
			ret.back().S = max(ret.back().S, p.S);
		rb = max(rb, p.S);
	}

	return ret;
}

Segs Intersection(const vector<Segs> &vv)
{
	vector<Segs> v2;
	for(auto x: vv)
		v2.PB(Compl(x));
	Segs s = Union(v2);
	return Compl(s);
}

Segs good_interval(pdd x, pdd y, pdd p)
{
	//cout<<"Good "<<x<<" "<<y<<" "<<p<<endl;
	pdd d = y - x;
	ld da = abs(d), pa = abs(p);
	if(da < EPS) return {};

	ld r = abs(cross(x, y)) / da;
	if(pa <= r) return {{-PI, PI}};

	ld phi = ang(d) - PI/2;
	ld th = ang(p);
	ld lb = ang(x), rb = ang(y);
	ld alpha = acos(r / pa);

	vector<Segs> vv;
	vv.resize(2);
	//cout<<alpha<<" CEN "<<phi-th<<endl;
	AddSeg(vv[0], phi-th+alpha, phi-th-alpha);
	AddSeg(vv[1], lb-th, rb-th);

	//cout<<vv[0]<<" / "<<vv[1]<<endl;
	Segs ret = Intersection(vv);

	return ret;
}

int N, M;
ld L;
pdd pt[MAXN];

vector<pdd> convex_hull(vector<pdd> ptt){
  sort(ptt.begin(),ptt.end());
  int top=0;
  vector<pdd> stk(2*ptt.size());
  for (int i=0; i<(int)ptt.size(); i++){
    while (top >= 2 && cross(stk[top-1],ptt[i],stk[top-2]) <= 0)
      top--;
    stk[top++] = ptt[i];
  }
  for (int i=ptt.size()-2, t=top+1; i>=0; i--){
    while (top >= t && cross(stk[top-1],ptt[i], stk[top-2]) <= 0)
      top--;
    stk[top++] = ptt[i];
  }
  stk.resize(top-1);
  return stk;
}

bool calc()
{
	vector<pdd> vpt;
	for(int i=0; i<N; i++)
		vpt.PB(pt[i]);
	vpt = convex_hull(vpt);
	M = SZ(vpt);

	//cout<<"CVX "<<vpt<<endl;

	vector<Segs> vint;

	for(int i=0; i<M; i++)
	{
		Segs s[6];
		s[0] = good_interval({0, sqrt(3) * L}, {-3 * L / 2, -sqrt(3) * L / 2}, vpt[i]);
		//cout<<s[0]<<endl;
		for(int j=1; j<6; j++)
			s[j] = Rotate(s[0], 2 * PI * j / 6);
		vector<Segs> vs;
		for(int j=0; j<6; j++)
			vs.PB(s[j]);

		Segs ss = Union(vs);

		vint.PB(ss);
	}


	for(int i=0; i<M; i++)
	{
		pdd x = vpt[i], y = vpt[(i+1)%M];
		Segs s[6];
		s[0] = Reverse(Compl(good_interval(x, y, {L, 0})));
		for(int j=1; j<6; j++)
			s[j] = Rotate(s[0], 2 * PI * j / 6);
		for(int j=0; j<6; j++)
			vint.PB(s[j]);
	}

	Segs sf = Intersection(vint);

	//cout<<"Vint "<<vint<<endl;
	//cout<<"Final "<<sf<<endl;

	return !sf.empty();
}

int main() {
	IOS;

	int T;
	cin>>T;
	while(T--)
	{
		cin>>N>>L;
		L += 1E-8;

		for(int i=0; i<N; i++)
			cin>>pt[i].F>>pt[i].S;
		pt[N++] = {L/2, L/2};
		pt[N++] = {L/2, -L/2};
		pt[N++] = {-L/2, L/2};
		pt[N++] = {-L/2, -L/2};

		bool res = calc();
		cout<<(res ? "Cast" : "Change")<<endl;
	}

	return 0;
}

