#include<bits/stdc++.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define MC(n,m) memcpy((n),(m),sizeof(n))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define ALL(x) begin(x),end(x)
#define IOS do { ios_base::sync_with_stdio(0);cin.tie(0); } while (0)
#define SZ(x) ((int)(x).size())
#ifndef OFFLINE
    #define ONLINE_JUDGE
#endif
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
    do { \
        freopen(name".in", "r", stdin); \
        freopen(name".out", "w", stdout); \
    } while (0)
#else
    #define FILEIO(name) do { } while(0)
#endif

#define _TOKEN_CAT2(x, y) x ## y
#define _TOKEN_CAT(x, y) _TOKEN_CAT2(x, y)
#define _MACRO_OVERL3(_1, _2, _3, _N, ...) _N
#define _RANGE1(a) int _TOKEN_CAT(_t, __LINE__)=0; _TOKEN_CAT(_t, __LINE__)<(a); (_TOKEN_CAT(_t, __LINE__))++
#define _RANGE2(i, a) int (i)=0; (i)<(a); (i)++
#define _RANGE3(i, a, b) int (i)=(a); (i)!=(b); (i)+=((b)>(a)?1:-1)
#define loop(...) for (_MACRO_OVERL3(__VA_ARGS__, _RANGE3, _RANGE2, _RANGE1)(__VA_ARGS__))

#ifdef OFFLINE
template<typename T>
void _dump(const char* s, T&& head) { 
    cerr << s << " = " << head << " <<" << endl; 
}

template<typename T, typename... Args>
void _dump(const char* s, T&& head, Args&&... tail) {
    int c = 0;
    while (*s!=',' || c!=0) {
        if (*s=='(' || *s=='[' || *s=='{' || *s=='<') c++;
        if (*s==')' || *s==']' || *s=='}' || *s=='>') c--;
        cerr << *s++;
    }
    cerr << " = " << head << ", ";
    _dump(s+1, tail...);
}

#define dump(...) do { \
    cerr << "\033[32m>> " << __LINE__ << ": " << __PRETTY_FUNCTION__ << endl; \
    cout << "   "; \
    _dump(#__VA_ARGS__, __VA_ARGS__); \
    cout << "\033[0m"; \
} while (0)
#else
#define dump(...) 
#endif

#define au auto
template<class T>
using vec = vector<T>;

template<typename Iter>
ostream& _IterOutput_(ostream &o, Iter b, Iter e, const string ss="", const string se="") {
    o << ss;
    for (auto it=b; it!=e; it++) o << (it==b ? "" : ", ") << *it;
    return o << se;
}

template<typename T1, typename T2>
ostream& operator << (ostream &o, pair<T1, T2> &pair) {
    return o << "(" << pair.F << ", " << pair.S << ")";
}

template<typename T>
ostream& operator << (ostream &o, const vector<T> &vec) {
    return _IterOutput_(o, ALL(vec), "[", "]");
}

template<typename T>
ostream& operator << (ostream &o, const set<T> &st) {
    return _IterOutput_(o, ALL(st), "{", "}");
}

template<typename T, size_t N>
ostream& operator << (ostream &o, const array<T, N> &arr) {
    return _IterOutput_(o, ALL(arr), "|", "|");
}

#define int long long
int T, C1, C2, A1, A2;
int N;

int calc3() {
    vec<int> u(N), v(N);
    loop (i, N) {
        if (i < A2) u[i] = C2;
        else u[i] = C1;
    }
    random_shuffle(ALL(u));
    loop (i, N) {
        v[i] = T*(i+1);
        if (i) v[i] = max(v[i], v[i-1]);
        v[i] += u[i];
    }
    sort(ALL(v));

    int nt = 0;
    for (auto x: v) {
        nt = max(nt+T, x+T);
    }
    return nt;
}

bool test(int md) {
    int d = md - C1;
    int dmax = d, d2m = C2 - C1;
    int d1 = T - C1, d2 = C2 - T;
    int cnt1 = A1, cnt2 = A2;

    if (md < C2) return false;

    for (int i=0; i<N; i++) {
        if (not cnt2) {
            return true;
        }

        if (d < d2m) {
            if (not cnt1) return false;
            d = min(dmax, d+d1);
            cnt1--;
        } else {
            if (d - d2 < 0) {
                if (not cnt1) {
                    return false;
                }
                d = min(dmax, d+d1);
                cnt1--;
            } else {
                d -= d2;
                cnt2--;
            }
        }
    }
    return true;
}

int32_t main() {
    FILEIO("coffin");
    IOS;

    cin >> T >> C1>>C2>>A1>>A2;
    N = A1+A2;
    /*
    srand(time(0));
    int t = 102938;
    loop (100000) {
        t = min(t, calc3());
    }
    cout << t << endl;
    */
    if (not N) {
        cout << 0 << endl;
        return 0;
    }
    if (not A2 or not A1) {
        cout << calc3() << endl;
        return 0;
    }
    
    if (C2 <= T) {
        cout << calc3() << endl;
        return 0;
    } else if (C1 >= T) {
        int t = T*2;
        t += A1*C1;
        t += A2*C2;
        cout << t << endl;
        return 0;
    }

    int l = C2, r = (C2+1)*(N+1);
    while (l < r) {
        int md = (l+r)/2;

        if (test(md)) r = md; 
        else l = md+1;
    }
    cout << r+T*N+T << endl;

    return 0;
}
