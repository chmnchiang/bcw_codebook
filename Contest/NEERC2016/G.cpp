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
#ifdef BCW
#define FILEIO(name)
#else
#define FILEIO(name) \
    freopen(name".in", "r", stdin); \
    freopen(name".out", "w", stdout);
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


const int MAXN = 200005;
const int A = 0;
const int B = 1;
const int LOSE = 0;
const int WIN = 1;

int N,M;
int ws360[2][MAXN],hao123[2][MAXN],deg[2][MAXN];
vector<int> E[MAXN], rE[MAXN];

void make_ws360() {
	REP1(i,1,N) {
		deg[A][i] = deg[B][i] = SZ(E[i]);
	}
	FZ(ws360);
	queue<int> que;
	REP1(i,1,N) {
		if (deg[A][i] == 0) {
			ws360[A][i] = 1;
			que.push(A);
			que.push(i);

			ws360[B][i] = 1;
			que.push(B);
			que.push(i);
		}
	}
	
	while (!que.empty()) {
		int x = que.front(); que.pop();
		int u = que.front(); que.pop();
		if (x == A) {
			for (auto v:rE[u]) {
				if (ws360[B][v]) continue;
				ws360[B][v] = 1;
				que.push(B);
				que.push(v);
			}
		} else {
			for (auto v:rE[u]) {
				if (ws360[A][v]) continue;
				deg[A][v]--;
				if (deg[A][v] == 0) {
					ws360[A][v] = 1;
					que.push(A);
					que.push(v);
				}
			}
		}
	}
}
void make_hao123() {
	REP1(i,1,N) {
		deg[A][i] = deg[B][i] = 0;
	}
	REP1(i,1,N) {
		for (auto v:E[i]) {
			if (ws360[B][v]) deg[A][i]++;
			if (ws360[A][v]) deg[B][i]++;
		}
	}
	FMO(hao123);
	queue<int> que;
	REP1(i,1,N) {
		if (deg[A][i] == 0 and ws360[A][i]) {
			hao123[A][i] = LOSE;
			que.push(A);
			que.push(i);
		}

		if (deg[B][i] == 0 and ws360[B][i]) {
			hao123[B][i] = LOSE;
			que.push(B);
			que.push(i);
		}
	}

	/*
	REP1(i,1,N) {
		cout<<ws360[A][i]<<" "<<ws360[B][i]<<endl;
	}
	*/

	while (!que.empty()) {
		int x = que.front(); que.pop();
		int u = que.front(); que.pop();
		int y = x^1;

	//	cout<<x<<" "<<u<<endl;

		if (hao123[x][u] == LOSE) {
			for (auto v:rE[u]) {
				if (!ws360[y][v]) continue;
				if (hao123[y][v] != -1) continue;
				hao123[y][v] = WIN;
				que.push(y);
				que.push(v);
			}
		} else {
			for (auto v:rE[u]) {
				if (!ws360[y][v]) continue;
				if (hao123[y][v] != -1) continue;
				deg[y][v]--;
				if (deg[y][v] == 0) {
					hao123[y][v] = LOSE;
					que.push(y);
					que.push(v);
				}
			}
		}

	}
}
int main() {
	FILEIO("game");
	IOS;
	cin>>N>>M;
	REP(_,M) {
		int u,v;
		cin>>u>>v;
		E[u].PB(v);
		rE[v].PB(u);
	}

	make_ws360();
	make_hao123();

	REP1(i,1,N) {
		if (!ws360[A][i]) cout<<"D";
		else {
			if (hao123[A][i] == WIN) cout<<"W";
			else if (hao123[A][i] == LOSE) cout<<"L";
			else cout<<"W";
		}
	}
	cout<<endl;
	REP1(i,1,N) {
		if (!ws360[B][i]) cout<<"D";
		else {
			if (hao123[B][i] == WIN) cout<<"W";
			else if (hao123[B][i] == LOSE) cout<<"L";
			else cout<<"L";
		}
	}
	cout<<endl;

	return 0;
}

