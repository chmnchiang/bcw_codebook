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

const int MX = 40;
const double EPS = 1e-6;
const int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

int M, N;
char mp[MX][MX];
bool can[MX][MX][MX][MX];
vector<pair<int, int> > ans;

bool inr(int x, int y) {
  if(x < 0 or x >= M or y < 0 or y >= N) return false;
  return true;
}

double getp(double d, double alpha, double beta, double x) {
  return d * (x - alpha) + beta;
}


bool judge0(int x1, int y1, int x2, int y2) {
  if(x1 > x2) return judge0(x2, y2, x1, y1);

  double d = (0.0 + y2 - y1) / (0.0 + x2 - x1);
  double rx = x1 + 0.5, ry = y1 + 0.5;
  int low = x1 + 1;
  int high = x2;
  bool deb = (x1 == 1 and y1 == 3 and x2 == 2 and y2 == 2);
  //if(deb) cout << "!@#" << endl;
  
#define _jx(x, y) if(mp[x][y] == '#') return false; \
    if(mp[x-1][y]=='#') return false;
  for(int i=low; i<=high; i++) {
    double now = getp(d, rx, ry, 0.0+i) - EPS/2;
    int q = int(now);

    _jx(i, q);
    if( now - floor(now) < EPS ) {
      _jx(i, q-1);
    }

    if( ceil(now) - now < EPS ) {
      _jx(i, q+1);
    }
  }

  return true;
}

bool judge1(int x1, int y1, int x2, int y2) {
  if(y1 > y2) return judge1(x2, y2, x1, y1);

  double d = (0.0 + x2 - x1) / (0.0 + y2 - y1);
  double rx = x1 + 0.5, ry = y1 + 0.5;
  int low = y1 + 1;
  int high = y2;
  
#define _jy(x, y) if(mp[x][y] == '#') return false; \
    if(mp[x][y-1]=='#') return false;

  for(int i=low; i<=high; i++) {
    double now = getp(d, ry, rx, 0.0+i) - EPS;
    int q = int(now);
    _jy(q, i);
    if( now - floor(now) < EPS ) {
      _jy(q-1, i);
    }

    if( ceil(now) - now < EPS ) {
      _jy(q+1, i);
    }
  }

  return true;
}

void pre() {
  for(int i=0; i<M; i++) {
    for(int j=0; j<N; j++) {
      if(mp[i][j] == '#') continue;

      for(int ii=0; ii<M; ii++) {
        for(int jj=0; jj<N; jj++) {
          if(mp[ii][jj] == '#') continue;

          bool fg = true;
          if(i != ii) {
            fg &= judge0(i, j, ii, jj);
          }

          if(fg and j != jj) {
            fg &= judge1(i, j, ii, jj);
          }

          can[i][j][ii][jj] = fg;
          if(fg) {
            //cout << i << ' ' << j << ' ' << ii << ' ' << jj << endl;
          }
        }
      }
    }
  }
}

int main(){
  IOS;
  FILEIO("jealous");
  cin >> M >> N;

  for(int i=0; i<M; i++) {
    cin >> mp[i];
  }

  pre();

  for(int x1=0; x1<M; x1++) {
    for(int y1=0; y1<N; y1++) {
      if(mp[x1][y1] == '#') continue;
      bool fg = true;
      for(int x2=0; x2<M and fg; x2++) {
        for(int y2=0; y2<N and fg; y2++) {
        if(mp[x2][y2] == '#' or (x1 == x2 and y1 == y2)) continue;
          bool find = false;
          for(int d=0; d<4; d++) {
            int nx = x1, ny = y1;
            do {
              if(not can[x2][y2][nx][ny]) {
                find = true;
                //cout << "FIND: " << x2 << ' ' << y2 << ' ' << nx << ' ' << ny << ' ' << endl;
                break;
              }
              nx += dir[d][0];
              ny += dir[d][1];
            } while( inr(nx, ny) and mp[nx][ny] != '#');
            if(find) break;
          }

          if(not find) {
            fg = false;
            //cout << "NOT Find: " << x2 << ' ' << y2 << ' ' << x1 << ' ' << y1 << ' ' << endl;
            break;
          }
        }
      }

      if(fg) {
        ans.PB(MP(x1, y1));
      }
    }
  }

  cout << ans.size() << endl;
  for(int i=0; i<(int)ans.size(); i++) {
    cout << ans[i].F+1 << ' ' << ans[i].S+1 << endl;
  }


	return 0;
}

