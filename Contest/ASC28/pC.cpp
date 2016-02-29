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

typedef pair<int, int> pii;

const int MAXN = 303;

int N;
pii pt[MAXN];

int calc()
{
	int ans = 0;

	for(int i=0; i<N; i++)
	{
		set<pii> st;
		for(int j=0; j<N; j++)
		{
			if(i == j) continue;
			int dx = pt[j].F - pt[i].F;
			int dy = pt[j].S - pt[i].S;
			int g = __gcd(abs(dx), abs(dy));
			dx /= g;
			dy /= g;
			st.insert({dx, dy});
		}
		ans += st.size();
	}

	return ans;
}

int main() {
	IOS;
	FILEIO("cottages");

	cin>>N;
	for(int i=0; i<N; i++)
		cin>>pt[i].F>>pt[i].S;

	int ans = calc();
	cout<<ans<<endl;

    return 0;
}

