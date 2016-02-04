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

#define REP(i,x) for(int i=0; i<(x); i++)
#define REP1(i,a,b) for(int i=(a); i<=(b); i++)

int D,R,N,M;
pair<int,int> eg[514*514];

int main() {
	IOS;
	FILEIO("graph");
	cin >> D >> R;
	N = D+R;

	REP1(i,2,R) eg[M++] = {i-1,i};
	eg[M++] = {R,2*R};
	REP1(i,R+1,2*R-1) {
		if (i == R+1) eg[M++] = {1,i};
		else eg[M++] = {i-1,i};
	}
	if (R>1) eg[M++] = {2*R-1,2*R};

	vector<int> vec;
	vec.PB(1);
	REP(i,D-R) vec.PB(2*R+i+1);
	REP1(i,1,SZ(vec)-1) eg[M++] = {vec[i-1], vec[i]};
	
	cout << "YES" << endl;
	cout << N << " " << M << endl;
	REP(i,M) cout << eg[i].F << " " << eg[i].S << "\n";

    return 0;
}

