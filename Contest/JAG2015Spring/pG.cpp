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
#define SZ(x) ((int)(x).size())
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
  freopen(name".in", "r", stdin); \
  freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif
 
#define _TOKEN_CAT2(x, y) x ## y
#define _TOKEN_CAT(x, y) _TOKEN_CAT2(x, y)
#define _MACRO_OVERL3(_1, _2, _3, _N, ...) _N
#define _RANGE1(a) int _TOKEN_CAT(_t, __LINE__)=0; _TOKEN_CAT(_t, __LINE__)<(a); (_TOKEN_CAT(_t, __LINE__))++
#define _RANGE2(i, a) int (i)=0; (i)<(a); (i)++
#define _RANGE3(i, a, b) int (i)=a; (i)<(b); (i)++
#define range(...) _MACRO_OVERL3(__VA_ARGS__, _RANGE3, _RANGE2, _RANGE1)(__VA_ARGS__)
 
typedef pair<int, int> pii;
typedef tuple<int, int, int> tup;
 
int& operator / (tup &t, int a) 
{
    if (a == 0)
        return get<0>(t);
    else if (a == 1)
        return get<1>(t);
    else if (a == 2)
        return get<2>(t);
    assert(false);
}
 
const int MX = 1010101;
int djs[MX];
void djsInit(int n) 
{
    for (int i=0; i<n; i++) djs[i] = i;
}
int ffa(int a)
{
    return (djs[a] == a ? a : djs[a] = ffa(djs[a]));
}
 
template<typename T>
vector<T>& operator << (vector<T>& v, T x) {
    v.PB(x); return v;
}
 
vector<tup> blks;
vector<tup> pts;
map<pii, vector<int>> mp[3];
int X, Y, Z, N;
 
 
int main() 
{
    cin >> X >> Y >> Z >> N;
    if (!N) {
        cout << 1 << endl;
        return 0;
    }
    for (int i=0; i<N; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        blks << tup{x, y, z};
    }
    sort(ALL(blks));
 
#define REP(i, n) for (int (i)=0; (i)<(n); (i)++)
 
    auto inr = [&](int x, int y, int z) {
        return (x >= 0 and x < X and
                y >= 0 and y < Y and
                z >= 0 and z < Z);
    };
 
    for (auto p: blks) {
        REP(i, 3)
            REP(j, 3)
                REP(k, 3) {
            int x = p/0 + i-1,
                y = p/1 + j-1,
                z = p/2 + k-1;
            if (not inr(x, y, z)) continue;
            tup _p = tup{x, y, z};
            pts << _p;
            _p/2 = 0;
            pts << _p;
            _p/1 = 0;
            pts << _p;
            _p/0 = 0;
            pts << _p;
        }
    }
 
    sort(ALL(pts));
    pts.resize(unique(ALL(pts)) - pts.begin());
 
 
    int sz = SZ(pts);
    djsInit(sz);
    int ans = sz;
 
    for (int i=0; i<sz; i++) {
        auto p = pts[i];
        int x, y, z;
        tie(x, y, z) = p;
        auto &s0 = mp[0][{x, y}],
             &s1 = mp[1][{y, z}],
             &s2 = mp[2][{x, z}];
        auto pb = lower_bound(ALL(blks), p);
        bool fg = (pb == blks.end() or *pb != p);
        if (fg) {
 
#define _magic(a) \
            if (SZ(a)) { \
                int b = a.back(); \
                if (b >= 0) { \
                    int f1 = ffa(b), f2 = ffa(i); \
                    ans -= (f1 != f2); \
                    djs[f1] = f2; \
                } \
            } \
            a << i;
 
            _magic(s0);
            _magic(s1);
            _magic(s2);
        } else {
            ans --;
            s0 << -1;
            s1 << -1;
            s2 << -1;
        }
    }
 
    cout << ans << endl;
 
    return 0;
}
