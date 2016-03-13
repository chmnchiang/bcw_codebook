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

const int MXN = 2100;

struct Cmd {
	int t;
	vector<int> vec;
};

int A,B,C,D;
int is2[MXN];
int flag;
vector<Cmd> ans;

void output() {
	assert(SZ(ans) <= 15000);
	cout << SZ(ans) << endl;
	for (auto it:ans) {
		cout << it.t;
		if (it.t != 3) {
			for (int i=0; i<SZ(it.vec); i+=2) {
				int a = it.vec[i];
				int b = it.vec[i+1];
				if (flag) swap(a,b);
				cout << " " << a << " " << b;
			}
		} else {
			if (flag) {
				swap(it.vec[0],it.vec[1]);
				swap(it.vec[2],it.vec[3]);
				cout << " " << it.vec[2] << " " << it.vec[3] << " " << it.vec[0] << " " << it.vec[1];
			} else {
				cout << " " << it.vec[0] << " " << it.vec[1] << " " << it.vec[2] << " " << it.vec[3];
			}
		}
		cout << "\n";
	}
}
void solve() {
	int e = B - A;
	while (e % 2 == 0) e /= 2;
	if ((D - C) % e) return;
	e = B - A;
	while (e % 2 == 0) {
		if (A & 1) {
			ans.PB({1,{A,B}});
			A++;
			B++;
		} else {
			ans.PB({2,{A,B}});
			assert(A % 2 == 0);
			assert(B % 2 == 0);
			A /= 2;
			B /= 2;
		}
		e = B - A;
	}
	int lst = 2049;
//	int lst = 10;
	while (A != 1) {
		int x = A, y = B;
		while (x < lst) {
			ans.PB({1,{x,y}});
			x++;
			y++;
		}
		lst = A;
		ans.PB({3,{A,B,B,B+e}});
		B = B + e;
		if (A & 1) {
			ans.PB({1,{A,B}});
			A++;
			B++;
		}
		assert(A % 2 == 0);
		assert(B % 2 == 0);
		ans.PB({2,{A,B}});
		A /= 2;
		B /= 2;
		assert(B-A == e);
	}
	int x = A, y = B;
	while (x < lst) {
		ans.PB({1,{x,y}});
		x++;
		y++;
	}
	while (B-A != D-C) {
		ans.PB({3,{A,B,B,B+e}});
		B += e;
	}
	while (A < C) {
		ans.PB({1,{A,B}});
		A++;
		B++;
	}
}
int main() {
	for (int i=1; i<MXN; i*=2) {
		is2[i] = 1;
	}
	IOS;
	flag = 0;
	cin >> A >> B >> C >> D;
	if (A == B and C == D) {
		while (not is2[A]) {
			ans.PB({1,{A,A}});
			A++;
		}
		while (A > 1) {
			ans.PB({2,{A,A}});
			assert(A % 2 == 0);
			A /= 2;
		}
		while (A < C) {
			ans.PB({1,{A,A}});
			A++;
		}
	} else if (A == B or C == D) {
		// pass
	} else {
		if (A < B and C < D) {
			solve();
		} else if (A > B and C > D) {
			flag = 1;
			swap(A,B);
			swap(C,D);
			solve();
		}
	}
	output();

	return 0;
}

