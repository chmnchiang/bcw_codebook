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

const int MAXN = 30;
const string name[] = {"Pre", "In", "Post"};

struct PIP
{
	string pre, in, post;
};

bool operator<(PIP &a, PIP &b)
{
	return tie(a.pre, a.in, a.post) < tie(b.pre, b.in, b.post);
}

int N;
string str[3];
vector<int> stk;
bool dp[MAXN][MAXN][3][3][3];
PIP dstr[MAXN][MAXN][3][3][3];

pii match[MAXN][MAXN][2];

bool anyans = false;

void make_match()
{
	for(int i=0; i<MAXN; i++)
		for(int j=0; j<MAXN; j++)
			for(int k=0; k<2; k++)
				match[i][j][k] = {-1, -1};

	for(int i=0; i<=N; i++)
	{
		for(int j=i+1; j<=N; j++)
		{
			int len = j - i;
			for(int k=0; k<2; k++)
			{
				for(int ii=0; ii+len<=N; ii++)
				{
					int jj = ii + len;
					string s1 = str[0].substr(i, len);
					string s2 = str[k+1].substr(ii, len);
					sort(ALL(s1));
					sort(ALL(s2));
					if(s1 == s2)
						match[i][j][k] = {ii, jj};
				}
			}
		}
	}
}

void calc()
{
//	vector<int> vvv;
//	vvv.PB(0); vvv.PB(2); vvv.PB(1); vvv.PB(2); vvv.PB(1); vvv.PB(0);
//	if(vvv != stk) return;

//	cout<<stk<<endl;

	for(int i=0; i<=N; i++)
		for(int j=0; j<=N; j++)
			for(int a=0; a<3; a++)
				for(int b=0; b<3; b++)
					for(int c=0; c<3; c++)
						dp[i][j][a][b][c] = false;

	for(int i=0; i<N; i++)
	{
		string ss = str[0].substr(i, 1);
		for(int a=0; a<3; a++)
			for(int b=0; b<3; b++)
				for(int c=0; c<3; c++)
				{
					dp[i][i+1][a][b][c] = true;
					dstr[i][i+1][a][b][c] = {ss, ss, ss};
				}
	}

	for(int len=2; len<=N; len++)
	{
		for(int i=0; i+len<=N; i++)
		{
			int j = i + len;
			int lb[3], rb[3];
			lb[0] = i;
			rb[0] = j;
			tie(lb[1], rb[1]) = match[i][j][0];
			tie(lb[2], rb[2]) = match[i][j][1];

			for(int ll=0; ll<len; ll++)
			{
				int rl = len - ll - 1;
				for(int a=0; a<3; a++)
				{
					for(int b=0; b<3; b++)
					{
						for(int c=0; c<3; c++)
						{
							int ord[3];
							ord[0] = a;
							ord[1] = b;
							ord[2] = c;

							int al = stk[a*2], ar = stk[a*2+1];
							int bl = stk[b*2], br = stk[b*2+1];
							int cl = stk[c*2], cr = stk[c*2+1];

							char root = '!';
							bool ok = true;
							int lx[3], ly[3], rx[3], ry[3];
							for(int x=0; x<3; x++)
							{
								char nr;
								if(ord[x] == 0)
								{
									nr = str[x][lb[x]];
									lx[x] = lb[x] + 1;
									ly[x] = lx[x] + ll;
									ry[x] = rb[x];
									rx[x] = ry[x] - rl;
								}
								else if(ord[x] == 1)
								{
									nr = str[x][lb[x]+ll];
									lx[x] = lb[x];
									ly[x] = lx[x] + ll;
									ry[x] = rb[x];
									rx[x] = ry[x] - rl;
								}
								else
								{
									nr = str[x][rb[x]-1];
									lx[x] = lb[x];
									ly[x] = lx[x] + ll;
									ry[x] = rb[x] - 1;
									rx[x] = ry[x] - rl;
								}
								if(x == 0) root = nr;
								else if(root != nr) ok = false;
							}

							PIP lpip, rpip;
							if(ll == 0)
								lpip = {"", "", ""};
							else
							{
								if(pii(lx[1], ly[1]) != match[lx[0]][ly[0]][0]) ok = false;
								if(pii(lx[2], ly[2]) != match[lx[0]][ly[0]][1]) ok = false;
								if(!dp[lx[0]][ly[0]][al][bl][cl]) ok = false;
								lpip = dstr[lx[0]][ly[0]][al][bl][cl];
							}

							if(rl == 0)
								rpip = {"", "", ""};
							else
							{
								if(pii(rx[1], ry[1]) != match[rx[0]][ry[0]][0]) ok = false;
								if(pii(rx[2], ry[2]) != match[rx[0]][ry[0]][1]) ok = false;
								if(!dp[rx[0]][ry[0]][ar][br][cr]) ok = false;
								rpip = dstr[rx[0]][ry[0]][ar][br][cr];
							}

							if(ok)
							{
								PIP allpip = {root + lpip.pre + rpip.pre, lpip.in + root + rpip.in, lpip.post + rpip.post + root};
								if(!dp[i][j][a][b][c] || allpip < dstr[i][j][a][b][c])
								{
									dp[i][j][a][b][c] = true;
									dstr[i][j][a][b][c] = allpip;
								}
							}

						}
					}
				}
			}
		}
	}

	for(int i=0; i<N; i++)
		for(int j=0; j<N; j++)
			for(int a=0; a<3; a++)
				for(int b=0; b<3; b++)
					for(int c=0; c<3; c++)
						if(dp[i][j][a][b][c])
							;//cout<<i<<" "<<j<<" "<<a<<" "<<b<<" "<<c<<endl;


	if(dp[0][N][0][1][2])
	{
		if(anyans) cout<<endl;
		PIP pip = dstr[0][N][0][1][2];
		for(int i=0; i<6; i++)
			cout<<name[stk[i]]<<(i==5 ? "\n" : " ");
		cout<<pip.pre<<endl<<pip.in<<endl<<pip.post<<endl;
		anyans = true;
	}

}

void dfs(int lv)
{
	if(lv == 6)
	{
		int cnt[3];
		for(int i=0; i<3; i++)
			cnt[i] = 0;
		for(auto x: stk)
			cnt[x]++;
		for(int i=0; i<3; i++)
			if(cnt[i] != 2)
				return;
		calc();

		return;
	}

	for(int i=0; i<3; i++)
	{
		stk.PB(i);
		dfs(lv+1);
		stk.pop_back();
	}
}

void solve()
{
	N = str[0].size();
	make_match();
	dfs(0);
}

int main() {
	IOS;

	for(int i=0; i<3; i++)
		cin>>str[i];

	solve();

	return 0;
}

