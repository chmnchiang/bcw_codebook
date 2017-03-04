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

typedef pair<int,int> pii;

const int MXN = 1005;
const int MX = 100005;
const int INF = 1029384756;

struct BIT {
	int bit[MXN];
	void init() {
		REP(i,MXN) bit[i] = INF;
	}
	void update(int st, int v) {
		st += 2;
		for (int i=st; i>0; i-=i&-i)
			bit[i] = min(bit[i], v);
	}
	int query(int st) {
		st += 2;
		int res = INF;
		for (int i=st; i<MXN; i+=i&-i)
			res = min(res, bit[i]);
		return res;
	}
}bit;

int N,ip[MX],ed[MX],app[MX],ss[MX];
vector<int> at[MX];


int main() {
	IOS;
	int T;
	cin>>T;
	REP1(t,1,T) {
		REP(i,MX) at[i].clear();
		cin>>N;
		REP(i,N) {
			cin>>ip[i];
			at[ip[i]].PB(i);
		}

		REP(i,N) {
			REP(j,N) app[ip[j]] = 0;

			ip[N] = ip[i];
			REP1(j,i,N) {
				int v = ip[j];
				if (app[v]) {
					ed[i] = j;
					break;
				}
				app[v] = 1;
			}
			//cout<<"ED : "<<i<<" "<<ed[i]<<endl;
		}

		int ans=0;
		REP(i,N) ans = max(ans, ed[i] - i);


		REP1(i,1,N-1) {
			REP(j,N) app[ip[j]] = 0;
			bit.init();

			priority_queue<pii> pq;
			REP(j,i) {
				ss[j] = min(ed[j], i);
				pq.push({ss[j]-j,j});
			}

			REP1(j,i,N-1) {
				//cout<<"==="<<j<<"==="<<endl;
				int v = ip[j];
				if (app[v]) break;
				app[v] = 1;
				for (auto p:at[v]) {
					bit.update(p,p);
					//cout<<"UPDATE " << p <<endl;
				}

				while (!pq.empty()) {
					auto tmp = pq.top();
					int r = min(bit.query(tmp.S), ss[tmp.S]);
					if (r - tmp.S != tmp.F) {
						pq.pop();
						pq.push({r-tmp.S,tmp.S});
						continue;
					}
					//cout<<"*"<<tmp.S<<" "<<tmp.F<<endl;
					ans = max(ans, tmp.F + (j - i + 1));
					break;
				}
			}
		}

		cout<<"Case #"<<t<<": "<<ans<<endl;
	}

	return 0;
}

