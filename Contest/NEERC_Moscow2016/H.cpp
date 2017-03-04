#pragma GCC optimize ("O2")
#include<bits/stdc++.h>
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
#define REP(i,x) for (int i=0; i<(x); i++)
#define REP1(i,a,b) for (int i=(a); i<=(b); i++)
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
// Let's Fight!

static const int LOSE = 0;
static const int WIN = 1;
static const int MAYBE = 2;
static const string teamStr[] = {"Russia", "Sweden", "Finland", "NA"};

using Arr = array<int,3>;
struct Race {
  int t1,t2,g1,g2,ot;
};

Race race[6];
int point[6], win[6], pwin[6], in[6], out[6];
int canwin[6][6];
int arr[5][10];

int team2id(string s) {
  REP(i,4) if (teamStr[i] == s) return i;
  assert(false);
}

inline bool isin(vector<int> vec) {
  for(auto y: vec) if (y == 0) return true;
  return false;
}

using pii = pair<int, int>;
int cocona(vector<int> vec, int r, int k) {
  int n = SZ(vec);
  if (k <= 0) return LOSE;
  if (n == 1) {
    if (isin(vec)) return WIN;
    return LOSE;
  }

  if (n == 2) {
    int t = vec[0], q = vec[1];
    if (canwin[q][t]) swap(t, q);

    if (cocona({t}, 5, k) == WIN) return WIN;
    return cocona({q}, 5, k-1);
  }
  if (r == 5) {
    if (!isin(vec)) return LOSE;
    if (k >= n) return WIN;
    else return MAYBE;
  }


  vector<pii> zz;
  for (auto x: vec) zz.PB({arr[r][x], x});
  sort(ALL(zz));
  reverse(ALL(zz));

  int i = 0, j = 0;
  while (i < n) {
    vector<int> vvv;
    while (j < n && zz[j].F == zz[i].F) {
      vvv.PB(zz[j].S);
      j++;
    }
    int t = cocona(vvv, r+1, k);
    if (t != LOSE) return t;

    k -= SZ(vvv);
    i = j;
  }

  return LOSE;
}

int solve() {
  REP(i,6) {
    point[i] = win[i] = pwin[i] = in[i] = out[i] = 0;
    REP(j,6) canwin[i][j] = 0;
  }
  REP(i,6) {
    int t1 = race[i].t1;
    int t2 = race[i].t2;
    int g1 = race[i].g1;
    int g2 = race[i].g2;
    int ot = race[i].ot;
    if (ot) assert(abs(g1-g2) == 1);
    if (g1 < g2) {
      swap(t1,t2);
      swap(g1,g2);
    }
    if (ot) {
      point[t1] += 2;
      point[t2] += 1;
    } else {
      point[t1] += 2;
      pwin[t1]++;
    }

    win[t1]++;
    in[t1] += g1;
    out[t1] += g2;
    in[t2] += g2;
    out[t2] += g1;

    canwin[t1][t2] = 1;
  }
  REP(i,4) arr[0][i] = point[i];
  REP(i,4) arr[1][i] = win[i];
  REP(i,4) arr[2][i] = pwin[i];
  REP(i,4) arr[3][i] = in[i]-out[i];
  REP(i,4) arr[4][i] = in[i];
  /*
  cout << "===" <<endl;
  REP(i,5) {
    REP(j,4) cout << arr[i][j] << " ";
    cout << endl;
  }
  */
  vector<int> v = {0, 1, 2, 3};
  return cocona(v, 0, 2);


  return MAYBE;
}
int main() {
  IOS;
  string s;
  REP(i,5) {
    getline(cin, s);
    stringstream ss(s);
    string t1,t2,ot;
    int g1,g2;
    ss >> t1 >> t2 >> g1 >> g2;
    ss >> ot;
    race[i] = {team2id(t1), team2id(t2), g1, g2, 0};
    if (!ss.fail())
      race[i].ot = 1;
  }
  cin >> s;
  race[5].t1 = team2id(s);
  cin >> s;
  race[5].t2 = team2id(s);


  vector<Arr> cond;
  REP(i,100) REP(j,100) {
    if (i == j) continue;
    cond.PB({i,j,0});
    if (abs(i-j) == 1)
      cond.PB({i,j,1});
  }

  /*
  race[5].g1 = 0;
  race[5].g2 = 1;
  race[5].ot = 1;
  cout << solve() << endl;
  return 0;
  */
  
  int winCnt = 0;
  int maybe = 0;
  for (auto it:cond) {
    race[5].g1 = it[0];
    race[5].g2 = it[1];
    race[5].ot = it[2];
    int res = solve();
    if (res == MAYBE) {
      maybe = 1;
    } else if (res == WIN) {
      winCnt++;
    } else {
      // pass
    }
  }

  if (maybe) cout << "Believe in playoff!" << endl;
  else {
    if (winCnt == SZ(cond)) cout << "Already in playoff!" << endl;
    else if (winCnt == 0) cout << "No chance" << endl;
    else cout << "Believe in playoff!" << endl;
  }

  return 0;
}
