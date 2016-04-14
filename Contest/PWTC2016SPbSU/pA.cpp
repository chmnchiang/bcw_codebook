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
#define int long long

const int MX = 1000005;

int N,K,arr[MX];
const int L = 1<<30;
const long long INF = 1LL << 60;

int last_ans = -1;

inline void f(int seed, int a) {
	REP(i,N) {
		seed = (seed * 239017 + a) % L;
		arr[i] = seed;
	}
}
int _ip[MX+MX];
int *ip;
int start=0;
int _sm[MX+MX];
int *sm;
int EXP;

int rangeSum(int i, int j) {
//	cout << "RANGE SUM " << i << " " << j << " = "<<sm[j]-sm[i]<<endl;
	return sm[j] - sm[i];
}

int cost(int i, int j) {
	int l = (j - i)/2;
	int md = i+l;
	int rcnt = j - md;
	int lcnt = md - i;

	int res;
	res = rangeSum(md, j) - ip[md] * rcnt;
	res += ip[md] * lcnt - rangeSum(i, md);
	//res = rangeSum(j-l, j) - rangeSum(i, i+l);
//	cout << "COST " << i << " " << j << " = " << res << endl;
	return res;
}

bool print;

int Z[MX];
bool test(int d, int st) {
	int ni = st;
	for (int _=0; _<K; _++) {
		/*
		if(N >= 100000)
		{
			l = ni + N/K * 0.999 - 100;
			r = ni + N/K * 1.001 + 100;
			l = min(l, N);
			l = max(l, ni);
			r = min(r, N);
			r = max(r, ni);
		}*/
		
		if (!st) {
			Z[_] = ni;
			int l = ni, r = N+st;
			while (l < r) {
				int md = (l+r+1)/2;
				if (cost(ni, md) <= d) {
					l = md;
				} else r = md-1;
			}
			ni = l;
			Z[_+1] = ni;
		} else {
			Z[_] = ni;
			int t = Z[_+1];
			while (t+1 <= N+st and cost(ni, t+1) <= d) t++;
			ni = t;
			Z[_+1] = t;
		}
//		if(print)
//		cout<<l-ni<<" "<<N/K<<endl;
		if (ni == N+st) break;
	}
//	cout<<"d "<<d<<" st "<<st<<" : "<<(ni==N+st)<<endl;
	return ni == N+st;
}

bool test(int d) {
	for (int i=0; i<min(N/K+3, N); i++) {
		if (test(d, i)) return true;
	}
	return false;

}

int solve() {

	print = false;
	int l = 0, r = INF;
	if(last_ans != -1 && N >= 100000)
	{
		l = last_ans * 0.9999 - 1000;
		r = last_ans;
	}
	if(N >= 100000)
	{
		l = EXP * 0.9;
		r = EXP * 1.1;
	}
//	cout<<l<<" "<<r<<endl;
	while (l < r) {
		int md = (l+r)/2;
		//cout<<"TEST "<<md<<endl;
		if (test(md)) {
			r = md;
		} else l = md+1;
	}

	print = true;
	test(l);

//	ip[N] = ip[0] + L;
//	sm[N+1] = sm[N] + ip[N];
//	sm++;
//	ip++;

	last_ans = l;
	return l;

}
int32_t main() {
	auto t = clock();
	IOS;
	srand(time(0));
	cin >> N >> K;
	int s, a; cin >> s >> a;
//	s = rand();
	f(s, a);
	sort(arr, arr+N);
	
	int ed = min(N,N/K+3);
	if (N <= 100) ed = N;
	for (int i=0; i<=N*2; i++) {
		_ip[i] = arr[i%N] + (i >= N) * L;
		_sm[i+1] = _sm[i] + _ip[i];
	}
	EXP = L * N / (4*K*K);
	sm = _sm;
	ip = _ip;
	int ans = INF;
	int res = solve();
	ans = res;
//		if (1.0 * (clock() - t) / CLOCKS_PER_SEC >= 1.4) break;
//	cout<<EXP<<" = EPS"<<endl;

	cout << ans << endl;

	exit(0);
}
