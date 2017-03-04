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

const int MX = 333333;
int N;
vector<int> ip;
set<int> st;
bool con1[MX], con2[MX];
int C[MX];

int le(int a) {
  int t = 0;
  while (a) {
    t ++; a /= 10;
  }
  return t;
}

inline int se(int x, int b) {
  return x | (1<<b);
}

inline int cl(int x, int b) {
  return x & (~(1<<b));
}

const int INF = 1029384756;

using pii = pair<int, int>;

int mem[MX][10];
bool us[MX][10];
int bf[MX][10];
int tp[MX][10];

int dp(int n, int f) {
  if (f >= 5) return INF;
  if (n == -1) {
    if (f == 0) return 0;
    else return INF;
  }
  if (us[n][f]) return mem[n][f];

  us[n][f] = 1;
  int &res = mem[n][f];
  int &ff = bf[n][f];
  int &tt = tp[n][f];
  res = INF;
  int z = ip[n] & 1;

  if (f == 4) {
    if (con1[n]) {
      if (res > dp(n-1, f)) {
        res = dp(n-1, f);
        ff = f;
        tt = 0;
      }
    }

    int t = dp(n-1, cl(f, 2)) + C[n];
    if (res > t) {
      res = t;
      ff = cl(f, 2);
      tt = -4;
    }
  } else if (z == 1 and (f&1)) {
    if (con2[n]) {
      if (res > dp(n-1, f)) {
        res = dp(n-1, f);
        ff = f;
        tt = 0;
      }
    }
    int t = dp(n-1, cl(f, 0)) + C[n];
    if (res > t) {
      res = t;
      ff = cl(f, 0);
      tt = -1;
    }
  } else if (!z and (f&2)) {
    if (con2[n]) {
      if (res > dp(n-1, f)) {
        res = dp(n-1, f);
        ff = f;
        tt = 0;
      }
    }
    int t = dp(n-1, cl(f, 1)) + C[n];
    if (res > t) {
      res = t;
      ff = cl(f, 1);
      tt = -2;
    }
  } else {
    {
      int t = dp(n-1, f) + C[n] + 1;
      if (res > t) {
        res = t;
        ff = f;
        tt = 3;
      }
    }
    
    if (!(f&4) and con1[n]) {
      int t = dp(n-1, f | 4) + C[n] + 2;
      if (res > t) {
        res = t;
        ff = f | 4;
        tt = 4;
      }
    }
    if (con2[n]) {
      if (!z and !(f&2)) {
        int t = dp(n-1, f | 2) + C[n] + 2;
        if (res > t) {
          res = t;
          ff = f | 2;
          tt = 2;
        }
      }
      if (z and !(f&1)) {
        int t = dp(n-1, f | 1) + C[n] + 2;
        if (res > t) {
          res = t;
          ff = f | 1;
          tt = 1;
        }
      }
    }
  }
  return res;
}

int main() {
  IOS;
  cin >> N;
  ip.resize(N);
  for (int i=0; i<N; i++) {
    cin >> ip[i];
    st.insert(ip[i]);
  }

  sort(ALL(ip));
  for (int i=0; i<N; i++) {
    C[i] = le(ip[i]);
    con1[i] = st.count(ip[i]-1);
    con2[i] = st.count(ip[i]-2);
  }
  
  dp(N-1, 0);
  int n = N-1, f = 0; 
  int Z[10] = {};
  vector<string> ans;
  while (n != -1) {
    int t = tp[n][f];
    if (t == 3) {
      ans.PB(to_string(ip[n]));
    } else if (t == 0) {
    } else if (t > 0) {
      Z[t] = ip[n];
    } else if (t == -1) {
      ans.PB(to_string(ip[n]) + "#" + to_string(Z[-t]));
    } else if (t == -2) {
      ans.PB(to_string(ip[n]) + "%" + to_string(Z[-t]));
    } else if (t == -4) {
      ans.PB(to_string(ip[n]) + "-" + to_string(Z[-t]));
    }
    f = bf[n][f];
    n--;
  }

  int sz = SZ(ans);
  for (int i=0; i<sz; i++) {
    cout << ans[i] << ",\n"[i == sz-1];
  }

  return 0;
}
