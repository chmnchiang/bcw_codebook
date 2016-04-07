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

#define int long long 

typedef long long ll;
typedef pair<ll, ll> pll;

vector<pll> VBAD;

ll A, M, P, Q, R, S;

vector<ll> to_m(int m, int k, int x)
{
	vector<ll> ret;
	ret.resize(k+1);

	for(int i=0; i<=k; i++)
	{
		ret[i] = (i==k ? x : x % m);
		x /= m;
	}

	return ret;
}

bool greater_m(vector<ll> v1, vector<ll> v2)
{
	int k = v1.size();
	for(int i=k-1; i>=0; i--)
	{
		if(v1[i] > v2[i]) return true;
		if(v1[i] < v2[i]) return false;
	}
	return false;
}

ll get_sum(vector<ll> v)
{
	ll ans = 0;
	for(auto x: v)
		ans += x;
	return ans;
}

bool cmp_v(vector<pll> v1, vector<pll> v2)
{
	int s1 = 0, s2 = 0;
	for(auto v: v1)
		s1 += v.S;
	for(auto v: v2)
		s2 += v.S;
	if(s1 != s2) return s1 < s2;

	for(int i=0; ; i++)
	{
		if(i == (int)v1.size() || i == (int)v2.size()) return false;
		if(v1[i].F != v2[i].F)
			return v1[i].F < v2[i].F;
		else if(v1[i].S != v2[i].S)
		{
			if(v1[i].F == 0)
				return v1[i].S > v2[i].S;
			else
				return v1[i].S < v2[i].S;
		}
	}
	return false;
}

vector<pll> calc()
{
	if(M == 1)
	{
		vector<pll> rett;
		ll lb = R - P, rb = S - Q; 
		lb = max(lb, 0LL);
		lb = (lb + A - 1) / A;
		rb /= A;
		if(rb < 0 || lb > rb)
			return VBAD;
		if(lb > 0)
			rett.PB({0, lb});
		return rett;
	}

	vector<pll> vans = VBAD;

	ll PP = P, QQ = Q;
	for(int k=0; ; k++)
	{
		if(k > 0)
		{
			PP *= M;
			QQ *= M;
		}
		if(QQ > S) break;

		ll lb = R - PP, rb = S - QQ;
		if(rb < 0) continue;
		lb = max(lb, 0LL);
		lb = (lb + A - 1) / A;
		rb = rb / A;
		if(lb > rb) continue;

//		cout<<k<<" : "<<lb<<"~"<<rb<<endl;

		vector<ll> vl = to_m(M, k, lb), vr = to_m(M, k, rb);
//		cout<<vl<<" "<<vr<<endl;

		vector<ll> vcur = vl;
		vector<ll> vbest = vcur;
		ll bestsum = get_sum(vcur);
		for(int i=0; i<k; i++)
		{
			vector<ll> vnxt = vcur;
			vnxt[i] = 0;
			vnxt[i+1]++;
			for(int j=i+1; j<k; j++)
			{
				if(vnxt[j] >= M)
				{
					vnxt[j] -= M;
					vnxt[j+1]++;
				}
			}
			if(greater_m(vnxt, vr)) break;

			vcur = vnxt;
			ll s = get_sum(vcur);
			if(s <= bestsum)
			{
				bestsum = s;
				vbest = vcur;
			}
		}

		vector<pll> vvz;
		reverse(ALL(vbest));
		for(int i=0; i<=k; i++)
		{
			if(vbest[i])
				vvz.PB({0, vbest[i]});
			if(i < k)
			{
				if(vvz.empty() || vvz.back().F == 0)
					vvz.PB({1, 1});
				else
					vvz.back().S++;
			}
		}

//		cout<<vbest<<endl;
//		cout<<vvz<<endl;
		if(cmp_v(vvz, vans))
			vans = vvz;
	}

	return vans;
}

int32_t main() {
	IOS;

	VBAD.PB({12341234,1234123412341234LL});
	int t = 0;
	while(cin>>A>>M>>P>>Q>>R>>S && A)
	{
		t++;
		vector<pll> vec = calc();
		cout<<"Case "<<t<<": ";
		if(vec == VBAD)
			cout<<"impossible";
		else if(vec.empty())
			cout<<"empty";
		else
		{
			int s = vec.size();
			for(int i=0; i<s; i++)
			{
				if(i>0) cout<<" ";
				cout<<vec[i].S<<(vec[i].F ? 'M' : 'A');
			}
		}
		cout<<endl;
	}

	return 0;
}


