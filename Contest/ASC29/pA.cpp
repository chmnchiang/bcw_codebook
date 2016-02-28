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
#define REP(i,x) for(int i=0;i<(x);i++)
#define REP1(i,a,b) for (int i=(a);i<=(b);i++)
// Let's Fight!

typedef pair<int, int> pii;

pii operator+(pii a, pii b){return {a.F+b.F, a.S+b.S};}
pii operator-(pii a, pii b){return {a.F-b.F, a.S-b.S};}
int dot(pii a, pii b){return a.F*b.F+a.S*b.S;}
int cross(pii a, pii b){return a.F*b.S-a.S*b.F;}

const int MAXN = 105;
const pii QQ = {-1, -1};
const pii OO = {0, 0};

int N;
pii ot[MAXN], pt[MAXN];
int ord[MAXN], iord[MAXN];
pii lft[MAXN], rgt[MAXN], mid[MAXN][MAXN];
int dp[MAXN][MAXN][MAXN];

bool cmp(int a, int b)
{
	return ot[a] < ot[b];
}

void calc()
{
	for(int i=0; i<N; i++)
		ord[i] = i;
	sort(ord, ord+N, cmp);
	for(int i=0; i<N; i++)
	{
		iord[ord[i]] = i;
		pt[i] = ot[ord[i]];
	}

	for(int i=0; i<N; i++)
	{
		lft[i] = OO;
		for(int j=0; j<i; j++)
		{
			if(pt[i].S == pt[j].S)
			{
				lft[i] = QQ;
				break;
			}
			else
			{
				if(pt[j].S > pt[i].S)
					lft[i].F++;
				else
					lft[i].S++;
			}
		}

		rgt[i] = OO;
		for(int j=i+1; j<N; j++)
		{
			if(pt[i].S == pt[j].S)
			{
				rgt[i] = QQ;
				break;
			}
			else
			{
				if(pt[j].S > pt[i].S)
					rgt[i].F++;
				else
					rgt[i].S++;
			}
		}
	}

	for(int i=0; i<N; i++)
	{
		for(int j=i+1; j<N; j++)
		{
			mid[i][j] = OO;
			if(pt[i].F == pt[j].F)
			{
				mid[i][j] = QQ;
				continue;
			}
			pii d = pt[j] - pt[i];
			for(int k=i+1; k<j; k++)
			{
				pii e = pt[k] - pt[i];
				int crs = cross(d, e);
				if(crs == 0)
				{
					mid[i][j] = QQ;
					break;
				}
				else if(crs > 0)
					mid[i][j].F++;
				else
					mid[i][j].S++;
			}
		}
	}

	for(int i=0; i<=N; i++)
		for(int j=0; j<=N; j++)
			for(int k=0; k<=N; k++)
				dp[i][j][k] = -1;

	for(int i=0; i<N; i++)
		if(lft[i] != QQ)
			dp[i][lft[i].F][lft[i].S] = -2;

	for(int i=0; i<N; i++)
	{
		for(int j=0; j<=N; j++)
		{
			for(int k=0; k<=N; k++)
			{
				if(dp[i][j][k] == -1) continue;
				for(int x = i+1; x<N; x++)
				{
					if(mid[i][x] == QQ) continue;
					dp[x][j+mid[i][x].F][k+mid[i][x].S] = i;
				}
			}
		}
	}

	for(int i=0; i<N; i++)
	{
		if(rgt[i] == QQ) continue;
		for(int j=0; j<=N; j++)
		{
			for(int k=0; k<=N; k++)
			{
				if(dp[i][j][k] == -1) continue;
				dp[N][j+rgt[i].F][k+rgt[i].S] = i;
			}
		}
	}

	int mindif = MAXN;
	int cur = N;
	int bj = -1, bk = -1;
	for(int j=0; j<=N; j++)
	{
		for(int k=0; k<=N; k++)
		{
			if(dp[N][j][k] == -1) continue;
			int l = N - j - k;
			int mx = max(max(j, k), l);
			int mn = min(min(j, k), l);
			int dif = mx - mn;
			if(dif < mindif)
			{
				mindif = dif;
				bj = j;
				bk = k;
			}
		}
	}

	vector<int> vans;

	while(cur != -2)
	{
		if(cur != N) vans.PB(cur);
		int prv = dp[cur][bj][bk];
		if(prv == -2) break;
		int dj, dk;
		if(cur == N)
		{
			tie(dj, dk) = rgt[prv];
		}
		else
		{
			tie(dj, dk) = mid[prv][cur];
		}
		bj -= dj;
		bk -= dk;
		cur = prv;
	}

	reverse(ALL(vans));
	vector<int> vbns;
	for(auto v: vans)
		vbns.PB(ord[v]+1);

	int S = vbns.size();
	cout<<S<<endl;
	for(int i=0; i<S; i++)
		cout<<vbns[i]<<(i==S-1 ? "\n" : " ");
}

int main() {
	IOS;
	FILEIO("division");

	cin>>N;
	for(int i=0; i<N; i++)
		cin>>ot[i].F>>ot[i].S;

	calc();

	return 0;
}
