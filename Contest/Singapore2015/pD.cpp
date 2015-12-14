#include <bits/stdc++.h>
using namespace std;

#define F first
#define S second
#define PB push_back

typedef long long ll;
typedef long double ld;
typedef pair<ld, ll> pdl;

const int MAXN = 102;
const ll MOD = 1000000007;
const ld EPS = 1E-15;

int a[MAXN];
ld totallg = 0;
ll total = 1;
ld curbest = 1E30;
ll ans = 0;
vector<pdl> dp1, dp2;

ll inv(ll ab)
{
	ll ret = 1, cur = ab, p = MOD-2;
	while(p)
	{
		if(p&1LL)
			ret = ret * cur % MOD;
		cur = cur * cur % MOD;
		p >>= 1;
	}
	return ret;
}

void input()
{
	string s;
	cin>>s;
	int sz = s.size();
	for(int i=0; 2*i<sz; i++)
	{
		int aa = s[2*i] - '0';
		int bb = s[2*i+1] - '0';
		int cc = aa * 10 + bb;
		a[cc]++;
		totallg += log(cc);
		total = total * cc % MOD;
	}
}

void dfs(vector<int> &pm, vector<pdl> &dp, int dep)
{
	if(dep == (int)pm.size()) return;
	int p = pm[dep];
	int sz = dp.size();
	ll cur = 1;
	ld curlg = 0;
	for(int i=1; i<=a[p]; i++)
	{
		cur = (cur * p) % MOD;
		curlg += log(p);
		for(int j=0; j<sz; j++)
			dp.PB({dp[j].F + curlg, dp[j].S * cur % MOD});
	}

	dfs(pm, dp, dep+1);
}

void calc()
{
	vector<int> pm1, pm2;
	ll prod = 1;
	bool fl = false;
	for(int i=0; i<MAXN; i++)
	{
		if(!a[i]) continue;
		if(fl) pm2.PB(i);
		else pm1.PB(i);
		prod *= a[i]+1;
		if(prod > 77777) fl = true;
	}

	dp1.PB({0, 1});
	dp2.PB({0, 1});
	dfs(pm1, dp1, 0);
	dfs(pm2, dp2, 0);

//	cout<<dp1.size()<<" "<<dp2.size()<<endl;

	sort(dp1.begin(), dp1.end());
	sort(dp2.begin(), dp2.end());

	//for(auto p: pm1) cout<<p<<" "; cout<<endl;
	//for(auto p: pm2) cout<<p<<" "; cout<<endl;
	//for(auto v: dp1) cout<<v.F<<" , "<<v.S<<" "; cout<<endl;
	//for(auto v: dp2) cout<<v.F<<" , "<<v.S<<" ";cout<<endl;

	int pos2 = dp2.size() - 1;
	for(auto p: dp1)
	{
		ld v1 = p.F;
		ll m1 = p.S;
		while(1)
		{
			if(pos2 < 0)
			{
				pos2++;
				break;
			}
			ld v2 = dp2[pos2].F;
			ll m2 = dp2[pos2].S;
			ld vv = v1 + v2;
			if(vv + vv < totallg - EPS)
			{
				if(pos2 < (int)dp2.size() - 1) pos2++;
				break;
			}
			else
			{
				if(vv < curbest)
				{
					curbest = vv;
					ans = (m1 * m2) % MOD;
				}
				pos2--;
			}
		}
	}
}


int main() {
	input();
	calc();

	ll anan = (ans + (total * inv(ans)) ) % MOD;
	cout<<anan<<endl;

	return 0;
}

