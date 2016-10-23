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
ostream& operator << (ostream &o, const pair<T1, T2> &pair) {
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

template<typename T1, typename T2>
ostream& operator << (ostream &o, const map<T1, T2> &mp) {
    o << "{";
    for (auto it=mp.begin(); it!=mp.end(); it++) {
        o << (it==mp.begin()?"":", ") << it->F << ":" << it->S;
    }
    o << "}";
    return o;
}

vector<string> ip_;
vector<int> lns;
vector<int> op;
const int MX = 1010101;
char ip[MX];
int ipid;
vector<int> st; 
bool isd[MX];

bool better(int x, int y) {
    int sx = st[x], sy = st[x+1], ex = st[y];
    while (sx < ex) {
        while (isd[sx]) sx++;
        while (isd[sy]) sy++;
        if (sx >= ex) break;
        if (ip[sx] != ip[sy]) {
            return ip[sy] < ip[sx];
        }
        sx++;
        sy++;
    }
    return 1;
}

int32_t main() {
    IOS;
    int N, K;
    cin >> N >> K;
    for (int i=0; i<N; i++) {
        string s; cin >> s;
        ip_.PB(s);
        lns.PB(SZ(s));
    }

    sort(ALL(lns));
    int L = lns[K-1];

    for (int i=0; i<N; i++) {
        string s = ip_[i];
        if (SZ(s) >= L) {
            st.PB(ipid);
            for (auto c: s) ip[ipid++] = c;
        }
        else K--;

        if (SZ(s) == L) op.PB(SZ(st) - 1);
    }

    for (int kk=0; kk<K; kk++) {
        int bs = op.front(), bi = 0;
        for (int i=1; i<SZ(op); i++) {
            if (better(bs, op[i])) {
                bs = op[i], bi = i;
            } else break;
        }

        for (int i=0; i<L; i++) isd[st[bs]+i] = 1;
        for (int i=bi+1; i<SZ(op); i++) op[i-1] = op[i];
        op.pop_back();
    }


    for (int i=0; i<ipid; i++) {
        if (!isd[i]) cout << ip[i];
    }
    cout << endl;

    return 0;
}
