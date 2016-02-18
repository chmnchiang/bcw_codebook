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
#define REP(i,x) for(int i=0; i<(x); i++)
#define REP1(i,a,b) for(int i=(a); i<=(b); i++)
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

const int MX = 100005;

ll N, cnt[MX], tot[MX];

string ip;

inline ll sqr(ll x) { return x * x; }
inline void upd(ll &ans, ll x) { ans = max(ans, x); }

int main() {
    IOS;
    int nT;
    cin >> nT;
    REP1(t,1,nT) {
        cout << "Case #" << t << ": ";

        ll ans = 0;
        ll tmp = 0;
        cin >> ip;
        N = SZ(ip);
        if (N == 1) {
            cout << "1\n";
            continue;
        }
        cnt[0] = 1;
        REP1(i,1,N-1) {
            if (ip[i] == ip[i-1]) {
                cnt[i] = cnt[i-1] + 1;
            } else {
                cnt[i] = 1;
            }
        }
        REP(i,N) tot[i] = cnt[i];
        for (int i=N-2; i>=0; i--) {
            if (ip[i] == ip[i+1])
                tot[i] = tot[i+1];
        }
        REP1(i,1,N-1) {
            if (ip[i] != ip[i-1]) {
                tmp += sqr(cnt[i-1]);
            }
        }
        tmp += sqr(cnt[N-1]);
        //cout << tmp << endl;
        ans = tmp;
        if (ip[0] == ip[1]) {
            upd(ans, tmp - sqr(tot[0]) + 1 + sqr(tot[0] - 1)); 
        } else {
            upd(ans, tmp - sqr(tot[1]) - 1 + sqr(tot[1] + 1));
        }
        if (ip[N-1] == ip[N-2]) {
            upd(ans, tmp - sqr(tot[N-1]) + 1 + sqr(tot[N-1] - 1));
        } else {
            upd(ans, tmp - sqr(tot[N-2]) - 1 + sqr(tot[N-2] + 1));
        }
        
        REP1(i,1,N-2) {
            if (ip[i] == ip[i-1] && ip[i] == ip [i+1]) {
                upd(ans, tmp - sqr(tot[i]) + 1 + sqr(cnt[i-1]) + sqr(tot[i]-cnt[i]));
            } else if (ip[i] == ip[i-1] && ip[i] != ip[i+1]) {
                upd(ans, tmp - sqr(tot[i]) - sqr(tot[i+1]) + sqr(tot[i+1]+1) + sqr(tot[i]-1));
            } else if (ip[i] != ip[i-1] && ip[i] == ip[i+1]) {
                upd(ans, tmp - sqr(tot[i]) - sqr(tot[i-1]) + sqr(tot[i-1]+1) + sqr(tot[i]-1));
            } else {
                upd(ans, tmp - sqr(tot[i-1]) - 1 - sqr(tot[i+1]) + sqr(tot[i-1]+1+tot[i+1]));
            }
        }
        cout << ans << endl;
        
    }

    return 0;
}
