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

#define int long long

int32_t main() {
	FILEIO("budget");
	IOS;

	int N, M, P;
	cin >> M >> N >> P;
	const int MX = 123;
	static int S[MX];
	static int R[MX];

	for (int i=0; i<M; i++) {
		cin >> S[i];
		S[i] = (P + S[i] - 1) / S[i];
	
	} 
	for (int j=0; j<N; j++)
		cin >> R[j];

	sort(R, R+N);
	reverse(R, R+N);

	int l = 0, r = 12345678901234ll;

	static int T[MX];

	auto test = [&](int a) -> bool{
		for (int i=0; i<M; i++) {
			T[i] = a - S[i];
		}

		for (int j=0; j<N; j++) {
			int mn = T[0];
			int mp = 0;
			for (int i=1; i<M; i++) {
				if (T[i] > mn) {
					mn = T[i];
					mp = i;
				}
			}
			if (mn < R[j])
				return false;
			T[mp] -= S[mp];
		}
		return true;
	};

	while (l < r) {
		int md = (l+r) / 2;
		if (test(md))
			r = md;
		else
			l = md+1;
	}

	cout << l-1 << endl;

    return 0;
}
