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

typedef pair<int,int> pii;
const int MX = 100005;

int N;
int sonCnt[MX];
int blue[MX], red[MX];
vector<int> E[MX];
priority_queue<pii, vector<pii>> pq1, pq2, pq3;

int DFS(int u){
  sonCnt[u] = 1;
  for (auto v : E[u])
    sonCnt[u] += DFS(v);
  return sonCnt[u];
}
vector<pii> get_node(){
  vector<pii> ans;
  for (int i=0; i<2; i++){
    if (!pq1.empty()){
      int v = pq1.top().S;
      pq1.pop();
      ans.PB(MP(v,1));
    }
    if (!pq2.empty()){
      int v = pq2.top().S;
      pq2.pop();
      ans.PB(MP(v,2));
    }
    if (!pq3.empty()){
      int v = pq3.top().S;
      pq3.pop();
      ans.PB(MP(v,3));
    }
  }
  return ans;
}
bool comp(pii a, pii b){
  return sonCnt[a.F] > sonCnt[b.F];
}
void draw_blue(int t, int v){
//  cout << "draw blue " << v << " @ time " << t << endl;
  blue[t] = v;
  for (auto it : E[v])
    pq1.push(MP(sonCnt[it], it));
}
void draw_red(int t, int v){
//  cout << "draw red " << v << " @ time " << t << endl;
  red[t] = v;
  for (auto it : E[v])
    pq2.push(MP(sonCnt[it], it));
}

int main(){
  FILEIO("dual");
  cin >> N;
  for (int i=1, fa; i<=N; i++){
    cin >> fa;
    E[fa].PB(i);
  }
  DFS(0);
  for (auto v : E[0]){
    pq3.push(MP(sonCnt[v],v));
  }
  for (int i=1, t=1; i<=N; t++){
    vector<pii> vec = get_node();
    sort(vec.begin(), vec.end(), comp);
    while (!pq1.empty()){
      pq3.push(pq1.top());
      pq1.pop();
    }
    while (!pq2.empty()){
      pq3.push(pq2.top());
      pq2.pop();
    }
    int redp1, bluep1;
    redp1 = bluep1 = -1;
    if (vec[0].S == 1 || vec[0].S == 3){
      bluep1 = 0;
      for (int j=1; j<(int)vec.size(); j++){
        if (vec[j].S != 1){
          redp1 = j;
          break;
        }
      }
    }
    int redp2, bluep2;
    redp2 = bluep2 = -1;
    if (vec[0].S == 2 || vec[0].S == 3){
      redp2 = 0;
      for (int j=1; j<(int)vec.size(); j++){
        if (vec[j].S != 2){
          bluep2 = j;
          break;
        }
      }
    }
    if (bluep2 != -1 || bluep1 == -1){
      redp1 = redp2;
      bluep1 = bluep2;
    }
    if (redp1 != -1){
      i++;
      draw_red(t, vec[redp1].F);
    }
    if (bluep1 != -1){
      i++;
      draw_blue(t, vec[bluep1].F);
    }
    for (int j=0; j<(int)vec.size(); j++){
      if (j == redp1 || j == bluep1) continue;
      int v = vec[j].F;
      pq3.push(MP(sonCnt[v], v));
    }
  }
  vector<pii> ans;
  for (int i=1; ; i++){
    if (blue[i] == 0 && red[i] == 0) break;
    ans.PB(MP(blue[i], red[i]));
  }
  cout << ans.size() << endl;
  for (auto it : ans)
    cout << it.F << " " << it.S << "\n";

  return 0;
}

