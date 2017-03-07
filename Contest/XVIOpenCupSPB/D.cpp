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

typedef pair<int, int> pii;
const int MAXN = 1010101;
const int INF = 1029384756;

int N, L;
int arr[MAXN];
bool notp[MAXN];
vector<int> factor[MAXN];
vector<int> pos[MAXN];
int psum[MAXN], px[MAXN];
int BIT[MAXN];
vector<int> GEZI;

void BITinit()
{
	for(int i=0; i<MAXN; i++)
		BIT[i] = -INF;
	GEZI.clear();
}

void BITrollback()
{
	for(auto x: GEZI)
		BIT[x] = -INF;
	GEZI.clear();
}

void BITupd(int po, int val)
{
	po++;
	while(po < MAXN)
	{
		GEZI.PB(po);
		BIT[po] = max(BIT[po], val);
		po += po & (-po);
	}
}

int BITqry(int po)
{
	po++;
	int ans = -INF;
	while(po)
	{
		ans = max(ans, BIT[po]);
		po -= po & (-po);
	}
	return ans;
}

void pre()
{
	for(int i=2; i<MAXN; i++)
	{
		if(notp[i]) continue;
		for(int j=i; j<MAXN; j+=i)
		{
			factor[j].PB(i);
			notp[j] = true;
		}
	}
}

pii maxlen()
{
	int ans = 0;
	int bx = 0, by = 0;

	int maxval = 0;
	for(int i=0; i<=L; i++)
		maxval = max(maxval, psum[i]);
	for(int i=0; i<=L; i++)
		psum[i] -= maxval;

	BITrollback();
	for(int i=L; i>=0; i--)
	{
		int res = BITqry(-psum[i]);
		if(res > i)
		{
			int lb = px[i];
			int dif = psum[res] - psum[i];
			int rb = px[res];
			if(rb < N)
				rb += dif;

			if(rb - lb > ans)
			{
				ans = rb - lb;
				bx = lb;
				by = rb;
			}
		}

		BITupd(-psum[i], i);
	}

	return {bx, by};
}

pii calc()
{
	BITinit();
	for(int i=0; i<MAXN; i++)
		pos[i].clear();

	for(int i=0; i<N; i++)
		for(auto x: factor[arr[i]])
			pos[x].PB(i);

	int ans = 0;
	int bx = -1, by = 0;

	for(int i=0; i<MAXN; i++)
	{
		if(pos[i].empty()) continue;

		//cout<<i<<" : "<<pos[i]<<endl;

		int S = SZ(pos[i]);
		L = 0;
		psum[L] = 0;
		px[L] = 0;
		L++;
		int cur = 0;
		for(int j=0; j<S; j++)
		{
			if(pos[i][j] > cur)
			{
				int dif = pos[i][j] - cur;
				psum[L] = psum[L-1] - dif;
				px[L] = pos[i][j];
				L++;
			}
			psum[L] = psum[L-1] + 1;
			px[L] = pos[i][j] + 1;
			L++;
			cur = pos[i][j] + 1;
		}
		if(cur < N)
		{
			psum[L] = psum[L-1] - (N - cur);
			px[L] = N;
			L++;
		}
		L--;

		/*
		cout<<"L = "<<L<<endl;
		for(int j=0; j<=L; j++) cout<<px[j]<<"\t"; cout<<endl;
		for(int j=0; j<=L; j++) cout<<psum[j]<<"\t"; cout<<endl;
		*/

		pii res = maxlen();
		int len = res.S - res.F;
		if(len > ans)
		{
			ans = len;
			bx = res.F;
			by = res.S;
		}

		reverse(psum, psum+L+1);
		reverse(px, px+L+1);
		for(int j=0; j<=L; j++)
		{
			px[j] = N - px[j];
			psum[j] = -psum[j];
		}

		res = maxlen();
		len = res.S - res.F;
		if(len > ans)
		{
			ans = len;
			bx = N - res.S;
			by = N - res.F;
		}
	}

	return {bx+1, by};
}

int main() {
	IOS;

	pre();
	while(cin>>N)
	{
		for(int i=0; i<N; i++)
			cin>>arr[i];

		pii res = calc();
		cout<<res.F<<" "<<res.S<<endl;
	}

	return 0;
}

