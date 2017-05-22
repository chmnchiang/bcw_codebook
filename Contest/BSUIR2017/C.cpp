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

const int MAXN = 101010;

ll N;
set<ll> st;
unordered_map<ll, int> mnum;

ll num[MAXN];
vector<ll> edge[MAXN];
ll mp[MAXN];
bool vis[11];

void pre()
{
  st.insert(1);
  queue<ll> q;
  q.push(1);
  while(!q.empty())
  {
    ll v = q.front();
    q.pop();
    if(v > 1E18) continue;

    for(int i=2; i<=9; i++)
    {
      ll nv = v * i;
      if(!st.count(nv))
      {
        st.insert(nv);
        q.push(nv);
      }
    }
  }

  int cur = SZ(st);
  for(auto it=st.rbegin(); it!=st.rend(); it++)
  {
    cur--;
    ll v = *it;
    num[cur] = v;
    mnum[v] = cur;
    for(int i=2; i<=9; i++)
    {
      ll nv = v * i;
      if(st.count(nv))
        edge[cur].PB(mnum[nv]);
    }
  }

  //for(int i=0; i<10; i++) cout<<i<<" : "<<num[i]<<" EDGE "<<edge[i]<<endl;
}

bool calc()
{
  for(int j=SZ(st)-1; j>=0; j--)
  {
    ll v = num[j];
    if(v > N)
      continue;
    for(int i=0; i<=10; i++)
      vis[i] = false;
    for(auto e: edge[j])
    {
      ll nv = num[e];
      ll s = (nv>N ? 0 : mp[e]);
      //if(v < 20) cout<<v<<" => "<<nv<<endl;
      vis[s] = true;
    }
    for(int i=0; ; i++)
    {
      if(!vis[i])
      {
        mp[j] = i;
        break;
      }
    }
    //cout<<v<<" : "<<mp[v]<<endl;
  }
  return mp[0] != 0;
}

int main() {
  IOS;
  pre();

  int T;
  cin>>T;
  while(T--)
  {
    cin>>N;
    bool ans = calc();
    cout<<(ans ? "YES" : "NO")<<endl;
  }

  return 0;
}

