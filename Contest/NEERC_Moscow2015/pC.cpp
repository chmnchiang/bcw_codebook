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

#define int long long
int _px = 0, _py = 0;
int _lx = -1, _ly;
typedef pair<int, int> pii;

int dis(int x, int y) {
	return (_px - x) * (_px - x) + (_py - y) * (_py - y);
}

int _t = 0;
int guess(int x, int y) {
//	_t ++;
//	if (_lx == -1) {
//		tie(_lx, _ly) = pii{x, y};
//		return 0;
//	}
//	int fg = (dis(x, y) < dis(_lx, _ly));
//	tie(_lx, _ly) = pii{x, y};
	cout << x << " " << y << endl;
	int fg; cin >> fg;
	return fg;
}

void answer(int x, int y) {
	cout << "A " << x << " " << y << endl;
	exit(0);
}

int32_t main() {

	const int INF = 1e9;
	int l = 0, r = INF;
	while (l < r) {
		guess(l, 0);
		int res = guess(r, 0);
		if (res) {
			l = (l+r)/2 + 1;
		} else {
			r = (l+r)/2;
		}
	}
	int x = l;

	l = 0, r = INF;
	while (l < r) {
		guess(0, l);
		int res = guess(0, r);
		if (res) {
			l = (l+r)/2 + 1;
		} else {
			r = (l+r)/2;
		}
	}
	answer(x, l);

    return 0;
}

