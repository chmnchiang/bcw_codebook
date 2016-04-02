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

#define loop(i, a, b) for (auto (i)=(a); (i) != (b); (i) += ((b) < (a) ? -1 : 1))
#define int long long

const int MX = 222;
const int ML = 1111;
const int MV = ML*MX*2;
int N, NN;
int S, A, V;
char ip[MX][ML];
int len[MX];
int vs[MX];
int val[MV];
using pii=pair<int, int>;
vector<pii> el[MV];

inline int getId(int i, int j) {
	//assert(j < len[i]);
	return vs[i] + j;
}

namespace Z {
void value(char *s, int *z, int len) {
	int i,j,left,right;
	left=right=0; z[0]=len;
	for(i=1;i<len;i++) {
		j=max(min(z[i-left],right-i),0LL);
		for(;i+j<len&&s[i+j]==s[j];j++);
		z[i]=j;
		if(i+z[i]>right) {
			right=i+z[i];
			left=i;
		}
	}
}
};

void prt(int u) {
	int z = -1;
	for (int i=0; i<NN; i++) {
		if (vs[i] > u) {
			z = i-1;
			break;
		}
	}
	if (z == -1) {
		if (z == S) cout << "Start" << endl;
		else cout << "Abr" << endl;
		return;
	}
	int q = u - vs[z];
	//cout << (q ? " " : "*") << (ip[z]+q) << endl;
}

void addEdge(int u, int v, int c) {
	//cout << u << "->" << v << endl;
	//prt(u); prt(v);
	el[u].PB({v, c});
}

char tmp[ML*2];
int zv[ML*2];
void make(int a, int b) {
	auto *sa = ip[a], *sb = ip[b];
	int la=len[a], lb=len[b];
	loop (i, 0, la)
		tmp[i] = sa[i];

	tmp[la] = '@';
	loop (i, 0, lb)
		tmp[la+i+1] = sb[i];

	Z::value(tmp, zv, la+lb+1);
	/*
	loop (i, 0, lb)
		cout << zv[la+i+1] << ' ';
	cout << a << ' ' << b << endl;
	*/
	loop (i, 0, lb) {
		int z = zv[i+la+1];
		////////////////assert(z <= la);
		int id = getId(b, i);
		if (z == la) {
			if (i+z == lb) addEdge(id, A, 2*z);
			else addEdge(id, getId(b, i+z), 2*z); 
		} else {
			if (i+z == lb) addEdge(id, getId(a, z), 2*z);
			else {
				//cout << b << ' ' << i << ' ' << 
				val[id] = max(val[id], 2*z);
				//val[getId(a, 0)] = max(val[getId(a, 0)], 2*z);
			}
		}
	}
}

bool vt[MV];
bool ins[MV];

bool dfs(int u) {
	vt[u] = ins[u] = true;

	for (auto p: el[u]) {
		int v = p.F;
		if (!vt[v]) {
			auto res = dfs(v);
			if (res) return true;
		} else if (ins[v]) return true;
	}
	ins[u] = false;
	return false;
}

bool hasLoop() {
	fill(vt, vt+V+5, 0);
	return dfs(S);
}

int mem[MV];
int dp(int u) {
	if (vt[u]) return mem[u];
	vt[u] = true;
	int res = val[u];

	for (auto p: el[u]) {
		int v = p.F, c = p.S;
		res = max(res, dp(v) + c);
	}
	return mem[u] = res;
}

int32_t main() {
	IOS;
	FILEIO("palindrome");

	cin >> N;
	
	loop (i, 0, N) {
		cin >> ip[i];
		vs[i+1] = vs[i+N+1] = len[i+N] = len[i] = strlen(ip[i]);
		loop(j, 0, len[i]) {
			ip[i+N][len[i]-j-1] = ip[i][j];
		}
	}
	NN=N*2;

	loop (i, 0, NN) {
		vs[i+1] += vs[i];
		//cout << vs[i+1] << ' ';
	} //cout << endl;

	S = vs[NN];
	A = S+1;
	V = A+2;
	//cout << "S = " << S << endl;

	val[S] = 1;
	loop (i, 0, N) {
		int l = len[i];
		loop (j, 0, l) {
			int k=0, s1=j+1, s2=l-j-1;
			while (s1+k < l and s2+k < l and ip[i][s1+k] == ip[i+N][s2+k]) k++;
			//cout << i << ' ' << j << ' ' << k << endl;
			//cout << ip[i]+s1 << ' ' << ip[i+N]+s2 << endl;
			if (s1+k == l and s2+k == l)
				addEdge(S, A, 2*k);
			else if(s1+k == l)
				addEdge(S, getId(i+N, s2+k), k*2);
			else if(s2+k == l)
				addEdge(S, getId(i, s1+k), k*2);
			else val[S] = max(val[S], k*2);
		}
		loop(j, 0, l) {
			int k=0, s1=j+1, s2=l-j;
			while (s1+k < l and s2+k < l and ip[i][s1+k] == ip[i+N][s2+k]) k++;
			//cout << i << ' ' << j << ' ' << k << endl;
			//cout << ip[i]+s1 << ' ' << ip[i+N]+s2 << endl;
			if (s1+k == l and s2+k == l)
				addEdge(S, A, 2*k+1);
			else if(s1+k == l)
				addEdge(S, getId(i+N, s2+k), k*2+1);
			else if(s2+k == l)
				addEdge(S, getId(i, s1+k), k*2+1);
			else val[S] = max(val[S], k*2+1);
		}
	}

	loop (i, 0, N) {
		addEdge(A, getId(i, 0), 0);
	}

	loop (i, 0, N) {
		 loop(j, 0, N) {
			 make(i+N, j);
			 make(i, j+N);
		 }
	}

	if (hasLoop()) {
		cout << -1 << endl;
		return 0;
	}
	fill(vt, vt+V+5, 0);
	cout << dp(S) << endl;


	return 0;
}

