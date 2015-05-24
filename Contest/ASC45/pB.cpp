//bcw0x1bd2 {{{
#include<bits/stdc++.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define MC(n,m) memcpy((n),(m),sizeof(n))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define FOR(x,y) for(__typeof(y.begin())x=y.begin();x!=y.end();x++)
#define IOS ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
  freopen(name".in", "r", stdin); \
  freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif

void RI() {}

template<typename... T>
void RI( int& head, T&... tail ) {
	    scanf("%d",&head);
			    RI(tail...);
}

mt19937 rng(0x5EED);
int randint(int lb, int ub) {
    return uniform_int_distribution<int>(lb, ub)(rng);
}
// Let's Fight! }}}

const int MX = 200005;
double EPS = 1e-8;
typedef pair<double, double> pdd;

int N;
double A, B, alpha;
int pSZ, ivSZ;
pdd points[MX];
double iv[MX];
//vector<pdd> points;
//vector<double> iv;

void aozora() {
	//points.clear();
	//iv.clear();
	pSZ = ivSZ = 0;
}

pair<bool, double> getx(pdd p1, pdd p2, double y) {
	if( y < min(p1.S, p2.S) or y > max(p1.S, p2.S) ) {
		return MP(false, 0.0);
	}
	double x = p1.F + (y - p1.S) / (p2.S - p1.S) * (p2.F - p1.F); 
	return MP(true, x);
}

void getiv() {
	int sz = pSZ;//points.size();
	if(A <= points[0].S and points[0].S <= B) {
		iv[ivSZ++] = points[0].F; //.PB(points[0].F);
	}

	for(int i=1; i<sz; i++) {
		auto rt1 = getx(points[i-1], points[i], A);
		auto rt2 = getx(points[i-1], points[i], B);
		double xs[2]; int cnt = 0;
		if(rt1.F) xs[cnt++] = rt1.S;
		if(rt2.F) xs[cnt++] = rt2.S;
		if(cnt == 2 and xs[0] > xs[1]) swap(xs[0], xs[1]);
		for(int j=0; j<cnt; j++){
			iv[ivSZ++] = xs[j]; //.PB(xs[j]);
		}
	}

	int vsz = ivSZ; //iv.size();
	if(vsz & 1) {
		iv[ivSZ++] = points[sz-1].F; //.PB(points[sz-1].F);
	}
}

int main(){
	FILEIO("bayes");

//	IOS;

	while(~scanf("%d", &N) && N) {
		aozora();
		scanf("%lf%lf", &A, &B);
		A -= EPS; B += EPS;
		scanf("%lf", &alpha);
		for(int i=0; i<N+1; i++) {
			double x, y;
			scanf("%lf%lf", &x, &y);
			points[pSZ++] = MP(x,y); //.PB(MP(x, y));
		}
		getiv();
		double tot = 0.0;
		for(int i=0; i<ivSZ; i+=2) {
			tot += iv[i+1] - iv[i];
			//cout << iv[i] << "--" << iv[i+1] << endl;
		}

		double rql = tot * alpha;
		int id1 = 0, id2 = 0;
		int sz = ivSZ; //iv.size();
		double ans = 1e9, nowl = 0.0, bestL=0;
#define LEN(a) (iv[(a)+1]-iv[a])
		while(id1 < sz) {
			while(id2 < sz and (nowl + LEN(id2) < rql - EPS)) {
				nowl += LEN(id2);
				id2 += 2;
			}
			if(id2 < sz) {
				double nowans = iv[id2] - iv[id1] + rql - nowl;
				if(ans > nowans) {
					ans = nowans;
					bestL = iv[id1];
				}
			}

			if(id2 > id1) {
				nowl -= LEN(id1);
			} else id2 += 2;		
			id1 += 2;
		}
		printf("%.7f %.7f\n", bestL, ans+bestL);
//		cout << fixed << setprecision(10) << bestL << ' ' << ans + bestL << "\n";
	}

	return 0;
}

