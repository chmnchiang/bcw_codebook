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

const int MAXN = 30;
const double PI = acos(-1);

int N;
double arr[MAXN], brr[MAXN];
double xl, xh, inc;
double totv;

double eval(double x)
{
	double ret = 0;
	double cur = 1;
	for(int i=0; i<=2*N+1; i++)
	{
		ret += cur * brr[i];
		cur *= x;
	}
	return ret;
}

vector<double> calc()
{
	FZ(brr);
	for(int i=0; i<=N; i++)
		for(int j=0; j<=N; j++)
			brr[i+j+1] += arr[i] * arr[j] / (i+j+1.);
	inc /= PI;

//	for(int i=0; i<=N; i++) cout<<arr[i]<<" ";cout<<endl;
//	for(int i=0; i<=2*N+1; i++) cout<< brr[i]<<" ";cout<<endl;

	vector<double> ret;
	double init = eval(xl);
	totv = eval(xh) - init;
	for(int i=1; i<=8; i++)
	{
		double target = inc * i;
		if(target > totv) continue;

		double lb = xl, rb = xh;
		for(int j=0; j<100; j++)
		{
			double mb = (lb + rb) / 2;
			double e = eval(mb) - init;
			if(e > target)
				rb = mb;
			else
				lb = mb;
		}

		ret.PB(lb-xl);
	}

	return ret;
}

int main() {
	IOS;

	int t = 0;
	while(cin>>N)
	{
		t++;
		for(int i=0; i<=N; i++)
			cin>>arr[i];
		cin>>xl>>xh>>inc;

		vector<double> vec = calc();
		cout<<"Case "<<t<<": "<<fixed<<setprecision(2)<<(totv*PI)<<endl;
		if(vec.empty())
			cout<<"insufficient volume"<<endl;
		else
		{
			int S = vec.size();
			for(int i=0; i<S; i++)
				cout<<vec[i]<<(i==S-1 ? "\n" : " ");
		}
	}

	return 0;
}

