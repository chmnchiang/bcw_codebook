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

int P, Q;

void calc()
{
  vector<int> vec;
  swap(P, Q);
  while(Q)
  {
    vec.PB(P / Q);
    P %= Q;
    swap(P, Q);
  }

  //cout<<vec<<endl;

  int A = 0, B = 1;
  for(auto x: vec)
  {
    A += B * x;
    swap(A, B);
  }
  cout<<A<<" "<<B<<endl;
}

int main() {
  IOS;
  FILEIO("reversed-fraction");

  cin>>P>>Q;
  calc();

  return 0;
}

