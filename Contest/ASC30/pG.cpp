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
#define REP(i,n) for (int i=0; i<(n); i++)
#define REP1(i,a,b) for (int i=(a); i<=(b); i++)
// Let's Fight!

typedef long long ll;
typedef pair<ll, ll> pll;

const int MAXN = 101010;
const ll INF = 1LL<<60;

int N;
pll arr[MAXN];

ll calc()
{
	ll ans = 0;

	sort(arr, arr+N);
	int curpos = 0;
	
	ll curtime = 0;

	priority_queue<ll, vector<ll>, greater<ll>> pq;
	while(curtime < INF)
	{
		ll nxttime = INF;
		if(curpos < N)
			nxttime = arr[curpos].F;

		if(!pq.empty())
		nxttime = min(nxttime, curtime + pq.top());

		if(!pq.empty())
		{
			ll dif = nxttime - curtime;
			ll rem = pq.top() - dif;
			pq.pop();
			if(rem == 0)
				ans += nxttime;
			else
				pq.push(rem);
		}

		while(curpos < N && arr[curpos].F == nxttime)
		{
			pq.push(arr[curpos++].S);
		}

		curtime = nxttime;
	}

	return ans;
}

int main() {
	IOS;
	FILEIO("pulp");

	cin>>N;
	for(int i=0; i<N; i++)
		cin>>arr[i].F>>arr[i].S;

	ll ans = calc();
	cout<<ans<<endl;

    return 0;
}
