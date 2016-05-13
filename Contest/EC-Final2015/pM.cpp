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

int R,C,B;
bitset<1024> ban[1024];

void input() {
	cin >> R >> C;
	cin >> B;
	REP(i,R) ban[i].reset();
	REP(i,B) {
		int x,y;
		cin >> x >> y;
		ban[x][y] = 1;
	}
}
pii solve() {
	int a,b;
	a = b = 0;
	REP(i,R) {
		REP(j,C) {
			if (ban[i][j]) continue;
			int k = j;
			while (k < C and !ban[i][k]) k++;
			k--;
			int cnt = k - j + 1;
			a += (cnt+1)/2;
			b += (cnt+2)/3;
			j = k;
		}
	}

	return {a,b};
}
int main() {
	IOS;
	int nt;
	cin >> nt;
	REP1(t,1,nt) {
		input();
		pii ans = solve();
		cout << "Case #" << t << ": " << ans.F << " " << ans.S << endl;
	}


	return 0;
}


