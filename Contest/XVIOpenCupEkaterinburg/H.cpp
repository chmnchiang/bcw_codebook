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

typedef long long ll;

const int MAXN = 16;
const int MAXR = 1010;

struct Perm
{
	int v[MAXN];
};

int N, R;

istream& operator >>(istream &s, Perm &p) {
	for(int i=0; i<N; i++)
	{
		s>>p.v[i];
		p.v[i]--;
	}
	return s;
}

ostream& operator <<(ostream &s, const Perm &p) {
	s<<"[ ";
	for(int i=0; i<N; i++) s<<p.v[i]<<" ";
	s<<"]";
	return s;
}

Perm operator*(const Perm &a, const Perm &b)
{
	Perm p;
	for(int i=0; i<N; i++)
		p.v[i] = a.v[b.v[i]];
	return p;
}

bool operator<(const Perm &a, const Perm &b)
{
	for(int i=0; i<N; i++)
		if(a.v[i] != b.v[i]) return a.v[i] < b.v[i];
	return false;
}

bool operator==(const Perm &a, const Perm &b)
{
	for(int i=0; i<N; i++)
		if(a.v[i] != b.v[i]) return false;
	return true;
}

Perm inv(Perm &a)
{
	Perm p;
	for(int i=0; i<N; i++)
		p.v[a.v[i]] = i;
	return p;
}

Perm Id;
vector<Perm> vgen;
bool gs_found[MAXN];
Perm gs[MAXN];
bool sim_found[MAXN][MAXN];
Perm sim[MAXN][MAXN];

void dfs(int v, Perm p)
{
	if(gs_found[v]) return;
	gs_found[v] = true;
	gs[v] = p;

	for(auto g: vgen)
		dfs(g.v[v], g * p);
}

void shrink()
{
	for(int i=0; i<N; i++)
		for(int j=0; j<N; j++)
			sim_found[i][j] = false;

	for(int i=0; i<N; i++)
	{
		vector<Perm> newgen;
		for(auto g: vgen)
		{
			if(g == Id) continue;
			int s = g.v[i];
			if(!sim_found[i][s])
			{
				sim_found[i][s] = true;
				sim[i][s] = g;
			}
			else
			{
				newgen.PB(inv(g) * sim[i][s]);
			}
		}
		vgen = newgen;
	}
	
	vgen.clear();
	for(int i=0; i<N; i++)
		for(int j=0; j<N; j++)
			if(sim_found[i][j])
				vgen.PB(sim[i][j]);
}

ll calc()
{
	for(int i=0; i<N; i++)
		Id.v[i] = i;

	ll ret = 1;

	for(int i=0; i<N; i++)
	{
		for(int j=0; j<N; j++)
			gs_found[j] = false;
		dfs(i, Id);

		int Usize = 0;
		for(int j=0; j<N; j++)
			Usize += gs_found[j];
		ret *= Usize;

		vector<Perm> oldgen;
		swap(oldgen, vgen);
		for(int j=0; j<N; j++)
		{
			if(!gs_found[j]) continue;
			Perm r = gs[j];
			for(auto s: oldgen)
			{
				Perm sr = s * r;
				Perm sr_gua = gs[sr.v[i]];
				Perm srguainvsr = inv(sr_gua) * sr;
				vgen.PB(srguainvsr);
			}
		}

		shrink();
	}

	return ret;
}

int main() {
	IOS;

	while(cin>>R>>N)
	{
		Perm p;
		vgen.clear();
		for(int i=0; i<R; i++)
		{
			cin>>p;
			vgen.PB(p);
		}

		ll ans = calc();
		cout<<ans<<endl;
	}

	return 0;
}

