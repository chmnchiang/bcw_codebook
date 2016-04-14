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

const int MAXN = 6010;

typedef bitset<MAXN*2> BS;

int N;
BS arr[MAXN];
int ord[MAXN];

int main() {
	IOS;
	srand(time(0));

	cin>>N;
	for(int i=0; i<N; i++)
	{
		string s;
		cin>>s;
		for(int j=0; j<(int)s.size(); j++)
		{
			int x = s[j] - 33;
			for(int k=0; k<6; k++)
				arr[i][6*j+k] = (x & (1<<k));
		}
	}

	int N2 = N / 2;

	for(int i=0; i<N; i++)
		ord[i] = i;
	random_shuffle(ord, ord+N);

	for(int i=0; i<N; i++)
	{
		for(int j=i+1; j<N; j++)
		{
			int ii = ord[i], jj = ord[j];
			BS cur = arr[ii] & arr[jj];
			if((int)cur.count() >= N2)
			{
				cout<<ii+1<<" "<<jj+1<<endl;
				return 0;
			}
		}
	}

	return 0;
}
