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

//#define int long long
const int MXN = 100005;

struct Event {
    ll t;
    int f,id;
};
struct SegmentTree {
    int n;
    pii tree[4*MXN];
    void init(int _n) {
        n = _n;
        REP(i,4*MXN) tree[i] = {-1,-1};
    }
    void upd_tree(int l, int r, int fn, int x, int id) {
        if (l == r) {
            tree[id] = {x,x};
            return;
        }
        int mid=(l+r)/2, lc=id*2, rc=id*2+1;
        if (fn <= mid) upd_tree(l,mid,fn,x,lc);
        else upd_tree(mid+1,r,fn,x,rc);
        tree[id] = tree[lc];
        if (tree[id].F == -1) tree[id].F = tree[rc].F;
        if (tree[rc].S != -1) tree[id].S = tree[rc].S;
    }
    void upd(int id, int x) {
        upd_tree(1,n,id,x,1);
    }
    pii qry_tree(int l, int r, int fl, int fr, int id) {
        if (l == fl and r == fr) return tree[id];
        int mid=(l+r)/2, lc=id*2, rc=id*2+1;
        if (fr <= mid) return qry_tree(l,mid,fl,fr,lc);
        if (mid < fl) return qry_tree(mid+1,r,fl,fr,rc);
        pii x = qry_tree(l,mid,fl,mid,lc);
        pii y = qry_tree(mid+1,r,mid+1,fr,rc);
        if (x.F == -1) x.F = y.F;
        if (y.S != -1) x.S = y.S;
        return x;
    }
    pii qry(int l, int r) {
        if (l > r) swap(l,r);
        return qry_tree(1,n,l,r,1);
    }
}tree;

int N,M,A,B,done[MXN];
int curF,call;
ll curT,lstS,ans[MXN];
queue<Event> que;
Event ip[MXN];
vector<int> vec[MXN];

void push(int &i) {
    //cout << "PUSH " << i << endl;
    que.push(ip[i]);
    vec[ip[i].f].push_back(i);
    tree.upd(ip[i].f,ip[i].f);
    i++;
}
int32_t main() {
    FILEIO("elevator");
    IOS;
    cin >> N >> M >> A >> B;
    REP(i,M) {
        cin >> ip[i].t >> ip[i].f;
        ip[i].id = i;
        done[i] = 0;
    }

    tree.init(N);
    call = -1;
    curF = 1;
    curT = 0;
    lstS = -1029384756;
    int curi = 0;
    while (!que.empty() or curi < M or call != -1) {
        //cout << "CURT = " << curT << " " << curF << endl;
        if (call == -1) {
            if (!que.empty()) {
                Event e = que.front();
                if (!done[e.id]) call = e.id;
                else que.pop();
            } else {
                curT = ip[curi].t;
                while (curi < M and ip[curi].t <= curT) {
                    push(curi);
                }
            }
            continue;
        }
        if (!vec[curF].empty()) {
            auto it = vec[curF][0];
            ans[it] = curT;
            done[it] = 1;
            lstS = curT;
            REP1(i,1,SZ(vec[curF])) vec[curF][i-1] = vec[curF][i];
            vec[curF].pop_back();
            curT += A;
            if (vec[curF].empty()) {
                tree.upd(curF,-1);
            }
            while (curi < M and ip[curi].t <= curT) {
                push(curi);
            }
            if (done[call]) {
                call = -1;
            }
            continue;
        }
        if (curT < lstS + A) {
            if (curi < M and ip[curi].t <= curT) {
                call = curi;
                push(curi);
                continue;
            }
            curT++;
        } else {
            if (curT == lstS + A and curi < M and ip[curi].f == curF) {
                push(curi);
                continue;
            }
            if (curF < ip[call].f) {
                curF++;
                curT += B;
            } else {
                curF--;
                curT += B;
            }
            while (curi < M and ip[curi].t <= curT) {
                push(curi);
            }
            continue;
            pii tmp = tree.qry(curF,ip[call].f);
            if (curF < ip[call].f) {
                int fst = tmp.F;
                //cout << ip[curi].t << " " <<ip[curi].f << " " <<ip[curi].id << endl;
                if (curi < M and ip[curi].f >= curF and ip[curi].f < fst and curT+B*(ip[curi].f-curF) >= ip[curi].t) {
                    curT += B*(ip[curi].f-curF);
                    curF = ip[curi].f;
                    push(curi);
                } else {
                    curT += B*(fst-curF);
                    curF = fst;
                }
            } else {
                int fst = tmp.S;
                if (curi < M and ip[curi].f <= curF and ip[curi].f > fst and curT+B*(curF-ip[curi].f) >= ip[curi].t) {
                    curT += B*(curF-ip[curi].f);
                    curF = ip[curi].f;
                    push(curi);
                } else {
                    curT += B*(curF-fst);
                    curF = fst;
                }
            }
        }
    }

    REP(i,M) {
        assert(done[i]);
        cout << ans[i] << "\n";
    }

    return 0;
}

