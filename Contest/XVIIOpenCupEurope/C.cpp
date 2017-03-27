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


typedef pair<double, double> pdd;

pdd operator+(pdd a, pdd b){return {a.F+b.F, a.S+b.S};}
pdd operator-(pdd a, pdd b){return {a.F-b.F, a.S-b.S};}
double dot(pdd a, pdd b){return a.F*b.F+a.S*b.S;}
double cross(pdd a, pdd b){return a.F*b.S-a.S*b.F;}
double cross(pdd a, pdd b, pdd o){return cross(a-o, b-o);}
double abs(pdd a){return sqrt(dot(a, a));}

const double PI = acos(-1);

vector<pdd> convex_hull(vector<pdd> pt){
  sort(pt.begin(),pt.end());
  int top=0;
  vector<pdd> stk(2*pt.size());
  for (int i=0; i<(int)pt.size(); i++){
    while (top >= 2 && cross(stk[top-1],pt[i],stk[top-2]) <= 0)
      top--;
    stk[top++] = pt[i];
  }
  for (int i=pt.size()-2, t=top+1; i>=0; i--){
    while (top >= t && cross(stk[top-1],pt[i], stk[top-2]) <= 0)
      top--;
    stk[top++] = pt[i];
  }
  stk.resize(top-1);
  return stk;
}

int main() {
	IOS;

	int N;
	while(cin>>N)
	{
		string s;
		cin>>s;

		vector<pdd> vpt;
		int Z = SZ(s);
		for(int i=0; i<Z; i++)
		{
			if(s[i] == 'S')
			{
				vpt.PB({0+i, 0});
				vpt.PB({0+i, 1});
				vpt.PB({1+i, 0});
				vpt.PB({1+i, 1});
			}
			else if(s[i] == 'T')
			{
				vpt.PB({0+i, 0});
				vpt.PB({1+i, 0});
				vpt.PB({0.5+i, 0.5 * sqrt(3)});
			}
			else
			{
				int MX = 32768;
				for(int j=0; j<MX; j++)
				{
					double th = 2 * PI * j / MX;
					vpt.PB({0.5+i + 0.5 * cos(th), 0.5 + 0.5 * sin(th)});
				}
			}
		}

		vpt = convex_hull(vpt);

		double ans = 0;
		int S = SZ(vpt);
		for(int i=0; i<S; i++)
			ans += abs(vpt[i] - vpt[(i+1)%S]);

		cout<<fixed<<setprecision(10)<<ans<<endl;
	}

	return 0;
}

