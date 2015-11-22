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

string S, T;

int main() {
    IOS;
	cin>>S>>T;

	bool ok = false;

	int pos = 0;
	int sz = S.size(), tz = T.size();

	for(int i=0; i<sz; i+=2)
	{
		while(pos < tz && T[pos] != S[i]) pos++;
		pos++;
	}
	if(pos <= tz) ok = true;

	pos = 0;
	for(int i=1; i<sz; i+=2)
	{
		while(pos < tz && T[pos] != S[i]) pos++;
		pos++;
	}
	if(pos <= tz) ok = true;

	cout<<(ok ? "Yes" : "No")<<endl;

    return 0;
}

