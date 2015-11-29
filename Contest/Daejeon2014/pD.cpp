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

const int MAXN = 1010;

int N, K, F;
bool arr[MAXN][MAXN];
int deg[MAXN];
bool in[MAXN];

int calc()
{
	while(1)
	{
		int idx = -1;
		for(int i=0; i<N; i++)
		{
			if(!in[i]) continue;
			if(deg[i] < K)
			{
				idx = i;
				break;
			}
		}
		if(idx == -1) break;

		in[idx] = false;
		for(int i=0; i<N; i++)
		{
			if(arr[idx][i])
			{
				deg[idx]--;
				deg[i]--;
			}
		}
	}

	int ans = 0;
	for(int i=0; i<N; i++)
		ans += in[i];
	return ans;
}

int main() {
	IOS;
	int T;
	cin>>T;
	while(T--)
	{
		cin>>N>>K>>F;
		for(int i=0; i<N; i++)
		{
			deg[i] = 0;
			in[i] = true;
		}
		for(int i=0; i<N; i++)
			for(int j=0; j<N; j++)
				arr[i][j] = false;
		for(int i=0; i<F; i++)
		{
			int a, b;
			cin>>a>>b;
			a--;
			b--;
			arr[a][b] = arr[b][a] = true;
			deg[a]++;
			deg[b]++;
		}

		int ans = calc();
		cout<<ans<<"\n";
	}

    return 0;
}

