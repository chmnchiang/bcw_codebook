//bcw0x1bd2 {{{
#include<bits/stdc++.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define MC(n,m) memcpy((n),(m),sizeof(n))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define FOR(x,y) for(__typeof(y.begin())x=y.begin();x!=y.end();x++)
#define IOS ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
  freopen(name".in", "r", stdin); \
  freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif

void RI() {}

template<typename... T>
void RI( int& head, T&... tail ) {
	    scanf("%d",&head);
			    RI(tail...);
}

mt19937 rng(0x5EED);
int randint(int lb, int ub) {
    return uniform_int_distribution<int>(lb, ub)(rng);
}
// Let's Fight! }}}

typedef pair<int, int> pii;

const int MAXN = 111;

int P, Q;
int nodecnt = 0;
vector< vector<int> > edges;

int newnode()
{
	edges.PB(vector<int>());
	return ++nodecnt;
}

void addedge(int u, int v)
{
	edges[u-1].PB(v);
}

void make(int D, int start, int good, int bad)
{
	while(D%2==0)
	{
		int np = newnode();
		addedge(start, np);
		addedge(start, bad);
		start = np;
		D >>= 1;
	}
	if(D == 1)
	{
		addedge(start, good);
		addedge(start, good);
		return;
	}

	int C = __lg(D) + 1;
	D = (1<<C) - D;

	vector<int> nds;
	nds.PB(start);
	for(int i=1; i<C; i++)
		nds.PB(newnode());
	for(int i=0; i<C-1; i++)
		addedge(nds[i], nds[i+1]);
	addedge(nds[C-1], good);

	for(int i=0; i<C; i++)
	{
		if(D&(1<<i))
			addedge(nds[C-i-1], nds[0]);
		else
			addedge(nds[C-i-1], bad);
	}
}

int alpha(int x)
{
	if(x == -1) return nodecnt + 1;
	if(x == -2) return nodecnt + 2;
	return x;
}

int main(){
	IOS;
	FILEIO("drunkard");

	while(cin>>P>>Q && P && Q)
	{
		nodecnt = 0;
		edges.clear();
		int start = newnode();
		int good = -1, bad = -2;
		for(int i=0; i<P; i++)
		{
			int newbad = newnode();
			make(Q-i, start, good, newbad);
			start = newbad;
		}
		addedge(start, bad);
		addedge(start, bad);

		cout<<nodecnt+2<<endl;
		for(int i=0; i<(int)edges.size(); i++)
		{
			cout<<alpha(edges[i][0])<<" "<<alpha(edges[i][1])<<endl;
		}
	}

	return 0;
}

