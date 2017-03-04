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

const int MAXN = 303030;

int N;
int arr[MAXN];
int ord[MAXN];

bool cmp(int a, int b)
{
	return arr[a] < arr[b];
}

void calc()
{
	int ans = MAXN*2;
	int aa = -1, bb = -1, cc = -1;

	for(int i=0; i<N; i++)
		ord[i] = i;
	sort(ord, ord+N, cmp);

	set<int> st;
	for(int i=0; i<N; i++)
	{
		int v = ord[i];
		st.insert(v);
		st.insert(v-N);
		st.insert(v+N);

		auto it = st.lower_bound(v);
		auto it1 = it, it2 = it;
		it1--;
		it2++;
		int llen = (*it) - (*it1), rlen = (*it2) - (*it);
		if(llen == N or rlen == N) continue;
		int tlen = llen + rlen;
		if(tlen < ans)
		{
			ans = tlen;
			bb = v;
			aa = ((*it1) + N) % N;
			cc = ((*it2) + N) % N;
		}
	}


	cout<<aa+1<<" "<<bb+1<<" "<<cc+1<<endl;
}

int main() {
	IOS;

	cin>>N;
	for(int i=0; i<N; i++)
		cin>>arr[i];

	calc();

	return 0;
}
