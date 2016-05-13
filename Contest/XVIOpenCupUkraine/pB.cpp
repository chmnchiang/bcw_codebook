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


typedef pair<int,int> pii;
typedef long long ll;

const int MXN = 2000005;

int N,M,app[MXN];
int sum[MXN];

int qry(int l, int r) {
	if (l == 0) return sum[r];
	return sum[r] - sum[l-1];
}
ll calc(vector<pii> vec, int st) {
	ll res = 0;
	REP(i,MXN) sum[i] = app[i] = 0;
	for (auto &it:vec) {
		it.S += N;
		app[it.F] = 1;
		sum[it.S] = 1;
	}
	REP1(i,1,MXN-1) sum[i] += sum[i-1];
	for (int a=st; a<2*N; a+=2) {
		pii l(1+a,1-a+N);
		pii r(a+1,a-1+N);
		if (a > N) {
			int x = N;
			int y = a - N + 1;
			r = pii(x+y,x-y+N);
			swap(x,y);
			l = pii(x+y,x-y+N);
//			cout << x << " " << y << endl;
		}
		int tot = (r.S-l.S)/2+1;
		if (app[l.F]) {
			res += tot;
//			cout << "ALL BLACK " << a << endl;
			continue;
		}
//		cout << l << " " << r << endl;
		res = res + qry(l.S,r.S);
//		cout << "SOME BLACK " << a << " " << qry(l.S,r.S) << endl;
	}

	return res;
}
int main() {
	IOS;
	cin >> N >> M;
	vector<pii> odd,even;
	REP(i,M) {
		int a,b,x,y;
		cin >> a >> b;
		x = a+b;
		y = a-b;
		if (x & 1) odd.PB(pii(x,y));
		else even.PB(pii(x,y));
	}
	ll ans = calc(odd,2) + calc(even,1);
	ans = 1LL * N * N - ans;
	cout << ans << endl;

	return 0;
}

