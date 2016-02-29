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

const int MX = 3e7 + 9;

int N,M,K,ip[MX],A,B,C;
int fr,bk,deq[MX];

inline void push(int i) {
	while (bk-fr > 0 && ip[deq[bk-1]] >= ip[i]) bk--;
	deq[bk++] = i;
}
inline void pop(int pos) {
	while (bk-fr > 0 && deq[fr] <= pos-M) fr++;
}
int main() {
	IOS;
	FILEIO("minima");
	cin >> N >> M >> K;
	cin >> A >> B >> C;
	REP(i,K) {
		cin >> ip[i];
	}
	REP1(i,K,N-1) {
		ip[i] = A * ip[i-2] + B * ip[i-1] + C;
	}

	fr = bk = 0;
	REP(i,M) {
		push(i);
	}
	long long ans = 0;
	ans += ip[deq[fr]];
	REP1(i,M,N-1) {
		push(i);
		pop(i);
		ans += ip[deq[fr]];
	}
	cout << ans << endl;



    return 0;
}

