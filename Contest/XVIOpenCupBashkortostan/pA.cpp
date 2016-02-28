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
#define endl "\n"
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
#define REP(i,x) for(int i=0;i<(x);i++)
#define REP1(i,a,b) for (int i=(a);i<=(b);i++)
// Let's Fight!

const int MXN = 3005;

struct Answer {
	string s,c;
	int v;
};

int N,doneR[MXN],doneC[MXN],rem;

int cntR[MXN][26], cntC[MXN][26], zr[MXN], zc[MXN];

string mp[MXN];
vector<Answer> ans;

void erase(int i, int j) {
	if (mp[i][j] == '?') return;
	int c = mp[i][j] - 'a';
	cntR[i][c]--;
	if (!cntR[i][c]) zr[i]--;
	cntC[j][c]--;
	if (!cntC[j][c]) zc[j]--;
	rem--;
	mp[i][j] = '?';
}
void setr(int r) {
	//cout << "SETR " << r << endl;
	char c;
	REP(j,N) {
		if (mp[r][j] != '?') c = mp[r][j];
		erase(r,j);
	}
	string p;
	p += c;
	ans.PB({string("h"),p,r});
	doneR[r] = 1;
}
void setc(int c) {
	//cout << "SETC " << c << endl;
	char col=0;
	REP(i,N) {
		if (mp[i][c] != '?') col = mp[i][c];
		erase(i,c);
	}
	string p;
	p += col;
	ans.PB({string("v"),p,c});
	doneC[c] = 1;
}
int main() {
	IOS;

	cin >> N;
	rem = 0;
	REP(i,N) {
		cin >> mp[i];
		REP(j,N) {
			if (mp[i][j] != '?') {
				int c = mp[i][j] - 'a';
				cntR[i][c]++;
				cntC[j][c]++;
				if (cntR[i][c] == 1) zr[i]++;
				if (cntC[j][c] == 1) zc[j]++;
				rem++;
			}
		}
	}

	while (rem) {
		REP(i,N) {
			if (zr[i] == 1) {
				setr(i);
				break;
			}
			if (zc[i] == 1) {
				setc(i);
				break;
			}
		}
	}

	REP(i,N) {
		if (!doneR[i]) ans.PB({"h", "a", i});
		if (!doneC[i]) ans.PB({"v", "a", i});
	}
	reverse(ALL(ans));
	for (auto it:ans)
		cout << it.s << " " << it.v+1 << " " << it.c << endl;
	
	
	return 0;
}

