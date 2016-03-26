//bcw0x1bd2 {{{
#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define IOS ios_base::sync_with_stdio(0); cin.tie(0);
#define SZ(x) ((int)((x).size()))
#define ALL(x) begin(x),end(x)
#define REP(i,x) for (int i=0; i<(x); i++)
#define REP1(i,a,b) for (int i=(a); i<=(b); i++)

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef long double ld;

#ifdef DARKHH
#define FILEIO(name)
#else
#define FILEIO(name) \
  freopen(name".in", "r", stdin); \
  freopen(name".out", "w", stdout);
#endif

#ifdef DARKHH
template<typename Iter>
ostream& _out(ostream &s, Iter b, Iter e) {
    s << "[ ";
    for ( auto it=b; it!=e; it++ ) s << *it << " ";
    s << "]";
    return s;
}
template<typename A, typename B>
ostream& operator << (ostream &s, const pair<A,B> &p) { return s<<"("<<p.first<<","<<p.second<<")"; }
template<typename T>
ostream& operator << (ostream &s, const vector<T> &c) { return _out(s,ALL(c)); }
template<typename T, size_t N>
ostream& operator << (ostream &s, const array<T,N> &c) { return _out(s,ALL(c)); }
template<typename T>
ostream& operator << (ostream &s, const set<T> &c) { return _out(s,ALL(c)); }
template<typename A, typename B>
ostream& operator << (ostream &s, const map<A,B> &c) { return _out(s,ALL(c)); }
#endif
// }}}
// Let's Fight! ~OAO~~

const int MX = 150005;

struct Coord {
    int x,y,z;
};
struct Lisan {
    vector<int> seq;
    void add(int x) { seq.PB(x); }
    void build() {
        sort(ALL(seq));
        seq.resize(unique(ALL(seq))-begin(seq));
    }
    int qry(int x) { return lower_bound(ALL(seq),x)-begin(seq)+1; }
}lisan;
struct BIT {
    int bit[MX];
    int lb(int x) { return x & -x; }
    void upd(int x, int v) {
        for (int i=x; i>0; i-=lb(i)) {
            bit[i] = max(bit[i], v);
        }
    }
    int qry(int x) {
        int res = 0;
        for (int i=x; i<MX; i+=lb(i)) {
            res = max(res, bit[i]);
        }
        return res;
    }
}bit;

int N;
Coord pt[50005];

bool comp(Coord a, Coord b) { return tie(a.x,a.y,a.z) < tie(b.x,b.y,b.z); }
int main() {
    IOS;
    FILEIO("pareto");
    cin >> N;
    REP(i,N) {
        cin >> pt[i].x >> pt[i].y >> pt[i].z;
        lisan.add(pt[i].x);
        lisan.add(pt[i].y);
        lisan.add(pt[i].z);
    }
    lisan.build();
    REP(i,N) {
        pt[i].x = lisan.qry(pt[i].x);
        pt[i].y = lisan.qry(pt[i].y);
        pt[i].z = lisan.qry(pt[i].z);
    }
    sort(pt,pt+N,comp);
    int ans = N;
    for (int i=N-1; i>=0; i--) {
        int mxz = bit.qry(pt[i].y+1);
        if (mxz > pt[i].z) ans--;
        bit.upd(pt[i].y,pt[i].z);
    }
    cout << ans << endl;

    return 0;
}

