#pragma GCC optimize ("O2")
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
#define REP(i,x) for (int i=0; i<(x); i++)
#define REP1(i,a,b) for (int i=(a); i<=(b); i++)
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
    freopen(name".in", "r", stdin); \
    freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif
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
	FILEIO("java2016");

	int C;
	cin>>C;
	if(C == 0)
	{
		cout<<"?/?/?"<<endl;
		return 0;
	}

	C = 256 - C;

	for(int i=0; i<10; i++)
	{
		char c1 = 'a' + i;
		char c2 = 'a' + i - 1;
		if(i == 0) c2 = '?';

		cout<<c1<<" = "<<c2<<" max "<<c2<<" max "<<c2<<endl;
	}

	for(int i=0; i<8; i++)
	{
		char c1 = 'j'+i+1;
		char c2 = 'j'+i;
		cout<<c1<<" = "<<c2<<" + "<<c2<<endl;
	}

	bool any = false;

	for(int i=0; i<8; i++)
	{
		if(C&(1<<i))
		{
			if(any) cout<<" + ";
			cout<<(char)('j'+i);
			any = true;
		}
	}

	cout<<endl;

	return 0;
}

