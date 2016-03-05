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

typedef long long ll;
typedef pair<int,int> pii;
const int MXN = 200005;

struct Item {
	int id;
	ll a,b,t;
	friend ostream& operator << (ostream &o, const Item &he) {
		o << "[ " << he.a << " " << he.b << " " << he.t << " ]";
		return o;
	}
};

int N,at[MXN];
ll A,B;
Item ip[MXN];

bool comp(Item a, Item b) {
	return a.t < b.t;
}
int check_ok(ll delay) {
	REP(i,N) {
		ip[i].t += delay;
//		cout << ip[i].a << " " << ip[i].b << " " << ip[i].t << endl;
	}
	int ok = 1;
	ll curt = 0;
	for (int i=0; i<N; ) {
		ll totA = A;
		ll totB = B;
		if (ip[i].t - A - B - ip[i].a - ip[i].b - curt < 0) {
			ok = 0;
			break;
		}
		ll rem = 1e18;
//		cout << "START\n";
		while (i < N and curt + totA + ip[i].a + totB + ip[i].b <= ip[i].t) {
			if (rem - ip[i].a < 0) break;
//			cout << ip[i] << endl;
			rem -= ip[i].a;
			totA += ip[i].a;
			totB += ip[i].b;
			rem = min(rem, ip[i].t - curt - totA - totB);
			i++;
		}
//		cout << "END" << endl;
		curt += totA + totB;
	}
	REP(i,N) {
		ip[i].t -= delay;
	}
	return ok;
}
int app[MXN];
void output(ll delay) {
	cout << delay << endl;
	REP(i,N) {
		ip[i].t += delay;
	}
	vector<int> ans;
	ll curt = 0;
	for (int i=0; i<N; ) {
		ll totA = A;
		ll totB = B;
		ll rem = 1e18;
		vector<int> vec;
		while (i < N and curt + totA + ip[i].a + totB + ip[i].b <= ip[i].t) {
			if (rem - ip[i].a < 0) break;
			rem -= ip[i].a;
			totA += ip[i].a;
			totB += ip[i].b;
			rem = min(rem, ip[i].t - curt - totA - totB);
			vec.PB(ip[i].id);
			i++;
		}
		curt += totA + totB;
		for (auto it:vec) ans.PB(-it);
		for (auto it:vec) ans.PB(it);
		//cout << vec << endl;
	}


	for (auto it:ans) cout << it << " ";
	cout << endl;

	REP1(i,1,N) app[i] = 0;
	REP(i,N) at[ip[i].id] = i;
	curt = 0;
	int prv = 1;
	REP(i,SZ(ans)) {
		int id = abs(ans[i]);
		if (ans[i] < 0) {
			assert(app[id] == 0);
			app[id]++;
			if (prv > 0) curt += A;
			curt += ip[at[id]].a;
		} else {
			assert(app[id] == 1);
			app[id]++;
			if (prv < 0) curt += B;
			curt += ip[at[id]].b;
			assert(curt <= ip[at[id]].t);
		}
		prv = ans[i];
	}
}
int main() {
	IOS;
	cin >> N >> A >> B;
	REP(i,N) {
		cin >> ip[i].a >> ip[i].b >> ip[i].t;
		ip[i].id = i+1;
	}
	sort(ip,ip+N,comp);
	ll l = 0, r = 1e13;
	while (l < r) {
		ll m = (l + r) / 2;
		if (check_ok(m)) r = m;
		else l = m+1;
	}
	output(l);

	return 0;
}
