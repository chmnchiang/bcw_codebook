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
#define REP(i,x) for (int i=0; i<(x); i++)
#define REP1(i,a,b) for (int i=(a); i<=(b); i++)

const int MXN = 54;
const int MX = 120005;

struct Command {
	string s;
	int k;
}cmd[MXN];

int N;
vector<int> ans;

bool check(int y) {
	int money = 0;
	int con = 1;
	REP(i,N) {
		if (cmd[i].s == "IN") {
			con = 0;
			if (money % y) return false;
			money = 0;
			y += cmd[i].k;
		} else if (cmd[i].s == "OUT") {
			con = 0;
			if (money % y) return false;
			money = 0;
			y -= cmd[i].k;
			if (y < 1) return false;
		} else if (cmd[i].s == "PAY") {
			if (con) continue;
			money += cmd[i].k;
		}
	}
	return true;
}
int main() {
	IOS;
	increase_stack_size();
	while (cin >> N && N) {
		int payed = 0;
		REP(i,N) {
			cin >> cmd[i].s >> cmd[i].k;
			if (cmd[i].s == "PAY") payed = 1;
		}
		ans.clear();
		REP1(i,1,MX-1) {
			if (check(i)) {
				ans.PB(i);
				if (!payed) break;
			}
		}
		if (SZ(ans) == 0) {
			cout << "IMPOSSIBLE" << endl;
		} else if (!payed || SZ(ans) > 110000) {
			assert(!ans.empty());
			cout << "SIZE >= " << ans[0] << endl;
		} else {
			for (int i=0; i<SZ(ans); i++)
				cout << ans[i] << " \n"[i == SZ(ans)-1];
		}
		
	}

    return 0;
}

