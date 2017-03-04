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

typedef pair<int,int> pii;
vector<int> score;
vector<pii> vec;
map<vector<int>,int> mp;

void DFS(int i) {
	if (i >= SZ(vec)) {
		mp[score]++;
		return;
	}

	int a = vec[i].F, b = vec[i].S;
	score[a] += 3;
	score[b] += 0;
	DFS(i+1);
	score[a] -= 3;
	score[b] -= 0;
	score[a] += 1;
	score[b] += 1;
	DFS(i+1);
	score[a] -= 1;
	score[b] -= 1;
	score[a] += 0;
	score[b] += 3;
	DFS(i+1);
	score[a] -= 0;
	score[b] -= 3;
}
void pre() {
	REP(i,4) {
		REP(j,i) {
			vec.PB({j,i});
		}
	}
	score.resize(4);
	fill(ALL(score),0);
	DFS(0);
}

int main() {
	IOS;
	pre();
	int T;
	cin>>T;
	REP1(t,1,T) {
		REP(i,4) {
			cin>>score[i];
		}

		cout<<"Case #"<<t<<": ";
		if (mp.count(score)) {
			if (mp[score] == 1) cout<<"Yes"<<endl;
			else cout<<"No"<<endl;
		} else {
			cout<<"Wrong Scoreboard"<<endl;
		}

	}

	return 0;
}

