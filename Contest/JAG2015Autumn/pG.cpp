#include<bits/stdc++.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define F first
#define S second
#define PB push_back
#define ALL(x) begin(x),end(x)
#define SZ(x) ((int)(x).size())
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
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

const int MAXN = 20202;

struct Point
{
	int x;
	int y;
	int z;

	bool operator<(const Point &p) const
	{
		return tie(x, y, z) < tie(p.x, p.y, p.z);
	}
};

struct Edge
{
	Point p[2];

	bool operator<(const Edge &e) const
	{
		return tie(p[0], p[1]) < tie(e.p[0], e.p[1]);
	}
};

struct Face
{
	Point p[2];

	bool operator<(const Face &f) const
	{
		return tie(p[0], p[1]) < tie(f.p[0], f.p[1]);
	}
};

int A, B, C, N, PP;

set<Point> pts;
set<Edge> edges;
set<Face> faces;
map<Point, int> mp;
vector<int> el[1010101];
bool vis[1010101];

void init()
{
	pts.clear();
	edges.clear();
	faces.clear();
	mp.clear();
}

void make_point(Point p)
{
	int x = p.x, y = p.y, z = p.z;

	vector<Point> vec;
	vec.PB({x, y, z});
	vec.PB({x, y, z+1});
	vec.PB({x, y+1, z});
	vec.PB({x, y+1, z+1});
	vec.PB({x+1, y, z});
	vec.PB({x+1, y, z+1});
	vec.PB({x+1, y+1, z});
	vec.PB({x+1, y+1, z+1});

	for(auto v: vec)
		pts.insert(v);

	edges.insert({vec[0], vec[1]});
	edges.insert({vec[2], vec[3]});
	edges.insert({vec[4], vec[5]});
	edges.insert({vec[6], vec[7]});
	edges.insert({vec[0], vec[2]});
	edges.insert({vec[1], vec[3]});
	edges.insert({vec[4], vec[6]});
	edges.insert({vec[5], vec[7]});
	edges.insert({vec[0], vec[4]});
	edges.insert({vec[1], vec[5]});
	edges.insert({vec[2], vec[6]});
	edges.insert({vec[3], vec[7]});

	faces.insert({vec[0], vec[3]});
	faces.insert({vec[4], vec[7]});
	faces.insert({vec[0], vec[5]});
	faces.insert({vec[2], vec[7]});
	faces.insert({vec[0], vec[6]});
	faces.insert({vec[1], vec[7]});
}

bool inrange(int xl, int xr, int yl, int yr, int zl, int zr, Point p)
{
	return xl <= p.x && p.x <= xr && yl <= p.y && p.y <= yr && zl <= p.z && p.z <= zr;
}

int calcE(int xl, int xr, int yl, int yr, int zl, int zr, int &cure)
{
	for(auto e: edges)
	{
		if(!inrange(xl, xr, yl, yr, zl, zr, e.p[0])) continue;
		if(!inrange(xl, xr, yl, yr, zl, zr, e.p[1])) continue;
		cure++;
	}

	int vs = 0;
	vector<Point> vec;
	for(auto p: pts)
	{
		if(!inrange(xl, xr, yl, yr, zl, zr, p)) continue;
		vec.PB(p);
		vs++;
	}

	for(auto v: vec)
	{
		int a = mp[vec[0]];
		int b = mp[v];
		if(a == b) continue;
		el[a].PB(b);
		el[b].PB(a);
	}

	return vs - 1;
}

