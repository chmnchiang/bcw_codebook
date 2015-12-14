#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
#define PB push_back
#define IOS ios_base::sync_with_stdio(0);cin.tie(0)
#define SZ(x) ((int)(x).size())
#define ALL(x) begin(x),end(x)
template<typename A, typename B>
ostream& operator <<(ostream &s, const pair<A,B> &p) {
	return s<<"("<<p.first<<","<<p.second<<")";
}
template<typename A>
ostream& operator <<(ostream &s, const vector<A> &v) {
	s << "[ ";
	for (auto it:v) s << it << " ";
	s << "]";
	return s;
}
/* Let's Fight! */
#define F first
#define S second
#define PB push_back
#define IOS ios_base::sync_with_stdio(0);cin.tie(0)
#define x first
#define y second

typedef double ld;
typedef pair<ld,ld> pdd;
typedef pair<int,int> pii;
typedef pair<ld, int> pdi;

const ld PI = acosl(-1);

pdd operator + (const pdd p1, const pdd p2) {
	return {p1.x+p2.x, p1.y+p2.y};
}
pdd operator - (const pdd p1, const pdd p2) {
	return {p1.x-p2.x, p1.y-p2.y};
}
pdd operator * (const ld c, const pdd p) {
	return {p.x * c, p.y * c};
}
pdd operator - (const pdd p) {
	return (-1.0) * p;
}
ld operator * (const pdd p1, const pdd p2) {
	return p1.x * p2.x + p1.y * p2.y;
}
ld operator % (const pdd p1, const pdd p2) {
	return p1.x * p2.y - p2.x * p1.y;
}

ld sqr(ld a) { return a*a; }
ld abs2(pdd a) { return a*a; }
pdd find_center(pdd p0, pdd p1, pdd p2) {
	pdd a = p1-p0;
	pdd b = p2-p0;
	ld c1 = abs2(a)*0.5;
	ld c2 = abs2(b)*0.5;
	ld d = a%b;
	ld x = p0.x + (c1*b.y-c2*a.y) / d;
	ld y = p0.y + (a.x*c2-b.x*c1) / d;
	return {x, y};
}
pair<pdd, double> mcc(vector<pdd> p) {
	int n = SZ(p);
	pdd cen;
	random_shuffle(begin(p), end(p));
	ld r2=0;
	for (int i=0; i<n; i++) {
		if (abs2(cen-p[i]) <= r2) continue;
		cen = p[i];
		r2 = 0;
		for (int j=0; j<i; j++) {
			if (abs2(cen-p[j]) <= r2) continue;
			cen = 0.5 * (p[i]+p[j]);
			r2 = abs2(cen-p[j]);
			for (int k=0; k<j; k++) {
				if (abs2(cen-p[k]) <= r2) continue;
				cen = find_center(p[i], p[j], p[k]);
				r2 = abs2(cen-p[k]);
			}
		}
	}
	return {cen, r2};
}

struct SegmentTree {
	struct qq{
		int x, y, id;
		bool operator < (const qq &he) const {
			return tie(x, y, id) < tie(he.x, he.y, he.id);
		}
	};
	const static int MAXN = 1000005;
	int N,low,high;
	set<qq> tree[MAXN*4];
	vector<qq> ans, ip;

	void init(vector<pii> vec) {
		N = 1000000;
		init_tree(0, N, 0);
		int i=0;
		for (auto it : vec) {
			insert(0, N, {it.x, it.y, i}, 0);
			ip.PB({it.x, it.y, i});
			i++;
		}
	}
	void init_tree(int l, int r, int id) {
		tree[id].clear();
		if (l == r) return;
		int mid=(l+r)/2, lc=id*2+1, rc=id*2+2;
		init_tree(l, mid, lc);
		init_tree(mid+1, r, rc);
	}
	// fn = p.y
	void insert(int l, int r, qq p, int id) {
		tree[id].insert(p);
		if (l == r) {
			return;
		}
		int mid=(l+r)/2, lc=id*2+1, rc=id*2+2;
		if (p.y <= mid) insert(l, mid, p, lc);
		else insert(mid+1, r, p, rc);
	}
	void qry(int l, int r, int fl, int fr, int id) {
		if (l == fl && r == fr) {
			auto it = tree[id].lower_bound({low,l,-1});
			while (it != tree[id].end()) {
				if (low <= it->x && it->x <= high) {
					ans.PB(*it);
				} else {
					break;
				}
				it++;
			}
			return ;
		}
		int mid=(l+r)/2, lc=id*2+1, rc=id*2+2;
		if (fr <= mid) return qry(l, mid, fl, fr, lc);
		if (mid < fl) return qry(mid+1, r, fl, fr, rc);
		qry(l,mid,fl,mid,lc);
		qry(mid+1,r,mid+1,fr,rc);
	}
	vector<int> query(int x1, int y1, int x2, int y2) {
		y1 = max(y1, 0);
		y2 = min(y2, N);
	/*
		ans.clear();
		for (auto it : ip) {
			if (x1 <= it.x && it.x <= x2 && y1 <= it.y && it.y <= y2)
				ans.PB(it);
		}
		
		vector<int> res;
	
		for (auto it : ans)
			res.PB(it.id);
		return res;
	*/	
		vector<int> res;
		ans.clear();
		low = x1;
		high = x2;
		//assert(y1 <= y2);
		qry(0, N, y1, y2, 0);
		for (auto it : ans)
			res.PB(it.id);
		return res;
	}
}tree;

