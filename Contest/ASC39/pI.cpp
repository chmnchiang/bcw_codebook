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

typedef pair<int, int> pii;

const int MAXN = 262144;

int N, SS, M, L, Q;
vector<int> dvec;
int c[MAXN], a[MAXN], b[MAXN];
map<int, int> mseg[MAXN*2];
vector<pii> vp[MAXN];

void disc()
{
	L = 0;
	dvec.PB(1);
	dvec.PB(N);
	for(int i=0; i<M; i++)
	{
		dvec.PB(a[i]);
		dvec.PB(b[i]);
	}
	sort(ALL(dvec));
	L = unique(ALL(dvec)) - dvec.begin();
	dvec.resize(L);

	for(int i=0; i<M; i++)
	{
		a[i] = lower_bound(ALL(dvec), a[i]) - dvec.begin();
		b[i] = lower_bound(ALL(dvec), b[i]) - dvec.begin();
	}
}

void make_seg()
{
	for(int i=0; i<M; i++)
	{
		vp[c[i]].PB({a[i], b[i]});
	}

	for(int i=0; i<SS; i++)
	{
		int rb = 0;
		vp[i].PB({L-1, L-1});
		sort(ALL(vp[i]));
		vector<pii> tmp = vp[i];
		vp[i].clear();
		for(auto p: tmp)
		{
			if(p.F > rb)
				vp[i].PB({rb, p.F});
			rb = p.S;
		}
	}
}

void addSeg(int s, int lb, int rb)
{
	if(rb - lb == 1)
	{
		for(auto p: vp[lb])
			mseg[s].insert(p);
	}
	else
	{
		int mb = (lb + rb) / 2;
		addSeg(2*s, lb, mb);
		addSeg(2*s+1, mb, rb);

		vector<pii> vec;
		for(auto p: mseg[2*s])
			vec.PB(p);
		for(auto p: mseg[2*s+1])
			vec.PB(p);
		sort(ALL(vec), [](pii aa, pii bb){if(aa.F == bb.F) return aa.S > bb.S; return aa.F < bb.F;});

		int r = 0;
		for(auto p: vec)
		{
			if(p.S <= r) continue;
			mseg[s].insert(p);
			r = p.S;
		}
	}
}

bool qrySeg(int s, int lb, int rb)
{
	auto it = mseg[s].upper_bound(lb);
	if(it == mseg[s].begin()) return false;
	it--;
	return it->S >= rb;
}

int calc(int x, int y)
{
	int l = (--upper_bound(ALL(dvec), x)) - dvec.begin();
	int r = lower_bound(ALL(dvec), y) - dvec.begin();

	int s = 1, lb = 0, rb = SS;
	if(!qrySeg(s, l, r)) return 0;

	while(rb - lb > 1)
	{
		int mb = (lb + rb) / 2;
		if(qrySeg(2*s, l, r))
		{
			s = 2*s;
			rb = mb;
		}
		else
		{
			s = 2*s+1;
			lb = mb;
		}
	}

	return lb+1;
}

int main() {
    FILEIO("intercity");
	IOS;
	cin>>N>>SS>>M;
	for(int i=0; i<M; i++)
	{
		cin>>c[i]>>a[i]>>b[i];
		c[i]--;
	}

	disc();
	make_seg();
	addSeg(1, 0, SS);

	int p = 0;
	cin>>Q;
	for(int i=0; i<Q; i++)
	{
		int x, y;
		cin>>x>>y;
		x += p;
		y += p;

		int ans = calc(x, y);
		cout<<ans<<"\n";
		p = ans;
	}

    return 0;
}

