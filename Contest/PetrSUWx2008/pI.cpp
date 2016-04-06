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
const int MX = 2101010;

int Z;
struct SAM{
	struct State{
		int par, go[50], val;
		int dp;
		int walk;
		bool vt, vt2;
		State () : par(0), val(0), dp(0), walk(0), vt(0), vt2(0) { FZ(go); }
		State (int _val) : par(0), val(_val), dp(0), walk(0), vt(0), vt2(0) { FZ(go);}
	};
	vector<State> vec;
	int root, tail;
	
	void init(int arr[], int len){
		vec.resize(2);
		vec[0] = vec[1] = State(0);
		root = tail = 1;
		for (int i=0; i<len; i++)
			extend(arr[i]);
	}
	void extend(int w){
		int p = tail, np = vec.size();
		vec.PB(State(vec[p].val+1));
		for ( ; p && vec[p].go[w]==0; p=vec[p].par)
			vec[p].go[w] = np;
		if (p == 0){
			vec[np].par = root;
		} else {
			if (vec[vec[p].go[w]].val == vec[p].val+1){
				vec[np].par = vec[p].go[w];
			} else {
				int q = vec[p].go[w], r = vec.size();
				vec.PB(vec[q]);
				vec[r].val = vec[p].val+1;
				vec[q].par = vec[np].par = r;
				for ( ; p && vec[p].go[w] == q; p=vec[p].par)
					vec[p].go[w] = r;
			}
		}
		tail = np;
	}

	int dp2(int v) {
		auto &st = vec[v];
		if (st.vt2) return st.walk;

		st.vt2 = true;
		int s = 0;
		for (int i=0; i<26; i++) {
			if (st.go[i]) 
				s |= dp2(st.go[i]);
		}
		for (int i=26; i<26+20; i++) {
			if (st.go[i]) 
				s |= (1<<(i-26));
		}
		st.walk = s;
		//cout << v << ' ' << s << endl;
		return s;
	}

	void mkdp2() {
		for (int i=root; i<SZ(vec); i++) {
			dp2(i);
		}
	}

	int dp(int v) {
		auto &st = vec[v]; 
		if (st.walk != Z) return 0;
		if (st.vt) return st.dp;
		int s = 0;
		st.vt = true;
		for (int i=0; i<26; i++) {
			if (st.go[i]) 
				s += dp(st.go[i]);
		}
		s++;
		st.dp = s;
		return s;
	}
} sam;

int N;

void qry(int n) {
	int nv = sam.root;
	while (true) {
		//cout << n << endl;
		if (!n) {
			putchar('\n');
			return;
		}
		n--;
		for (int i=0; i<26; i++) {
			if (!sam.vec[nv].go[i]) continue;
			if (sam.dp(sam.vec[nv].go[i]) > n) {
				putchar('a'+i);
				nv = sam.vec[nv].go[i];
				break;
			} else n -= sam.dp(sam.vec[nv].go[i]);
			assert(i != 25);
		}
	}
}

int32_t main() {
	IOS;
	FILEIO("spell");

	cin >> N;
	Z = (1<<N)-1;
	int L = 0;
	static int op[MX];
	string s;
	int tc = 26;
	loop (i, 0, N) {
		cin >> s;
		for (auto c: s) {
			op[L++] = c - 'a';
		}
		op[L++] = tc++;
	}
	sam.init(op, L);
	sam.mkdp2();


	int Q; cin >> Q;
	loop (i, 0, Q) {
		int n;
		cin >> n;
		assert(n < sam.dp(sam.root));
		qry(n);
	}

	return 0;
}
