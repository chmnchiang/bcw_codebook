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

struct ZZ {
	map<string,int> mp;
	map<string,string> hao;
} tree[100005];

int pos,len,mem;
string ip;
vector<vector<string>> ans;
vector<int> width;

char preview() {
	for (int i=pos; i<len; i++) {
		if (ip[i] != ' ' and ip[i] != '\t' and ip[i] != '\n') {
			return ip[i];
		}
	}
	return 0;
}
string read_until(char ch) {
	string s;
	while (pos < len and ip[pos] != ch) {
		s += ip[pos];
		pos++;
	}
	assert(pos < len);
	s += ip[pos++];
	return s;
}

int parseKSON() {
	read_until('{');
	int id = mem++;
	if (preview() == '}') {
		read_until('}');
		return id;
	}


	while (true) {
		string key = read_until('"');
		key = read_until(':');
		while (!key.empty() and key.back() != '"') key.pop_back();
		key.pop_back();

		if (preview() == '{') {
			tree[id].mp[key] = parseKSON();
		} else {
			assert(preview() == '"');
			read_until('"');
			string val = read_until('"');
			val.pop_back();
			tree[id].hao[key] = val;
		}

		if (preview() == ',') {
			read_until(',');
		} else {
			break;
		}
	}
	read_until('}');
	return id;
}
void go(int u) {
	cout << "{\n";
	for (auto it:tree[u].mp) {
		cout<<it.F<<" : "<<endl;
		go(it.S);
	}
	for (auto it:tree[u].hao) {
		cout<<it.F<<" : "<<it.S<<endl;
	}
	cout << "}\n";
}
string strip(string s) {
	int p = 0;
	int l = SZ(s);
	while (p < l and s[p] != ':') p++;
	p++;
	int r = l-1;
	while (r >= p and s[r] == ' ') r--;
	if (p > r) return "";
	return s.substr(p,r-p+1);
}
int isv(string s) {
	int p = 0;
	int l = SZ(s);
	while (p < l and s[p] == ' ') p++;
	if (p+6 > l) return 0;
	if (s.substr(p,6) == "Value:") return 1;
	return 0;
}
void outputbar() {
	int m = SZ(width);
	cout<<"+";
	REP(i,m) {
		REP(j,width[i]) cout<<"-";
		cout<<"+";
	}
	cout<<endl;
}
string query(string s2) {
	string s = strip(s2);
	vector<string> vec;
	{
		int p = 0;
		string tmp;
		while (p < SZ(s)) {
			if (s[p] != '.') {
				tmp += s[p];
			} else {
				vec.PB(tmp);
				tmp.clear();
			}
			p++;
		}
		vec.PB(tmp);
	}
	int rt = 0;
	REP(i,SZ(vec)) {
		//cout<<"*"<<vec[i]<<"*"<<endl;
		if (i == SZ(vec)-1) {
			if (!tree[rt].hao.count(vec[i])) break;
			return tree[rt].hao[vec[i]];
		}
		if (!tree[rt].mp.count(vec[i])) break;
		rt = tree[rt].mp[vec[i]];
	}
	return s2;
}
int main() {
	IOS;
	{
		string s;
		while (getline(cin,s)) {
			ip += s + "\n";
		}
		len = SZ(ip);
	}
	parseKSON();

	vector<string> sheet;
	read_until('\n');
	string s = read_until('\n');
	int m = count(ALL(s), '+') - 1;
	int n = 0;

	vector<int> ws360(m);
	vector<int> start(m);
	{
		int j = 1;
		REP(i,m) {
			start[i] = j;
			while (j < SZ(s) and s[j] != '+') j++;
			ws360[i] = j++;
		}
	}

	width.resize(m);
	fill(ALL(width),0);
	while (true) {
		if (preview() == '+' or preview() == 0) break;

		n++;
		string ss = read_until('\n');
		vector<string> vec;
		REP(i,m) {
			s = ss.substr(start[i], ws360[i]-start[i]);
			if (isv(s)) {
				s = query(s);
			}
			vec.PB(s);
			width[i] = max(width[i], SZ(s));
		}
		ans.PB(vec);
		read_until('\n');
	}


	outputbar();
	REP(i,n) {
		cout<<"|";
		REP(j,m) {
			cout<<ans[i][j];
			int rem = width[j] - SZ(ans[i][j]);
			while (rem--) cout<<" ";
			cout<<"|";
		}
		cout<<endl;
		outputbar();
	}

	return 0;
}

