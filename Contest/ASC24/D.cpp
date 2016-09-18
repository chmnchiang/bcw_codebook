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

const int MAXN = 201010;

int K;
int arr[MAXN];

int calc()
{
	for(int i=K-1; i>=0; i--)
	{
		while(arr[i]  >= arr[i+1] + 2)
			arr[i]-=2;
	}

	string s;
	int cur = MAXN;
	arr[K] = 0;
	for(int i=0; i<=K; i++)
	{
		while(cur > arr[i])
		{
			cur--;
			s.PB('u');
		}
		s.PB('z');
	}

	string s1, s2;
	for(int i=0; i<SZ(s); i++)
	{
		if(i%2) s2.PB(s[i]);
		else s1.PB(s[i]);
	}
	sort(ALL(s1));
	sort(ALL(s2));
	for(int i=0; i<SZ(s); i++)
	{
		if(i%2) s[i] = s2[i/2];
		else s[i] = s1[i/2];
	}

	int res = 0;
	for(int i=0; i<SZ(s)-1; i++)
		if(s[i]=='z' and s[i+1]=='u')
			res++;
	
	return res;
}

int main() {
	IOS;
	FILEIO("irreducible");

	cin>>K;
	for(int i=0; i<K; i++)
		cin>>arr[i];

	int ans = calc();
	cout<<1<<endl;
	cout<<ans;
	for(int i=ans; i>=1; i--)
		cout<<" "<<i;
	cout<<endl;

	return 0;
}

