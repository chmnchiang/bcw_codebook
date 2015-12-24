/* bcw0x1bd2 */
#include <bits/stdc++.h>
//
using namespace std;
//
#define REP(n,i) for(int (i)=0;(i)<(n);(i)++)
#define CDREP(n,i) for(int (i)=((n)-1);(i)>=0;(i)--)
#define CDFOR(s,e,i) for(int i=((e)-1);(i)>=(s);(i)--)
#define _SZ(n) memset((n),0,sizeof(n))
#define _SMO(n) memset((n),-1,sizeof(n))
#define _MC(n,m) memcpy((n),(m),sizeof(n))
#define _F first
#define _S second
#define _MP make_pair
#define _PB push_back
#define FOR(x,y) for(__typeof(y.begin())x=y.begin();x!=y.end();x++)
#define IOS ios_base::sync_with_stdio(0);
// Let's Fight!


class Isap{
public:
	class Edge{
	public:
		int v,f,re;
		Edge (){ v=f=re=-1; }
		Edge (int _v, int _f, int _r){
			v = _v;
			f = _f;
			re = _r;
		}
	};
	int n,s,t,h[1014],gap[1014];
	vector<Edge> E[1014];
	void init(int _n, int _s, int _t){
		n = _n;
		s = _s;
		t = _t;
		for (int i=0; i<1014; i++)
			E[i].clear();
	}
	void add_edge(int u, int v, int f){
//		printf("%d %d %d\n", u, v, f);
		E[u]._PB(Edge(v,f,E[v].size()));
		E[v]._PB(Edge(u,f,E[u].size()-1));
	}
	int DFS(int u, int nf, int res=0){
		if (u == t) return nf;
		FOR(it,E[u]){
			if (h[u]==h[it->v]+1 && it->f>0){
				int tf = DFS(it->v,min(nf,it->f));
				res += tf;
				nf -= tf;
				it->f -= tf;
				E[it->v][it->re].f += tf;
				if (nf == 0) return res;
			}
		}
		if (nf){
			if (--gap[h[u]] == 0) h[s]=n;
			gap[++h[u]]++;
		}
		return res;
	}
	int flow(int res=0){
		_SZ(h);
		_SZ(gap);
		gap[0] = n;
		while (h[s] < n)
			res += DFS(s,2147483647);
		return res;
	}
}flow;
const int MX = 1014;

int N,K,ans[MX];
int appX[MX], appXbar[MX];
int fail = 0;

void find_answer(){
	for (int i=1; i<=N; i++){
		ans[i] = !flow.E[i][0].f;
	}
}
int main(int argc, char** argv)
{
	freopen("sat.in", "r", stdin);
	freopen("sat.out", "w", stdout);
	_SMO(appX);
	_SMO(appXbar);
	scanf("%d%d", &N, &K);
	if (N < K){
		puts("NO");
		return 0;
	}
	int S = 0;
	int trash = N+K+1;
	int T = N+K+2;
	flow.init(T+1,S,T);
	for (int i=N+1; i<=N+K; i++){
		int m;
		scanf("%d", &m);
		for (int j=0; j<m; j++){
			int x;
			scanf("%d", &x);
			if (x < 0){
				x *= -1;
				if (appXbar[x] != -1)
					fail = 1;
				appXbar[x] = i;
			} else if (x > 0){
				if (appX[x] != -1)
					fail = 1;
				appX[x] = i;
			}
		}
		flow.add_edge(i,T,1);
	}
	for (int i=1; i<=N; i++){
		if (appX[i] != -1){
			flow.add_edge(i,appX[i],1);
		} else {
			flow.add_edge(i,trash,1);
		}
		if (appXbar[i] != -1){
			flow.add_edge(i,appXbar[i],1);
		} else {
			flow.add_edge(i,trash,1);
		}
	}
	for (int i=1; i<=N; i++){
		flow.add_edge(S,i,1);
	}
	flow.add_edge(trash,T,N-K);
	
	int res = flow.flow();
//	printf("flow = %d\n", res);
	if (res != N)
		fail = 1;
	if (fail){
		puts("NO");
	} else {
		puts("YES");
		find_answer();
		for (int i=1; i<=N; i++){
			printf("%d%c", ans[i], i==N ? '\n' : ' ');
		}
	}

	return 0;
}
/*
   S = 0
   X = 1 .. N
   K = N+1 .. N+K
   Trush = N+K+1
   T = N+K+2

   */
