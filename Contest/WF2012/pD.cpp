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

const int MAXN = 1000000;
const int MAXL = 32;

int N;
int M;
string s;

ll fib[MAXL];
string fs[MAXL];

ll count(int lv, bool expand=false)
{
	int len = fib[lv];
	while(expand && lv+2<MAXL)
		lv += 2;

	ll ret = 0;
	for(int i=0; i<len; i++)
	{
		int j;
		for(j=0; j<M; j++)
		{
			if(i+j<(int)fs[lv].size() && s[j] == fs[lv][i+j]);
			else break;
		}
		if(j == M) ret++;
	}
	return ret;
}

void pre()
{
	fib[0] = fib[1] = 1;
	fs[0] = "0";
	fs[1] = "1";
	for(int i=2; i<MAXL; i++)
	{
		fib[i] = fib[i-1] + fib[i-2];
		fs[i] = fs[i-1] + fs[i-2];
	}

//	for(int i=0; i<MAXL; i++) cout<<i<<" : "<<fib[i]<<endl;
}

ll calc()
{
	M = s.size();

	if(N < MAXL)
		return count(N);

	ll ans = 0;

	ll L = MAXL-3;
	ll a = count(L-1, true), b = count(L, true);
	while(L<N)
	{
		ll c = b;
		b += a;
		a = c;
		L++;
	}

	ans = b;
	while(L >= MAXL-2) L -= 2;
	ans -= count(L, true) - count(L);

	return ans;
}

int main() {
	IOS;
	pre();

	int t = 0;
	while(cin>>N>>s)
	{
		t++;

		ll ans = calc();
		cout<<"Case "<<t<<": "<<ans<<endl;
	}

	return 0;
}

