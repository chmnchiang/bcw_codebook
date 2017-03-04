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

const int INF = 33333;

int G;
string S;
string arr[6][20];
int pos[5];

bool check(int x)
{
	map<string, int> st;
	for(int i=0; i<5; i++)
		pos[i] = 0;
	for(int i=0; i<100; i++)
	{
		if(SZ(st) >= x) break;
		int a = i%5;
		while(pos[a] < 20)
		{
			if(false and st.count(arr[a][pos[a]]))
			{
				pos[a]++;
				continue;
			}
			else
			{
				st.insert({arr[a][pos[a]], SZ(st)+1});
				pos[a]++;
				break;
			}
		}
	}
	for(int i=0; i<20; i++)
	{
		if(SZ(st) >= G) break;
		st.insert({arr[5][i], SZ(st)+1});
	}

	//cout<<"X = "<<x<<" : ";
	//for(auto p: st) cout<<p<<" ";cout<<endl;

	return st.count(S);
}

int main() {
	IOS;

	int T;
	cin>>T;
	for(int t=1; t<=T; t++)
	{
		cin>>G>>S;
		for(int i=0; i<6; i++)
			for(int j=0; j<20; j++)
				cin>>arr[i][j];

		int ans = INF;
		for(int x=0; x<=G; x++)
			if(!check(x))
				ans = min(ans, G-x);

		cout<<"Case #"<<t<<": ";
		if(ans == INF)
			cout<<"ADVANCED!";
		else
			cout<<ans;
		cout<<endl;
	}

	return 0;
}

