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

const int MAXN = 1000005;

int N, K;
int px[MAXN], py[MAXN];
vector<pii> event[MAXN*4];
vector<int> es[MAXN*4];
int seg[MAXN*10], tag[MAXN*10];

void initSeg()
{
  for(int i=0; i<8*K+4; i++)
    seg[i] = tag[i] = 0;
}

void clearTag(int s, int lb, int rb)
{
  if(rb - lb > 1)
  {
    seg[2*s] += tag[s];
    seg[2*s+1] += tag[s];
    tag[2*s] += tag[s];
    tag[2*s+1] += tag[s];
  }
  tag[s] = 0;
}

void addSeg(int s, int lb, int rb, int l, int r, int val)
{
  if(rb <= l || r <= lb) return;
  if(l <= lb && rb <= r)
  {
    seg[s] += val;
    tag[s] += val;
  }
  else
  {
    int mb = (lb + rb) / 2;
    clearTag(s, lb, rb);
    addSeg(2*s, lb, mb, l, r, val);
    addSeg(2*s+1, mb, rb, l, r, val);
    seg[s] = min(seg[2*s], seg[2*s+1]);
  }
}

int qrySeg()
{
  return seg[1];
}

bool test()
{
  //cout<<"TEST "<<K<<endl;
  initSeg();
  for(int i=0; i<=2*K; i++)
  {
    event[i].clear();
    es[i].clear();
  }
  for(int i=0; i<N; i++)
  {
    int x1 = px[i], x2 = px[i] + 2*K, y1 = py[i], y2 = py[i] + 2*K;
    if(x2<0 || y2<0 || x1>2*K || y1>2*K) continue;
    x1 = max(x1, 0);
    y1 = max(y1, 0);
    x2 = min(x2, 2*K);
    y2 = min(y2, 2*K);
    //cout<<x1<<"~"<<x2<<" , "<<y1<<"~"<<y2<<endl;
    event[x1].PB({y1, y2+1});
    es[x1].PB(1);
    if(x2+1 <= 2*K)
    {
      event[x2+1].PB({y1, y2+1});
      es[x2+1].PB(-1);
    }
  }

  for(int i=0; i<=2*K; i++)
  {
    for(int j=0; j<(int)event[i].size(); j++)
    {
      int lb = event[i][j].F, rb = event[i][j].S, val = es[i][j];
      addSeg(1, 0, 2*K+1, lb, rb, val);
    }
    int res = qrySeg();
    if(res == 0) return true;
  }

  return false;
}

int calc()
{
  int lb = 0, rb = MAXN - 1;
  while(lb < rb)
  {
    int mb = (lb + rb) / 2;
    K = mb;
    if(test())
      lb = mb + 1;
    else
      rb = mb;
  }

  return lb;
}

int main() {
  IOS;

  int t = 0;
  while(~scanf("%d", &N) && N != -1)
  {
    t++;
    for(int i=0; i<N; i++)
      scanf("%d%d", &px[i], &py[i]);

    int ans = calc();
    cout<<"Case "<<t<<": ";
    if(ans == MAXN - 1)
      cout<<"never"<<endl;
    else
      cout<<ans<<endl;
  }
  return 0;
}
