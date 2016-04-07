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

typedef pair<int,int> pii;

int N,Q;
int dx,dy,X,Y;
int minX,minY;
pii cen;
int cnt[2005][2005];
pii pt[500005];

inline int qry(int x1, int y1, int x2, int y2) {
//	cout << pii(x1,y1) << " " << pii(x2,y2) << " : ";
	x1 = max(x1, 1); x1 = min(x1, X);
	y1 = max(y1, 1); y1 = min(y1, Y);
	x2 = min(x2, X); x2 = max(x2, 1);
	y2 = min(y2, Y); y2 = max(y2, 1);
	assert(x1 <= x2);
	assert(y1 <= y2);
	assert(0 < x1 and x2 < 2005 and 0 < y1 and y2 < 2005);
//	cout << cnt[x2][y2] - cnt[x1-1][y2] - cnt[x2][y1-1] + cnt[x1-1][y1-1] << endl;
	return cnt[x2][y2] - cnt[x1-1][y2] - cnt[x2][y1-1] + cnt[x1-1][y1-1];
}
int calc(int M) {
	if (N == 0) {
		cen = {1,1};
		return 0;
	}
	int ans = 0;
	REP1(i,1,dx) REP1(j,1,dy) {
		int x = i + j, y = i - j;
		x = x - minX + 1;
		y = y - minY + 1;
		int tmp = qry(x-M,y-M,x+M,y+M);
//		cout <<" CHECK " << pii(i,j) << " : " << tmp << endl;
		if (tmp > ans or (tmp == ans and tie(j,i) < tie(cen.S,cen.F))) {
			ans = tmp;
			cen = {i,j};
		}
	}
	
	return ans;
}
int main() {
	IOS;
	int cas = 0;
	while (cin >> dx >> dy >> N >> Q) {
		if (not dx) break;
		minX = minY = 1e9;
		REP(i,N) {
			int x,y;
			cin >> x >> y;
			pt[i] = {x+y,x-y};
			minX = min(minX, pt[i].F);
			minY = min(minY, pt[i].S);
		}
		X = Y = 0;

		REP1(i,1,dx) REP1(j,1,dy) {
			minX = min(minX, i+j);
			minY = min(minY, i-j);
		}
		REP(i,N) {
			pt[i].F = pt[i].F - minX + 1;
			pt[i].S = pt[i].S - minY + 1;
			X = max(X, pt[i].F);
			Y = max(Y, pt[i].S);
		}

		REP1(i,1,dx) REP1(j,1,dy) {
			X = max(X, i+j-minX+1);
			Y = max(Y, i-j-minY+1);
		}
		
		REP1(i,0,X) REP1(j,0,Y) cnt[i][j] = 0;
		REP(i,N) {
			cnt[pt[i].F][pt[i].S]++;
		}

		REP1(i,1,X) {
			REP1(j,1,Y) {
				cnt[i][j] = cnt[i][j] + cnt[i-1][j] + cnt[i][j-1] - cnt[i-1][j-1];
			}
		}

		cas++;
		cout << "Case " << cas << ":\n";
		REP(_,Q) {
			int M;
			cin >> M;
			int ans = calc(M);
			cout << ans << " (" << cen.F << "," << cen.S << ")" << endl;
		}
	}



	return 0;
}

