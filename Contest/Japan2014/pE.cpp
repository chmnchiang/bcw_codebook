#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define MC(n,m) memcpy((n),(m),sizeof(n))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define ALL(x) begin(x),end(x)
#define SZ(x) ((int)(x).size())
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
// Let's Fight!

#define y0 hai_kou_yi_zi_hao

const int MAXN = 52;
const int dx[] = {1, 0,-1, 0};
const int dy[] = {0, 1, 0,-1};

int N, T;
int x0, y0;

map<char, int> mdir;
bool cango[MAXN][MAXN][4];
bool poss[MAXN][MAXN][4][4], ptmp[MAXN][MAXN][4][4];

void evo()
{
	FZ(ptmp);
	for(int x=0; x<MAXN; x++)
	{
		for(int y=0; y<MAXN; y++)
		{
			for(int d2=0; d2<4; d2++)
			{
				if(!cango[x][y][d2]) continue;
				int nx = x + dx[d2], ny = y + dy[d2];
				for(int d1=0; d1<4; d1++)
				{
					if(!poss[x][y][d1][d2]) continue;
					for(int d3=0; d3<4; d3++)
					{
						if(!cango[nx][ny][d3]) continue;
						if((d3-d2+4)%4 == 2) continue;
						ptmp[nx][ny][d2][d3] = true;
					}
				}
			}
		}
	}
	swap(poss, ptmp);
}

void filter(int dir)
{
	for(int x=0; x<MAXN; x++)
		for(int y=0; y<MAXN; y++)
			for(int d1=0; d1<4; d1++)
				for(int d2=0; d2<4; d2++)
					if(d1 != dir && d2 != dir)
						poss[x][y][d1][d2] = false;
}

void init()
{
	mdir['E'] = 0;
	mdir['N'] = 1;
	mdir['W'] = 2;
	mdir['S'] = 3;
}

int main() {
	init();
	IOS;
	cin>>N>>x0>>y0>>T;
	for(int i=0; i<N; i++)
	{
		int xs, ys, xe, ye;
		cin>>xs>>ys>>xe>>ye;

		if(xs > xe) swap(xs, xe);
		if(ys > ye) swap(ys, ye);
		if(xs == xe)
		{
			for(int j=ys; j<ye; j++)
				cango[xs][j][1] = true;
			for(int j=ye; j>ys; j--)
				cango[xs][j][3] = true;
		}
		else
		{
			for(int j=xs; j<xe; j++)
				cango[j][ys][0] = true;
			for(int j=xe; j>xs; j--)
				cango[j][ys][2] = true;
		}
	}

	for(int i=0; i<4; i++)
		if(cango[x0][y0][i])
			poss[x0][y0][0][i] = true;

	for(int i=0; i<T; i++)
	{
		int d;
		char c;
		cin>>d>>c;
		for(int j=0; j<d; j++)
			evo();
		filter(mdir[c]);
	}

	for(int x=0; x<MAXN; x++)
	{
		for(int y=0; y<MAXN; y++)
		{
			bool any = false;
			for(int d1=0; d1<4; d1++)
				for(int d2=0; d2<4; d2++)
					if(poss[x][y][d1][d2])
						any = true;
			if(any)
				cout<<x<<" "<<y<<"\n";
		}
	}

    return 0;
}

