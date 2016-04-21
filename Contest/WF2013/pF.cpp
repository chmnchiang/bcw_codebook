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

const int MX = 2020202;
int N, K;
int M;
int ip[MX];
bool us[MX];

bool test(int a) {
	fill(us, us+M+5, 0);
	int c = 0;
	for (int i=0; i<M-1; i++) {
		if (us[i]) continue;
		int x = ip[i], y = ip[i+1];
		if (y - x <= a) {
			us[i] = us[i+1] = 1;
			c += 2;
		}
	}
	if (c < N*2) return 0;

	int z = 0;
	for (int i=0; i<M; i++) {
		if (us[i]) z++;

		if (i/K+1 > z) {
			return 0;
		}
	}
	return 1;
}

int main() {
	IOS;
	cin >> N >> K;
	M=2*N*K;
	for (int i=0; i<M; i++) {
		cin>>ip[i];
	}
	sort(ip, ip+M);

	int l = 0, r = 1e9+10;
	while (l<r) {
		int md=(l+r)/2;
		if (test(md)) r = md;
		else l = md+1;
	}
	cout << l << endl;

	return 0;
}

