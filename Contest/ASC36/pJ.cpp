#include<bits/stdc++.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define MC(n,m) memcpy((n),(m),sizeof(n))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define FOR(x,y) for(__typeof(y.begin())x=y.begin();x!=y.end();x++)
#define ALL(x) x.begin(),x.end()
#define IOS ios_base::sync_with_stdio(0);cin.tie(0)
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
  freopen(name".in", "r", stdin); \
  freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif

#define int long long

struct dt {
    int n, k, a;
    dt(){}
    dt(int _n, int _k, int _a) : n(_n), k(_k), a(_a) {}
    bool operator < (const dt &d) const {
        return tie(n, k, a) < tie(d.n, d.k, d.a);
    }
};

int N, K;
map<dt, int> mp;
vector<int> ans;

int dp(int n, int k, int a) {
    //cout << n << ' ' << k << ' ' << a << endl;
    if (n < 0 or a < 0) return -1;
    if (k == 0) {
        if(n == 0) return 1;
        else return -1;
    }
    if (a*a*k < n) return -1;
    if(mp[dt(n, k, a)]) return mp[dt(n, k, a)];

    if (a*a > n or a*a >= N) {
        return mp[dt(n, k, a)] = dp(n, k, a-1);
    }

    if (dp(n-a*a, k-1, a-1) != -1) {
        return mp[dt(n, k, a)] = 1;
    } 
    if (dp(n, k, a-1) != -1) 
        return mp[dt(n, k, a)] = 1;

    return mp[dt(n, k, a)] = -1;
}

void go(int n, int k, int a) {
    if (k == 0) return;
    if (dp(n-a*a, k-1, a-1) != -1) {
        go(n-a*a, k-1, a-1);
        ans.PB(a);
    } else go(n, k, a-1);
}

int32_t main() {
    FILEIO("squary");
    cin >> N >> K;
    int a = sqrt(N);
    if((a+1)*(a+1) <= N) a ++;
    int fg = dp(N*(K-1), K, a);
    cout << (fg != -1 ? "YES" : "NO") << endl;
    if(fg == -1) return 0;
    go(N*(K-1), K, a);
    vector<int> aa;
    for(auto x: ans) {
        aa.PB(N - x*x);
    }
    sort(ALL(aa));

    for(int i=0; i<K; i++) {
        cout << aa[i] << (i != K-1 ? ' ' : '\n');
    }
  return 0;
}
