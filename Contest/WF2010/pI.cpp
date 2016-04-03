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

const int dir[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
int N,M,tot,ans,arr[8][8];
int check_pos[4];
pii ip[4];
int fr,bk,que[514],vst[8][8],curt;

void go(int pos, int x, int y) {
  //cout << pos << endl;
  //REP(i,N) {
    //REP(j,M) cout << arr[i][j] << " ";
    //cout << endl;
  //}
  REP(i,4) {
    if (pos == check_pos[i] and (x != ip[i].F or y != ip[i].S)) {
      //cout << "CHECK POINT FAILED " << ip[i] << endl;
      return;
    }
    if (pos < check_pos[i] and (abs(x-ip[i].F)+abs(y-ip[i].S) > check_pos[i]-pos)) {
      //cout << "WONT ARRIVE CHECK POINT " << ip[i] << endl;
      return;
    }
    if (pos < check_pos[i] and arr[ip[i].F][ip[i].S]) {
      //cout << "CHECK POINT INSERT TOO EARLY " << ip[i] << endl;
      return;
    }
  }
  if (pos >= tot) {
    ans++;
    return;
  }
  int ok = 0;
  REP(i,N) {
    REP(j,M) {
      if (not arr[i][j]) {
        fr = bk = 0;
        curt++;
        vst[i][j] = curt;
        que[bk++] = i;
        que[bk++] = j;
        while (fr < bk) {
          int x1 = que[fr++];
          int y1 = que[fr++];
          REP(d,4) {
            int nx = x1 + dir[d][0];
            int ny = y1 + dir[d][1];
            if (nx < 0 or nx >= N or ny < 0 or ny >= M) continue;
            if (arr[nx][ny]) continue;
            if (vst[nx][ny] < curt) {
              vst[nx][ny] = curt;
              que[bk++] = nx;
              que[bk++] = ny;
            }
          }
        }
        if (bk/2+pos != tot) {
          arr[x][y] = 0;
          //cout << "BYE QQ" << endl;
          return;
        }
        ok = 1;
        break;
      }
    }
    if (ok) break;
  }
  REP(d,4) {
    int nx = x + dir[d][0];
    int ny = y + dir[d][1];
    if (nx < 0 or nx >= N or ny < 0 or ny >= M) continue;
    if (arr[nx][ny]) continue;
    arr[nx][ny] = pos+1;
    go(pos+1,nx,ny);
    arr[nx][ny] = 0;
  }
}

int main() {
  IOS;
  int cas = 0;
  while (cin >> M >> N) {
    if (not N) break;
    tot = N * M;
    REP(i,3) {
      cin >> ip[i].S >> ip[i].F;
      check_pos[i] = tot * (i+1) / 4;
    }
    ip[3] = {1,0};
    check_pos[3] = tot;
    ans = 0;
    REP(i,N) REP(j,M) arr[i][j] = 0;
    arr[0][0] = 1;
    go(1,0,0);
    cas++;
    cout << "Case " << cas << ": " << ans << endl;
  }

  return 0;
}

