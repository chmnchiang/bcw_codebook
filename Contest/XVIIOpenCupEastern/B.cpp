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

const int MAXN = 202020;

typedef long long ll;
typedef pair<ll, ll> pll;

pll operator+(pll a, pll b){return {a.F+b.F, a.S+b.S};}
pll operator-(pll a, pll b){return {a.F-b.F, a.S-b.S};}
ll dot(pll a, pll b){return a.F*b.F+a.S*b.S;}
ll cross(pll a, pll b){return a.F*b.S-a.S*b.F;}
ll cross(pll a, pll b, pll o){return cross(a-o, b-o);}
ll area(pll a, pll b, pll o){return abs(cross(a, b, o));}

int N;
pll pt[MAXN];

vector<pll> convex_hull(vector<pll> vpt){
  sort(vpt.begin(),vpt.end());
  int top=0;
  vector<pll> stk(2*vpt.size());
  for (int i=0; i<(int)vpt.size(); i++){
    while (top >= 2 && cross(stk[top-1],vpt[i],stk[top-2]) <= 0)
      top--;
    stk[top++] = vpt[i];
  }
  for (int i=vpt.size()-2, t=top+1; i>=0; i--){
    while (top >= t && cross(stk[top-1],vpt[i], stk[top-2]) <= 0)
      top--;
    stk[top++] = vpt[i];
  }
  stk.resize(top-1);
  return stk;
}

void calc()
{
	vector<pll> vpt;
	for(int i=0; i<N; i++)
		vpt.PB(pt[i]);
	vpt = convex_hull(vpt);

	int M = SZ(vpt);

	if(M < 3)
	{
		for(int i=0; i<3; i++)
			cout<<pt[i].F<<" "<<pt[i].S<<endl;
		return;
	}

	for(int i=0; i<M; i++)
		vpt.PB(vpt[i]);

	int j = 1, k = 2;
	ll mxa = 0;
	pll mp[3];
	for(int i=0; i<M; i++)
	{
		if(j == i) j++;

		bool ok = true;
		while(ok)
		{
			ok = false;

			if(j+1 < k and area(vpt[i], vpt[j+1], vpt[k]) >= area(vpt[i], vpt[j], vpt[k]))
			{
				j++;
				ok = true;
			}
			if(k+1 < i+M and area(vpt[i], vpt[j], vpt[k+1]) >= area(vpt[i], vpt[j], vpt[k]))
			{
				k++;
				ok = true;
			}
		}

		ll a = area(vpt[i], vpt[j], vpt[k]);
		if(a > mxa)
		{
			mxa = a;
			mp[0] = vpt[i];
			mp[1] = vpt[j];
			mp[2] = vpt[k];
		}
	}

	for(int i=0; i<3; i++)
		cout<<mp[i].F<<" "<<mp[i].S<<endl;
}

int main() {
	IOS;

	while(cin>>N)
	{
		for(int i=0; i<N; i++)
			cin>>pt[i].F>>pt[i].S;

		calc();
	}

	return 0;
}

