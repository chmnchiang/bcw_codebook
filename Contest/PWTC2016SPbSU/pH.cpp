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
const int MAXN = 42;

int N, K;
ll pa[MAXN], pb[MAXN], pc[MAXN];
double prod[MAXN];
int ord[MAXN];
ll ans;
vector<int> vec;
int lab[MAXN];

bool cmp(int a, int b)
{
	return prod[a] > prod[b];
}

double randf()
{
	return rand() / (double)RAND_MAX;
}

void check(double A, double B, double C)
{
	for(int j=0; j<N; j++)
		prod[j] = A * pa[j] + B * pb[j] + C * pc[j];
	sort(ord, ord+N, cmp);

	ll SA = 0, SB = 0, SC = 0;
	for(int j=0; j<K; j++)
	{
		SA += pa[ord[j]];
		SB += pb[ord[j]];
		SC += pc[ord[j]];
	}
	ll val = SA * SA + SB * SB + SC * SC;
	if(val > ans)
	{
		ans = val;
//		cout<<"UPDATE "<<ans<<endl;
		vec.clear();
		for(int j=0; j<K; j++)
			vec.PB(ord[j]+1);
		sort(ALL(vec));
	}
}

void check2()
{
	random_shuffle(ord, ord+N);

	ll SA = 0, SB = 0, SC = 0;
	for(int j=0; j<K; j++)
	{
		SA += pa[ord[j]];
		SB += pb[ord[j]];
		SC += pc[ord[j]];
	}
	ll val = SA * SA + SB * SB + SC * SC;
	if(val > ans)
	{
		ans = val;
		vec.clear();
		for(int j=0; j<K; j++)
			vec.PB(ord[j]+1);
		sort(ALL(vec));
	}
}

void pla(double &A, double &B, double &C)
{
	double b = 0;
	for(int i=0; i<10; i++)
	{
		for(int j=0; j<N; j++)
		{
			int z = (lab[j] ? 1 : -1);
			double val = (A * pa[j] + B * pb[j] + C * pc[j] + b) * z;
			if(val <= 0)
			{
				A += pa[j] * z;
				B += pb[j] * z;
				C += pc[j] * z;
				b += z;
			}
		}
	}
}

void calc()
{
	ans = -1;
	for(int i=0; i<N; i++)
		ord[i] = i;
	for(int i=0; i<100000; i++)
	{
		double A = randf(), B = randf(), C = randf();
		check(A, B, C);
	}

	for(int i=0; i<100000; i++)
	{
		double A = 0, B = 0, C = 0;
		for(int j=0; j<5; j++)
		{
			int x = rand() % N;
			A += pa[x];
			B += pb[x];
			C += pc[x];
		}
		check(A, B, C);
	}

	for(int i=0; i<100000; i++)
		check2();

	for(int i=0; i<1000; i++)
	{
		double A = 0, B = 0, C = 0;
		for(int j=0; j<N; j++)
			lab[j] = rand() % 2;
		pla(A, B, C);
		check(A, B, C);
	}

	cout<<ans<<endl;
	for(auto v: vec)
		cout<<v<<" ";
	cout<<endl;
}

int main() {
	IOS;
	srand(time(0));

	int T;
	cin>>T;
	while(T--)
	{
		cin>>N>>K;
		for(int i=0; i<N; i++)
			cin>>pa[i]>>pb[i]>>pc[i];
		calc();
	}

	return 0;
}
