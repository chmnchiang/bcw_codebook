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

const int MX = 200005;

struct Rule {
	int c,tar;
	vector<int> vec;
}rule[MX];

int N,M,inq[MX],canOdd[MX],canEven[MX];
vector<int> app[MX];

int main() {
	while (~scanf("%d%d", &N, &M) && N+M > 0) {
		REP(i,N) {
			app[i].clear();
		}

		REP(i,M) {
			rule[i].c = 0;
			rule[i].vec.clear();
			int k,v;
			char str[105];
			int trash = scanf("%d%d", &rule[i].tar, &k);
			assert(trash == 2);
			rule[i].tar--;

			REP(_,k) {
				trash = scanf("%s", str);
				assert(trash == 1);
				if (isdigit(str[0])) {
					sscanf(str, "%d", &v);
					v--;
					rule[i].vec.PB(v);
					app[v].PB(i);
				} else {
					rule[i].c ^= 1;
				}
			}
		}

		REP(i,N) {
			inq[i] = 0;
			canOdd[i] = 0;
			canEven[i] = 0;
		}
		queue<int> que;
		REP(i,M) {
			if (rule[i].vec.empty()) {
				int u = rule[i].tar;
				if (rule[i].c == 0) canEven[u] = 1;
				else canOdd[u] = 1;
				if (!inq[u]) {
					que.push(u);
					inq[u] = 1;
				}
			}
		}

//		REP(i,N) cout << "app " << i << " : " << app[i] << endl;

		while (!que.empty() and !canOdd[0]) {
			int u = que.front();
			que.pop();
			inq[u] = 0;
//			cout << u << endl;
			for (auto id:app[u]) {
				Rule &r = rule[id];
				int c = r.c;
				int both = 0;
				int fail = 0;
				for (auto it:r.vec) {
					if (canOdd[it] and canEven[it]) {
						both++;
					} else if (canOdd[it]) {
						c ^= 1;
					} else if (canEven[it]) {
						// pass
					} else {
						fail = 1;
						break;
					}
				}
				if (fail) continue;
				int v = r.tar;
				if (both) {
					if (!canOdd[v]) {
						canOdd[v] = 1;
						if (!inq[v]) {
							que.push(v);
//							cout << "BOTH ODD " << v << " BY " << id << endl;
							inq[v] = 1;
						}
					}
					if (!canEven[v]) {
						canEven[v] = 1;
						if (!inq[v]) {
							que.push(v);
//							cout << "BOTH EVEN " << v << " BY " << id << endl;
							inq[v] = 1;
						}
					}
				} else {
					if (c) {
						if (!canOdd[v]) {
							canOdd[v] = 1;
							if (!inq[v]) {
//								cout << "ODD " << v << " BY " << id << endl;
								que.push(v);
								inq[v] = 1;
							}
						}
					} else {
						if (!canEven[v]) {
							canEven[v] = 1;
							if (!inq[v]) {
//								cout << "EVEN " << v << " BY " << id << endl;
								que.push(v);
								inq[v] = 1;
							}
						}
					}
				}
			}
		}
//		REP(i,N) cout << i << " " << canOdd[i] << " " << canEven[i] << endl;

		if (canOdd[0]) puts("YES");
		else puts("NO");
	}


	return 0;
}
