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

const int MX = 500005;

int N,M,ans[MX], send[MX];
set<pair<int,int>> eg;

int main(){
  IOS;
  FILEIO("intouch");
  cin >> N >> M;
  while (M--){
    int x,y;
    string cmd;
    cin >> cmd;
    if (cmd == "!"){
      cin >> x;
      send[x]++;
    } else if (cmd == "+"){
      cin >> x >> y;
      if (x > y) swap(x,y);
      ans[x] -= send[y];
      ans[y] -= send[x];
      eg.insert(MP(x,y));
    } else if (cmd == "-"){
      cin >> x >> y;
      if (x > y) swap(x,y);
      ans[x] += send[y];
      ans[y] += send[x];
      eg.erase(MP(x,y));
    }
  }
  for (auto it : eg){
    int x = it.F;
    int y = it.S;
    ans[x] += send[y];
    ans[y] += send[x];
  }
  for (int i=1; i<=N; i++){
    cout << ans[i];
    if (i == N) cout << endl;
    else cout << " ";
  }
  return 0;
}

