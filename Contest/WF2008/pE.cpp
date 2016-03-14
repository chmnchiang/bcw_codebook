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

int N;
const int MX = 1111;
typedef pair<int, int> pii;
struct Trie {
    struct Node {
        int fa;
        int c[2];
    };

    Node nd[MX];
    int cnt;
    int root;

    int newNode(int fa) {
        nd[++cnt] = {fa, 0, 0};
        return cnt;
    }

    void init() {
        cnt = 0;
        root = newNode(0);
    }

    void insert(int nv, int pos, const string &s) {
        if (pos >= SZ(s)) return;

        int c = s[pos] - '0';
        int &t = nd[nv].c[c];
        if (not t) {
            t = newNode(nv);
        }
        return insert(t, pos+1, s);
    }

    void insert(const string &s) {
        insert(root, 0, s);
    }

    vector<pii> dump() {
        vector<pii> res;
        queue<int> q;
        q.push(root);
        int v=1;
        while (SZ(q)) {
            auto &nv = nd[q.front()]; q.pop();
            int l, r; l = r = -1;
            if (int t=nv.c[1]) q.push(t), r=v++;
            if (int t=nv.c[0]) q.push(t), l=v++;
            res.PB({r, l});
        }
        return res;
    }
} trie;

const int MV = 100;
vector<pii> el;
int np[MV];
int ans;

template<class T>
inline int sum(T v) {
    int t = 0;
    for (auto x: v)
        t += x;
    return t;
}

void dfs(int n, int p) {
    if (n >= SZ(el)) {
        ans++;
        //cout << np[3] << ' ' << np[4] << ' ' << np[6] << ' ' << np[7] << ' ' << np[8] << endl;
        //vector<int> tp = {np[3], np[4], np[6], np[7], np[8]};
        //assert(sum(tp) == 100);
        //assert(op == tp);
        return;
    }
    int t = np[n];
    int l = el[n].F, r = el[n].S;
    if (l == -1) return dfs(n+1, p);

    for (int i=min(p, t-1); i>=1; i--) {
        int j=t-i;
        if (j > i) break;
        np[l] = i;
        np[r] = j;
        dfs(n+1, j);
    }
}

int solve() {
    trie.init();
    for (int i=0; i<N; i++) {
        string s; cin >> s;
        trie.insert(s);
    }
    el = trie.dump();
    
    ans = 0;
    np[0] = 100;
    dfs(0, 100);
    return ans;
}

int main() {

    int cas = 0;
    while (true) {
        cin >> N;
        if (not N) break;
        int ans = solve();
        cas++;
        cout << "Case " << cas << ": " << ans << endl;
    }
    return 0;
}

