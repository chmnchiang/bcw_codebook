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
#include <sys/resource.h>
void increase_stack_size() {
  const rlim_t ks = 64*1024*1024;
  struct rlimit rl;
  int res=getrlimit(RLIMIT_STACK, &rl);
  if(res==0){
    if(rl.rlim_cur<ks){
      rl.rlim_cur=ks;
      res=setrlimit(RLIMIT_STACK, &rl);
    }
  }
}

const int MX = 333;
const int INF = 1029384756;
int V, E, nV;
map<string, int> mp;
vector<int> el[MX];

void init() {
	mp.clear();
	nV = 0;
	for (int i=0; i<=V; i++) {
		el[i].clear();
	}
}

int getV(string s) {
	if (mp.find(s) == mp.end()) {
		mp[s] = nV;
		nV++;
		return nV-1;
	}

	return mp[s];
}

int dis[MX];
int calc(int u) {
	fill(dis, dis+V+1, INF);
	dis[u] = 0;

	queue<int> qe; qe.push(u);
	while (qe.size()) {
		int v = qe.front(); qe.pop();
		for (auto w: el[v]) {
			if (dis[w] == INF) {
				dis[w] = dis[v] + 1;
				qe.push(w);
			}
		}
	}

	int res = 0;
	for (int i=0; i<V; i++) {
		res = max(res, dis[i]);
	}
	return res;
}

int main() {
	IOS;
	increase_stack_size();

	int cas = 0;
	while (true) {
		cas++;
		cin >> V >> E;
		if (!V && !E) break;
		init();

		for (int i=0; i<E; i++) {
			string s1, s2;
			cin >> s1 >> s2;
			int u = getV(s1), v = getV(s2);
			el[u].PB(v);
			el[v].PB(u);
		}

		int ans = 0;
		for (int i=0; i<V; i++) {
			ans = max(ans, calc(i));
		}

		cout << "Network " << cas << ": ";
		if (ans == INF) {
			cout << "DISCONNECTED\n\n";
		} else cout << ans << "\n\n";
	}

    return 0;
}


