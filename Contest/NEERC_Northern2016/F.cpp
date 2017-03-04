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


const int INF = 1029384756;

int W, H, w, h;

int alog(int a, int b)
{
	if(a < b) return INF;
	int mult = (a + b - 1) / b;
	int ret = 0;
	while(mult > 1)
	{
		ret++;
		mult = (mult+1)/2;
	}
	return ret;
}

int main() {
	IOS;
	FILEIO("folding");

	cin>>W>>H>>w>>h;
	
	int ans = INF;
	ans = min(ans, alog(W, w) + alog(H, h));
	ans = min(ans, alog(W, h) + alog(H, w));
	
	if(ans == INF) cout<<-1<<endl;
	else cout<<ans<<endl;

	return 0;
}

