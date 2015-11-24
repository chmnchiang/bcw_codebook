#include <bits/stdc++.h>
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define MC(n,m) memcpy((n),(m),sizeof(n))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define FOR(x,y) for(__typeof(y.begin())x=y.begin();x!=y.end();x++)
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
	freopen(name".in", "r", stdin); \
	freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif

using namespace std;

typedef pair<int,int> pii;

struct Graph {
	static const int MXN = 55;
	int n, edge[MXN][MXN];
	vector<pii> vec;
	void init(int _n, int _t) {
		n = _n;
		for (int i=0; i<n; i++) {
			for (int j=0; j<n; j++) {
				edge[i][j] = 1;
			}
			edge[i][i] = 0;
		}
		if (n % 2 == 0) {
			for (int i=0; i<n; i+=2) {
				edge[i][i+1] = edge[i+1][i] = 2;
			}
		}

		if(_t % 2 == 0)
		{
			for(int i=0; i<_t; i++)
				edge[0][1]++, edge[1][0]++;
		}
		else if(_t >= 3)
		{
			while(_t > 3)
			{
				edge[0][1]+=2, edge[1][0]+=2;
				_t -= 2;
			}
			edge[0][1]++, edge[1][0]++;
			edge[0][2]++, edge[2][0]++;
			edge[2][1]++, edge[1][2]++;
		}
		else
		{
			edge[0][1]--, edge[1][0]--;
			edge[0][2]++, edge[2][0]++;
			edge[2][1]++, edge[1][2]++;
		}
	}
	void DFS(int u) {
		for (int v=0; v<n; v++) {
			if (edge[u][v]) {
				edge[u][v]--;
				edge[v][u]--;
				DFS(v);
				vec.PB(MP(v, u));
			}
		}
	}
	vector<int> get_answer() {
		DFS(0);
		vector<int> ret;
		ret.PB(vec[0].F);
		for (auto it : vec) {
			ret.PB(it.S);
		}
		return ret;
	}
}graph;

int main() {
	FILEIO("achromatic");
	
	int N;
	cin>>N;
	int n = 1;
	int num;
	while(1)
	{
		n++;
		num = (n%2 ? n*(n-1)/2 : n*n/2);
		if(num <= N);
		else
		{
			n--;
			break;
		}
	}

	num = (n%2 ? n*(n-1)/2 : n*n/2);
	int trash_edge = N - num;
	if(n % 2 == 1 && trash_edge == 1)
	{
		n--;
		num = (n%2 ? n*(n-1)/2 : n*n/2);
		trash_edge = N - num;
	}

	graph.init(n, trash_edge);
	auto vec = graph.get_answer();
	vec.pop_back();

	cout<<n<<endl;
	for(auto a: vec)
		cout<<a+1<<" ";
	cout<<endl;

	return 0;
}

