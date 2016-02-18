#include<bits/stdc++.h>/*{{{*/
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
}/*}}}*/
// Let's Fight!
#define REP(i,x) for(int i=0; i<(x); i++)
#define REP1(i,a,b) for(int i=(a); i<=(b); i++)

typedef pair<int,int> pii;
typedef long long ll;
const int LOG = 18;
const int MXN = 300005;
const ll INF = 1e17;

struct Edge {
    int u, v, w;
};
ostream& operator <<(ostream &s, const Edge &e) {
    return s<<"{"<<e.u<<"->"<<e.v<<" : "<<e.w<<"}";
}

Edge eg[MXN];
map<pii,int> mp;

int N,M,K;
int nxt[LOG][MXN];
vector<pii> tmpE[MXN];
vector<pii> E[MXN];
ll ans,dis[MXN];
int fr,bk,que[MXN],inq[MXN];
int wen[MXN];

int query(int eid, int k) {
    int u = eid;
    for (int i=0; i<LOG && k; i++) {
        if (k & (1 << i)) {
            k -= 1 << i;
            u = nxt[i][u];
        }
    }
    return u;
}
int query_edge(int u, int w) {
    int id = lower_bound(ALL(tmpE[u]), pii(w,0)) - begin(tmpE[u]);
    int best = id;
    if (id > 0) {
        best = id - 1;
    }
    if (id < SZ(tmpE[u]) - 1) {
        int c1 = abs(tmpE[u][best].F - w);
        int c2 = abs(tmpE[u][id+1].F - w);
        if (best == id || c1 > c2 || (c1 == c2 && tmpE[u][best].S > tmpE[u][id+1].S))
            best = id + 1;
    }
    int v = tmpE[u][best].S;
    return mp[pii(u,v)];
}
void build_edge() {
    REP1(i,1,M*2) {
        int v = eg[i].v;
        int w = eg[i].w;
        nxt[0][i] = query_edge(v, w);
    }
    REP1(i,1,LOG-1) {
        REP1(j,1,M*2) {
            nxt[i][j] = nxt[i-1][nxt[i-1][j]];
        }
    }
    REP1(i,1,N) {
      wen[i] = 2 * M + i;
    }
    REP1(i,1,M*2) {
        int u = eg[i].u;
        E[i].PB({nxt[0][i], 1});
        int tmp = query(i, K);
        int nv = eg[tmp].v;
        E[i].PB({wen[nv], K});
        E[wen[u]].PB({i, 1});
    }
}
void solve() {
    REP1(i,1,wen[N]) {
      inq[i] = 0;
      dis[i] = INF;
    }
    fr = bk = 0;
    que[bk++] = wen[1];
    dis[wen[1]] = 0;
    inq[wen[1]] = 1;

    int tt = mp[pii(1,tmpE[1][0].S)];
    for (int _ = 1; ; _++) {
      int hao = wen[eg[tt].v];
      if (inq[tt] && inq[hao]) {
        break;
      }
      if (!inq[hao]) {
        dis[hao] = _;
        que[bk++] = hao;
        inq[hao] = 1;
      }
      if (!inq[tt]) {
        dis[tt] = _;
        que[bk++] = tt;
        inq[tt] = 1;
      }
      tt = nxt[0][tt];
    }

    while (fr != bk) {
      int u = que[fr++];
      inq[u] = 0;
      if (fr >= MXN) fr -= MXN;
      for (auto it:E[u]) {
        int v = it.F;
        int w = it.S;
        if (dis[v] > dis[u] + w) {
          dis[v] = dis[u] + w;
          if (!inq[v]) {
            que[bk++] = v;
            if (bk >= MXN) bk -= MXN;
            inq[v] = 1;
          }
        }
      }
    }
    ans = dis[wen[N]];
    REP1(i,1,2*M) {
        int v = eg[i].v;
        if (v == N) {
          ans = min(ans, dis[i]);
        }
    }
    if (ans == INF) ans = -1;
    //assert(ans != INF);
}

int main() {
    IOS;
    int nT;
    cin >> nT;
    REP1(cas,1,nT) {
        cin >> N >> M >> K;
        REP(i,MXN) {
            E[i].clear();
            tmpE[i].clear();
        }
        mp.clear();
        REP1(i,1,M) {
            cin >> eg[i].u >> eg[i].v >> eg[i].w;
            eg[i+M] = eg[i];
            swap(eg[i+M].u, eg[i+M].v);
        }
        REP1(i,1,M*2) {
            tmpE[eg[i].u].PB({eg[i].w, eg[i].v});
            mp[pii(eg[i].u,eg[i].v)] = i;
        }
        REP1(i,1,N) {
            sort(ALL(tmpE[i]));
        }
        ans = INF;
        build_edge();
        solve();
        cout << "Case #" << cas << ": " << ans << endl;
    }

    return 0;
}

