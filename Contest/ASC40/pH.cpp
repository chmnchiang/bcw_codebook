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

typedef long double LD;

int N, p[50];
int ans = 0, choose;
LD lp[50], num, tar, best;
vector<__int128_t> vec;

void DFS(int cur){
  if (num > tar) return ;
  if (best < num){
    ans = choose;
    best = num;
  }
  if (cur >= N) return ;
  LD tmp = num;
  num += lp[cur];
  choose += (1 << cur);
  DFS(cur + 1);
  num = tmp;
  choose -= (1 << cur);
  DFS(cur + 1);
}
void output(__int128_t v){
  if (v == 0){
    cout << 0;
    return ;
  }
  string str;
  while (v){
    str += v % 10 + '0';
    v /= 10;
  }
  reverse(str.begin(), str.end());
  cout << str;
}
int main(){
  IOS;
  for (int i=2,np=0; np < 30; i++){
    int fail = 0;
    for (int j=2; j<i; j++){
      if (i % j == 0){
        fail = 1;
        break;
      }
    }
    if (!fail){
      lp[np] = log(i);
      p[np++] = i;
    }
  }
  for (int i=1; i<=30; i++){
    N = i;
    tar = num = 0;
    for (int j=0; j<N; j++)
      tar += lp[j];
    tar *= 0.5;
    ans = choose = 0;
    best = 0;
    DFS(0);
    cout << i << " " << best << endl;
    __int128_t tmp = 1;
    for (int j=0; j<N; j++){
      if ((1<<j) & ans){
        tmp = tmp * p[j];
      }
    }
    vec.PB(tmp);
  }
  cout << "string ans[] = {";
  for (int i=0; i<30 ;i++){
    output(vec[i]);
    if (i != 29) cout << ", ";
  }
  cout << "}" << endl;

	return 0;
}

