#pragma GCC optimize ("O2")
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


int R,C,vst[333][333];
string mp[333];

vector<string> rotate(vector<string> s) {
	int n = SZ(s);
	int m = SZ(s[0]);
	vector<string> res(m);
	REP(i,m) res[i].resize(n);
	REP(i,m) {
		REP(j,n) {
			res[i][j] = s[n-j-1][i];
		}
	}
	return res;
}
string cc(vector<string> vec) {
	string s;
	for (auto i:vec) s += i;
	return s;
}
string go(int x, int y) {
	int x1,x2,y1,y2;
	x1 = x2 = x;
	y1 = y2 = y;
	while (x1 >= 0 and mp[x1][y] != '#') x1--;
	while (x2 < R and mp[x2][y] != '#') x2++;
	while (y1 >= 0 and mp[x][y1] != '#') y1--;
	while (y2 < C and mp[x][y2] != '#') y2++;

	x1++;
	x2--;
	y1++;
	y2--;
	//int X = x2-x1+1;
	int Y = y2-y1+1;
	vector<string> s;
	REP1(i,x1,x2) {
		REP1(j,y1,y2) {
			assert(mp[i][j] != '#');
			vst[i][j] = 1;
		}
		s.PB(mp[i].substr(y1,Y));
	}

	//cout<<s<<endl;
	string res;
	REP(_,4) {
		s = rotate(s);
		string ss = cc(s);
		if (res.empty() or ss < res)
			res = ss;
	}

	return res;
}

int main() {
	IOS;
	cin>>R>>C;
	REP(i,R) {
		cin>>mp[i];
	}
	vector<string> vec;
	REP(i,R) {
		REP(j,C) {
			if (!vst[i][j] and mp[i][j] != '#') {
				vec.PB(go(i,j));
			}
		}
	}
	sort(ALL(vec));
	vec.resize(unique(ALL(vec))-begin(vec));
	cout<<SZ(vec)<<endl;

	return 0;
}

