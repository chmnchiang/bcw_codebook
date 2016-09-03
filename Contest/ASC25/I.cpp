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


typedef pair<int,int> pii;
int N;
pii pt[100005];
map<int,multiset<int>> s1,s2,s3,s4;

inline void del(int x, int y) {
	s1[y].erase(s1[y].find(x));
	s2[x].erase(s2[x].find(y));
	s3[x+y].erase(s3[x+y].find(x));
	s4[x-y].erase(s4[x-y].find(x));
}
bool check(int a, int b, const multiset<int> &s) {
	if (a > b) swap(a,b);
	a++; b--;
	if (a > b) return true;
	auto it = s.lower_bound(a);
	if (it == end(s)) return true;
	return *it > b;
}
int main() {
	FILEIO("queen2");
	IOS;
	cin >> N;
	REP1(i,1,N) {
		cin >> pt[i].F >> pt[i].S;
		s1[pt[i].S].insert(pt[i].F);
		s2[pt[i].F].insert(pt[i].S);
		s3[pt[i].F+pt[i].S].insert(pt[i].F);
		s4[pt[i].F-pt[i].S].insert(pt[i].F);
	}
	int cx=0,cy=0;
	int ans = 0;
	REP1(i,1,N) {
		int x = pt[i].F, y = pt[i].S;
//		cout << i << " " << x << " " << y << endl;
//		cout << cx << " " << cy << endl;
		if (y == cy) {
//			cout << "CHECK y" << endl;
			if (!check(x, cx, s1[y])) break;
		} else if (x == cx) {
//			cout << "CHECK x" << endl;
			if (!check(y, cy, s2[x])) break;
		} else if (x+y == cx+cy) {
//			cout << "CHECK x+y" << endl;
			if (!check(x, cx, s3[x+y])) break;
		} else if (x-y == cx-cy) {
//			cout << "CHECK x-y" << endl;
			if (!check(x, cx, s4[x-y])) break;
		} else {
			break;
		}
		del(x,y);
		cx = x;
		cy = y;
		ans = i;
	}
	cout << ans << endl;

	return 0;
}
