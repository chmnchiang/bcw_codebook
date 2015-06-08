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
// par : fail link
// val : a topological order ( useful for DP )
// go[x] : automata edge ( x is integer in [0,26) )

class SAM{ public:
  class State{ public:
    int par, val, go[26];
    State () : par(0), val(0){ FZ(go); }
    State (int _val) : par(0), val(_val){ FZ(go); }
  };
  vector<State> vec;
  int root, tail;
  
  void init(int arr[], int len){
    vec.resize(2);
    vec[0] = vec[1] = State(0);
    root = tail = 1;
    for (int i=0; i<len; i++)
      extend(arr[i]);
  }
  void extend(int w){
    int p = tail, np = vec.size();
    vec.PB(State(vec[p].val+1));
    for ( ; p && vec[p].go[w]==0; p=vec[p].par)
      vec[p].go[w] = np;
    if (p == 0){
      vec[np].par = root;
    } else {
      if (vec[vec[p].go[w]].val == vec[p].val+1){
        vec[np].par = vec[p].go[w];
      } else {
        int q = vec[p].go[w], r = vec.size();
        vec.PB(vec[q]);
        vec[r].val = vec[p].val+1;
        vec[q].par = vec[np].par = r;
        for ( ; p && vec[p].go[w] == q; p=vec[p].par)
          vec[p].go[w] = r;
      }
    }
    tail = np;
  }
}sam;

typedef pair<int,int> pii;
const int MXN = 400005;
const int INF = 1029384756;

struct Edge{
  int v,f,c,re,ch,ori;
  Edge () { v=f=c=re=ch=ori=0; }
  Edge (int _v, int _f, int _c, int _re, int _ch):
    v(_v), f(_f), c(_c), re(_re), ch(_ch) {
      ori = _f;
    }
};


int N,ip[MXN];
int dis[MXN],fa[MXN],el[MXN];
int V,S,T;
int fr,bk,que[MXN],inq[MXN];
vector<Edge> E[MXN];
string ret;
vector<string> ans;

void add_edge(int u, int v, int f, int c, int ch){
  E[u].PB(Edge(v,f,c,E[v].size(),ch));
  E[v].PB(Edge(u,0,-c,(int)E[u].size()-1,26));
}
void DFS(int u){
  if (u == T) return ;
  for (auto &it : E[u]){
    if (it.ori > it.f){
      it.f++;
      if (it.ch != 26)
        ret += ('a'+it.ch);
      DFS(it.v);
      return ;
    }
  }
}

int main(){
  FILEIO("incomparable");
  string str;
  while (cin >> str){
    N = str.length();
    for (int i=0; i<N; i++)
      ip[i] = str[i]-'a';
    sam.init(ip,N);
    V = sam.vec.size();
    for (int i=0; i<=2*V+100; i++)
      E[i].clear();
    for (int i=0; i<V; i++){
      if (i>1) add_edge(i,i+sam.vec.size(),1,0,26);

      for (int j=0; j<26; j++){
        if (sam.vec[i].go[j] != 0){
          add_edge(i+ (i==1?0:sam.vec.size()),sam.vec[i].go[j],1,-1,j);
        }
      }
    }
    V += sam.vec.size()+5;
    S = 1;
    T = V-1;
    int tail = sam.tail;
    while (tail && tail != 1){
      add_edge(tail+sam.vec.size(),T,1,-1,26);
      tail = sam.vec[tail].par;
    }
    int cost = 0;
    while (true){
      for (int i=0; i<V; i++){
        dis[i] = INF;
        el[i] = -1;
        fa[i] = 0;
        inq[i] = 0;
      }
      set<pii> pq;
      dis[S] = 0;
      pq.insert(MP(0,S));
      int cnt = 1;
      inq[S] = 1;
      while (cnt){
        int u = pq.begin()->S;
        pq.erase(pq.begin());
        if (!inq[u]) continue;
        for (int i=0; i<(int)E[u].size(); i++){
          Edge it = E[u][i];
          if (it.f > 0){
            int v = it.v;
            int w = it.c;
            if (dis[v] > dis[u] + w){
              int tmp = dis[v];
              dis[v] = dis[u] + w;
              el[v] = i;
              fa[v] = u;
              if (!inq[v]){
                inq[v] = 1;
                cnt++;
              } else {
                pq.erase(pq.find(MP(tmp,v)));
              }
              pq.insert(MP(dis[v],v));
            }
          }
        }
        cnt--;
        inq[u] = 0;
      }
      if (dis[T] == INF) break;
      cost += dis[T];
      int u, v;
      v = T;
      while (v != S){
        u = fa[v];
        E[u][el[v]].f--;
        E[v][E[u][el[v]].re].f++;
        v = u;
      }
    }
    ans.clear();
    while (true){
      ret = "";
      DFS(S);
      if (ret == "") break;
      ans.PB(ret);
    }
    cout << ans.size() << " " << -cost - ans.size()<< endl;
    for (auto it : ans)
      cout << it << endl;
  }
  return 0;
}

