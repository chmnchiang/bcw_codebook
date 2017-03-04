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

const int MXN = 100005;

int N,M,R,leader[MXN],star[MXN],A[MXN];

int main() {
	IOS;
	int nT;
	cin>>nT;
	REP1(cas,1,nT) {
		cin>>N>>M>>R;
		REP1(i,1,N) {
			cin>>A[i];
		}
		REP1(i,1,N) {
			star[i] = 0;
			leader[i] = i;
		}
		REP1(i,1,N) {
			leader[i] = min(leader[i], R);
			leader[R] = min(leader[R], i);

		}

		REP(_,M) {
			int u,v;
			cin>>u>>v;
			leader[u] = min(leader[u], v);
			leader[v] = min(leader[v], u);
		}
		
		REP1(i,1,N) star[leader[i]]++;

		long long ans = 0;
		int j = 2;
		REP1(i,1,N) {
			j = max(j, i+1);
			if (A[i] <= star[i]) continue;
			while (star[i] < A[i]) {
				while (j <= N and !star[j]) j++;
				if (j <= N and star[j]) {
					star[j]--;
					star[i]++;
				} else {
					long long tmp = A[i] - star[i];
					ans += tmp;
					star[i] = A[i];
				}
			}
		}
		cout<<"Case #"<<cas<<": "<<ans<<endl;
	}

	return 0;
}

