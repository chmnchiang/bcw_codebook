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

const int MAXN = 1515;

int N;
int M1, M2, M3;
int a1[MAXN];
vector<int> a2[MAXN];
vector<int> a3[MAXN];
int b3[MAXN];
int rem3[MAXN];
bool istrue[MAXN];
vector<int> to3[MAXN];

void init()
{
	for(int i=0; i<N; i++)
	{
		istrue[i] = false;
		to3[i].clear();
	}
	for(int i=0; i<M2; i++)
	{
		a2[i].clear();
	}
	for(int i=0; i<M3; i++)
	{
		a3[i].clear();
	}
}

bool calc()
{
	queue<int> Q;
	for(int i=0; i<M1; i++)
		Q.push(a1[i]);

	while(!Q.empty())
	{
		int v = Q.front();
		Q.pop();
		if(istrue[v]) continue;

		istrue[v] = true;
		for(auto x: to3[v])
		{
			rem3[x]--;
			if(rem3[x] == 0)
			{
				Q.push(b3[x]);
			}
		}
	}

	for(int i=0; i<M2; i++)
	{
		bool any = false;
		for(auto v: a2[i])
		{
			if(!istrue[v])
				any = true;
		}
		if(!any) return false;
	}

	return true;
}

int main() {
	IOS;
	int T;
	cin>>T;
	while(T--)
	{
		cin>>N>>M1>>M2>>M3;
		init();

		for(int i=0; i<M1; i++)
		{
			cin>>a1[i];
			a1[i]--;
		}

		for(int i=0; i<M2; i++)
		{
			int k;
			cin>>k;
			for(int j=0; j<k; j++)
			{
				int x;
				cin>>x;
				x--;
				a2[i].PB(x);
			}
		}

		for(int i=0; i<M3; i++)
		{
			int k;
			cin>>k;
			rem3[i] = k;
			for(int j=0; j<k; j++)
			{
				int x;
				cin>>x;
				x--;
				a3[i].PB(x);
				to3[x].PB(i);
			}
			cin>>b3[i];
			b3[i]--;
		}

		bool ans = calc();
		cout<<(ans ? "YES" : "NO")<<"\n";
	}

    return 0;
}

