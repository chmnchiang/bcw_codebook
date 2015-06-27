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

const double INF = 1e14;
double dp[55][12][55][105];
int prv[55][12][55][105];
int N,S;
double v[12],vSum;
int people[12][105];


int main(){
  FILEIO("elections");
  cin >> N >> S;
  vSum = 0;
  for (int i=0, m; i<N; i++){
    cin >> v[i];
    vSum += v[i];
    cin >> m;
    people[i][0] = 1;
    for (int j=0, x; j<m; j++){
      cin >> x;
      if (x < 105) people[i][x] = 1;
    }
  }
  for (int i=0; i<N; i++)
    v[i] = v[i] / vSum;

  for (int A=0; A<=50; A++){
    for (int i=0; i<12; i++)
      for (int j=0; j<55; j++)
        for (int k=0; k<105; k++)
          dp[A][i][j][k] = INF;
    for (int l=0, s=0; l<105; l++){
      if (people[0][l] == 0) s++;
      dp[A][0][s][l] = fabs(1.0*l/(A+S) - v[0]);
      prv[A][0][s][l] = l;
    }
    for (int i=1; i<N; i++){
      for (int j=0; j<55; j++){
        for (int k=0; k<105; k++){
          int s = 0;
          for (int l=0; l<=k; l++){
            if (people[i][l] == 0) s++;
            if (j - s < 0) break;
            if (dp[A][i][j][k] > dp[A][i-1][j-s][k-l] + fabs(1.0*l/(A+S) - v[i])){
              dp[A][i][j][k] = dp[A][i-1][j-s][k-l] + fabs(1.0*l/(A+S) - v[i]);
              prv[A][i][j][k] = l;
            }
          }
        }
      }
    }
  }
  vector<int> ans;
  int best = 0;
  for (int A=0; A<=50; A++){
    if (dp[A][N-1][S][S+A] < dp[best][N-1][S][S+best])
      best = A;
  }
  int a = best;
  int b = N-1;
  int c = S;
  int d = S+best;
  for (int i=0; i<N; i++){
    ans.PB(prv[a][b][c][d]);
    int s=0;
    for (int l=0; l<=prv[a][b][c][d]; l++)
      if (people[b][l] == 0) s++;
    b = b - 1;
    c = c - s;
    d = d - ans.back();
  }
  reverse(ans.begin(), ans.end());
  for (auto it : ans)
    cout << it << endl;
  return 0;
}

