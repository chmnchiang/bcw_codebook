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

int M, N, P;

int main() {
	IOS;
	int T;
	cin>>T;
	while(T--)
	{
		cin>>M>>N>>P;

		cout<<1<<"\n";

		if(P == 3)
		{
			for(int i=0; i<M; i++)
			{
				for(int j=0; j<N; j++)
				{
					int x = (i%2) ? (N-1-j) : j;
					cout<<"("<<i<<","<<x<<")\n";
				}
			}
		}
		else
		{
			for(int i=0; i<N; i++)
			{
				for(int j=0; j<M; j++)
				{
					int x = (i%2) ? j : (M-1-j);
					cout<<"("<<x<<","<<i<<")\n";
				}
			}
		}

	}

    return 0;
}

