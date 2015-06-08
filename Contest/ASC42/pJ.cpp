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

const int MXN = 100005;
const int L = 1005;

int N,M;
int fr,bk;
int que[MXN],vst[MXN],lst[MXN],value[MXN];
vector<int> E[MXN], rE[MXN];

int BFS(int st){
  fill(vst,vst+1+N,0);
  fr = bk = 0;
  vst[st] = 1;
  que[bk++] = st;
  while (fr < bk && bk <= L+5){
    int u = que[fr++];
    for (auto v : E[u]){
      if (vst[v]) continue;
      que[bk++] = v;
      vst[v] = 1;
    }
  }
  return bk;
}
void rBFS(int st){
  fill(vst,vst+1+N,0);
  fr = bk = 0;
  vst[st] = 1;
  que[bk++] = st;
  while (fr < bk){
    int u = que[fr++];
    value[u]++;
    for (auto v : rE[u]){
      if (vst[v]) continue;
      que[bk++] = v;
      vst[v] = 1;
    }
  }
}
int find_answer(int st){
  fill(vst,vst+1+N,0);
  fr = bk = 0;
  vst[st] = 1;
  que[bk++] = st;
  while (fr < bk){
    int u = que[fr++];
    for (auto v : E[u]){
      if (vst[v]) continue;
      que[bk++] = v;
      vst[v] = 1;
    }
  }
  return bk;
}
int main(){
  FILEIO("journey");
  while (cin >> N >> M && N){
    for (int i=1; i<=N; i++){
      value[i] = 0;
      E[i].clear();
      rE[i].clear();
    }
    for (int i=0,u,v; i<M; i++){
      cin >> u >> v;
      E[u].PB(v);
      rE[v].PB(u);
    }
    int case2 = 0;
    int v=0,d=0;
    for (int i=1; i<=N; i++){
      int tmp = BFS(i);
      if (tmp >= L){
        case2 = 1;
        break;
      }
      if (tmp >= d){
        d = tmp;
        v = i;
      }
    }
    if (case2){
      for (int i=1; i<=N; i++){
        lst[i-1] = i;
      }
      random_shuffle(lst,lst+N);
      for (int i=0; i<L && i < N; i++){
        rBFS(lst[i]);
      }
      v = 0; d = 0;
      for (int i=1; i<=N; i++){
        if (value[i] >= d){
          d = value[i];
          v = i;
        }
      }
      cout << v << " " << find_answer(v) << endl;
    } else {
      cout << v << " " << d << endl;
    }
  }
  return 0;
}

