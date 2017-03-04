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

typedef long long ll;

const int MAXM = 15;
const int MAXN = 101010;
const int MAX2M = (1<<15) + 5;
const int MAX3M = 3*3*3*3*3*3*3*3*3*3*3*3*3*3*3 + 5;
const int MOD = 1000000007;

int N, M;
int arr[MAX2M];
int NN[MAX3M], MM[MAX2M];
int two[MAXN], three[MAXN];
int ans;

int reg(int x)
{
	while(x >= MOD) x -= MOD;
	while(x < 0) x += MOD;
	return x;
}

void pre()
{
	two[0] = three[0] = 1;
	for(int i=1; i<MAXN; i++)
	{
		two[i] = (two[i-1] * 2LL) % MOD;
		three[i] = (three[i-1] * 3LL) % MOD;
	}
}

void f(int lv, int s1, int s2, int s3, int lst, int sgn)
{
	if(lv == M)
	{
		if(lst == -1)
			NN[s1] = arr[s3];
		else
			NN[s1] = NN[s1-three[lst]] + NN[s1-2*three[lst]];
		MM[s2] = reg(MM[s2] + sgn * (two[NN[s1]]-1));
		return;
	}

	f(lv+1, s1, s2, s3, lst, -sgn);
	f(lv+1, s1 + three[lv], s2, s3 + two[lv], lst, -sgn);
	f(lv+1, s1 + 2*three[lv], s2 + two[lv], 0, lv, sgn);
}

void g(int lv, int s1, int s3, int lst, bool ok)
{
	if(lv == M)
	{
		if(lst == -1)
			NN[s1] = MM[s3];
		else
			NN[s1] = reg(NN[s1-three[lst]] + NN[s1-2*three[lst]]);
		if(ok and s1*2 != three[M]-1)
		{
			int val = reg(NN[s1]);
			//cout<<s1<<" :::: "<<val<<endl;
			ans ^= val;
		}
		return;
	}

	g(lv+1, s1, s3, lst, false);
	g(lv+1, s1 + three[lv], s3 + two[lv], lst, ok);
	g(lv+1, s1 + 2*three[lv], 0, lv, ok);
}

int main() {
	IOS;
	pre();

	int T;
	cin>>T;
	for(int t=1; t<=T; t++)
	{
		cin>>N>>M;
		for(int i=0; i<(1<<M); i++)
			arr[i] = MM[i] = 0;
		for(int i=0; i<N; i++)
		{
			string s;
			cin>>s;
			int idx = 0;
			for(int j=0; j<M; j++)
				if(s[j] == 'Y') 
					idx += (1<<j);
			arr[idx]++;
		}

		//for(int i=0; i<(1<<M); i++) cout<<"arr["<<i<<"] = "<<arr[i]<<endl;
		ans = 0;
		f(0, 0, 0, 0, -1, 1);
		//for(int i=0; i<three[M]; i++) cout<<"NN["<<i<<"] = "<<NN[i]<<endl;
		//for(int i=0; i<(1<<M); i++) cout<<"MM["<<i<<"] = "<<MM[i]<<endl;
		g(0, 0, 0, -1, true);
		//for(int i=0; i<three[M]; i++) cout<<"S["<<i<<"] = "<<NN[i]<<endl;

		cout<<"Case #"<<t<<": "<<ans<<endl;
	}

	return 0;
}

