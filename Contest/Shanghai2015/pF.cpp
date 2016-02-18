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
#define REP(i,x) for(int i=0; i<(x); i++)
#define REP1(i,a,b) for(int i=(a); i<=(b); i++)

const int INF = 1029384756;
int lst[514];
string s;

int main() {
    int nT;
    cin >> nT;
    REP1(t,1,nT) {
        cin >> s;
        int ans = INF;
        FMO(lst);
        REP(i,SZ(s)) {
            int c = s[i];
            if (lst[c] != -1) {
                ans = min(ans, i - lst[c]);
            }
            lst[c] = i;
        }
        if (ans == INF) ans = -1;
        cout << "Case #" << t << ": " << ans << endl;
    }

    return 0;
}
