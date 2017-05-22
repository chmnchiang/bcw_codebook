//a34021501 {{{
#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define IOS ios_base::sync_with_stdio(0); cin.tie(0);
#define SZ(x) ((int)((x).size()))
#define ALL(x) begin(x),end(x)
#define REP(i,x) for (int i=0; i<(x); i++)
#define REP1(i,a,b) for (int i=(a); i<=(b); i++)

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef long double ld;

#ifdef HAO123
#define FILEIO(name)
#else
#define FILEIO(name) \
  freopen(name".in", "r", stdin); \
  freopen(name".out", "w", stdout);
#endif

#ifdef HAO123
template<typename T>
void _dump( const char* s, T&& head ) { cerr<<s<<"="<<head<<endl; }

template<typename T, typename... Args>
void _dump( const char* s, T&& head, Args&&... tail ) {
  int c=0;
  while ( *s!=',' || c!=0 ) {
    if ( *s=='(' || *s=='[' || *s=='{' ) c++;
    if ( *s==')' || *s==']' || *s=='}' ) c--;
    cerr<<*s++;
  }
  cerr<<"="<<head<<", ";
  _dump(s+1,tail...);
}

#define dump(...) do { \
  fprintf(stderr, "%s:%d - ", __PRETTY_FUNCTION__, __LINE__); \
  _dump(#__VA_ARGS__, __VA_ARGS__); \
} while (0)

template<typename Iter>
ostream& _out( ostream &s, Iter b, Iter e ) {
  s<<"[";
  for ( auto it=b; it!=e; it++ ) s<<(it==b?"":" ")<<*it;
  s<<"]";
  return s;
}

template<typename A, typename B>
ostream& operator <<( ostream &s, const pair<A,B> &p ) { return s<<"("<<p.first<<","<<p.second<<")"; }
template<typename T>
ostream& operator <<( ostream &s, const vector<T> &c ) { return _out(s,ALL(c)); }
template<typename T, size_t N>
ostream& operator <<( ostream &s, const array<T,N> &c ) { return _out(s,ALL(c)); }
template<typename T>
ostream& operator <<( ostream &s, const set<T> &c ) { return _out(s,ALL(c)); }
template<typename A, typename B>
ostream& operator <<( ostream &s, const map<A,B> &c ) { return _out(s,ALL(c)); }
#else
#define dump(...)
#endif
// }}}
// Let's Fight! !111111111!

const int MAXK = 10;
const int MAXN = 101010;
const int MAXM = 256;
const int LG = 40;
const ll MOD = 1000000007;

struct Mat
{
  ll v[MAXM][MAXM];
};

ll N;
int K, V;
map<pii, int> smap;
vector<pii> states;
queue<int> q;
vector<int> edge[MAXN];
ll v1[MAXN], v2[MAXN];
Mat I, A[LG];

Mat mult(const Mat &a, const Mat &b)
{
  Mat res;
  for(int i=0; i<V; i++)
  {
    for(int j=0; j<V; j++)
    {
      res.v[i][j] = 0;
      for(int k=0; k<V; k++)
      {
        res.v[i][j] += a.v[i][k] * b.v[k][j];
        res.v[i][j] %= MOD;
      }
    }
  }
  return res;
}

int get_state(pii p)
{
  auto it = smap.find(p);
  if(it == smap.end())
  {
    states.PB(p);
    smap[p] = V;
    q.push(V);
    return V++;
  }
  else
    return it->S;
}

void pre()
{
  get_state({0, 0});

  while(!q.empty())
  {
    int v = q.front();
    pii st = states[v];
    q.pop();

    vector<pii> vec, vec2;
    vec.PB(st);

    vec2.clear();
    vec2.swap(vec);
    for(auto p: vec2)
    {
      vec.PB({p.F+(1<<K), p.S});
      for(int i=0; i<K; i++)
        if(p.S&(1<<i))
          vec.PB({p.F, p.S-(1<<i)});
    }

    vec2.clear();
    vec2.swap(vec);
    for(auto p: vec2)
    {
      vec.PB({p.F, p.S+(1<<K)});
      for(int i=0; i<=K; i++)
        if(p.F&(1<<i))
          vec.PB({p.F-(1<<i), p.S});
    }

    vec2.clear();
    vec2.swap(vec);
    for(auto p: vec2)
    {
      if(p.F%2==0 and p.S%2==0)
        vec.PB({p.F>>1, p.S>>1});
    }

    for(auto p: vec)
    {
      edge[v].PB(get_state(p));
    }

    //cout<<st<<" => "<<vec<<endl;
  }

  //cout<<"#States = "<<V<<endl;
}

ll calc()
{
  ll ans = 0;
  if(K >= 5)
  {
    for(int i=0; i<V; i++)
      v1[i] = 0;
    v1[0] = 1;

    for(ll x=0; x<N; x++)
    {
      for(int i=0; i<V; i++)
      {
        v2[i] = v1[i];
        v1[i] = 0;
      }
      for(int i=0; i<V; i++)
      {
        if(v2[i] == 0) continue;
        for(auto e: edge[i])
        {
          v1[e] += v2[i];
          if(v1[e] >= MOD) v1[e] -= MOD;
        }
      }
    }

    ans = v1[0];
  }
  else
  {
    for(int i=0; i<V; i++)
    {
      for(int j=0; j<V; j++)
      {
        I.v[i][j] = (i == j);
        A[0].v[i][j] = 0;
      }
    }

    for(int i=0; i<V; i++)
      for(auto e: edge[i])
        A[0].v[e][i]++;

    for(int i=1; i<LG; i++)
      A[i] = mult(A[i-1], A[i-1]);

    Mat m = I;
    for(int i=0; i<LG; i++)
    {
      if(N&(1LL<<i))
        m = mult(m, A[i]);
    }

    ans = m.v[0][0];
  }

  return ans;
}

int main() {
  IOS;

  cin>>N>>K;
  pre();

  ll ans = calc();
  cout<<ans<<endl;

  return 0;
}

