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
template<typename A, typename B>
ostream& operator <<(ostream &s, const pair<A,B> &p) {
  return s<<"("<<p.first<<","<<p.second<<")";
}
template<typename A, typename B>
istream& operator >>(istream &s, pair<A,B> &p) {
  return s>>p.F>>p.S;
}
template<typename T>
ostream& operator <<(ostream &s, const vector<T> &c) {
  s<<"[ ";
  for (auto it : c) s << it << " ";
  s<<"]";
  return s;
}
// Let's Fight!

typedef pair<int, int> pii;

pii operator-(pii a, pii b){return {a.F-b.F, a.S-b.S};}

pii src[3], dst[3];
vector<pii> rdst[6];

pii rotate(pii p, double c, double s)
{
  int nx = round(p.F * c - p.S * s);
  int ny = round(p.F * s + p.S * c);
  return {nx, ny};
}

vector<pii> proc(vector<pii> x)
{
  for(int i=1; i<(int)x.size(); i++)
    x[i] = x[i] - x[0];
  x[0] = x[0] - x[0];
  return x;
}

vector<pii> rotate(vector<pii> v, double c, double s)
{
  vector<pii> ret;
  for(auto x: v)
    ret.PB(rotate(x, c, s));
  return proc(ret);
}

int calc()
{
  int ord[3];
  for(int i=0; i<3; i++)
    ord[i] = i;
  int z = 0;
  do
  {
    rdst[z].clear();
    for(int i=0; i<3; i++)
      rdst[z].PB(dst[ord[i]]);
    rdst[z] = proc(rdst[z]);
    z++;
  } while(next_permutation(ord, ord+3));

  vector<pii> orig;
  for(int i=0; i<3; i++)
    orig.PB(src[i]);
  orig.PB({1234, 5678});
  orig.PB({8765, 4321});
  orig.PB({314159, 265359});
  orig.PB({-1111, -1111});

  vector< vector<pii> > vv, vv2;
  for(int i=-10; i<=10; i++)
  {
    double r = sqrt(i*i+10*10);
    double c = 10 / r;
    double s = i / r;
    vv.PB(rotate(orig, c, s));
    vv.PB(rotate(orig, s, -c));
    vv.PB(rotate(orig, -c, -s));
    vv.PB(rotate(orig, -s, c));
  }

  for(int i=0; i<6; i++)
  {
    for(auto v: vv)
    {
      int x = 0, y = 0;
      for(int j=0; j<3; j++)
      {
        if(v[j].F != 0) x = rdst[i][j].F / v[j].F;
        if(v[j].S != 0) y = rdst[i][j].S / v[j].S;
      }
      for(int xx=-1; xx<=1; xx+=2)
      {
        if(x != 0) xx = x;
        for(int yy=-1; yy<=1; yy+=2)
        {
          if(y != 0) yy = y;
          vector<pii> vp = v;
          for(auto &zz: vp)
          {
            zz.F *= xx;
            zz.S *= yy;
          }
          if(vp[0] == rdst[i][0] && vp[1] == rdst[i][1] && vp[2] == rdst[i][2])
            vv2.PB(vp);
          if(y != 0) break;
        }
        if(x != 0) break;
      }
    }
  }

  sort(ALL(vv2));
  vv2.resize(unique(ALL(vv2)) - vv2.begin());

  //cout<<vv2.size()<<endl;

  return vv2.size();
}

int main() {
  IOS;

  int t = 0;
  while(cin>>src[0]>>src[1]>>src[2] && src[0] != src[1])
  {
    cin>>dst[0]>>dst[1]>>dst[2];
    t++;

    int ans = calc();
    cout<<"Case "<<t<<": ";
    if(ans == 1)
      cout<<"equivalent solutions"<<endl;
    else if(ans >= 2)
      cout<<"inconsistent solutions"<<endl;
    else
      cout<<"no solution"<<endl;
  }

  return 0;
}
