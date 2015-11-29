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

typedef long long LL;
typedef pair<LL, LL> pll;
const int MXN = 100005;
const int INF = 1029384756;

int N;
vector<pll> pt;
pll xBound, yBound;

bool inrange(pll a, int x1, int x2, int y1, int y2) {
	return x1 <= a.F && a.F <= x2 && y1 <= a.S && a.S <= y2;
}
vector<pll> delPoint(const vector<pll>& vec, int x1, int x2, int y1, int y2) {
	vector<pll> ret;
	for (auto it : vec) {
		if (!inrange(it, x1, x2, y1, y2)) {
			ret.PB(it);
		}
	}
	return ret;
}
bool check(int k, const vector<pll>& vec, int len) {
	if (k == 0) return SZ(vec) == 0;
	pll xb, yb;
	xb = yb = {INF, -INF};
	for (auto it : vec) {
		xb.F = min(xb.F, it.F);
		xb.S = max(xb.S, it.F);
		yb.F = min(yb.F, it.S);
		yb.S = max(yb.S, it.S);
	}
	vector<pll> delVec;
	delVec = delPoint(vec, xb.F, xb.F+len, yb.F, yb.F+len);
	if (check(k-1, delVec, len))
		return true;
	delVec = delPoint(vec, xb.F, xb.F+len, yb.S-len, yb.S);
	if (check(k-1, delVec, len))
		return true;
	delVec = delPoint(vec, xb.S-len, xb.S, yb.F, yb.F+len);
	if (check(k-1, delVec, len))
		return true;
	delVec = delPoint(vec, xb.S-len, xb.S, yb.S-len, yb.S);
	if (check(k-1, delVec, len))
		return true;
	return false;
}

bool checkOK(int len) {
	return check(3, pt, len);
}

int main() {
	IOS;
	int nT;
	cin >> nT;
	while (nT--) {
		cin >> N;
		pt.resize(N);
		xBound = yBound = {INF, -INF};
		for (int i=0; i<N; i++) {
			cin >> pt[i].F >> pt[i].S;
			xBound.F = min(xBound.F, pt[i].F);
			xBound.S = max(xBound.S, pt[i].F);
			yBound.F = min(yBound.F, pt[i].S);
			yBound.S = max(yBound.S, pt[i].S);
		}
		sort(ALL(pt));
		N = unique(ALL(pt)) - pt.begin();
		pt.resize(N);
		if (N <= 3) {
			cout << "0\n";
			continue;
		}
		int l = 0, r = max(xBound.S - xBound.F, yBound.S - yBound.F) + 1;
		while (l < r) {
			int mid = (l+r)/2;
			if (checkOK(mid)) r = mid;
			else l = mid+1;
		}
		cout << l << "\n";
	}

    return 0;
}

