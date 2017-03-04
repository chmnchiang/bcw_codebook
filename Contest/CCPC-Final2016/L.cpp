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

using pii = pair<int,int>;

int weekday[300][14][33];
int s1[300], s2[300];
int mday[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

void pre() {
	FMO(weekday);
	int d = 1;
	REP(i,100) {
		int year = 2007+i;
		REP1(mon,1,12) {
			int dd = mday[mon];
			if (year % 4 == 0 and year % 100 != 0 and mon == 2) {
				dd++;
			}
			REP1(k,1,dd) {
				weekday[i][mon][k] = d++;
				if (d > 7) d -= 7;
			}
		}
		int dd = mday[3];
		int cnt = 0;
		REP1(k,1,dd) {
			if (weekday[i][3][k] == 7) {
				cnt++;
				if (cnt == 2) {
					s1[i] = k;
					break;
				}
			}
		}
		dd = mday[11];
		REP1(k,1,dd) {
			if (weekday[i][11][k] == 7) {
				s2[i] = k;
				break;
			}
		}
	}
}
int main() {
	pre();
	int T;
	scanf("%d", &T);
	REP1(cas,1,T) {
		int ans = 1;
		int y,m,d,h,min,sec;
		scanf("%d-%d-%d %d:%d:%d", &y, &m, &d, &h, &min, &sec);
		y -= 2007;
		if (pii(m,d) < pii(3,s1[y]) or pii(m,d) > pii(11,s2[y])) {
			ans = 0;
		} else if (m == 3 and d == s1[y]) {
			if (h <= 1) ans = 0;
			else if (h == 2) ans = 3;
			else ans = 1;
		} else if (m == 11 and d == s2[y]) {
			if (h  == 0) ans = 1;
			else if (h == 1) ans = 2;
			else ans = 0;
		} else {
			ans = 1;
		}
		cout<<"Case #"<<cas<<": ";
		if (ans == 0) cout<<"PST";
		if (ans == 1) cout<<"PDT";
		if (ans == 2) cout<<"Both";
		if (ans == 3) cout<<"Neither";
		cout<<endl;
	}

	return 0;
}

