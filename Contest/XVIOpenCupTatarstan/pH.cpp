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

string S;
int N, L;
int arr[MAXN];

string calc()
{
	int off = 0;
	for(int i=0; i<N; i++)
		off = (L - off - arr[i]) % L;
	if(off < 0) off += L;
	if(N%2) reverse(ALL(S));

	return S.substr(off) + S.substr(0, off);
}

int main() {
	IOS;

	getline(cin, S);
	L = S.size();
	cin>>N;
	for(int i=0; i<N; i++)
		cin>>arr[i];

	string s = calc();
	cout<<s<<endl;

	return 0;
}

