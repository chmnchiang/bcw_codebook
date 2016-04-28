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





using pii=pair<int,int>;
int N;
int L, R;
vector<pii> ans;
const int MX = 333;
char _mp[MX*2];
char *mp = _mp+MX;

struct D {
	friend ostream& operator << (ostream &o, D d) {
		for (int i=L; i<=R; i++) {
			o << mp[i];
		}
		return o;
	}
} DD;

void in(int a, int b) {
	//cout << a << ' ' << b << endl;
	assert(L <= a and a+1 <= R);
	assert(L <= b and b+1 <= R);
	assert(mp[b] == '_' and mp[b+1] == '_');
	swap(mp[a], mp[b]);
	swap(mp[a+1], mp[b+1]);
	ans.PB({a, b});
	//cout << DD << endl;
}

int main() {
	cin>>N;
	L = -N*2+1;
	R = N*2;
	for (int i=L; i<=0; i++) mp[i] = '_';
	for (int i=1; i<=R; i++) {
		mp[i] = (i%2 ? 'b' : 'a');
	}

	int z = N%4;
	if (z != 2 and z != 3) {
		int l = 3, r = R-2;
		int t = 1;

		for (int i=0; i<N/2; i++) {
			if (t) {
				in(r, l-4);
				r -= 4;
			} else {
				in(l, r+4);
				l += 4;
			}
			t = !t;
		}
	}

	if (N == 3) {
		in(2, -1);
		in(5, 2);
		in(3, -3);
	} else if (z == 0) {
		int l = 0, r = N+3;
		for (int i=0; i<N/2; i++) {
			if (i % 2 == 0) {
				in(l, r-4);
				l += 4;
			} else {
				in(r, l-4);
				r += 4;
			}
		}
	} else if (z == 1) {
		in(N+1, N-2);
		int l = 0, r = N+4;
		for (int i=0; i<N/2; i++) {
			if (i % 2 == 0) {
				in(l, r-4 + (i==0));
				l += 4;
			} else {
				in(r, l-4);
				r += 4;
			}
		}
	} else if (z == 2) {
		in(R-2, -1);
		in(R-5, R-2);

		//cout << "zzz" << endl;
		{
		int a = N-4, b = N+1, ls = R-5;
		for (int i=0; i<N/2-2; i++) {
			if (i%2 == 0) {
				in(a, ls);
				ls = a;
				a -= 4;
			} else {
				in(b, ls);
				ls = b;
				b += 4;
			}
		}
		}

		int a = N, b = 0, ls = 2;
		for (int i=0; i<N/2; i++) {
			if (i%2 == 0) {
				in(a + (i == N/2-1), ls);
				ls = a;
				a += 4;
			} else {
				in(b, ls);
				ls = b;
				b += (4 + (i == 1));
			}
		}
	} else if (z == 3) {
		in(N+1, -1);
		{
		int ls = N+1, b = N-2, a = N+5;
		for (int i=0; i<N/2-1; i++) {
			if (i%2 == 0) {
				in(b, ls);
				ls = b;
				b -= 4;
			} else {
				in(a, ls);
				ls = a;
				a += 4;
			}
		}
		}
		in(3, R-2);
		{
		int ls = 3, b = N-5, a = N+2;
		for (int i=0; i<N/2-1; i++) {
				if (i%2 == 1) {
					in(b - 2 * (i==N/2-2), ls);
					ls = b;
					b -= 4;
				} else {
					in(a, ls);
					ls = a;
					a += 4;
				}
			}
		}
		in(R-1, 0);
	}

	for (auto p: ans) {
		cout << p.F << " to " << p.S << endl;
	}

	return 0;
}

