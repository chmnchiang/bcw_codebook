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
template<typename T>
ostream& operator <<(ostream &s, const vector<T> &c) {
  s<<"[ ";
  for (auto it : c) s << it << " ";
  s<<"]";
  return s;
}
// Let's Fight!

typedef pair<int, int> pii;

const int INF = 1029384756;

int L, V1, V2, DV, S;
int VL, VR;
vector<pii> vset;

bool test(int thr)
{
  int lv = thr;
  int cur = 0;

  for(auto p: vset)
  {
    int nlv = p.F, cnt = p.S;
    while(lv > nlv && cur > 0)
    {
      lv--;
      cur >>= 1;
    }
    if(lv > nlv)
      lv = nlv;
    cur += cnt;
  }

  return cur == 0;
}

int calc()
{
  VR = V2 - DV;
  int d = (V2 - V1 - 1) / DV;
  VL = V2 - DV * d;
  if(VL > VR) return 0;

  L /= S;
  if(VR > L) return INF;

  vset.clear();
  int cur = VL;
  while(cur < V2)
  {
    int lay = L / cur;
    int nxt = L / lay + 1;
    nxt += (DV - ((nxt-cur) % DV)) % DV;
    nxt = min(nxt, V2);
    int dd = (nxt - cur) / DV;
    vset.PB({lay, dd});
    cur = nxt;
  }
  vset.PB({0, 0});

  int lb = 0, rb = INF;
  while(lb < rb)
  {
    int mb = (lb + rb) / 2;
    if(test(mb))
      rb = mb;
    else
      lb = mb + 1;
  }
  return lb;
}

int main() {
  IOS;

  int T;
  cin>>T;
  while(T--)
  {
    cin>>L>>V1>>V2>>DV>>S;
    int ans = calc();
    if(ans == INF)
      cout<<"impossible"<<endl;
    else
      cout<<ans<<endl;
  }

  return 0;
}
