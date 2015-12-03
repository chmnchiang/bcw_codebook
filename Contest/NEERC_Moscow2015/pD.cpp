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

int main() {
	double t1, t2, h1, h2;
	cin>>h1>>t1>>h2>>t2;

	double dom = (sqrt(h1) - sqrt(h2)) / (t1 - t2);
	double g = 2 * dom * dom;

	double d = -sqrt(2*h1/g) + t1;
	cout<<fixed<<setprecision(10)<<d<<endl;

    return 0;
}

