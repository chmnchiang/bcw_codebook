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


using Arr = array<int, 4>;
int Z[60];
const int INF = 1029384756;
int ans = INF;
Arr AAA;
void test(Arr a) {
	int cost = 0;
	int i = 0;
	while (i < 4) {
		int j = i+1;
		while (j < 4 and a[j] == a[j-1] + 1) {
			j++;
		}
		int l = j - i;
		int z = Z[a[i]] + i;
		cost += l * (52 - z);

		i = j;
	}
	if (cost < ans) {
		ans = cost;
		AAA = a;
	}
}

int main() {
	IOS;

	for (int i=0; i<4; i++) {
		int x; cin >> x;
		Z[x] = 1;
	}
	for (int i=51; i>=0; i--) {
		Z[i] += Z[i+1];
	}

	for (int i=1; i<=52; i++) {
		for (int j=i+1; j<=52; j++) {
			for (int k=j+1; k<=52; k++) {
				for (int ii=k+1; ii<=52; ii++) {
					test({i, j, k, ii});
				}
			}
		}
	}
	
	cout << AAA[0] << ' ' << AAA[1] << ' ' << AAA[2] << ' ' << AAA[3] << endl;


	return 0;
}
