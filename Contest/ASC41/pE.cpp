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
vector<LL> ans;
vector<LL> choc;

vector<LL> judge(LL a, LL b) {
  if( a < b ) return judge(b, a);
  vector<LL> t;
  if( a/2 <= b ) {
    t.PB(a-1); t.PB(1); t.PB(b);
  } else {
    t.PB(a/2); t.PB(a-a/2); t.PB(b);
  }
  sort(t.begin(), t.end(), greater<LL>());
  return t;
}


int main(){
  FILEIO("eating");

  int T = 0;
  LL a, b, c;
  while(cin >> a >> b >> c and a and b and c) {
    T++;
    choc.clear();
    choc.PB(a); choc.PB(b); choc.PB(c);
    ans.clear();

    while(true) {
      sort(choc.begin(), choc.end(), greater<LL>());
      if(choc[2] <= 0) break;
      LL bv = -1, eat = -1;
      vector<LL> best_vec;
      for(int i=0; i<3; i++) {
        int aa = (i+1)%3, bb = (i+2)%3;
        vector<LL> v = judge(min(choc[aa], choc[bb]), choc[i]);
        if( v[2] == 0 ) continue;
        if( v[1] >= bv ) {
          bv = v[1];
          best_vec = v;
          eat = max(choc[aa], choc[bb]);
      //    cout << i << ' ' << bv << endl;
        }
      }

      if(bv == -1){
        ans.PB(1);
        break;
      }
      ans.PB(eat);
      choc = best_vec;

    }

    cout << "Case #" << T << ":\n" << ans.size() << "\n";
    for(int i=0; i<(int)ans.size(); i++) {
      cout << ans[i] << (i == (int)ans.size() - 1 ? "" : " ");
    }
    cout << endl;
  }
	return 0;
}

