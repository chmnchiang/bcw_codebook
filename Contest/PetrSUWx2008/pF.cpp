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

struct Point {
  int x,y,z;
  Point operator - (const Point &he) {
    return {x-he.x,y-he.y,z-he.z};
  }
  bool operator < (const Point &he) const {
    return tie(x,y,z) < tie(he.x,he.y,he.z);
  }
  bool operator == (const Point &he) const {
    return tie(x,y,z) == tie(he.x,he.y,he.z);
  }
  friend ostream& operator << (ostream &s, const Point &he) {
    return s << "(" << he.x << "," << he.y << "," << he.z << ")";
  }
};
struct Block {
  vector<Point> vec;
  bool operator < (const Block &he) const {
    return vec < he.vec;
  }
  bool operator == (const Block &he) const {
    return vec == he.vec;
  }
  void norm() {
    if (vec.empty()) return;
    Point mn = vec[0];
    for (auto it:vec) mn = min(mn,it);
    for (auto &it:vec) it = it - mn;
    sort(ALL(vec));
  }
};

Block rotatex(Block a) {
  for (auto &it:a.vec) {
    swap(it.y,it.z);
    it.y = -it.y;
  }
  a.norm();
  return a;
}
Block rotatey(Block a) {
  for (auto &it:a.vec) {
    swap(it.x,it.z);
    it.x = -it.x;
  }
  a.norm();
  return a;
}
Block rotatez(Block a) {
  for (auto &it:a.vec) {
    swap(it.x,it.y);
    it.x = -it.x;
  }
  a.norm();
  return a;
}

vector<Block> blk[7];

void predo() {
  vector<Point> vec;
  vec = {{0,0,0},{0,1,0},{1,0,0}};
  blk[0].PB({vec});
  vec = {{0,0,0},{1,0,0},{1,1,0},{2,0,0}};
  blk[1].PB({vec});
  vec = {{0,0,0},{1,0,0},{1,1,0},{2,1,0}};
  blk[2].PB({vec});
  vec = {{0,0,0},{0,1,0},{1,0,0},{2,0,0}};
  blk[3].PB({vec});
  vec = {{0,0,0},{0,0,1},{1,0,1},{1,1,1}};
  blk[4].PB({vec});
  vec = {{0,0,0},{0,1,0},{1,0,0},{1,0,-1}};
  blk[5].PB({vec});
  vec = {{0,0,0},{0,0,1},{0,1,1},{1,0,1}};
  blk[6].PB({vec});
  REP(i,7) {
    blk[i][0].norm();
    Block tmp = blk[i][0];
    REP(_,4) {
      tmp = rotatez(tmp);
      REP(__,4) {
        tmp = rotatey(tmp);
        REP(___,4) {
          tmp = rotatex(tmp);
          blk[i].PB(tmp);
        }
      }
    }
    sort(ALL(blk[i]));
    blk[i].resize(unique(ALL(blk[i]))-begin(blk[i]));
  }
}


const ll P1 = 12721;
const ll P2 = 14341;
const ll MOD = 1000000000039;
const int dir[6][3] = {{1,0,0},{-1,0,0},{0,1,0},{0,-1,0},{0,0,1},{0,0,-1}};

unordered_set<ll> app;
int fr,bk,que[20*20*20*4];
int vst[21][21][21],curt;
int M,N,K;
int tot;
int ban[21][21][21];

inline bool check_ok(int x, int y, int z, Block b) {
  for (auto it:b.vec) {
    int nx = x + it.x;
    int ny = y + it.y;
    int nz = z + it.z;
    if (nx < 0 or nx >= M or ny < 0 or ny >= N or nz < 0 or nz >= K or ban[nx][ny][nz])
      return false;
  }
  return true;
}
inline void set_block(int x, int y, int z, Block b, int v) {
  for (auto it:b.vec) {
    int nx = x + it.x;
    int ny = y + it.y;
    int nz = z + it.z;
    ban[nx][ny][nz] = v;
  }
}
bool DFS(int id) {
  if (id > 8) {
    return tot == M*N*K;
  }
  ll hs = 0;
  REP(i,M) REP(j,N) REP(k,K) {
    if (ban[i][j][k]) hs = (hs + 1) * P1 % MOD;
    else hs = hs * P2 % MOD;
  }
  if (app.count(hs)) return false;
  app.insert(hs);

  curt++;
  int three = 0;
  if (id > 2) three++;
  REP(i,M) REP(j,N) REP(k,K) {
    if (ban[i][j][k] or vst[i][j][k] >= curt) continue;
    fr = bk = 0;
    que[bk++] = i;
    que[bk++] = j;
    que[bk++] = k;
    vst[i][j][k] = curt;
    while (fr < bk) {
      int x = que[fr++];
      int y = que[fr++];
      int z = que[fr++];
      REP(d,6) {
        int nx = x + dir[d][0];
        int ny = y + dir[d][1];
        int nz = z + dir[d][2];
        if (nx < 0 or nx >= M or ny < 0 or ny >= N or nz < 0 or nz >= K) continue;
        if (ban[nx][ny][nz] or vst[nx][ny][nz] >= curt) continue;
        vst[nx][ny][nz] = curt;
        que[bk++] = nx;
        que[bk++] = ny;
        que[bk++] = nz;
      }
    }
    int c = bk / 3;
    if ((c-3) % 4 == 0) three++;
    else if (c % 4 != 0) return false;
    if (three >= 2) return false;
  }

  REP(i,M) REP(j,N) REP(k,K) {
    if (!ban[i][j][k]) {
      for (auto it:blk[id-2]) {
        if (check_ok(i,j,k,it)) {
          set_block(i,j,k,it,id);
          tot += SZ(it.vec);
          if (DFS(id+1)) return true;
          tot -= SZ(it.vec);
          set_block(i,j,k,it,0);
        }
      }
    }
  }
  return false;
}
int main() {
  IOS;
  FILEIO("lock");
  predo();
  cin >> M >> N >> K;
  tot = 0;
  REP(i,M) REP(j,N) REP(k,K) {
    cin >> ban[i][j][k];
    ban[i][j][k] ^= 1;
    tot += ban[i][j][k];
  }
  assert(DFS(2));
  REP(i,M) {
    REP(j,N) {
      REP(k,K) {
        cout << (ban[i][j][k]-1);
      }
      cout << endl;
    }
    cout << endl;
  }

  return 0;
}
