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
		int N, M;
		cin>>N>>M;
		N--;
		int A = 0, B = 0;
		int x;
		for(int i=0; i<N; i++)
		{
			cin>>x;
			A += x;
		}
		for(int i=0; i<M; i++)
		{
			cin>>x;
			B += x;
		}
		int lb = (B / M) + 1;
		int rb = (A-1) / N;
		cout<<lb<<" "<<rb<<"\n";
	}

    return 0;
}
