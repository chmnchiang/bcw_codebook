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

#define int long long

  const int MX = 55;
  const int MV = 123;
  const int MM = 1111;
int L, N;

struct ACautomata{
  struct Node{
    int cnt,dp;
    Node *go[26], *fail;
	int mask, id;
    Node (){
      cnt = 0;
      dp = -1;
      memset(go,0,sizeof(go));
      fail = 0;
	  mask = 0;
    }
  };

  Node *root, pool[1048];
  int nMem;
  vector<Node*> nd;

  Node* new_Node(){
    pool[nMem] = Node();
	pool[nMem].id = nMem;
	nd.PB(&pool[nMem]);
    return &pool[nMem++];
  }
  
  void init(){
    nMem = 0;
	for (int l=0; l<=L; l++) {
		for (int i=0; i<=SZ(nd); i++) {
			for (int j=0; j<=(1<<N); j++) {
				vt[l][i][j] = false;
			}
		}
	}
	nd.clear();
	va.clear();
	FZ(vt2);
    root = new_Node();
  }

  void add(const string &str, int m){
    insert(root,str,0, m);
  }

  void insert(Node *cur, const string &str, int pos, int m){
    if (pos >= (int)str.size()){
      cur->cnt++;
	  cur->mask |= m;
      return;
    }
    int c = str[pos]-'a';
    if (cur->go[c] == 0){
      cur->go[c] = new_Node();
    }
    insert(cur->go[c],str,pos+1,m);
  }

  void make_fail(){
    queue<Node*> que;
    que.push(root);
    while (!que.empty()){
      Node* fr=que.front();
      que.pop();
      for (int i=0; i<26; i++){
        if (fr->go[i]){
          Node *ptr = fr->fail;
          while (ptr && !ptr->go[i]) ptr = ptr->fail;
          if (!ptr) fr->go[i]->fail = root;
          else {
			  fr->go[i]->fail = ptr->go[i];
			  fr->go[i]->mask |= fr->go[i]->fail->mask;
		  }
          que.push(fr->go[i]);
        }
      }
    }
  }

  int vt2[MV][30];
  int mem2[MV][30];
  int walk(int cur, char c) {
	  Node* cv = nd[cur];
	  int t = c - 'a';
	  if (vt2[cur][t]) return mem2[cur][t];
	  vt2[cur][t] = true;
	  if (cv->go[t]) return mem2[cur][t] = cv->go[t]->id;
	  else {
		  if (cv == root) return mem2[cur][t] = 0;
		  else return mem2[cur][t] = walk(cv->fail->id, c);
	  }
  }

  
  int mem[MX][MV][MM];
  bool vt[MX][MV][MM];
  int dp(int pos, int cv, int mask) {
	  int xmask = mask | (nd[cv]->mask);
	  if (pos == L) {
		  if (xmask == (1<<N)-1) return 1;
		  return 0;
	  }

	  if (vt[pos][cv][mask]) return mem[pos][cv][mask];

	  vt[pos][cv][mask] = true;

	  int ans = 0;
	  for (char c='a'; c<='z'; c++) {
		  int nx = walk(cv, c);
		  ans += dp(pos+1, nx, xmask);
	  }

	  return mem[pos][cv][mask] = ans;
  }

  vector<string> va;
  void dump(int pos, int cv, int mask, string s) {
	  if (not dp(pos, cv, mask)) return;
	  int xmask = mask | (nd[cv]->mask);
	  if (pos == L) {
		  if (xmask == (1<<N)-1) {
			  va.PB(s);
		  }
		  return;
	  }
	  for (char c='a'; c<='z'; c++) {
		  int nx = walk(cv, c);
		  dump(pos+1, nx, xmask, s+c);
	  }
  }
} ac;


void solve() {
	for (int i=0; i<N; i++) {
		string s; cin >> s;
		ac.add(s, 1<<i);
	}
	ac.make_fail();
	int t;
	cout << (t = ac.dp(0, 0, 0)) << " suspects" << endl;
	assert(t >= 0);
	if (t <= 42) {
		ac.dump(0, 0, 0, "");
		for (auto x: ac.va) {
			cout << x << endl;
		}
	}
	ac.init();
}

int32_t main() {
	IOS;
	ac.init();

	int cas = 0;
	while (true) {
		cin >> L >> N;
		if (not L and not N) break;
		cas++;
		cout << "Case " << cas << ": ";
		solve();
	}

    return 0;
}

