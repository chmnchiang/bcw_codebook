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

#define x first
#define y second

#define loop(i, a, b) for (auto (i)=(a); (i) != (b); (i)+= ((a) > (b) ? -1 : 1))

template<typename T>
using vec = vector<T>;
using p6i = array<int, 6>;
using pii = pair<int, int>;
using Rect = pair<pii, pii>;

int N, Q;
int W, H;
vector<Rect> geo;
vector<p6i> link;

bool inside(Rect r, pii p) {
	return (r.F.x <= p.x and p.x <= r.S.x) and
		   (r.F.y <= p.y and p.y <= r.S.y);
}

bool inside(Rect r, Rect r2) {
	return inside(r, r2.F) and inside(r, r2.S);
}

int main() {
	IOS;

	int cas=0;
	while (true) {
		cin>>N>>Q>>W>>H;

		if (not N and not Q and not W and not H)
			break;

		cin >> N >> 


	}

	return 0;
}


