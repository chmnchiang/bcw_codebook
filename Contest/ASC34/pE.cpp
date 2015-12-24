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

int ans[30];
set<int> vec[30];

int main() {
	IOS;
	FILEIO("chipmunks");
	ans[1] = 1;
	ans[2] = 2;
	ans[3] = 3;
	ans[4] = 5;
	ans[5] = 8;
	ans[6] = 14;
	ans[7] = 25;
	ans[8] = 45;
	ans[9] = 85;
	ans[10] = 162;
	ans[11] = 310;
	ans[12] = 595;
	ans[13] = 1165;
	ans[14] = 2285;
	ans[15] = 4485;
	ans[16] = 8808;
	ans[17] = 17306;
	ans[18] = 34302;
	ans[19] = 68009;
	ans[20] = 134853;
	/*
	   vec[0].insert(0);
	vec[1].insert(1);
	for (int n=2; n<=20; n++) {
		vector<int> bye;
		set<int> app;
		for (int i=1; i<=n-1; i++) {
			for (auto v1:vec[i]) {
				for (auto v2:vec[i-1]) {
					if (app.count(v1-v2)) continue;
					if (v1-v2 > 0 && v1-v2 < 4LL*ans[n-1]) {
						bye.PB(v1-v2);
						app.insert(v1-v2);
					}
				}
			}
//			cout << "vec " << i << " : " << vec[i] <<  endl;
		}
	
		sort(ALL(bye));
		bye.resize(unique(ALL(bye)) - begin(bye));
//		cout << bye << endl;
//		if (n >= 9) break;
		int x = bye.back() + 1;
		for (int i=1; i<SZ(bye); i++) {
			if (bye[i] != bye[i-1]+1) {
				x = bye[i-1] + 1;
				break;
			}
		}
		for (int i=n-1; i>=0; i--) {
			for (auto v:vec[i]) {
				vec[i+1].insert(v+x);
			}
		}
		ans[n] = x;
		cout << "ans[" << n << "] = " << x << endl;
	}
*/
	int N;
	cin >> N;
	cout << ans[N] << endl;

    return 0;
}
