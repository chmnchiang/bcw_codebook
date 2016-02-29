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

const int MAXN = 1010;

int N, M;
int es[MAXN*MAXN], et[MAXN*MAXN], ec[MAXN*MAXN];
int cnt = 0;

void add_edge(int a, int b, int c)
{
	es[cnt] = a;
	et[cnt] = b;
	ec[cnt] = c;
	cnt++;
}

void calc()
{
	for(int i=0; i<N-1; i++)
	{
		add_edge(i, i+1, 0);
		for(int j=i+2; j<N; j++)
			add_edge(i, j, 10000-i+j);
	}
}

int main() {
	IOS;
	FILEIO("test");

	cin>>N>>M;
	calc();

	for(int i=0; i<M; i++)
		cout<<es[i]+1<<" "<<et[i]+1<<" "<<ec[i]<<"\n";

    return 0;
}

