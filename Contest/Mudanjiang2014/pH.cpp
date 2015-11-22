#include<bits/stdc++.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define F first
#define S second
#define PB push_back
#define ALL(x) begin(x),end(x)
#define SZ(x) ((int)(x).size())
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
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
const int MX = 100005;


int Q, root, nMem;
string str, qry;
int len, val;
map<string, int> mp[MX];
vector<string> ss;

void init() {
	for (int i=0; i<=val+2; i++) {
		mp[i].clear();
	}
	val = 0;
	ss.clear();
}

int parse(int v, int l) {
	int id = l;
	id ++;
	while (str[id] != '}') {
		string key;
		while (str[id] != ':') {
			key += str[id++];
		}
		id ++;
		if (str[id] == '{') {
			int u = ++val;
			mp[v][key] =  u;
			id = parse(u, id);
			id ++;
		} else {
			string x = "";
			while (str[id] != ',' and str[id] != '}') {
				x += str[id++];
			}
			int u = ss.size();
			mp[v][key] = -u-1;
			ss.PB(x);
		}
		if (str[id] == ',') id++;
	}
	return id;
}

void prt(int id) {
	if (id < 0) {
		cout << ss[-id-1];
	} else {
		cout << "{";
		bool fs = true;
		for (auto x: mp[id]) {
			if (fs) {
				fs = false;
			} else {
				cout << ',';
			}
			string key = x.F;
			int z = x.S;
			cout <<  key << ':';
			prt(z);
		}
		cout << "}";
	}
}

void build() {
	len = str.length();
	parse(val, 0);
}

vector<string> split(string ip, char ch) {
	vector<string> ret;
	string s = "";
	for (int i=0; i<SZ(ip); i++) {
		if (ch == ip[i]) {
			ret.PB(s);
			s = "";
		} else {
			s += ip[i];
		}
	}
	ret.PB(s);
	return ret;
}

int main() {
    IOS;
	int nT;
	cin >> nT;
	while (nT--) {
		cin >> str;
		cin >> Q;
		init();
		build();
		while (Q--) {
			cin >> qry;
			auto q = split(qry, '.');
			int v = 0;
			bool fg = true;
			for (auto x: q) {
				if (mp[v].find(x) == mp[v].end()) {
					fg = false; break;
				}
				v = mp[v][x];
			}
			if (fg) {
				prt(v);
				cout << "\n";
			} else {
				cout << "Error!" << endl;
			}
		}

	}


    return 0;
}
