#include<bits/stdc++.h>
using namespace std;
#define REP(n,i) for(int (i)=0;(i)<(n);(i)++)
#define CDREP(n,i) for(int (i)=((n)−1);(i)>=0;(i)−−)
#define CDFOR(s,e,i) for(int i=((e)−1);(i)>=(s);(i)−−)
#define _SZ(n) memset((n),0,sizeof(n))
#define _SMO(n) memset((n),−1,sizeof(n))
#define _MC(n,m) memcpy((n),(m),sizeof(n))
#define _F first
#define _S second
#define _MP(a,b) make_pair((a),(b))
#define _PB(a) push_back((a))
#define FOR(x,y) for(__typeof(y.begin())x=y.begin();x!=y.end();x++)
#define IOS ios_base::sync_with_stdio(0);
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
    freopen(name".in", "r", stdin); \
    freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif
//Let's Fight!

#define ll long long

const int MAXN = 1536;
const double PI = acos(-1);

int N;
int px[MAXN], py[MAXN];
vector<double> vect;

int main(){
	FILEIO("points");

	IOS
	cin>>N;
	for(int i=0; i<N; i++)
	{
		cin>>px[i]>>py[i];
	}

	ll cnt = 0;
	for(int i=0; i<N; i++)
	{
		vect.clear();
		for(int j=0; j<N; j++)
		{
			if(j==i)continue;
			vect._PB(atan2(py[j]-py[i], px[j]-px[i]));
		}
		sort(vect.begin(), vect.end());
		for(int j=0; j<N-1; j++)
			vect._PB(vect[j]+2*PI);

		//FOR(it, vect)cout<<(*it)<<" ";cout<<endl;

		int r = 0;
		for(int l=0; l<N-1; l++)
		{
			while(r<2*N-3 && vect[r+1]-vect[l]<=PI)r++;
			ll x = r-l+1;
			//cout<<i<<" , "<<l<<" , "<<x<<endl;
			cnt += (x-2)*(x-1)/2;
		}
	}

	//cout<<cnt<<endl;
	//if(cnt%4!=0)while(1);
	
	ll tot = (ll)N*(N-1)*(N-2)*(N-3)/24;
	cnt -= tot*3;
	ll c2 = tot - cnt;
	ll ans = cnt*2+c2;

	ll mn = (ll)N*(N-1)*(N-2)/6;
	long double ratio = (long double)ans / mn;

	cout<<fixed<<setprecision(15)<<ratio<<endl;	

	return 0;
}
