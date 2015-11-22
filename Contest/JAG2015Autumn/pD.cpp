#include<bits/stdc++.h>
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

typedef pair<int, int> pii;
int N;
string ip;

pii walk(int s) {
	int l = s, r = s+1;
	int pos = s;
	for (int i=0; i<N; i++) {
		int dir = (ip[pos] == '>' ? 1 : 0);
		if (dir == 1) {
			pos = r;
			r++;
		} else {
			pos = l - 1;
			l --;
		}
		if (pos < 0 or pos >= N) {
			return {i+1, (pos < 0 ? 1 : 0)};
		}
	}
	return {-1, -1};
}



int main() {
    IOS;


	cin >> N;
	cin >> ip;

	int l = 0, r = N-1;

	while (l < r) {
		int md = (l+r+1)/2;
		if (walk(md).S) {
			l = md;
		} else {
			r = md - 1;
		}
	}
	int ans = walk(l).F;
	if (l < N-1) {
		ans = max(ans, walk(l+1).F);
	}
	cout << ans << endl;

    return 0;
}

