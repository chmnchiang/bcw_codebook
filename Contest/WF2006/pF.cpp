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

typedef pair<int, int> pii;
const int MX = 223123;
const int INF = 1029384756;

#include <sys/resource.h>
void increase_stack_size() {
  const rlim_t ks = 63*1024*1024;
  struct rlimit rl;
  int res=getrlimit(RLIMIT_STACK, &rl);
  if(res==0){
    if(rl.rlim_cur<ks){
      rl.rlim_cur=ks;
      res=setrlimit(RLIMIT_STACK, &rl);
    }
  }
}

struct Item {
    pii p;
    int id;
    bool operator < (const Item &he) const {
        return tie(p,id) < tie(he.p, he.id);
    }
    bool operator > (const Item &he) const {
        return tie(p,id) > tie(he.p, he.id);
    }
};

struct BSP {
    int n;
    Item tree[MX*4];
    void init(int _n) {
        n = _n;
        init_tree(0, n, 0);
    }
    void init_tree(int l, int r, int id) {
        //cout << l << ' ' << r << ' ' << id << endl;
        if (l == r) {
            tree[id] = Item{{-INF, -INF}, l};
            return;
        }
        int m = (l + r) / 2, lc = id * 2 + 1, rc = id * 2 + 2;
        init_tree(l, m, lc);
        init_tree(m+1, r, rc);
        tree[id] = max(tree[lc], tree[rc]);
    }
    void upd(int l, int r, int fn, Item v, int id) {
        if (l == r) {
            tree[id] = v;
            return;
        }
        int m = (l + r) / 2, lc = id * 2 + 1, rc = id * 2 + 2;
        if (fn <= m) upd(l, m, fn, v, lc);
        else upd(m+1, r, fn, v, rc);
        tree[id] = max(tree[lc], tree[rc]);
    }
    Item qry(int l, int r, int fl, int fr, int id) {
        if (l == fl && r == fr) return tree[id];
        int m = (l + r) / 2, lc = id * 2 + 1, rc = id * 2 + 2;
        if (fr <= m) return qry(l, m, fl, fr, lc);
        if (m < fl) return qry(m+1, r, fl, fr, rc);
        return max(qry(l, m, fl, m, lc), qry(m+1, r, m+1, fr, rc));
    }
    void update(int x, Item v) {
        assert(0 <= x && x <= n);
        upd(0, n, x, v, 0);
    }
    Item query(int l, int r) {
        assert(0 <= l && l <= r && r <= n);
        return qry(0, n, l, r, 0);
    }
}rmq1, rmq2;

int N, nM;
int H[MX];
typedef array<int, 3> Event;
vector<Event> M;
int lc[MX], rc[MX];
int el[MX];

int calc(int l, int r) {
    //cout << l << ' ' << r << endl;
    if (r < l) {
        //assert(r == l-1);
        int res = 0, m = 0;
        int ql = el[l], qr = el[r+2] - 1;
        if (qr >= ql) {
            while (true) {
                auto d = rmq2.query(ql, qr);
                int dh, dc, di;
                dh = d.p.F;
                dc = d.p.S;
                di = d.id;
                if (dh < 0) break;
                m -= dc;
                res = max(res, m);

                rmq2.update(di, {{-INF, -INF}, di});
            }
        }
        return res;
    }
    //cout << l << ' ' << r << endl;
    auto dt = rmq1.query(l, r);
    //cout << l << ' ' << r << endl;
    
    int h = dt.p.F;
    int hid = dt.id;
    int m = 0;
    int res = 0;

    int ql = el[l], qr = el[r+2] - 1;
    if (qr >= ql) {
        while (true) {
            auto d = rmq2.query(ql, qr);
            int dh, dc, di;
            dh = d.p.F;
            dc = d.p.S;
            di = d.id;
            if (dh < h) break;
            m -= dc;
            res = max(res, m);

            rmq2.update(di, {{-INF, -INF}, di});
        }
    }

    int m1 = calc(l, hid-1), m2 = calc(hid+1, r);
    res = max(res, m+m1+m2);


    return res;
}

void build_events() {
    sort(ALL(M));
    rmq2.init(nM);
    for (int i=0; i<nM; i++) {
        rmq2.update(i, {{M[i][1], M[i][2]}, i});
    }

    int id = 0;
    for (int i=1; i<=N; i++) {
        while (id < nM and M[id][0] < i) {
            id ++;
        }
        el[i] = id;
    }
    el[N+1] = nM;
}

int main() {
    increase_stack_size();
    IOS;
    int T;
    cin >> T;
    for (int cas=1; cas<=T; cas++) {
        cin >> N >> nM;
        for (int i=1; i<=N-1; i++) {
            cin >> H[i];
        }
        M.clear();
        int ans = 0;
        for (int i=0; i<nM; i++) {
            int x, h, t;
            cin >> x >> h >> t;
            int c = (t == 1) ? 1 : -1;
            ans += t;
            M.PB({x, h, c});
        }


        //cout << 123 << endl;
        rmq1.init(N+1);
        //cout << 123 << endl;
        for (int i=1; i<=N-1; i++) {
            rmq1.update(i, {{H[i], i}, i});
        }

        build_events();

        ans += calc(1, N-1);
        
        cout << "Case #" << cas << ": " << ans << endl;
    }
    return 0;
}
