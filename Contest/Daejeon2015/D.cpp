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

const int MAXN = 10101;

int N;
int px[MAXN], py[MAXN];
const int INF = 1e9;

bool calc()
{
	int MX = INF, mx = -INF, MY = INF, my = -INF;

	for (int i=0; i<N; i++) {
		int i1 = i, i2 = (i+1)%N, i3 = (i+2)%N, i4 = (i+3)%N;

		if (px[i2] == px[i3]) {
			bool f1 = px[i1] < px[i2];
			bool f2 = px[i3] < px[i4];
			if (f1^f2) {
				if (py[i2] < py[i3]) {
					MX = min(MX, px[i2]);
				} else {
					mx = max(mx, px[i2]);
				}
			}
		} else {
			bool f1 = py[i1] < py[i2];
			bool f2 = py[i3] < py[i4];
			if (f1^f2) {
				if (px[i2] < px[i3]) {
					my = max(my, py[i2]);
				} else MY = min(MY, py[i2]);
			}
		}
	}

	//cout << mx << ' ' << MX << endl;
	//cout << my << ' ' << MY << endl;
	return (mx <= MX) and (my <= MY);
}

int main() {
	IOS;

	int T;
	cin>>T;
	while(T--)
	{
		cin>>N;
		for(int i=0; i<N; i++)
			cin>>px[i]>>py[i];

		bool ans = calc();
		cout<<(ans ? "YES" : "NO")<<endl;
	}

    return 0;
}

