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


using DT = array<int, 4>;

const int MX = 1111;
DT M, MM;
vector<int> nx[MX][4];
bool bad[MX][4];

int toi(DT d) {
	return d[0] + d[1]*MM[0] + d[2]*MM[0]*MM[1] + d[3]*MM[0]*MM[1]*MM[2];
}

ostream& operator << (ostream &o, const DT &d) {
	return o << d[0] << ' ' << d[1] << ' ' << d[2] << ' ' << d[3];
}

void bui(int id, DT d, int j) {
#define _MMM(x) for(i[x]=max(0, d[x]-1); i[x]<=min(M[x], d[x]+1); i[x]++) \

	int zz = d[j];
	DT i;

	_MMM(0)
		_MMM(1)
			_MMM(2)
				_MMM(3) {
					DT k = i;
					k[j] = zz+1;
					if (zz == M[j]) bad[id][j] = false;
					else nx[id][j].PB(toi(k));
				}

	sort(ALL(nx[id][j]));
	nx[id][j].resize(unique(ALL(nx[id][j])) - nx[id][j].begin());

}

void build() {
	DT i;
#define _MAG(x) for(i[x]=0; i[x]<=M[x]; i[x]++)
	_MAG(0)
		_MAG(1)
			_MAG(2)
				_MAG(3) {
					int id = toi(i);
					for (int j=0; j<4; j++) {
						bui(id, i, j);
						//cout << id << ": " << nx[id][j] << endl;
					}
				}
}

double ans[MX];

void calc() {

	build();

	int st = toi({0, 0, 0, 0}),
		ed = toi(M);

	int iter = 300;

	for (int i=0; i<=ed; i++) {
		ans[i] = ed+1;
	}



	for (int zz=0; zz<iter; zz++) {
		double err = 0.0;
		for (int i=0; i<=ed; i++) {
			if (i == ed) {
				ans[i] = 0.0;
				continue;
			}
			double best = 1e9;
			for (int k=0; k<4; k++) {
				if (bad[i][k]) continue;
				double tot = 0.0;
				for (auto n: nx[i][k]) {
					tot += ans[n];
				}
				best = min(best, tot/SZ(nx[i][k]));
			}
			err = max(err, best+1.0 - ans[i]);
			ans[i] = best + 1.0;
			
		}
		//if (zz % 100 == 0) cout << zz << ": " << err << endl;
	}

	cout << ans[st] << endl;
}

int main() {
	FILEIO("school");

	cout << fixed << setprecision(10);
	cin >> M[0] >> M[1] >> M[2] >> M[3];
	MM = M;
	for (int i=0; i<4; i++) MM[i]++;

	calc();


    return 0;
}

