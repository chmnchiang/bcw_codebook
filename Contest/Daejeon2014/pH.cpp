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

string a, b;
vector<int> v1, v2;

int main() {
	IOS;
	int nT;
	cin >> nT;
	while (nT--) {
		cin >> a >> b;
		v1.clear();
		v2.clear();
		int n = SZ(a);
		for (int i=0; i<n; i++) {
			if (a[i] == 'a') v1.PB(i);
			if (b[i] == 'a') v2.PB(i);
		}
		int ans = 0;
		for (int i=0; i<n/2; i++) 
			ans += abs(v1[i] - v2[i]);
		cout << ans << "\n";
	}

    return 0;
}

