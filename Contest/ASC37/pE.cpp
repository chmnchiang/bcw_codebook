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

#define _TOKEN_CAT2(x, y) x ## y
#define _TOKEN_CAT(x, y) _TOKEN_CAT2(x, y)
#define _MACRO_OVERL3(_1, _2, _3, _N, ...) _N
#define _RANGE1(a) int _TOKEN_CAT(_t, __LINE__)=0; _TOKEN_CAT(_t, __LINE__)<(a); (_TOKEN_CAT(_t, __LINE__))++
#define _RANGE2(i, a) int (i)=0; (i)<(a); (i)++
#define _RANGE3(i, a, b) int (i)=a; (i)<(b); (i)++
#define range(...) _MACRO_OVERL3(__VA_ARGS__, _RANGE3, _RANGE2, _RANGE1)(__VA_ARGS__)

typedef pair<int, int> pii;

const int MX = 260000;
string S;
int len;

int z[MX];
int fail[MX];
int deep[MX];

vector<int> zlist[MX];
vector<int> el[MX];

void makeZ() {
    z[0] = len;
    int l = 0, r = 0;
    for (int i=1; i<len; i++) {
        if (i >= r) z[i] = 0;
        else {
            int ip = i - l;
            if (ip+z[ip] <= z[l]) z[i] = z[ip];
            else z[i] = r - i;
        }

        while (i+z[i] < len and S[i+z[i]] == S[z[i]])
            z[i] ++;

        if (i+z[i] > r) {
            l = i; r = i+z[i];
        }
        
    }

    for (int i=0; i<len; i++) zlist[z[i]].PB(i);
}

void makeKMP() {
    int t;
    fail[0] = t = -1;
    for (int i=1; i<len; i++) {
        while (t != -1 and S[t+1] != S[i]) t = fail[t];
        if (S[t+1] == S[i]) t ++;
        fail[i] = t;
    }

    for (int i=len; i>0; i--) {
        fail[i] = fail[i-1] + 1;
        el[fail[i]].PB(i);
        //cout << fail[i] << ' ' << i << endl;
    }
    //cout << "---" << endl;
}

deque<int> dq;
int ans[MX];
void dfs(int v) {

    vector<int> l1, l2;
    while (dq.size() and deep[dq.back()] < deep[v]) {
        l1.PB(dq.back());
        dq.pop_back();
    }
    dq.push_back(v);
    ans[v] = dq[0];
    //cout << v << ' ' << dq[0] << endl;
    for (auto x: el[v]) {
        while (dq.size() and deep[dq[0]] < x) {
            l2.PB(dq[0]);
            dq.pop_front();
        }
        dfs(x);
        while (l2.size()) {
            dq.push_front(l2.back());
            l2.pop_back();
        }
    }
    dq.pop_back();
    while (l1.size()) {
        dq.push_back(l1.back());
        l1.pop_back();
    }
}

int main() {
    IOS;
    FILEIO("cover");
    cin >> S;
    len = S.length();

    makeZ();
    makeKMP();

    priority_queue<pii, vector<pii>, greater<pii>> pq;
    set<int> st;
    static bool us[MX];

    for (int i=0; i<len; i++) {
        st.insert(i);
        pq.push({i, i+1});
    }
    st.insert(len);

    for (int i=1; i<=len; i++) {
        for (auto x: zlist[i-1]) {
            st.erase(x);
            us[x] = true;
            auto ref = st.lower_bound(x);
            int p = *ref, q = *(--ref);
            pq.push({q, p});
        }

        while ( [&]() {
                    if (pq.empty()) return false;
                    pii tp = pq.top();
                    if (us[tp.F] or us[tp.S]) return true;
                    if (tp.S - tp.F > i) return false;
                    return true;
                }() ) {
            pq.pop();
        }

        if (pq.empty()) deep[i] = len;
        else {
            pii t = pq.top(); 
            deep[i] = t.F + i;
        }
    }
    dfs(0);
    
    for (int i=1; i<=len; i++) {
        cout << ans[i] << (i == len ? '\n' : ' ');
    }
    return 0;
}

