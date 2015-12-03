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

vector<int> ans;

int main() {
	int N;
	cin >> N;
	N--;
	int sqn = sqrt(N)+1;
	for (int i=1; i<sqn; i++) {
		if (N%i == 0) {
			ans.PB(i);
			ans.PB(N/i);
		}
	}
	sort(ALL(ans));
	ans.resize(unique(ALL(ans)) - begin(ans));
	for (int i=0; i<SZ(ans); i++) {
		cout << ans[i] << " \n"[i==(SZ(ans)-1)];
	}


    return 0;
}

