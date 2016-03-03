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

vector<string> s_type = {
	"AA",
	"AB",
	"AO",
	"BB",
	"BO",
	"OO"
};
map<string, string> abo_map;
vector<string> abo_type = {
	"A",
	"AB",
	"B",
	"O"
};

string s_to_abo(string s) {
	assert(SZ(s) == 2);
	if (s[0] > s[1]) swap(s[0], s[1]);
	
	return abo_map[s];
}

void pre() {
	abo_map["AA"] = "A";
	abo_map["AB"] = "AB";
	abo_map["AO"] = "A";
	abo_map["BB"] = "B";
	abo_map["BO"] = "B";
	abo_map["OO"] = "O";
}

bool judge_abo(string s1, string s2, string s) {


	for (int i=0; i<6; i++) {
		string r1 = s_type[i];
		if (s_to_abo(r1) != s1) continue;
		for (int j=0; j<6; j++) {
			string r2 = s_type[j];
			if (s_to_abo(r2) != s2) continue;

			for (int ii=0; ii<2; ii++) {
				for (int jj=0; jj<2; jj++) {
					string r;
					r += r1[ii];
					r += r2[jj];

					if (s_to_abo(r) == s) return true;
				}
			}
		}
	}
	return false;
}

bool judge_pm(int i1, int i2, int i) {
	if (i1 == -1 and i2 == -1) {
		return i == -1;
	}

	return true;
}

pair<string, int> conv(string s) {
	string ss = s.substr(0, SZ(s)-1);
	int t = (s[SZ(s)-1] == '+' ? 1 : -1);
	return {ss, t};
}

string rev(string s, int t) {
	return s + (t == 1 ? "+" : "-");
}

int main() {
    IOS;

	pre();

	
//	cout << judge_abo("A", "B", "B") << endl;

	int T = 0;
	while (true) {
		string x1, x2, x;
		cin >> x1 >> x2 >> x;
		if (x1 == "E") return 0;

		vector<string> ans;
		if (x == "?") {
			string s1, s2;
			int i1, i2;
			tie(s1, i1) = conv(x1);
			tie(s2, i2) = conv(x2);
			for (int i=0; i<4; i++) {
				string abo = abo_type[i];
				for (int j=-1; j<=1; j+=2) {
					if (judge_abo(s1, s2, abo) and judge_pm(i1, i2, j)) {
						ans.PB(rev(abo, j));
					}
				}
			}
		} else {
			int t = (x1 == "?" ? 1 : 2);
			string s1, s;
			int i1, i3;
			if (t == 1) 
				tie(s1, i1) = conv(x2);
			else
				tie(s1, i1) = conv(x1);

			tie(s, i3) = conv(x);

			for (int i=0; i<4; i++) {
				string abo = abo_type[i];
				//cout << s1 << ' ' << abo << ' ' << s << endl;
				for (int j=-1; j<=1; j+=2) {
					if (judge_abo(s1, abo, s) and judge_pm(i1, j, i3)) {
						ans.PB(rev(abo, j));
					}
				}
			}
		}

		sort(ALL(ans));
		ans.resize(unique(ALL(ans)) - ans.begin());

#define _pa(v) if ((v) == "?") { \
	if (SZ(ans) > 1) {\
		cout << "{"; \
		for (int i=0; i<SZ(ans); i++) { \
			if (i) cout << ", "; \
			cout << ans[i]; \
		} cout << "}"; \
	} else if (SZ(ans) == 1) { \
		cout << ans[0]; \
	} else cout << "IMPOSSIBLE"; \
} else cout << v;
		
		T++;
		cout << "Case " << T << ": ";
		_pa(x1);
		cout << ' ';
		_pa(x2);
		cout << ' ';
		_pa(x);
		cout << endl;
	}
	

    return 0;
}

