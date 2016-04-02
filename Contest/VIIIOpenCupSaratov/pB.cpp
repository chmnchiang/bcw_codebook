#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define F first
#define S second
#define PB push_back
#define MB emplace_back
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
template<typename T, size_t N>
ostream& operator <<(ostream &s, const array<T, N> &c) {
    s<<"| ";
    for (auto it : c) s << it << " ";
    s<<"|";
    return s;
}
// Let's Fight!

#define loop(i, a, b) for (auto (i)=(a); (i) != (b); (i) += ((b) < (a) ? -1 : 1))

#define int long long
using a26 = array<int, 26>;
const int MX = 101010;

string ip;
int N;

int nid = 0;
struct Node {
	bool isa;
	int c;
	int rp;
	vector<Node> ch;
	int id;

	Node () { id = nid++;};
	Node (bool i, int _c, int r) : isa(i), c(_c), rp(r) { id=nid++; };
};

Node alpNode(char c) {
	return {1, c-'a', 0};
}
Node repNode(int t) {
	return {0, 0, t};
}


Node root;

int getInt(int &id) {
	int ret = 0;
	while (isdigit(ip[id])) {
		ret *= 10;
		ret += ip[id++]-'0';
	}
	return ret;
}

int parse(Node &nd, int id) {
	while (id < N) {
		char c = ip[id];
		if (c == ')') {
			return id+1;
		} else if (isdigit(c)) {
			int t = getInt(id);
			nd.ch.PB(repNode(t));
			id++;
			id = parse(nd.ch.back(), id);
		} else {
			nd.ch.PB(alpNode(c));
			id++;
		}
	}
	return id;
}

const int INF = 1e13;
a26 operator + (const a26 &a1, const a26 &a2) {
	a26 ret = {};
	for (int i=0; i<26; i++)
		ret[i] = min(a1[i] + a2[i], INF);
	return ret;
}

const int ZZ = 1e5;
a26 operator * (int t, const a26 &a1) {
	a26 ret = {};
	if (t <= ZZ) { 
		for (int i=0; i<26; i++) {
			ret[i] = min(t*a1[i], INF);
		}
		return ret;
	}

	int q1 = ZZ, q2 = t/q1, q3 = t%q1;
	for (int i=0; i<26; i++)
		ret[i] = min(q1*a1[i], INF);
	
	for (int i=0; i<26; i++)
		ret[i] = min(q2*ret[i], INF);
	
	for (int i=0; i<26; i++)
		ret[i] = min(ret[i] + q3*a1[i], INF);
	return ret;
}

a26 dfs(const Node &n, int k) {
	int kk=k;
	//cout << "ID = " << n.id << ' ' << k << endl;
	a26 arr = {};
	if (n.isa) {
		arr[n.c] = 1;
		return arr;
	}

	vector<a26> vec;
	int sm = 0;
	for (const auto &c: n.ch) {
		auto res = dfs(c, k);
		k -= res[0];
		sm += res[0];
		vec.PB(res);
		arr = arr + res;
		//cout << arr << ' ' << k << endl;
		if (not k) {
			return arr;
		}
	}

	int m = (sm ? (k-1) / sm : n.rp - 1);
	if (m >= n.rp - 1) {
		auto x = (n.rp)*arr;
		//cout << n.rp << endl;
		assert(x[0] <= kk);
		return x;
	}

	arr = (m+1) * arr;
	int re = k - m * sm;
	//cout << "Re = " << re << endl;

	for (int i=0; i<SZ(vec); i++) {
		if (vec[i][0] >= re) {
			arr = arr + dfs(n.ch[i], re);
			//cout << kk << " " << arr << endl;
			assert (arr[0] == kk);
			return arr;
		} else {
			re -= vec[i][0];
			arr = arr + vec[i];
		}
	}

	
	return arr;
}

int32_t main() {
	IOS;
	FILEIO("az");
	cin >> ip;
	N = ip.length();
	int K;
	cin >> K;

	root.rp=1;
	parse(root, 0);

	auto res = dfs(root, K);
	for (int i=0; i<26; i++) {
		if (res[i]) {
			cout << char('a'+i) << ' ' << (res[i] > 1000000000000LL ? -1 : res[i]) << endl;
		}
	}
	
	
	return 0;
}

