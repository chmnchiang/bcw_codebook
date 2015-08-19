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

const int MXN = 102005;
class Scc{
public:
  int n, nScc, vst[MXN], bln[MXN];
  vector<int> E[MXN], rE[MXN], vec;
  void init(int _n){
    n = _n;
    for (int i=0; i<MXN; i++){
      E[i].clear();
      rE[i].clear();
    }
  }
  void add_edge(int u, int v){
    E[u].PB(v);
    rE[v].PB(u);
  }
  void DFS(int u){
    vst[u]=1;
    for (auto v : E[u])
      if (!vst[v]) DFS(v);
    vec.PB(u);
  }
  void rDFS(int u){
    vst[u] = 1;
    bln[u] = nScc;
    for (auto v : rE[u])
      if (!vst[v]) rDFS(v);
  }
  void solve(){
    nScc = 0;
    vec.clear();
    FZ(vst);
    for (int i=0; i<n; i++)
      if (!vst[i]) DFS(i);
    reverse(vec.begin(),vec.end());
    FZ(vst);
    for (auto v : vec){
      if (!vst[v]){
        rDFS(v);
        nScc++;
      }
    }
  }
}scc;

typedef pair<int, int> pii;
const int MX = 101010;
int N, N2;
int colo[MX];
pii pos[MX];
int ip[MX];

int get_rev(int a) {
    int i = ip[a];
    if (pos[i].F == a) return pos[i].S;
    return pos[i].F;
}

int main() {
    FILEIO("chip");
    cin >> N; N2 = N + N;
    scc.init(N2);
    for(int i=0; i<N2; i++) {
        pos[i] = MP(-1, -1);
    }
    for(int i=0; i<N; i++) {
        cin >> colo[i];
    }
    for(int i=0; i<N+N; i++) {
        cin >> ip[i]; ip[i] -= 1;
        int a = ip[i];
        if (pos[a].F == -1) pos[a].F = i; 
        else pos[a].S = i;
    }

    for(int i=0; i<N+N; i++) {
        int p = i, q = (i+1)%(N+N);
        int a = ip[p], b = ip[q];
        //cout << colo[a] << ' ' << colo[b] << endl;
        if (a != b and colo[a] == colo[b]) {
            int pr = get_rev(p), qr = get_rev(q);
            scc.add_edge(p, qr);
            scc.add_edge(q, pr);
        }
    }
    scc.solve();

    bool fg = true;
    for(int i=0; i<N; i++) {
        int a = pos[i].F, b = pos[i].S;
        if(scc.bln[a] == scc.bln[b]) {
            fg = false;
            break;
        }
    }


    cout << (fg ? "YES" : "NO") << endl;

    if(fg) {
        for (int i=0; i<N; i++) {
            int a = pos[i].F, b = pos[i].S;
            if(scc.bln[a] > scc.bln[b]) cout << a+1 << ' ';
            else cout << b+1 << ' ';
        }
        cout << endl;
    }
    
  return 0;
}
