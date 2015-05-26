//bcw0x1bd2 {{{
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
#define IOS ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
  freopen(name".in", "r", stdin); \
  freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif

void RI() {}

template<typename... T>
void RI( int& head, T&... tail ) {
	    scanf("%d",&head);
			    RI(tail...);
}

mt19937 rng(0x5EED);
int randint(int lb, int ub) {
    return uniform_int_distribution<int>(lb, ub)(rng);
}
// Let's Fight! }}}

typedef pair<int,int> pii;
const int MXN = 200005;

struct DisjointSet{
  vector<int> fa;
  void init(int _n){
    fa.resize(_n);
    for (int i=0; i<_n; i++) fa[i] = i;
  }
  int find(int a){ return a == fa[a] ? a : fa[a]=find(fa[a]); }
  void uni(int a, int b){
    fa[find(b)] = find(a);
  }
};
struct Chain{
	pii lowest;
	vector<pii> station;
	int zone(int s){
		return (upper_bound(station.begin(), station.end(), MP(s,MXN))-1)->second;
	}
  pii seg(int a, int b){
    if (a > b) swap(a,b);
    if (lowest.F > b) return MP(zone(b), zone(a));
    if (lowest.F < a) return MP(zone(a), zone(b));
    return MP(lowest.S, max(zone(a),zone(b)));
  }
};
struct Transfer{
	vector<pii> station;
};
struct Query{
	int x,a,y,b,u,v;
};
struct Edge{
  int u,v;
  pii seg;
};
bool operator < (const Edge a, const Edge b){
  return a.seg < b.seg;
}

Chain chain[15];
Transfer transfer[55];
Query qry[MXN];

int N,Z,T,Q;
int M;
int np,possible[55];
Edge E[MXN];
vector<pii> egT[55][55];

void input(){
	cin >> N >> Z;
	for (int i=0, ci, m; i<N; i++){
		cin >> ci >> m;
		for (int j=0, z, s, t; j<m; j++){
			cin >> z >> s >> t;
			chain[i].station.PB(MP(s,z));
			if (j == 0) chain[i].lowest = MP(s,z);
			else if (z < chain[i].lowest.S) chain[i].lowest = MP(s,z);
		}
	}
	cin >> T;
	for (int i=0,m; i<T; i++){
		cin >> m;
		for (int j=0,x,s; j<m; j++){
			cin >> x >> s;
      x--;
			transfer[i].station.PB(MP(x,s));
		}
	}
	cin >> Q;
	for (int i=0; i<Q; i++){
		cin >> qry[i].x >> qry[i].a >> qry[i].y >> qry[i].b;
    qry[i].x--;
    qry[i].y--;
	}
}

void sweep_line(int L){
  DisjointSet djs;
  djs.init(T);
  vector<int> vec[55];
  for (int i=0; i<T; i++)
    vec[i].PB(i);
  int p=0;
  while (p<M && E[p].seg.F < possible[L]) p++;
  vector<Edge> eg;
  for (int i=L; i<np; i++){
    while (p<M && E[p].seg.F <= possible[i]){
      eg.PB(E[p]);
      p++;
    }
    for (int j=0; j<(int)eg.size(); j++){
      if (eg[j].seg.S <= possible[i]){
        int u = djs.find(eg[j].u);
        int v = djs.find(eg[j].v);
        if (u != v){
          djs.uni(u,v);
          for (auto it1 : vec[u]){
            for (auto it2 : vec[v]){
              egT[it1][it2].PB(MP(possible[L], possible[i]));
              egT[it2][it1].PB(MP(possible[L], possible[i]));
            }
          }
          for (auto it : vec[v])
            vec[u].PB(it);
          vec[v].clear();
        }
        swap(eg[j],eg.back());
        eg.pop_back();
        j--;
      }
    }
  }

}
void pre_solve(){
  np = 0;
  for (int i=0; i<N; i++)
    possible[np++] = chain[i].lowest.S;
  for (int i=0; i<T; i++){
    int x = transfer[i].station[0].F;
    int s = transfer[i].station[0].S;
    possible[np++] = chain[x].zone(s);
  }
  sort(possible, possible+np);
  np = unique(possible,possible+np) - possible;

  M = 0;
  for (int i=0; i<T; i++){
    for (int j=0; j<T; j++)
      for (auto u : transfer[i].station)
        for (auto v : transfer[j].station)
          if (u.F == v.F){
            E[M++] = (Edge){i,j,chain[u.F].seg(u.S, v.S)};
          }
  }
  sort(E,E+M);
  for (int i=0; i<np; i++)
    sweep_line(i);
  for (int i=0; i<T; i++){
    int x = transfer[i].station[0].F;
    int s = transfer[i].station[0].S;
    int z = chain[x].zone(s);
    egT[i][i].PB(MP(z,z));
  }
}

void solve(){
  for (int _q=0; _q<Q; _q++){
    int x1 = qry[_q].x;
    int x2 = qry[_q].y;
    int s1 = qry[_q].a;
    int s2 = qry[_q].b;
    pii t1[2],t2[2];
    t1[0] = t1[1] = t2[0] = t2[1] = MP(-1,-1);
    for (int i=0; i<T; i++){
      for (auto it : transfer[i].station){
        if (it.F == x1 && it.S <= s1){
          if (t1[0].F == -1 || t1[0].S < it.S)
            t1[0] = MP(i, it.S);
        }
        if (it.F == x1 && it.S >= s1){
          if (t1[1].F == -1 || t1[1].S > it.S)
            t1[1] = MP(i,it.S);
        }
        if (it.F == x2 && it.S <= s2){
          if (t2[0].F == -1 || t2[0].S < it.S)
            t2[0] = MP(i, it.S);
        }
        if (it.F == x2 && it.S >= s2){
          if (t2[1].F == -1 || t2[1].S > it.S)
            t2[1] = MP(i, it.S);
        }
      }
    }
    int ans = Z;
    if (x1 == x2){
      pii seg = chain[x1].seg(s1,s2);
      ans = seg.S - seg.F + 1;
    }
    for (int i=0,u,v; i<2; i++){
      u = t1[i].F;
      if (u == -1) continue;
      pii seg1 = chain[x1].seg(s1, t1[i].S);
      for (int j=0; j<2; j++){
        v = t2[j].F;
        if (v == -1) continue;
        pii seg2 = chain[x2].seg(s2, t2[j].S);
        for (auto it : egT[u][v]){
          int tx = min(seg1.F, seg2.F);
          int ty = max(seg1.S, seg2.S);
          tx = min(tx, it.F);
          ty = max(ty, it.S);
          ans = min(ans, ty-tx+1);
        }
      }
    }
    cout << ans << "\n";
  }
}

int main(int argc, char** argv){
  IOS;
  FILEIO("automatic");
  input();
  pre_solve();
  solve();

  return 0;
}
