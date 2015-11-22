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
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
  freopen(name".in", "r", stdin); \
  freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif
// Let's Fight!

const int MAXN = 10101;

int N;
bool isp[MAXN];
vector<int> primes;

void pre()
{
	for(int i=2; i<MAXN; i++)
		isp[i] = true;
	for(int i=2; i<MAXN; i++)
	{
		if(!isp[i]) continue;
		primes.PB(i);
		for(int j=2*i; j<MAXN; j+=i)
			isp[j] = false;
	}
}

int calc()
{
	if(N==2) return 1;
	if(N==3 || N==4) return 2;
	if(N==5) return 3;

	vector<int> p1, p2;
	for(auto v: primes)
	{
		if(v*v<=N) p1.PB(v);
		else if(v <= N) p2.PB(v);
	}

	int sz = p2.size();

	reverse(p1.begin(), p1.end());
	if(p1.size() > p2.size()) return sz+1;

	bool ok = true;
	for(int i=0; i<(int)p1.size(); i++)
	{
		if(p1[i] * p2[i] > N)
			ok = false;
	}
	return ok ? sz : sz+1;
}

int main() {
	FILEIO("GCD");

	IOS;
	pre();

	cin>>N;

	int ans = calc();
	cout<<ans<<endl;

    return 0;
}
