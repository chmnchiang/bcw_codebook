//bcw0x1bd2 {{{
#include<bits/stdc++.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define IOS ios_base::sync_with_stdio(0); cin.tie(0);
#define SZ(x) ((int)((x).size()))
#define ALL(x) begin(x),end(x)
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
const int MXN = 1505;
const int MXM = 10005;

int N, M, E, ans[MXM], sum[MXN];
int has_ans;
vector<pii> eg[MXN*2];

void add(int v, int id, int p) {
  sum[v] += p;
  sum[v] %= 3;
  ans[id] += p;
  ans[id] %= 3;
}
int main(int argc, char** argv) {
  IOS;
  FILEIO("3colors");
  cin >> N >> M >> E;
  for (int i=0, u, v; i<E; i++) {
    cin >> u >> v;
    u--; v--;
    eg[u].PB({v+N, i});
    eg[v+N].PB({u, i});
  }
  for (int a=0; a<N; a++) {
    if (sum[a] == 0) {
      int ok = 0;
      for (auto it:eg[a]) {
        int b = it.F;
        int id1 = it.S;
        for (auto it2:eg[b]) {
          int c = it2.F;
          int id2 = it2.S;
          if (id1 == id2) continue;
          if (sum[c] != 1) {
            add(a, id1, 1);
            add(c, id2, 2);
          } else {
            add(a, id1, 2);
            add(c, id2, 1);
          }
          ok = 1;
          break;
        }
        if (ok) break;
      }
      if (!ok && SZ(eg[a]) != 1) {
        sum[a] = 1;
        for (auto it:eg[a]) {
          int id = it.S;
          ans[id] += 1;
        }
      }
    }
  }

  for (int i=0; i<N; i++) {
    if (!sum[i]) {
      puts("-1");
      return 0;
    }
  }

  for (int i=0; i<E; i++) {
    int res = ans[i] % 3;
    cout << res << " \n"[i==E-1];
  }


  return 0;
}

