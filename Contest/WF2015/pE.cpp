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


using pii = pair<int, int>;

const int MX = 4010;

int N;
vector<string> ip;

bool ok(int i, int j) {
	int id1 = 0, id2 = 0;
	int sz1 = SZ(ip[i]), sz2 = SZ(ip[j]);
	auto &s1 = ip[i], &s2 = ip[j];
	while (id1 < sz1 and id2 < sz2) {
		if (s1[id1] == s2[id2]) {
			id1++; id2++;
		} else id2++;
	}

	return id1 == sz1;
}

int bk[MX];

int main() {
	IOS;
	cin >> N;
	ip.resize(N+1);

	for (int i=0; i<=N; i++) {
		cin >> ip[i];
	}

	sort(ip.begin()+1, ip.end(), [](string a, string b) { return SZ(a) > SZ(b); });
	if (SZ(ip[0]) <= SZ(ip[1])) { 
		cout << "impossible" << endl;
		return 0;
	}

	int ns = 1, x1 = 0, x2 = 0, x3 = 0;
	int ls2 = -1;

	for (int i=1; i<=N; i++) {
		if (ns == 1) {
			bool o1 = ok(i, x1);
			bool o2 = ok(i, x2);
			if (o1 and o2) {
				ns = 2;
				ls2 = x3 = i;
			} else if (o1) {
				bk[i] = x1;
				x1 = i;
			} else if (o2) {
				bk[i] = x2;
				x2 = i;
			} else {
				cout << "impossible" << endl;
				return 0;
			}
		} else {
			if (ok(i, x3)) {
				bk[i] = x3;
				x3 = i;
			} else {
				bool o1 = ok(i, x1);
				bool o2 = ok(i, x2);
				if (o1) {
					ns = 1;
					bk[i] = x1;
					bk[ls2] = x2;
					x1 = x3;
					x2 = i;
				} else if (o2) {
					ns = 1;
					bk[i] = x2;
					bk[ls2] = x1;
					x1 = x3;
					x2 = i;
				} else {
					cout << "impossible" << endl;
					return 0;
				}
			}
		}
	}

	if (ns == 2) {
		bk[ls2] = x1;
		x1 = x3;
	}


	int x = x1;
	int y = x2;
	vector<int> ans[2];
	while (x) {
		int z = bk[x];
		ans[0].PB(x);
		x = z;
	}

	while (y) {
		int z = bk[y];
		ans[1].PB(y);
		y = z;
	}

	cout << SZ(ans[0]) << ' ' << SZ(ans[1]) << endl;
	for (auto s: ans[0]) cout << ip[s] << endl;
	for (auto s: ans[1]) cout << ip[s] << endl;
	return 0;
}

