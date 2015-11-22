#include<bits/stdc++.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define F first
#define S second
#define PB push_back
#define ALL(x) begin(x),end(x)
#define SZ(x) ((int)(x).size())
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
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



int main() {
    IOS;
	int T;
	cin>>T;
	while(T--)
	{
		int N;
		string s;
		cin>>N>>s;
		double ans = 0;
		for(int i=0; i<N; i++)
		{
			int x;
			cin>>x;
			if(x == 0) continue;
			double p = x / 100.;
			ans -= p * log(p);
		}

		if(s == "bit") ans /= log(2);
		else if(s == "dit") ans /= log(10);

		cout<<fixed<<setprecision(12)<<ans<<endl;
	}

    return 0;
}
