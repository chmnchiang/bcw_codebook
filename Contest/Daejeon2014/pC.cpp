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

const int MAXN = 100;

set<int> st;

void pre()
{
	vector<int> vec;
	for(int i=1; i<MAXN; i++)
		vec.PB(i*(i+1)/2);
	for(auto a: vec)
		for(auto b: vec)
			for(auto c: vec)
				st.insert(a+b+c);
}

int main() {
	pre();
	IOS;
	int T;
	cin>>T;
	while(T--)
	{
		int K;
		cin>>K;
		cout<<(st.count(K))<<"\n";
	}

    return 0;
}

