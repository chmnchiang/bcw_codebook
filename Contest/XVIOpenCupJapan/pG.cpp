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
#define loop(i, a, b) for (auto (i) = (a); (i) != (b); (i) += (((a) < (b) ? 1 : -1)))

#define int long long
using pts = array<int, 3>;
int A, B, C, N;
vector<pts> ip;

bool inrange(int x, int y, int z) {
	if (x < 0 or x >= A) return false;
	if (y < 0 or y >= B) return false;
	if (z < 0 or z >= C) return false;
	return true;
}

bool test(int i, int j) {
	pts p1 = ip[i], p2 = ip[j];
	return (abs(p1[0]-p2[0]) + abs(p1[1]-p2[1]) + abs(p1[2]-p2[2])) == 1;
}

int outer(int a) {
	pts p = ip[a];
	int ret = 0;
	for (int i=0; i<3; i++)
		for (int j=-1; j<=1; j+=2) {
			pts q = p;
			q[i] += j;
			if (not inrange(q[0], q[1], q[2])) ret ++;
		}
	return ret;
}

int32_t main() {
	IOS;
	cin>>A>>B>>C>>N;
	ip.resize(N);
	for (int i=0; i<N; i++) {
		int x, y, z;
		cin >> x >> y >> z;
		ip[i] = pts{x, y, z};
	}

	int ans = (A*B+B*C+C*A)*2 + 6*N;
	for (int i=0; i<N; i++) { 
		for (int j=0; j<N; j++) {
			if (test(i, j)) ans --;
		}
		ans -= 2*outer(i);
	}
	cout << ans << endl;



	return 0;
}

