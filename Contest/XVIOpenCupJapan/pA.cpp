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
#define loop(i, a, b) for (auto (i) = (a); (i) != (b); (i) += (((a) < (b) ? 1 : -1)))

const int MAXN = 10101;
const int MAXM = 105;

int N, M;
string arr[MAXM];

int calc()
{
	long long sum = 0, mxsum = 0;
	int idx = 0;
	for(int i=0; i<N; i++)
	{
		int z = 0;
		for(int j=0; j<M; j++)
			z += (arr[j][i] == 'W' ? 1 : -1);
		mxsum += z;
		if(mxsum > sum)
		{
			sum = mxsum;
			idx = i+1;
		}
	}

	return idx;
}

int main() {
	IOS;

	cin>>N>>M;
	for(int i=0; i<M; i++)
		cin>>arr[i];

	int idx = calc();
	cout<<idx<<" "<<idx+1<<endl;

	return 0;
}

