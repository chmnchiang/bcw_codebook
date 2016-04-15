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
// Let's Fight!/*}}}*/

typedef pair<int,int> pii;

int nRing,totA,totB,col[30],done[30];
int c0,c1,dp[2][30];
pii nd[30];
vector<int> E[30];

inline int ban(int v) {
  return !(!E[v].empty() or (nd[v].F+nd[v].S));
}
int go(int goal, int u, int f) {
  if (!done[u] and col[u] == 0) c0++;
  else if (!done[u] and col[u] == 1) c1++;
  done[u] = 1;
  int &res = dp[goal][u];
  if (res != -1) return res;
  res = 0;
  if (col[u] == goal) {
    for (auto v:E[u]) {
      if (v == f) continue;
      res += go(goal,v,u);
    }
  } else if (col[u] == (goal^1)) {
    res = 2 + go(goal^1,u,f);
  } else {
    int tmp = 2;
    for (auto v:E[u]) {
      if (v == f) continue;
      res += min(go(goal,v,u), go(goal^1,v,u)+2);
      tmp += go(goal^1,v,u);
    }
    res = min(res, tmp);
  }
  return res;
}
int calc() {
  int res,con0,con1;
  con0 = con1 = res = 0;
  REP(i,30) {
    done[i] = 0;
    dp[0][i] = dp[1][i] = -1;
    if (ban(i)) done[i] = 1;
  }
  //REP(i,30) {
    //if (ban(i)) continue;
    //cout << i << " " << col[i] << " ";
    //cout << E[i] << endl;
  //}
  REP(i,30) {
    if (done[i]) continue;
    if (col[i] == 0) {
      c0 = c1 = 0;
      res += go(0,i,i);
      if (c0) {
        con0++;
      }
      if (c1) {
        con1++;
        res--;
      }
    }
  }
  REP(i,30) {
    if (done[i]) continue;
    if (col[i] == 1) {
      c0 = c1 = 0;
      //cout << "GO " << 1 << " " << i << endl;
      assert(go(1,i,i) == 0);
      assert(c0 == 0);
      con1++;
    }
  }
  //cout << pii(con0,con1) << endl;
  if (con0) res += con0-1;
  if (con1) res += con1-1;
  return res;
}
int main() {
  IOS;
  string s;
  int cas = 0;
  while (cin >> s) {
    REP(i,30) {
      nd[i] = {0,0};
      E[i].clear();
    }
    if ('A' <= s[0] and s[0] <= 'Z') swap(s[0],s[1]);
    if ('A' <= s[1] and s[1] <= 'Z') {
      int id = s[0] - 'a';
      if (s[1] <= 'M') nd[id].F++;
      else nd[id].S++;
    } else {
      int u = s[0] - 'a';
      int v = s[1] - 'a';
      E[u].PB(v);
      E[v].PB(u);
    }

    while (cin >> s) {
      if (s[0] == '0') break;
      if ('A' <= s[0] and s[0] <= 'Z') swap(s[0],s[1]);
      if ('A' <= s[1] and s[1] <= 'Z') {
        int id = s[0] - 'a';
        if (s[1] <= 'M') nd[id].F++;
        else nd[id].S++;
      } else {
        int u = s[0] - 'a';
        int v = s[1] - 'a';
        E[u].PB(v);
        E[v].PB(u);
      }
    }

    nRing = totA = totB = 0;
    REP(i,30) {
      if (!ban(i)) nRing++;
      totA += nd[i].F;
      totB += nd[i].S;
    }

    cas++;
    cout << "Case " << cas << ": ";
    //cout << endl;

    if (nRing == 1) {
      if (totA and totB) {
        cout << "impossible" << endl;
      } else {
        REP(i,30) {
          if (nd[i].F) col[i] = 0;
          else if (nd[i].S) col[i] = 1;
          else col[i] = 2;
        }
        cout << 0 << " " << calc() << endl;
      }
    } else {
      int f1,f2,keys,empty;
      int rings = 1029384756;
      f1 = f2 = keys = empty = 0;
      REP(i,30) {
        if (ban(i)) continue;
        if (nd[i].F and nd[i].S) {
          if (nd[i].F < nd[i].S) f1 = 1;
          if (nd[i].F > nd[i].S) f2 = 1;
          if (nd[i].F == nd[i].S) f1 = f2 = 1;
        }
        if (!(nd[i].F+nd[i].S)) empty++;
        keys += min(nd[i].F,nd[i].S);
      }
      keys *= 2;
      if (f1 and f2) {
        int f3,f4;
        f3 = f4 = 0;
        vector<int> same,emp;
        REP(i,30) {
          if (ban(i)) continue;
          if (nd[i].F < nd[i].S) col[i] = 1, f4 = 1;
          else if (nd[i].F > nd[i].S) col[i] = 0, f3 = 1;
          else if (nd[i].F + nd[i].S) same.PB(i);
          else col[i] = 2;
        }

        REP(i,1<<SZ(same)) {
          REP(j,SZ(same)) {
            if (i & (1<<j)) col[same[j]] = 0;
            else col[same[j]] = 1;
          }
          if (!f3 and i == 0) continue;
          if (!f4 and __builtin_popcount(i) == SZ(same)) continue;
          rings = min(rings,calc());
        }
        if (!f3 and empty) {
          for (auto i:same) col[i] = 1;
          REP(i,30) {
            if (ban(i)) continue;
            if (nd[i].F or nd[i].S) continue;
            col[i] = 0;
            rings = min(rings,calc());
            col[i] = 2;
          }
        }
        if (!f4 and empty) {
          for (auto i:same) col[i] = 0;
          REP(i,30) {
            if (ban(i)) continue;
            if (nd[i].F or nd[i].S) continue;
            col[i] = 1;
            rings = min(rings,calc());
            col[i] = 2;
          }

        }
      } else if (f1 || f2) {
        REP(i,30) {
          if (ban(i)) continue;
          if (f2) swap(nd[i].F,nd[i].S);
        }
        if (empty) {
          vector<int> vec;
          REP(i,30) {
            if (ban(i)) continue;
            if (!nd[i].S) vec.PB(i);
            else col[i] = 0;
          }
          for (auto it:vec) {
            for (auto it2:vec) col[it2] = 2;
            col[it] = 1;
            rings = min(rings, calc());
          }
        } else {
          int mn = 1029384756;
          REP(i,30) {
            if (ban(i)) continue;
            mn = min(mn, nd[i].S-nd[i].F);
          }
          keys += mn * 2;
          vector<int> vec;
          REP(i,30) {
            if (ban(i)) continue;
            if (nd[i].S-nd[i].F == mn) {
              vec.PB(i);
            } else if (nd[i].S) {
              col[i] = 0;
            } else {
              col[i] = 2;
            }
          }
          for (auto it:vec) {
            for (auto it2:vec) col[it2] = 0;
            col[it] = 1;
            rings = min(rings,calc());
          }
        }
      } else {
        REP(i,30) {
          if (ban(i)) continue;
          if (nd[i].F) col[i] = 0;
          else if (nd[i].S) col[i] = 1;
          else col[i] = 2;
        }
        rings = calc();
      }
     cout << keys << " " << rings << endl;
    }
  }

  return 0;
}
