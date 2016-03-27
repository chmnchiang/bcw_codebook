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

typedef pair<int, int> pii;

const int MAXN = 55;

vector<pii> edge;

int N, M;
int D, K, L;

void calc()
{
	if(K > L or L > D) return;
	N = 37;
	for(int i=0; i<12; i++)
	{
		for(int j=i+1; j<12; j++)
		{
			edge.PB({i, j});
			edge.PB({i+12, j+12});
			edge.PB({i+24, j+24});
		}
	}

	for(int i=0; i<D; i++)
		edge.PB({36, i});

	for(int i=0; i<L; i++)
		edge.PB({i, i+12});

	for(int i=0; i<K; i++)
	{
		for(int j=0; j<12; j++)
		{
			edge.PB({N, j+12});
			edge.PB({N, j+24});
		}
		N++;
	}
	M = edge.size();
}

int main() {
	IOS;
	FILEIO("dkl");

	cin>>D>>K>>L;

	calc();

	cout<<N<<" "<<M<<endl;
	for(int i=0; i<M; i++)
		cout<<edge[i].F+1<<" "<<edge[i].S+1<<endl;

	return 0;
}

