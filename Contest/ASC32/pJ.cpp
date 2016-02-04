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
// Let's Fight!


typedef pair<int, int> pii;

const int MAXN = 101010;

int N;
string s;

bool dp[MAXN][5];
pii prv[MAXN][5];
string prs[MAXN][5];

string calc()
{
	dp[0][0] = true;
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<5; j++)
		{
			if(!dp[i][j]) continue;
			if(s[i] != '\'')
			{
				dp[i+1][j] = true;
				prv[i+1][j] = {i, j};
				prs[i+1][j] = s[i];
			}
			if(i+3 <= N && j != 4 && s[i] == '\'' && s[i+1] == '\'' && s[i+2] == '\'')
			{
				int nxtj;
				string nxts;
				if(j == 0)
				{
					nxtj = 2;
					nxts = "<b>";
				}
				else if(j == 1)
				{
					nxtj = 3;
					nxts = "<b>";
				}
				else if(j == 2)
				{
					nxtj = 0;
					nxts = "</b>";
				}
				else
				{
					nxtj = 1;
					nxts = "</b>";
				}

				dp[i+3][nxtj] = true;
				prv[i+3][nxtj] = {i, j};
				prs[i+3][nxtj] = nxts;
			}
			if(i+2 <= N && j != 3 && s[i] == '\'' && s[i+1] == '\'')
			{
				int nxtj;
				string nxts;
				if(j == 0)
				{
					nxtj = 1;
					nxts = "<i>";
				}
				else if(j == 1)
				{
					nxtj = 0;
					nxts = "</i>";
				}
				else if(j == 2)
				{
					nxtj = 4;
					nxts = "<i>";
				}
				else
				{
					nxtj = 2;
					nxts = "</i>";
				}

				dp[i+2][nxtj] = true;
				prv[i+2][nxtj] = {i, j};
				prs[i+2][nxtj] = nxts;
			}
		}
	}

	if(!dp[N][0]) return "!@#$%";

	vector<string> vec;
	int cur = N;
	int cj = 0;
	while(cur != 0)
	{
		vec.PB(prs[cur][cj]);
		pii p = prv[cur][cj];
		cur = p.F;
		cj = p.S;
	}
	reverse(ALL(vec));
	string ret = "";
	for(auto v: vec)
		ret += v;
	return ret;
}

int main() {
	IOS;
	FILEIO("wikipidia");

	getline(cin, s);
	N = s.size();

	string ret = calc();
	cout<<ret<<endl;

    return 0;
}

