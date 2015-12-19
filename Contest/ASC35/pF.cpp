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

typedef long long ll;
typedef pair<int, int> pii;

const int MAXN = 202;

int N, M;

int g[MAXN][MAXN];
vector<pii> gr[MAXN];

void add_edge(int u, int v, int c) {
	gr[c].PB({u+1, v+1});
}

int main() {
	FILEIO("factor");
	IOS;

	cin>>N;
	N = N * 2;

	for (int i=1; i<N; i++) {
		bool us[MAXN] = {};
		us[i] = us[0] = true;
		add_edge(i, 0, i);
		vector<int> vl;
		for (int j=1; j<=N; j++) {
			int jj = (j+i) % N;
			if (not us[jj])
				vl.PB(jj);
		}

		for (int j=0; j<N/2-1; j++) {
			int u = vl[j], v = vl[(N-2)-j-1]; 
			add_edge(u, v, i);
		}
	}

	/*
	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
			if (i == j) continue;
			assert(g[i][j] == 1);
		}
	}
	*/

	cin>>M;
	int cur = 0;
	for(int i=0; i<M; i++)
	{
		int x;
		cin>>x;
		for(int j=0; j<x; j++)
		{
			cur++;
			for(auto p: gr[cur])
				cout<<p.F<<" "<<p.S<<"\n";
		}
		if(i<M-1)cout<<"\n";
	}

    return 0;
}
