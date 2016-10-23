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


const int II = 15;
const int OO = 10;
const int QQ = II+OO;
const int MD = 2010;
const int SQ = 222;
const int MX = 55555;
int N, M;
int nx[MX][20];

static void pre() {
	for (int i=0; i<MD; i++) {
		nx[i][0] = (i*i)%MD;
	}
	for (int j=1; j<20; j++) {
		for (int i=0; i<MD; i++) {
			nx[i][j] = nx[nx[i][j-1]][j-1];
		}
	}
}

int ip[MX];
int sm[MX][II+OO];
int cnt[MX];
int flg[MX];
int SS;

void build(int a) {
	int l = a*SQ, r = a*SQ+SQ;
	r = min(r, N);
	auto &s = sm[a];
	for (int j=0; j<QQ; j++) {
		s[j] = 0;
	}
	for (int i=l; i<r; i++) {
		int z = ip[i];
		for (int j=0; j<QQ; j++) {
			s[j] += z;
			z = nx[z][0];
		}
	}
}

int nex(int x, int n) {
	for (int i=0; i<18; i++) {
		if (n & (1<<i)) {
			x = nx[x][i];
		}
	}
	return x;
}

void push(int g) {
	int l = g*SQ, r = min(g*SQ+SQ, N);
	int c = cnt[g];
	cnt[g] = 0;
	for (int i=l; i<r; i++) {
		ip[i] = nex(ip[i], c);
	}
}

int main() {
	FILEIO("enigmatic");
	IOS;
	pre();
	cin >> N;
	for (int i=0; i<N; i++) {
		cin >> ip[i];
	}
	SS = ((N+SQ-1)/SQ);
	for (int i=0; i<SS; i++) {
		build(i);
	}
	
	int Q;
	cin >> Q;
	for (int q=0; q<Q; q++) {
		int t, l, r;
		cin >> t >> l >> r;
		l--; r--;
		if (t == 2) {
			int gl = l / SQ, gr = r / SQ;
			if (gl == gr) {
				push(gl);
				build(gl);
				int s = 0;
				for (int i=l; i<=r; i++) {
					s += ip[i];
				}
				cout << s << endl;
			} else {
				int s = 0;
				for (int i=gl+1; i<gr; i++) {
					int c = cnt[i];
					if (c < II) s += sm[i][c];
					else {
						int cc = (c - II) % OO;
						s += sm[i][cc+II];
					}
				}
				push(gl);
				build(gl);
				for (int i=l; i<(gl+1)*SQ; i++) {
					s += ip[i];
				}
				push(gr);
				build(gr);
				for (int i=gr*SQ; i<=r; i++) {
					s += ip[i];
				}
				cout << s << endl;
			}
		} else {
			int gl = l / SQ, gr = r / SQ;
			if (gl == gr) {
				push(gl);
				for (int i=l; i<=r; i++) {
					ip[i] = nx[ip[i]][0];
				}
				build(gl);
			} else {
				for (int i=gl+1; i<gr; i++) {
					cnt[i] ++;
				}
				push(gl);
				for (int i=l; i<(gl+1)*SQ; i++) {
					ip[i] = nx[ip[i]][0];
				}
				build(gl);
				push(gr);
				for (int i=gr*SQ; i<=r; i++) {
					ip[i] = nx[ip[i]][0];
				}
				build(gr);
			}
		}
		/*
		REP(i,QQ) {
			push(i);
			build(i);
		}
		*/
	}

	return 0;
}
