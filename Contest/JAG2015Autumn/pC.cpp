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

const int MAXN = 1024;

int N;
bool d[MAXN];
int l[MAXN];
bool used[MAXN];

int main() {
    IOS;

	cin>>N;
	for(int i=0; i<N; i++)
	{
		char c;
		cin>>c>>l[i];
		d[i] = (c == 'y');
	}

	int cost = 0;

	while(1)
	{
		int cur = -1;
		for(int i=0; i<N; i++)
		{
			if(d[i] && !used[i])
			{
				if(cur == -1 || l[i] < l[cur])
					cur = i;
			}
		}

		if(cur == -1) break;

		int lb = cur, rb = cur;
		while(lb>0 && !(!d[lb-1] && l[lb-1] >= l[cur])) lb--;
		while(rb<N-1 && !(!d[rb+1] && l[rb+1] >= l[cur])) rb++;

		cost++;
		for(int i=lb; i<=rb; i++)
			used[i] = true;
	}

	cout<<cost<<endl;

    return 0;
}

