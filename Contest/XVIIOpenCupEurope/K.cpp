#pragma GCC optimize ("O2")
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


const int MX = 1111111;
string _S;
int S[MX];
vector<int> ans;

int main() {
	IOS;
	cin >> _S;
	int NNN, N;
	NNN = SZ(_S);
	for (int i=0; i<NNN; i++) {
		S[i] = _S[i] == '1';
	}
	N = NNN / 3;

	for (int i=0; i<N; i++) {
		int h[3];
		int *q = S+3*i;
		int z = (i ? q[-1] : 0);
		for (int j=0; j<3; j++) h[j] = q[j] ^ z;

		int t = h[0] * 4 + h[1] * 2 + h[2];
		int j = 0;
		if (t == 0) {
			q[j] = !q[j];
			q[j+1] = !q[j+1];
			ans.PB(i*3+0);
		} else if (t == 1) {
			q[j+1] = !q[j+1];
			q[j+2] = !q[j+2];
			ans.PB(i*3+1);
		} else if (t == 3) {
			q[j] = !q[j];
			q[j+1] = !q[j+1];
			ans.PB(i*3+0);
		} else if (t == 7) {
			q[j+1] = !q[j+1];
			q[j+2] = !q[j+2];
			ans.PB(i*3+1);
		}
	}

	int n = SZ(ans);
	cout << n << endl;
	for (int i=0; i<n; i++) {
		cout << ans[i]+1 << " \n"[i == n-1];
	}
	return 0;

	int hao = 1;
	for (int i=1; i<NNN; i++) {
		if (S[i] != S[i-1]) hao ++;
	}

	for (int i=0; i<NNN; i++) {
		cout << S[i];
	}
	cout << endl;

	assert(hao >= N*2);


	return 0;
}

