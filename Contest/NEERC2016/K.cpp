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

typedef long long ll;
typedef pair<int, int> pii;

const int MAXN = 1024;
const ll A = 123, B = 543;
const ll LEN = 50;
const ll MSK = (1LL<<LEN) - 1;
const pii BAD = {1234873, 4897392};

ll mul(ll a, ll b)
{
	ll ret = 0, cur = a;
	while(b)
	{
		if(b&1LL)
			ret ^= cur;
		cur <<= 1;
		b >>= 1;
	}
	ll lft = (ret >> LEN);
	ret &= MSK;
	ret ^= lft ^ (lft << 1);
	return ret;
}

ll pows[MAXN][MAXN];
unordered_set<ll> h3st;

void pre()
{
	pows[0][0] = 1;
	for(int i=0; i<MAXN; i++)
	{
		if(i > 0)
			pows[i][0] = mul(pows[i-1][0], A);
		for(int j=1; j<MAXN; j++)
			pows[i][j] = mul(pows[i][j-1], B);
	}
}

ll get_hash()
{
	int H, W;
	cin>>H>>W;
	ll ret = 0;

	string s;
	for(int i=0; i<H; i++)
	{
		cin>>s;
		for(int j=0; j<W; j++)
			if(s[j] == '*')
				ret ^= pows[i][j];
	}

	return ret;
}

pii calc(ll h1, ll h2)
{
	ll ha = h1, hb = h2;
	for(int i=0; i<MAXN; i++)
	{
		ll za = ha, zb = hb;
		ll ya = h1, yb = h2;
		for(int j=0; j<MAXN; j++)
		{
			if(h3st.count(h1 ^ zb)) return {j, i};
			if(h3st.count(za ^ h2)) return {-j, -i};
			if(h3st.count(ha ^ yb)) return {j, -i};
			if(h3st.count(ya ^ hb)) return {-j, i};

			za = mul(za, B);
			zb = mul(zb, B);
			ya = mul(ya, B);
			yb = mul(yb, B);
		}
		ha = mul(ha, A);
		hb = mul(hb, A);
	}

	return BAD;
}

int main() {
	pre();
	FILEIO("kids");
	IOS;

	ll h1 = get_hash();
	ll h2 = get_hash();
	ll h3 = get_hash();

	ll cur = h3;
	for(int i=0; i<MAXN; i++)
	{
		ll z = cur;
		for(int j=0; j<MAXN; j++)
		{
			h3st.insert(z);
			z = mul(z, B);
		}
		cur = mul(cur, A);
	}

	pii res = calc(h1, h2);
	if(res == BAD) cout<<"NO"<<endl;
	else
	{
		cout<<"YES"<<endl;
		cout<<res.F<<" "<<res.S<<endl;
	}

	return 0;
}