int calcF(int xl, int xr, int yl, int yr, int zl, int zr, int &curf)
{
	int vs = 0;
	vector<Point> vec;
	for(auto p: pts)
	{
		if(!inrange(xl, xr, yl, yr, zl, zr, p)) continue;
		vec.PB(p);
		vs++;
	}

	int es = 0;
	for(auto e: edges)
	{
		if(!inrange(xl, xr, yl, yr, zl, zr, e.p[0])) continue;
		if(!inrange(xl, xr, yl, yr, zl, zr, e.p[1])) continue;
		es++;
	}

	for(auto f: faces)
	{
		if(!inrange(xl, xr, yl, yr, zl, zr, f.p[0])) continue;
		if(!inrange(xl, xr, yl, yr, zl, zr, f.p[1])) continue;
		curf++;
	}

	for(auto v: vec)
	{
		int a = mp[vec[0]];
		int b = mp[v];
		if(a == b) continue;
		el[a].PB(b);
		el[b].PB(a);
	}

	return es - vs + 1;
}

void dfs(int v)
{
	if(vis[v]) return;
	vis[v] = true;
	for(auto e: el[v])
		dfs(e);
}

int calc()
{
	int V = pts.size();
	int E = 0;
	int cure = 0;

	vector<int> nume;

	nume.PB(calcE(0, 0, 0, 0, 0, C, cure));
	nume.PB(calcE(0, 0, B, B, 0, C, cure));
	nume.PB(calcE(A, A, 0, 0, 0, C, cure));
	nume.PB(calcE(A, A, B, B, 0, C, cure));

	nume.PB(calcE(0, 0, 0, B, 0, 0, cure));
	nume.PB(calcE(0, 0, 0, B, C, C, cure));
	nume.PB(calcE(A, A, 0, B, 0, 0, cure));
	nume.PB(calcE(A, A, 0, B, C, C, cure));

	nume.PB(calcE(0, A, 0, 0, 0, 0, cure));
	nume.PB(calcE(0, A, 0, 0, C, C, cure));
	nume.PB(calcE(0, A, B, B, 0, 0, cure));
	nume.PB(calcE(0, A, B, B, C, C, cure));

	E += edges.size() - cure;
	for(auto x: nume)
		E += x;

	int F = 0;
	int curf = 0;

	vector<int> numf;

	numf.PB(calcF(0, 0, 0, B, 0, C, curf));
	numf.PB(calcF(A, A, 0, B, 0, C, curf));
	numf.PB(calcF(0, A, 0, 0, 0, C, curf));
	numf.PB(calcF(0, A, B, B, 0, C, curf));
	numf.PB(calcF(0, A, 0, B, 0, 0, curf));
	numf.PB(calcF(0, A, 0, B, C, C, curf));

	F += faces.size() - curf;
	for(auto x: numf)
		F += x;

	//cout<<"CURF "<<curf<<endl;

	for(auto e: nume)
		F += 2 * e;
	F -= 2 * cure;

	int conn = 0;

	for(int i=0; i<PP; i++)
	{
		if(vis[i]) continue;
		dfs(i);
		conn++;
	}

	cout<<"V "<<V<<" E "<<E<<" F "<<F<<" Conn "<<conn<<endl;

	return V - E + F - conn - N;
}

int main() {
    IOS;

	while(cin>>A>>B>>C>>N)
	{
		init();
		pts.insert({0, 0, 0});
		pts.insert({0, 0, C});
		pts.insert({0, B, 0});
		pts.insert({0, B, C});
		pts.insert({A, 0, 0});
		pts.insert({A, 0, C});
		pts.insert({A, B, 0});
		pts.insert({A, B, C});
		for(int i=0; i<N; i++)
		{
			Point p;
			cin>>p.x>>p.y>>p.z;
			make_point(p);
		}

		int cnt = 0;
		for(auto p: pts)
		{
			mp[p] = cnt++;
		}
		PP = cnt;
		for(int i=0; i<PP; i++)
		{
			el[i].clear();
			vis[i] = false;
		}
		for(auto e: edges)
		{
			int a = mp[e.p[0]];
			int b = mp[e.p[1]];
			el[a].PB(b);
			el[b].PB(a);
		}

		int ans = calc();
		cout<<ans<<endl;
	}

    return 0;
}

