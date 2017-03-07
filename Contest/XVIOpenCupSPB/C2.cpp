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

int ans[] = {0,1,1,5,11,49,218,1758,22179,523731,23442286,13888070,140494988,783172597,742329157,948714401,173930486,51216003,900602435,476518393,588911549,308065198,286320027,821882837,385556263,617962827,758914038,695502636,856048434,350055693,908810979,799497594,563784518,279824512,630498238,88110932,888007428,597111515,703575671,748502330,258336186,258658531,287427641,960839953,3897933,409987675,648540078,494762893,969815231,802699320,634858320,628525750,171094815,108958497,735620302,925245915,653612268,335687501,791708872,376304094,24697351,19505503};

int main() {
	IOS;

	int T;
	cin>>T;
	while(T--)
	{
		int N;
		cin>>N;
		cout<<ans[N]<<endl;
	}

	return 0;
}

