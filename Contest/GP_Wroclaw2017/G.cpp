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



using pii = pair<int,int>;

const int MX = 1000005;

int N,c[MX],bye[MX];
string s;

int main() {
	IOS;
	int T;
	cin>>T;
	while (T--) {
		cin>>N;
		cin>>s;
		REP(i,N) {
			cin>>c[i];
			bye[i] = 0;
		}

		priority_queue<pii> pq;
		long long ans = 0;
		int cur = 0;
		REP(i,N) {
			if (bye[i]) continue;
			if (s[i] == '(') cur++;
			else {
				pq.push({-c[i],i});
				cur--;

				if (cur < 0) {
					auto tmp = pq.top();
					pq.pop();
					ans += -tmp.F;
					bye[tmp.S] = 1;
					cur++;
				}
			}
		}
		while (!pq.empty()) pq.pop();
		cur = 0;
		for (int i=N-1; i>=0; i--) {
			if (bye[i]) continue;

			if (s[i] == ')') cur++;
			else {
				pq.push({-c[i],i});
				cur--;
				if (cur < 0) {
					auto tmp = pq.top();
					pq.pop();
					ans += -tmp.F;
					bye[tmp.S] = 1;
					cur++;
				}
			}
		}
		cout<<ans<<endl;
	}

	return 0;
}

