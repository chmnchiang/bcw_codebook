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
#define loop(i, a, b) for (auto (i)=(a); (i) != (b); (i) += ((b) < (a) ? -1 : 1))

const int MXN = 40005;
struct Lisan {
	vector<int> seq;
	int operator [] (int i) { return seq[i]; }
	void add(int x) { seq.PB(x); }
	void build() {
		sort(ALL(seq));
		seq.resize(unique(ALL(seq)) - begin(seq));
	}
	int qry(int x) { return lower_bound(ALL(seq),x) - begin(seq); }
	int size() { return SZ(seq); }
}lx;
struct Rec {
	int x1,y1,x2,y2;
	void read() {
		cin >> x1 >> y1 >> x2 >> y2;
	}
}rec[MXN];

int W,H,N;
vector<int> add[MXN],sub[MXN];
vector<int> add2[MXN],sub2[MXN];
double okx,oky;
multiset<int> st1,st2;

bool check_ok2(double ratio) {
	double w = W * ratio;
	double h = H * ratio;
	st1.clear();
	st2.clear();
	st1.insert(H);
	st2.insert(0);
	int j=SZ(lx)-1;
	for (int i=SZ(lx)-1; i>=0; i--) {
		while (j >= 0 and lx[i] - lx[j] <= w) {
			for (auto it:add2[j]) {
				if (rec[it].y2 > rec[0].y1) st1.insert(rec[it].y1);
				if (rec[it].y1 < rec[0].y2) st2.insert(rec[it].y2);
			}
			j--;
		}
		for (auto it:sub2[i]) {
			if (rec[it].y2 > rec[0].y1) {
				st1.erase(st1.find(rec[it].y1));
			}
			if (rec[it].y1 < rec[0].y2) {
				st2.erase(st2.find(rec[it].y2));
			}
		}

		if (lx[i]-w >= 0 and lx[i]-w <= rec[0].x1 and rec[0].x2 <= lx[i]) {
			int mx = *st1.begin();
			int mn = *st2.rbegin();
			if (mn <= rec[0].y1 and mx >= rec[0].y2 and mx - mn >= h) {
				if (mn + h >= rec[0].y2) {
					oky = mn;
				} else {
					oky = rec[0].y2 - h;
				}
				okx = lx[i]-w;
				return true;
			}
		}
	}

	return false;
}

bool check_ok(double ratio) {
	double w = W * ratio;
	double h = H * ratio;
	int j=0;
	st1.clear();
	st2.clear();
	st1.insert(H);
	st2.insert(0);
	REP(i,lx.size()) {
		while (j < lx.size() and lx[j]-lx[i] <= w) {
			for (auto it:add[j]) {
				if (rec[it].y2 > rec[0].y1) st1.insert(rec[it].y1);
				if (rec[it].y1 < rec[0].y2) st2.insert(rec[it].y2);
			}
			j++;
		}
		for (auto it:sub[i]) {
			if (rec[it].y2 > rec[0].y1) {
				st1.erase(st1.find(rec[it].y1));
			}
			if (rec[it].y1 < rec[0].y2) {
				st2.erase(st2.find(rec[it].y2));
			}
		}

		if (lx[i] <= rec[0].x1 and rec[0].x2 <= lx[i]+w and lx[i]+w <= W) {
			int mx = *st1.begin();
			int mn = *st2.rbegin();
			if (mn <= rec[0].y1 and mx >= rec[0].y2 and mx - mn >= h) {
				if (mn + h >= rec[0].y2) {
					oky = mn;
				} else {
					oky = rec[0].y2 - h;
				}
				okx = lx[i];
				return true;
			}
		}
	}

	return false;
}
int main() {
	IOS;
	FILEIO("art");
	cin >> W >> H;
	rec[0].read();
	cin >> N;
	REP1(i,1,N) {
		rec[i].read();
	}

	REP1(i,0,N) {
		lx.add(rec[i].x1);
		lx.add(rec[i].x2);
	}
	lx.add(0);
	lx.add(W);
	lx.build();
	REP1(i,1,N) {
		rec[i].x1 = lx.qry(rec[i].x1);
		rec[i].x2 = lx.qry(rec[i].x2);

		add[rec[i].x1].PB(i);
		sub[rec[i].x2].PB(i);

		add2[rec[i].x2].PB(i);
		sub2[rec[i].x1].PB(i);
	}


	int w = rec[0].x2 - rec[0].x1;
	int h = rec[0].y2 - rec[0].y1;
	double l = max(1.0*w/W,1.0*h/H), r=1.0;
	REP(_,100) {
		double m = (l+r)/2;
		if (check_ok(m) or check_ok2(m)) l = m;
		else r = m;
	}
	if (check_ok(l) or check_ok2(l)) {
		cout << fixed << setprecision(10) << l << endl;
		cout << okx << " " << oky << endl;
	} else {
		cout << "-1" << endl;
	}

	return 0;
}
