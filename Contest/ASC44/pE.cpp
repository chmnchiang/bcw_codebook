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

const int MX = 205;

int N,eg[MX][MX];
int vst[MX], match[MX], is1[MX];

bool DFS(int u){
	for (int v=1; v<=2*N; v++){
		if (is1[v]) continue;
		if (!eg[u][v]) continue;
		if (!vst[v]){
			vst[v] = 1;
			if (match[v] == -1 || DFS(match[v])){
				match[v] = u;
				match[u] = v;
				return true;
			}
		}
	}
	return false;
}
void do_match(vector<int> v1){
	FZ(is1);
	FMO(match);
	for (auto it : v1){
		is1[it] = 1;
	}
	for (int i=1; i<N; i++){
		int u = v1[i];
		if (match[u] == -1){
			FZ(vst);
			DFS(u);
		}
	}
}
void choose(vector<int> v1, vector<int> v2){
	assert((int)v1.size() == N+1);
	assert((int)v2.size() == N-1);
	for (auto it : v1)
		printf("%d ", it);
	for (int i=0; i<N-1; i++)
		printf("%d%c", v2[i], i==N-2 ? '\n' : ' ');
	for (int i=1; i<N+1; i++){
		int u = v1[i];
		int v = v1[i-1];
		assert(eg[u][v] == 1);
		eg[u][v] = eg[v][u] = 0;
		if (i != N){
			v = v2[i-1];
			assert(eg[u][v] == 1);
			eg[u][v] = eg[v][u] = 0;
		}
	}
}
int main(){
	FILEIO("embedding");
	while (~scanf("%d", &N) && N){
		if (N == 3){
			puts("1 2 3 4 5 6");
			puts("1 4 5 3 2 6");
			puts("2 6 1 3 4 5");
			continue;
		}
		for (int i=1; i<=2*N; i++){
			for (int j=1; j<=2*N; j++)
				eg[i][j] = 1;
			eg[i][i] = 0;
		}
		vector<int> v1, v2;
		for (int i=1; i<=N+1; i++)
			v1.PB(i);
		for (int i=N+2; i<=2*N; i++)
			v2.PB(i);
		choose(v1,v2);
		v1.clear();
		v2.clear();
		v1.PB(1);
		for (int i =N+2; i<=2*N; i++)
			v1.PB(i);
		v1.PB(N+1);
		for (int i=3; i<=N; i++)
			v2.PB(i);
		v2.PB(2);
		choose(v1,v2);
		v1.clear();
		v2.clear();
		for (int i=1; i<=N+1; i+=2)
			v1.PB(i);
		for (int i=2; i<=N+1; i+=2)
			v1.PB(i);
		do_match(v1);
		for (int i=1; i<N; i++){
			v2.PB(match[v1[i]]);
			assert(match[v1[i]] != -1);
		}
		choose(v1,v2);
	}

	return 0;
}

