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

typedef long long ll;

const ll MX = 1LL<<60;

ll sum = 0, lsum = 0;
ll _x, _m, _x0;
int cnt = 0;
ll N = 1LL<<60;

void addsum(ll x)
{
  sum += x;
  while(sum >= MX)
  {
    sum -= MX;
    lsum++;
  }
}

#ifdef ONLINE_JUDGE
char interact(ll del)
{
  cnt++;
  cout<<del<<endl;
  addsum(del);
  string s;
  cin>>s;
  return s[0];
}
#else
char interact(ll del)
{
  cnt++;
  addsum(del);
  ll nx = (del + _x) % _m;
  ll ox = _x;
  _x = nx;
  if(nx == ox) return '=';
  else if(nx > ox) return '>';
  else return '<';
}
#endif

void ending(ll M)
{
//  cout<<M<<" HAO123"<<endl;

//  cout<<"Cur at "<<_x<<endl;
  for(ll i=1LL<<60; i>0; i/=2)
  {
    if(i >= M) continue;
    if(interact(i) == '<')
      interact(M-i);
//    cout<<"Cur at "<<_x<<endl;
  }
  interact(1);

//  cout<<_x<<endl;
  ll x0 = (sum % M);
  while(lsum)
  {
    lsum--;
    x0 = (x0 + MX) % M;
  }
  x0 = (M - x0) % M;
//  cout<<x0<<endl;

  cout<<0<<" "<<x0<<" "<<M<<endl;
//  cout<<"USE "<<cnt<<endl;

//  cout<<"(X0 = "<<_x0<<", M = "<<_m<<")"<<endl;
  exit(0);
}

ll lrand()
{
  return rand() * (ll)RAND_MAX + rand();
}

int main() {
  IOS;
  srand(time(0));

#ifdef ONLINE_JUDGE
  cin>>N;
#else
  _m = lrand() % (1LL<<60);
//  _m = lrand() % 10 + 1;
  _x = lrand() % _m;
  _x0 = _x;
  cout<<"(X0 = "<<_x<<", M = "<<_m<<")"<<endl;
#endif

  interact(lrand() % N + 1);
  ll K = 1;
  int noret = 0;

  for(int i=1; i<=200; i++)
  {
    char res = interact(i);
    if(res == '=')
      ending(i);
  }

  for(int i=0; i<100; i++)
  {
    char res = interact(K);
    if(res == '=')
      ending(K);

    if(res == '>')
    {
      noret++;
      if(noret >= 2) K *= 2;
    }
    else
      noret = 0;
  }

//  cout<<"K = "<<K<<endl;

  ll x = K / 10;

//  cout<<"X = "<<x<<endl;

  while(interact(x) == '>');

  ll alpha = 1;
  while(interact(x) == '>') alpha++;

//  cout<<"Alpha = "<<alpha<<endl;

  ll lb = (alpha-1) * x + 1, rb = (alpha+1) * x - 1;
  rb = min(rb, N);

//  cout<<lb<<" <= M <= "<<rb<<endl;

  while(1)
  {
    ll z = lb / 8;
    while(interact(z) == '>');
    for(int i=0; i<4; i++)
      interact(z);

    ll y = (lb + rb) / 2;

    char res = interact(y);
    if(res == '=')
      ending(y);
    else if(res == '<')
      lb = y+1;
    else
      rb = y-1;

//    cout<<lb<<" <= M <= "<<rb<<endl;
  }

  return 0;
}
