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

typedef long long ll;

const int MAXN = 111;

int N;
ll A[MAXN], B[MAXN], C[MAXN];
int u[MAXN], v[MAXN], w[MAXN];
ll cur[MAXN], fin[MAXN], ocur[MAXN];

bool calc()
{
  for(int i=0; i<N; i++)
  {
    cur[i] = A[i] + B[i] - C[i];
    ocur[i] = cur[i];
    fin[i] = A[i] * (1-u[i]) + B[i] * (1-v[i]) - C[i] * (1-w[i]);
    if(fin[i] > 0 || (fin[i] == 0 && cur[i] < 0))
    {
      fin[i] = -fin[i];
      cur[i] = -cur[i];
    }
    //cout<<fin[i]<<" "<<cur[i]<<endl;
  }

  int failcnt = 0;
  for(int i=0; i<N; i++)
    if(cur[i] != 0) failcnt++;

  if(failcnt == 0) return true;
  else if(failcnt == 1)
  {
    for(int i=0; i<N; i++)
    {
      if(cur[i] != 0)
      {
        if(u[i] && A[i]>0 && ocur[i]==1) return true;
        if(v[i] && B[i]>0 && ocur[i]==1) return true;
        if(w[i] && C[i]>0 && ocur[i]==-1) return true;
      }
    }
  }

  //cout<<"QQ"<<endl;

  for(int i=0; i<N; i++)
    if(fin[i]<0 && cur[i]<=0) return false;

  vector<ll> alpha;
  for(int i=0; i<N; i++)
    if(fin[i]<0)
      alpha.PB(cur[i]);

  ll G = 0;
  for(int i=0; i<N; i++)
    if(fin[i] == 0)
      G += cur[i];

  //cout<<alpha<<" "<<G<<endl;

  int AL = alpha.size();
  if(AL >= 3) return false;
  else if(AL == 2) return (abs(alpha[0]-alpha[1]) == 1 && G == 0) || (alpha[0]==alpha[1] && G==1);
  else if(AL == 1) return alpha[0] >= G-1;
  else return true;
}

int main() {
  IOS;
  int T;
  cin>>T;
  for(int t=1; t<=T; t++)
  {
    cin>>N;
    for(int i=0; i<N; i++) cin>>A[i];
    for(int i=0; i<N; i++) cin>>u[i];
    for(int i=0; i<N; i++) cin>>B[i];
    for(int i=0; i<N; i++) cin>>v[i];
    for(int i=0; i<N; i++) cin>>C[i];
    for(int i=0; i<N; i++) cin>>w[i];

    bool res = calc();
    cout<<"Case #"<<t<<": "<<(res ? "Tweek" : "Craig")<<endl;
  }
  return 0;
}
