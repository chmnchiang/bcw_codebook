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


#define double long double

typedef pair<double, double> pdd;

const double EPS = 1E-10;

pdd operator+(pdd a, pdd b){return {a.F+b.F, a.S+b.S};}
pdd operator-(pdd a, pdd b){return {a.F-b.F, a.S-b.S};}
pdd operator*(pdd a, double b){return {a.F*b, a.S*b};}
double dot(pdd a, pdd b){return a.F*b.F+a.S*b.S;}
double cross(pdd a, pdd b){return a.F*b.S-a.S*b.F;}
double cross(pdd a, pdd b, pdd o){return cross(a-o, b-o);}
double cross2(pdd o, pdd a, pdd b){return cross(a-o, b-o);}
double abs(pdd a){return sqrtl(dot(a, a));}

pdd pt[4], cand[4], ans[4];

vector<pdd> convex_hull(vector<pdd> hongshihaoma){
  sort(hongshihaoma.begin(),hongshihaoma.end());
  int top=0;
  vector<pdd> stk(2*hongshihaoma.size());
  for (int i=0; i<(int)hongshihaoma.size(); i++){
    while (top >= 2 && cross2(stk[top-2],stk[top-1],hongshihaoma[i]) <= 0)
      top--;
    stk[top++] = hongshihaoma[i];
  }
  for (int i=hongshihaoma.size()-2, t=top+1; i>=0; i--){
    while (top >= t && cross2(stk[top-2],stk[top-1],hongshihaoma[i]) <= 0)
      top--;
    stk[top++] = hongshihaoma[i];
  }
  stk.resize(top-1);
  return stk;
}

pdd interPnt(pdd p1, pdd p2, pdd q1, pdd q2, bool res=false){
	double f1 = cross(p2, q1, p1);
	double f2 = -cross(p2, q2, p1);
	double f = (f1 + f2);

	if(fabs(f) < EPS) {
		res = false;
		return {};
    }

	res = true;
	return q1 * (f2 / f) + q2 * (f1 / f);
}

bool check()
{
	for(int i=0; i<4; i++)
	{
		int j = (i+1) % 4;
		int k = (i+2) % 4;
		assert(abs(dot(cand[i]-cand[j], cand[k]-cand[j])) < EPS);
		assert(abs(abs(cand[i]-cand[j]) - abs(cand[j]-cand[k])) < EPS);
	}

	if(abs(cand[0]-cand[1]) < EPS) return false;

	for(int i=0; i<4; i++)
	{
		pdd p1 = cand[i], p2 = cand[(i+3)%4];
		pdd dp = p2 - p1;
		if(abs(cross(dp, pt[i] - p1) > EPS)) return false;
		double dt = dot(dp, pt[i] - p1) / dot(dp, dp);
		if(dt < -EPS or dt > 1+EPS) return false;
//		cout<<pt[i]<<" IN "<<p1<<"~"<<p2<<endl;
	}

	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++)
			if(abs(pt[i] - cand[j]) < EPS)
				return false;

	for(int i=0; i<4; i++)
		ans[i] = cand[i];
	return true;
}

void calc()
{
	vector<pdd> cvx;
	for(int i=0; i<4; i++)
		cvx.PB(pt[i]);
	cvx = convex_hull(cvx);
	if(SZ(cvx) != 4) return;
	for(int i=0; i<4; i++)
		pt[i] = cvx[i];

	pdd d1 = pt[2] - pt[0];
	pdd d2 = pt[3] - pt[1];
	d2 = {d2.S, -d2.F};
	pdd d = d1 - d2;
	if(abs(d) < EPS) d = {-d1.S, d1.F};

	pdd t = {-d.S, d.F};

	cand[0] = interPnt(pt[0], pt[0]+d, pt[1], pt[1]+t);
	cand[1] = interPnt(pt[1], pt[1]+t, pt[2], pt[2]+d);
	cand[2] = interPnt(pt[2], pt[2]+d, pt[3], pt[3]+t);
	cand[3] = interPnt(pt[3], pt[3]+t, pt[0], pt[0]+d);

	if(check()) return;

	d = d1 + d2;
	if(abs(d) < EPS) d = {-d1.S, d1.F};
	t = {-d.S, d.F};

	cand[0] = interPnt(pt[0], pt[0]+d, pt[1], pt[1]+t);
	cand[1] = interPnt(pt[1], pt[1]+t, pt[2], pt[2]+d);
	cand[2] = interPnt(pt[2], pt[2]+d, pt[3], pt[3]+t);
	cand[3] = interPnt(pt[3], pt[3]+t, pt[0], pt[0]+d);

	if(check()) return;
}

int main() {
	FILEIO("four");
	IOS;

	for(int i=0; i<4; i++)
		cin>>pt[i].F>>pt[i].S;

	calc();

	cout<<fixed<<setprecision(10);
	for(int i=0; i<4; i++)
		cout<<ans[i].F<<" "<<ans[i].S<<endl;

	return 0;
}
