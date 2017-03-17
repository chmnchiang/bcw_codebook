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



vector<int> fst;
map<string,int> mp;
vector<string> ip;

int main() {
#ifndef BCW
    freopen("input.txt", "r", stdin); \
    freopen("output.txt", "w", stdout);
#endif
	IOS;
	int N;
	cin>>N;
	ip.resize(N);
	fst.resize(N);
	REP(i,N) {
		cin>>ip[i];
		int l = SZ(ip[i])-1;
		while (l>=0 and ip[i][l] != '.') l--;
		assert(l >= 0);
		string s = ip[i].substr(l+1);
		fst[i] = (mp.count(s) == 0);
		mp[s]++;
		ip[i] = s;
	}
	REP(i,N) {
		if (!fst[i]) continue;
		cout<<ip[i]<<": "<<mp[ip[i]]<<endl;
	}


	return 0;
}

