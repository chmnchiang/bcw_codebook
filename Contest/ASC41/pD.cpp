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
//#include<bits/extc++.h>
//using namespace __gnu_pbds;
//typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> set_t;

const int MX = 200005;

struct Query{
  int i,p,id;
}qry[MX];

int Q;
int N;
int ip[MX],id;
int num[MX], ans[MX];
map<int,int> mp;
//set_t st;
int bit[4*MX];


int lb(int a){ return a & -a; }
void update(int st, int v){
  for (int i=st; i<MX; i += lb(i))
    bit[i] += v;
}
int query(int st){
  int ret=0;
  for (int i=st; i>0; i -= lb(i))
    ret += bit[i];
  return ret;
}

int main(){
  IOS;
  FILEIO("data");
  cin >> N;
  for (int i=0; i<N; i++){
    cin >> ip[i];
    if (!mp.count(ip[i])) mp[ip[i]] = id++;
    ip[i] = mp[ip[i]];
    num[i] = -1;
  }
  cin >> Q;
  for (int i=0; i<Q; i++){
    cin >> qry[i].i >> qry[i].p;
    qry[i].i--;
    qry[i].p += qry[i].i - 1;
    qry[i].id = i;
  }
  sort(qry, qry+Q,
      [] (Query a, Query b){
        return a.i > b.i;
      }
      );
  for (int i=N-1, p=0; i>=0; i--){
    int v = ip[i];
    if (num[v] == -1){
      update(i+1,1);
//      st.insert(i);
      num[v] = i;
    } else {
      update(num[v]+1,-1);
      update(i+1,1);
//      st.erase(num[v]);
//      st.insert(i);
      num[v] = i;
    }
    while (p<Q && qry[p].i >= i){
      int qid = qry[p].id;
      v = num[ip[qry[p].p]];
//      ans[qid] = st.order_of_key(v) + 1;
      ans[qid] = query(v+1);
      p++;
    }
  }
  for (int i=0; i<Q; i++)
    cout << ans[i] << endl;

	return 0;
}

