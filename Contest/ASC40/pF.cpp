//bcw0x1bd2 {{{
#include<bits/stdc++.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define MC(n,m) memcpy((n),(m),sizeof(n))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define FOR(x,y) for(__typeof(y.begin())x=y.begin();x!=y.end();x++)
#define IOS ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
  freopen(name".in", "r", stdin); \
  freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif

void RI() {}

template<typename... T>
void RI( int& head, T&... tail ) {
	    scanf("%d",&head);
			    RI(tail...);
}

mt19937 rng(0x5EED);
int randint(int lb, int ub) {
    return uniform_int_distribution<int>(lb, ub)(rng);
}
// Let's Fight! }}}
typedef long long LL;
int L;
LL mask[50];
vector<string> ans;

bool same(long long v, int i, int k){
  long long a = (v >> i) & mask[k];
  long long b = (v >> (i+k)) & mask[k];
  return a == b;
}
void DFS(int cur, long long v){
  if (cur >= L){
    string str;
    for (int i=0; i<L; i++){
      if (v & (1ll << i)) str += "1";
      else str += "0";
    }
    ans.PB(str);
    return ;
  }
  int a[50], fail;
  // check 0
  for (int i=0; i<=cur; i++){
    a[i] = 1;
    for (int k=1; i+2*k-1 <= cur; k++){
      if (same(v,i,k)){
        a[i] = 0;
        break;
      }
    }
  }
  fail = 0;
  for (int i=0, sum=0; i<=cur; i++){
    sum += a[i];
    if (2*sum < i+1){
      fail = 1;
      break;
    }
  }
  if (!fail) DFS(cur+1, v);

  // check 1
  v = v + (1ll << cur);
  for (int i=0; i<=cur; i++){
    a[i] = 1;
    for (int k=1; i+2*k-1 <= cur; k++){
      if (same(v,i,k)){
        a[i] = 0;
        break;
      }
    }
  }
  fail = 0;
  for (int i=0, sum=0; i<cur; i++){
    sum += a[i];
    if (2*sum < i+1){
      fail = 1;
      break;
    }
  }
  if (!fail) DFS(cur+1, v);
}
int main(){
  for (int i=0; i<50; i++){
    mask[i] = (1ll<<(i)) - 1;
  }
  IOS;
  FILEIO("free");
  cin >> L;
  DFS(0, 0);
  cout << ans.size() << endl;
  for (auto it : ans)
    cout << it << "\n";
  return 0;
}

