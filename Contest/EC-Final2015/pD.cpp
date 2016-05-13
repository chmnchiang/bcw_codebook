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



double c[] = { 0.01, 0.02, 0.05, 0.1, 0.2, 0.5, 1, 2, 5, 10, 20, 50, 100  } ;

int A, B;

string tos(int a) {
	int m = a%100;
	string res = to_string(a/100);
	if (!m) return res;
	if (m%10==0) return res + "." + to_string(m/10);
	return res + "." + string(m < 10 ? "0" : "") + to_string(m);
}

string calc() {
	if(B != 1 and B != 10 and B != 100 and B != 1000) {
		return "0.01";
	}

	int t = (A-1) / B;
	if (t < 3) return "0.01";
	return "0.02";

}

int main() {
	IOS;
	int nt;
	cin >> nt;
	REP1(t,1,nt) {
		double _A,_B;
		cin >> _A >> _B;
		A = round(_A*100);
		B = round(_B*100);
		cout << "Case #" << t << ": " << calc() << endl;
	}

	return 0;
}

