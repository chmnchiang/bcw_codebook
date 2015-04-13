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

const int MX = 2048;
const int MXN = 4*MX;
const int dir[4][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}};
const int INF = 1029384756;

int H,W;
int nID, idx[MX][MX];
pair<int,int> coord[MXN];
int rightMost[MX][MX], upMost[MX][MX], downMost[MX][MX];
int dp[MXN][MXN];
char mp[MX][MX];

void pre_solve(){
	for (int j=0; j<W; j++)
		upMost[0][j] = idx[0][j];
	for (int i=1; i<H; i++){
		for (int j=0; j<W; j++){
			upMost[i][j] = idx[i][j];
			if (upMost[i-1][j] != -1)
				upMost[i][j] = upMost[i-1][j];
		}
	}
	for (int j=0; j<W; j++)
		downMost[H-1][j] = idx[H-1][j];
	for (int i=H-2; i>=0; i--){
		for (int j=0; j<W; j++){
			downMost[i][j] = idx[i][j];
			if (downMost[i+1][j] != -1)
				downMost[i][j] = downMost[i+1][j];
		}
	}
	for (int i=0; i<H; i++)
		rightMost[i][W-1] = idx[i][W-1];
	for (int j=W-2; j>=0; j--){
		for (int i=0; i<H; i++){
			rightMost[i][j] = idx[i][j];
			if (rightMost[i][j+1] != -1)
				rightMost[i][j] = rightMost[i][j+1];
		}
	}
}
int go1(int s, int t){ // right , down
	if (s == t) return 0;
	if (dp[s][t] != -1) return dp[s][t];
	int x1 = coord[s].F;
	int y1 = coord[s].S;
	int x2 = coord[t].F;
	int y2 = coord[t].S;
	if (x1 == x2 || y1 == y2) return dp[s][t] = 1;
	if (x1 > x2) return INF;
	if (y1 > y2) return INF;
	//printf("(%d, %d) ---> (%d, %d)\n", x1, y1, x2 ,y2);
	int ret = INF;
	if (coord[rightMost[x1][y1]].S >= y2)
		ret = min(ret, 2);
	else if (rightMost[x1][y1] != s)
		ret = min(ret, 1 + go1(rightMost[x1][y1], t));
	if (coord[downMost[x1][y1]].F >= x2)
		ret = min(ret, 2);
	else if (downMost[x1][y1] != s)
		ret = min(ret, 1 + go1(downMost[x1][y1], t));
	return dp[s][t] = ret;
}
int go2(int s, int t){ // right , up
	if (s == t) return 0;
	if (dp[s][t] != -1) return dp[s][t];
	int x1 = coord[s].F;
	int y1 = coord[s].S;
	int x2 = coord[t].F;
	int y2 = coord[t].S;
	if (x1 == x2 || y1 == y2) return dp[s][t] = 1;
	if (x1 < x2) return INF;
	if (y1 > y2) return INF;
	int ret = INF;
	if (coord[rightMost[x1][y1]].S >= y2)
		ret = min(ret, 2);
	else if (rightMost[x1][y1] != s)
		ret = min(ret, 1 + go2(rightMost[x1][y1], t));
	if (coord[upMost[x1][y1]].F <= x2)
		ret = min(ret, 2);
	else if (upMost[x1][y1] != s)
		ret = min(ret, 1 + go2(upMost[x1][y1], t));
	return dp[s][t] = ret;
}
int main()
{
	FILEIO("jinxiety");
	while (~scanf("%d%d", &H, &W) && H && W){
		for (int i=0; i<H; i++){
			scanf("%s", mp[i]);
			for (int j=0; j<W; j++)
				idx[i][j] = 0;
		}
		nID = 0;
		for (int i=0; i<H; i++){
			for (int j=0; j<W; j++){
				if (mp[i][j] != '#'){
					idx[i][j] = -1;
					continue;
				}
				int c = 0;
				for (int k=0; k<4; k++){
					int x = i + dir[k][0];
					int y = j + dir[k][1];
					if (x<0 || x>=H || y<0 || y>=W){
						c++;
						break;
					}
					if (mp[x][y] == '.') c++;
				}
				if (c == 0) idx[i][j] = -1;
				else {
					coord[nID] = MP(i,j);
					idx[i][j] = nID++;
				}
			}
		}

		pre_solve();
		for (int i=0; i<nID; i++)
			for (int j=0; j<nID; j++)
				dp[i][j] = -1;
		int ret = 0;
		for (int i=0; i<nID; i++)
			for (int j=0, tmp; j<nID; j++){
				tmp = go1(i, j);
				if (tmp != INF) ret = max(ret, tmp);
			}
		for (int i=0; i<nID; i++)
			for (int j=0; j<nID; j++)
				dp[i][j] = -1;
		for (int i=0; i<nID; i++){
			for (int j=0, tmp; j<nID; j++){
				tmp = go2(i, j);
				if (tmp != INF) ret = max(ret, tmp);
			}
		}

		printf("%d\n", max(ret-1,0));
	}
	return 0;
}