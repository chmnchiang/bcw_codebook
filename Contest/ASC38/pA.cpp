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

typedef long long ll;
typedef pair<ll, ll> pll;

const int MAXN = 202020;

int N;
int arr[MAXN];

int main() {
	FILEIO("approximation");
	IOS;

	cin>>N;
	for(int i=0; i<N; i++)
		cin>>arr[i];

	vector<pll> vec;
	for(int i=0; i<N; i++)
	{
		vec.PB({1, arr[i]});
		while(vec.size() >= 2)
		{
			pll &p1 = vec[vec.size()-2], &p2 = vec[vec.size()-1];
			if(p1.S * p2.F >= p1.F * p2.S)
			{
				p1.F += p2.F;
				p1.S += p2.S;
				vec.pop_back();
			}
			else
				break;
		}
	}

	vector<double> ans;
	for(auto p: vec)
	{
		double avg = (double) p.S / p.F;
		for(int i=0; i<p.F; i++)
			ans.PB(avg);
	}

	for(int i=0; i<N; i++)
		cout<<fixed<<setprecision(12)<<ans[i]<<(i==N-1 ? "\n" : " ");

    return 0;
}
