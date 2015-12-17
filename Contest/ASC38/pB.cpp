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

const int MAXN = 101010;

ll N;
int M;

bool test(ll x)
{
	ll cum = 0;
	for(int i=1; i<=M; i++)
	{
		ll dv = (x-1) / i;
		cum += dv;
	}
	return cum < N;
}

ll calc()
{
	ll lb = 0, rb = N;
	while(lb < rb)
	{
		ll mb = (lb + rb + 1) / 2;
		if(test(mb))
			lb = mb;
		else
			rb = mb - 1;
	}

	return lb;
}

int main() {
	FILEIO("bigset");
	IOS;

	cin>>N>>M;
	ll ans = calc();
	cout<<ans<<endl;

    return 0;
}