const int MX = 101010;

int N, K;
pii pt[MX];
pdd ptv[MX];
ld ptth[MX], ptd[MX];

ld reg(ld v)
{
  while(v <= -PI) v += 2*PI;
  while(v > PI) v -= 2*PI;
  return v;
}

bool check(int cen, vector<int> vec, ld r)
{
	//cout<<cen<<" "<<vec<<" "<<r<<endl;
	vector<pdi> st;
	for(auto v: vec)
	{
		if(v == cen) continue;
		if(ptd[v] > 2*r) continue;
		ld th = ptth[v];
		ld phi = acos(ptd[v]/(2*r));
    ld le = reg(th - phi);
    ld ri = reg(th + phi);
    if(le < ri)
    {
      st.PB({le, 1});
      st.PB({ri, -1});
    }
    else
    {
      st.PB({0, 1});
      st.PB({ri, -1});
      st.PB({le, 1});
    }
		//st.PB({th-phi, 1});
		//st.PB({th+phi, -1});
		//st.PB({th-phi+2*PI, 1});
		//st.PB({th+phi+2*PI, -1});
//		cout<<p<<" : "<<th-phi<<"~"<<th+phi<<" "<<th-phi+2*PI<<"~"<<th+phi+2*PI<<endl;
	}
	sort(st.begin(), st.end());

	int cnt = 1;
	for(auto p: st)
	{
		cnt += p.S;
//		cout<<p.F<<" : "<<cnt<<endl;
		if(cnt >= K)
			return true;
	}
	return false;
}

int ord[MX];

ld calc()
{
	vector<pii> vtmp;
	for(int i=0; i<N; i++)
		vtmp.PB(pt[i]);
	tree.init(vtmp);

	ld ans = 1E6;
	for(int i=0; i<N; i++)
		ord[i] = i;
	random_shuffle(ord, ord+N);
	for(int j=0; j<N; j++)
	{
		int i = ord[j];
		int z = 2;
		vector<int> vec = tree.query(pt[i].F-2*ans-z, pt[i].S-2*ans-z, pt[i].F+2*ans+z, pt[i].S+2*ans+z);
//		vec.clear();
//		for(int j=0; j<N; j++)
//			vec.PB(j);

    for(auto v: vec)
    {
      ptv[v] = {pt[v].F-pt[i].F, pt[v].S-pt[i].S};
      ptth[v] = atan2(ptv[v].S, ptv[v].F);
      ptd[v] = sqrt(ptv[v].F*ptv[v].F+ptv[v].S*ptv[v].S);
    }

    int lb = 0, rb = (ans+1)*100;
		//for(int t=0; t<40; t++)
    while(rb > lb)
		{
			int mb = (lb + rb) / 2;
			if(check(i, vec, (mb+0.500001)/100.))
				rb = mb;
			else
				lb = mb + 1;
		}
		ans = min(ans, rb/100.0);
	}
	return ans;
}

int main() {
//	tree.init({{0,0},{1,3},{2,4},{3,3}});
//	cout << tree.query(0,0,0,0) << endl;
//	cout << tree.query(0,1,0,3) << endl;
//	cout << tree.query(2,2,4,4) << endl;

	cin >> N >> K;
	for(int i=0; i<N; i++)
		cin>>pt[i].F>>pt[i].S;

	ld ans = calc() - 0.000 + 0E-6;
	cout<<fixed<<setprecision(2)<<(double)ans<<endl;

	return 0;
}

