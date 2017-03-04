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

struct SA{
	static const int MXN = 300010;
	bool _t[MXN*2];
	int _s[MXN*2], _sa[MXN*2], _c[MXN*2], x[MXN], _p[MXN], _q[MXN*2], hei[MXN], r[MXN];
	int operator [] (int i){ return _sa[i]; }
	void build(int *s, int n, int m){
		memcpy(_s, s, sizeof(int) * n);
		sais(_s, _sa, _p, _q, _t, _c, n, m);
		mkhei(n);
	}
	void mkhei(int n){
		REP(i,n) r[_sa[i]] = i;
		hei[0] = 0;
		REP(i,n) if(r[i]) {
			int ans = i>0 ? max(hei[r[i-1]] - 1, 0) : 0;
			while(_s[i+ans] == _s[_sa[r[i]-1]+ans]) ans++;
			hei[r[i]] = ans;
		}
	}
	void sais(int *s, int *sa, int *p, int *q, bool *t, int *c, int n, int z){
		bool uniq = t[n-1] = true, neq;
		int nn = 0, nmxz = -1, *nsa = sa + n, *ns = s + n, lst = -1;
#define MS0(x,n) memset((x),0,n*sizeof(*(x)))
#define MAGIC(XD) MS0(sa, n); \
		memcpy(x, c, sizeof(int) * z); \
		XD; \
		memcpy(x + 1, c, sizeof(int) * (z - 1)); \
		REP(i,n) if(sa[i] && !t[sa[i]-1]) sa[x[s[sa[i]-1]]++] = sa[i]-1; \
		memcpy(x, c, sizeof(int) * z); \
		for(int i = n - 1; i >= 0; i--) if(sa[i] && t[sa[i]-1]) sa[--x[s[sa[i]-1]]] = sa[i]-1;
		MS0(c, z);
		REP(i,n) uniq &= ++c[s[i]] < 2;
		REP(i,z-1) c[i+1] += c[i];
		if (uniq) { REP(i,n) sa[--c[s[i]]] = i; return; }
		for(int i = n - 2; i >= 0; i--) t[i] = (s[i]==s[i+1] ? t[i+1] : s[i]<s[i+1]);
		MAGIC(REP1(i,1,n-1) if(t[i] && !t[i-1]) sa[--x[s[i]]]=p[q[i]=nn++]=i);
		REP(i, n) if (sa[i] && t[sa[i]] && !t[sa[i]-1]) {
			neq=lst<0||memcmp(s+sa[i],s+lst,(p[q[sa[i]]+1]-sa[i])*sizeof(int));
			ns[q[lst=sa[i]]]=nmxz+=neq;
		}
		sais(ns, nsa, p + nn, q + n, t + n, c + z, nn, nmxz + 1);
		MAGIC(for(int i = nn - 1; i >= 0; i--) sa[--x[s[p[nsa[i]]]]] = p[nsa[i]]);
	}
} ssaa;

const int MX = 333333;
int hei[MX];
int sa[MX];

void suffix_array(int* ip, int len) {
	// should padding a zero in the back
	// s is int array, n is array length
	// s[0..n-1] != 0, and s[n] = 0
	// resulting SA will be length n+1
	ip[len++] = 0;
	ssaa.build(ip, len, 128);
	// original 1-base
	for (int i=0; i<len; i++) {
		hei[i] = ssaa.hei[i + 1];
		sa[i] = ssaa._sa[i + 1];
	}
}

const int INF = 1e9;

char S[MX];
int _S[MX];
int L;
int LA;
int lm[MX], rm[MX];
bool hao[MX];

static void init() {
	L = LA = 0;
}

int main() {
	IOS;

	int T;
	cin >> T;
	for (int cas=1; cas<=T; cas++) {
		init();
		int N; cin >> N;
		for (int i=0; i<N; i++) {
			cin >> &S[L];
			while (S[L]) L++;
			if (!i) LA = L;
			S[L++] = (i == 0 ? '@' : '!');
		}

		for (int i=0; i<L; i++) {
			_S[i] = S[i];
		}
		suffix_array(_S, L);

		for (int i=0; i<L; i++) {
			hao[i] = (sa[i] < LA);
		}

		 
		int cur = 0;
		for (int i=0; i<L; i++) {
			cur = min(cur, i ? hei[i] : 0);
			if (hao[i]) lm[i] = cur;
			else {
				lm[i] = INF;
				cur = INF;
			}
		}

		cur = 0;
		for (int i=L-1; i>=0; i--) {
			cur = min(cur, i==N-1 ? 0 : hei[i+1]);
			if (hao[i]) rm[i] = cur;
			else {
				rm[i] = INF;
				cur = INF;
			}
		}

		int bv = INF, bx = -1;
		for (int i=0; i<L; i++) {
			int z = max(lm[i], rm[i]);
			int pos = sa[i];
			if (pos + z >= LA) continue;

			z++;

			if (bv > z) {
				bv = z;
				bx = i;
			}
		}

		cout << "Case #" << cas << ": ";
		if (bx == -1) cout << "Impossible" << endl;
		else {
			int pos = sa[bx];
			for (int i=0; i<bv; i++) {
				cout << S[pos+i];
			}
			cout << endl;
		}
	}

	return 0;
}

