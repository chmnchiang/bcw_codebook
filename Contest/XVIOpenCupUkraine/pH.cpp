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

using vi = vector<int>;
const int MX = 666;
const double EPS = 1E-9;
vector<vi> par;
map<vi, int> pmap;
int P, M;
int N;
vi cur;
map<int, double> trans[MX];
double pr[MX][MX];
double pi[MX];
double r[MX][MX];
double q[MX][22];
double A[22][22];
double b[22];

void go (int n, int k) {
	if (!n) {
		par.PB(cur);
		sort(ALL(par.back()));
		return;
	}
	for (int i=k; i>=1; i--) {
		if (i > n) continue;
		cur.PB(i);
		go(n-i, i);
		cur.pop_back();
	}
}


vi merge(vi vec, int i, int j) {
	if (i > j) swap(i, j);
	vec[i] += vec[j];
	swap(vec[j], vec.back());
	vec.pop_back();
	sort(ALL(vec));
	return vec;
}

void pre() {
	go(N, N);
	P = SZ(par);
	M = N*(N-1)/2;

	for (int i=0; i<P; i++) {
		pmap[par[i]] = i;
	}

	for (int i=0; i<P; i++) {
		vi v = par[i];
		int sz = SZ(v);
		for (int j=0; j<sz; j++) {
			trans[i][i] += v[j] * (v[j]-1) / 2;
			for (int k=j+1; k<sz; k++) {
				double t = v[j] * v[k];
				vi u = merge(v, j, k);
				int id = pmap[u];
				trans[i][id] += t;
			}
		}
	}
}


void calcDP() {
	pr[0][P-1] = 1.0;
	for (int i=0; i<M; i++) {
		for (int j=1; j<P; j++) {
			for (auto p: trans[j]) {
				int jj = p.F;
				double v = p.S;
				if (jj == j)
					pr[i+1][jj] += (v - i) / (M-i) * pr[i][j];
				else
					pr[i+1][jj] += v / (M-i) * pr[i][j];
			}
		}
	}
}

double calc()
{
	for(int j=0; j<M; j++)
	{
		FZ(A);
		FZ(b);
		for(int i=0; i<N; i++)
		{
			double pip = pi[i] * (double)(M - j) / M;
			for(int k=0; k<N; k++)
				b[i] += r[i][k] * q[j][k];
			b[i] *= pip;
			b[i] += 1;
			for(int k=0; k<N; k++)
				A[i][k] = (i == k) - r[i][k] * (1 - pip);
		}

		for(int i=0; i<N; i++)
		{
			int piv = -1;
			for(int jj=0; jj<N; jj++)
				if(abs(A[jj][i]) > EPS)
					piv = jj;
			swap(A[i], A[piv]);
			swap(b[i], b[piv]);

			double rat = A[i][i];
			for(int jj=0; jj<N; jj++)
				A[i][jj] /= rat;
			b[i] /= rat;
			for(int jj=0; jj<N; jj++)
			{
				if(jj == i) continue;
				rat = A[jj][i];
				for(int k=0; k<N; k++)
					A[jj][k] -= rat * A[i][k];
				b[jj] -= rat * b[i];
			}
		}

		for(int i=0; i<N; i++)
			q[j+1][i] = b[i];
	}

//	for(int i=0; i<10; i++) cout<<i<<" : "<<pr[i][0]<<" "<<q[i][0]<<endl;

	double ans = 0;
	for(int i=0; i<=M; i++)
		ans += pr[i][0] * q[i][0];

	return ans;
}

int main() {
	IOS;
	cin >> N;
	for(int i=0; i<N; i++)
		cin>>pi[i];
	for(int i=0; i<N; i++)
	{
		int s;
		cin>>s;
		double zz = 1. / s;
		for(int j=0; j<s; j++)
		{
			int x;
			cin>>x;
			x--;
			r[i][x] = zz;
		}
	}

	pre();
	calcDP();
	double ans = calc();
	cout<<fixed<<setprecision(10)<<ans<<endl;

	return 0;
}

