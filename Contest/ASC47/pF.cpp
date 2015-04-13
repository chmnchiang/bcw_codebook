#include<bits/stdc++.h>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<vector>
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
  freopen(name".in", "r", stdin); \
  freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define MC(n,m) memcpy((n),(m),sizeof(n))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define FOR(x,y) for(__typeof(y.begin())x=y.begin();x!=y.end();x++)
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
// Let's Fight!

typedef pair<int,int> PII;
const int MX = 1024;

int N, cnt[5];
int color[MX];
vector<int> E[MX];

void DFS(int u, int fa){
	for (auto v : E[u]){
		if (v == fa) continue;
		if (color[v] > 0){
			cnt[color[v]]++;
		} else {
			DFS(v, u);
		}
	}
}
int choose(int p){
	FZ(cnt);
	int cnt2[5] = {0};
	for (auto v : E[p]){
		if (color[v]){
			cnt2[color[v]]++;
		} else {
			DFS(v,p);
		}
	}
	int ret = 0;
	for (int i=1; i<=4; i++){
		if (cnt2[i]) continue;
		if (ret == 0) ret = i;
		else if (cnt[i] > 1){
			ret = i;
		}
	}
	return ret;
}
int main()
{
	scanf("%d", &N);
	for (int i=1, u, v; i<=N-1; i++){
		scanf("%d%d", &u, &v);
		E[u].PB(v);
		E[v].PB(u);
	}
	color[1] = 1;
	printf("1 1\n");
	fflush(stdout);
	while (true){
		int u, c;
		scanf("%d%d", &u, &c);
		if (u == -1 && c == -1) break;
		color[u] = c;
		int p = -1;
		for (auto v : E[u]){
			if (color[v]) continue;
			vector<PII> vec;
			FZ(cnt);
			int q = 0;
			DFS(v, u);
			for (int i=1; i<=4; i++){
				if (cnt[i] >= 1){
					q++;
				}
			}
			if (q >= 1 && p == -1){
				p = v;
			} else if (q >= 2){
				p = v;
			}
		}
		if (p == -1){
			for (int i=1; i<=N; i++){
				if (color[i]){
					for (auto v : E[i]){
						if (!color[v]){
							p = v;
							break;
						}
					}
					if (p != -1) break;
				}
			}
		}
		color[p] = choose(p);
		printf("%d %d\n", p, color[p]);
		fflush(stdout);
	}

	return 0;
}