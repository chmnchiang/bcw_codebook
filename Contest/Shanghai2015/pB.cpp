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
// Let's Fight!

#define int long long

int32_t main() {
    IOS;
    int T;
    cin >> T;
    for (int cas=1; cas<=T; cas++) {
        int N, K; cin >> N >> K;
        int X = (1LL<<K);
        int d;
        if (N&1) {
            d = (X-1-N)/2;
        } else {
            d = (X-N)/2;
        }

        int now = 1;
        cout << "Case #" << cas << ":\n";
        for (int i=0; i<K-1; i++) {
            int t = (d&(1LL<<i));
            if (t) {
                cout << now << " -\n";
            } else cout << now << " +\n";
            now <<= 1;
        }
        if (N&1)
            cout << now << " +\n";
        else 
            cout << now+1 << " +\n";
    }
    return 0;
}
