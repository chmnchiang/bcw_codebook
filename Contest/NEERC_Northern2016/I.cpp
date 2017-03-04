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

const int MAXN = 202020;

int N;
int px[MAXN], py[MAXN], ps[MAXN];
int num[2][2][2];

ll calc()
{
	for(int i=0; i<N; i++)
	{
		px[i] = (px[i]%2!=0);
		py[i] = (py[i]%2!=0);
	}

	int nows = 0;
	for(int i=0; i<N; i++)
	{
//		cout<<i<<" : "<<px[i]<<","<<py[i]<<","<<nows<<endl;
		ps[i] = nows;
		num[px[i]][py[i]][nows]++;
		int j = (i+1)%N;
		if(px[i] != px[j] and py[i] != py[j])
			nows = 1 - nows;
	}
	if(nows) return 0;

	ll ans = 0;
	for(int i=0; i<N; i++)
	{
		int val = 0;
		for(int j=0; j<2; j++)
		{
			for(int k=0; k<2; k++)
			{
				int s = (j != px[i]) and (k != py[i]);
				val += num[j][k][s^ps[i]];
			}
		}
		val-=3;
//		cout<<i<<" OUT "<<val<<endl;
		ans += val;
	}
	ans /= 2;

	return ans;
}

int main() {
	IOS;
	FILEIO("integral");

	cin>>N;
	for(int i=0; i<N; i++)
		cin>>px[i]>>py[i];

	ll ans = calc();
	cout<<ans<<endl;

	return 0;
}

