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

typedef long long ll;

const int MAXN = 10101010;

bool notp[MAXN];
int pnum[MAXN];
ll sval[MAXN];

void pre()
{
	for(int i=2; i<MAXN; i++)
	{
		if(notp[i]) continue;

		pnum[i] = 1;
		sval[i] = int(sqrt(i+0.1)) - 1;

		for(int j=i*2; j<MAXN; j+=i)
		{
			notp[j] = true;
			if(sval[j] == 0)
			{
				sval[j] = i-1;
			}
		}
	}

	for(int i=3; i<MAXN; i++)
	{
		pnum[i] += pnum[i-1];
		sval[i] += sval[i-1];
	}
}

int main() {
	IOS;

	pre();

	int T;
	cin>>T;
	while(T--)
	{
		int N;
		cin>>N;
		ll s = sval[N];
		ll m = pnum[N];
		ll g = __gcd(s, m);
		s /= g;
		m /= g;
		cout<<s<<"/"<<m<<"\n";
	}

	return 0;
}

