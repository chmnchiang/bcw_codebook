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

#ifdef DEBUG
#define debug(a) cout << #a << " = " << a << endl;
#endif
template<typename T>
ostream& operator << (ostream &o, vector<T> &vec) {
    cout << "[";
    for (int i=0; i<SZ(vec); i++) {
        if (i) cout << ", ";
        cout << vec[i];
    }
    cout << "]";
    return o;
}

template<typename T1, typename T2>
ostream& operator << (ostream &o, pair<T1, T2> &pair) {
    cout << "(" << pair.F << ", " << pair.S << ")";
    return o;
}

typedef pair<int, int> pii;
const int MX = 2010;
int V, E;
vector<pii> el[MX];
bool isd[MX];
int bk[MX];
int djs[MX];

void djsInit() {
    for (int i=0; i<=V+E; i++)
        djs[i] = i;
}

int ffa(int a) {
    while(not a);
    return (djs[a] == a ? a : djs[a] = ffa(djs[a]));
}

bool ins[MX];
stack<int> st;
stack<pii> est;
vector<int> loop;
vector<pii> le;
vector<int> cv[MX];
vector<pii> ce[MX];
int nV;

int dfs(int v) {
    if (ins[v]) {
        int u;
        do {
            while(not SZ(st));
            u = st.top();
            loop.PB(u); st.pop();
            le.PB(est.top()); est.pop();
        } while (u != v);

        return v;
    }
    ins[v] = true;
    st.push(v);

    for (auto p: el[v]) {
        int u = ffa(p.F);
        est.push(p);
        if (int t = dfs(u)) {
            ins[v] = false;
            return t;
        }
        est.pop();
    }

    ins[v] = false;
    st.pop();
    return 0;
}

int dfs() {
    st = stack<int>();
    est = stack<pii>();
    loop.clear();
    le.clear();
    return dfs(ffa(1));
}

void prt(int u, int ind=0) {
    int sz = SZ(cv[u]);
    if (not sz) {
        cout << "vertex " << u << endl;
        return;
    }

    cout << "wheel " << sz << endl;
    for (int i=sz-1; i>=0; i--) {
        prt(cv[u][i], ind+1);
        cout << "edge " << ce[u][i].S << endl;
    }
}

int main() {
    FILEIO("wheels");
    IOS;
    cin >> V >> E;

    for (int i=1; i<=E; i++) {
        int u, v;
        cin >> u >> v;
        el[u].PB({v, i});
    }

    djsInit();
    nV = V;
    while (dfs()) {
        int u = ++nV;
        for (auto e: le) {
            isd[e.S] = true;
        }
        for (auto v: loop) {
            djs[ffa(v)] = u;

            for (auto x: el[v]) {
                if (not isd[x.S])
                    el[u].PB(x);
            }
        }
        cv[u] = loop;
        ce[u] = le;
    }

    prt(nV);
    return 0;
}

