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

int N,ons[52],vst[52];
int bln[52][52];

int ID(string s) {
	if (s[0] == '0') return -1;
	int x = (s[0] - 'A') * 2;
	if (s[1] == '-') x++;
	return x;
}
bool DFS(int u) {
	vst[u] = 1;
	ons[u] = 1;
	REP(v,52) {
		if (!bln[u^1][v]) continue;
		if (ons[v]) {
			return true;
		}
		if (DFS(v)) return true;
	}
	ons[u] = 0;
	return false;
}
int main() {
	IOS;
	cin >> N;
	REP(_,N) {
		string s;
		cin >> s;
		vector<int> vec;
		for (int i=0; i<SZ(s); i+=2) 
			vec.PB(ID(s.substr(i,2)));
		REP(i,4) {
			REP(j,4) {
				if (i == j or vec[i] == -1 or vec[j] == -1) continue;
				bln[vec[i]][vec[j]] = 1;
			}
		}
	}
	REP(i,52) {
		memset(vst,0,sizeof(vst));
		memset(ons,0,sizeof(ons));
		if (DFS(i)) {
			cout << "unbounded" << endl;
			return 0;
		}
	}
	cout << "bounded" << endl;


	return 0;
}

