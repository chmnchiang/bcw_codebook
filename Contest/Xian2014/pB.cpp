#include<bits/stdc++.h>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define MC(n,m) memcpy((n),(m),sizeof(n))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define FOR(x,y) for(__typeof(y.begin())x=y.begin();x!=y.end();x++)
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
    freopen(name".in", "r", stdin); \
    freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif
// Let's Fight!

typedef pair<int, int> pii;

struct Puzzle
{
  char p[5][7];
};

const char dc[] = {'U', 'D', 'L', 'R'};
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

Puzzle P;
int combo, drop;
int bcombo, bdrop, blen;
bool used[5][6], ok[5][6];
int ii, jj;
string ss;
int bii, bjj;
string bss;
pii vec[10000];

void eliminate(Puzzle pz)
{
  combo = drop = 0;

  bool any = true;
  while(any)
  {
    any = false;
    FZ(used);
    FZ(ok);

    for(int i=0; i<5; i++)
    {
      for(int j=0; j<6; j++)
      {
        if(pz.p[i][j] == 'X') continue;
        if(i > 0 && i < 4 && pz.p[i-1][j] == pz.p[i][j] && pz.p[i+1][j] == pz.p[i][j]) ok[i-1][j] = ok[i][j] = ok[i+1][j] = true;
        if(j > 0 && j < 5 && pz.p[i][j-1] == pz.p[i][j] && pz.p[i][j+1] == pz.p[i][j]) ok[i][j-1] = ok[i][j] = ok[i][j+1] = true;
      }
    }

    for(int i=0; i<5; i++)
    {
      for(int j=0; j<6; j++)
      {
        if(pz.p[i][j] == 'X') continue;
        if(used[i][j] || !ok[i][j]) continue;

        char c = pz.p[i][j];
        combo++;
        int cnt = 0;
        vec[cnt++] = {i, j};
        while(cnt)
        {
          pii p = vec[--cnt];
          if(used[p.F][p.S] || !ok[p.F][p.S]) continue;
          if(pz.p[p.F][p.S] != c) continue;
          drop++;
          pz.p[p.F][p.S] = 'X';
          used[p.F][p.S] = true;
          if(p.F > 0) vec[cnt++] = {p.F-1, p.S};
          if(p.F < 4) vec[cnt++] = {p.F+1, p.S};
          if(p.S > 0) vec[cnt++] = {p.F, p.S-1};
          if(p.S < 5) vec[cnt++] = {p.F, p.S+1};
          any = true;
        }
      }
    }

    for(int j=0; j<6; j++)
    {
      int cnt = 4;
      for(int i=4; i>=0; i--)
        if(pz.p[i][j] != 'X')
          pz.p[cnt--][j] = pz.p[i][j];
      for(int i=cnt; i>=0; i--)
        pz.p[i][j] = 'X';
    }
  }
}

void dfs(int i, int j, int len, char last)
{
  if(len > 9) return;

  eliminate(P);
  if(len >= 1 && (combo > bcombo || (combo == bcombo && drop > bdrop) || 
      (combo == bcombo && drop == bdrop && len < blen)))
  {
    bcombo = combo;
    bdrop = drop;
    blen = len;
    bii = ii;
    bjj = jj;
    bss = ss;
  }

  for(int k=0; k<4; k++)
  {
    int ni = i + dx[k], nj = j + dy[k];
    if(ni < 0 || ni >= 5 || nj < 0 || nj >= 6) continue;
    if(dc[k^1] == last) continue;
    swap(P.p[i][j], P.p[ni][nj]);
    ss.PB(dc[k]);
    dfs(ni, nj, len+1, dc[k]);
    ss.pop_back();
    swap(P.p[i][j], P.p[ni][nj]);
  }
}

int main()
{
  IOS;
  int T;
  cin>>T;
  for(int _t=1; _t<=T; _t++)
  {
    for(int i=0; i<5; i++)
      cin>>P.p[i];

    bcombo = bdrop = 0;
    blen = 123;

    for(int i=0; i<5; i++)
    {
      for(int j=0; j<6; j++)
      {
        ii = i;
        jj = j;
        ss = "";
        dfs(i, j, 0, 'X');
      }
    }

    cout<<"Case #"<<_t<<":\n";
    cout<<"Combo:"<<bcombo<<" Length:"<<blen<<"\n";
    cout<<bii+1<<" "<<bjj+1<<"\n";
    cout<<bss<<"\n";
  }

  return 0;
}
