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



int main() {
	IOS;
	FILEIO("prefixes");

	string s;
	cin >> s;

	int len = s.length();
	const int MX = 555555;
	static char mn[MX];
	char z = 127;
	for (int i=0; i<len; i++) {
		z = min(z, s[i]);
		mn[i] = z;
	}

	vector<char> v1, v2;
	v1.reserve(MX);
	v2.reserve(MX);
	for (int i=len-1; i>=0; i--) {
		if (s[i] == mn[i]) {
			v1.PB(s[i]);
		} else v2.PB(s[i]);
	}

	for (auto c: v1) {
		cout << c;
	}
	reverse(ALL(v2));
	for (auto c: v2) {
		cout << c;
	}
	cout << endl;


    return 0;
}

