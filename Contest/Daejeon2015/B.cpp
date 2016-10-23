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

typedef pair<double, double> pdd;
typedef pair<double, int> pdi;

pdd operator+(pdd a, pdd b){return {a.F+b.F, a.S+b.S};}
pdd operator-(pdd a, pdd b){return {a.F-b.F, a.S-b.S};}
pdd operator*(double a, pdd b){return {a*b.F, a*b.S};}

const int MAXN = 1010;

int K, M, N;
pdd fix[MAXN], pt[MAXN];
vector<pdi> edge[MAXN];

void calc()
{
	pdd cen = {0, 0};
	for(int i=1; i<=K; i++)
		cen = cen + fix[i];
	cen = (1. / K) * cen;
	for(int i=1; i<=N; i++)
		pt[i] = cen;

	double eta = 0.01;
	for(int t=0; t<10000; t++)
	{
		for(int i=1; i<=N; i++)
		{
			pdd grad = {0, 0};
			for(auto p: edge[i])
			{
				double w = p.F;
				int j = p.S;
				if(j < 0) grad = grad + w * (pt[i] - fix[-j]);
				else grad = grad + w * (pt[i] - pt[j]);
			}
			pt[i] = pt[i] - eta * grad;
		}
		
	}
}

int main() {
	IOS;

	int T;
	cin>>T;
	for(int t=1; t<=T; t++)
	{
		cin>>K>>M>>N;

		for(int i=0; i<=N; i++)
			edge[i].clear();

		for(int i=1; i<=K; i++)
			cin>>fix[i].F>>fix[i].S;
		for(int i=0; i<M; i++)
		{
			double W;
			int a, b;
			cin>>W>>a>>b;
			if(a>0) edge[a].PB({W, b});
			if(b>0) edge[b].PB({W, a});
		}

		calc();

		cout<<"Test case number : "<<t<<endl;
		cout<<fixed<<setprecision(2);
		for(int i=1; i<=N; i++)
			cout<<i<<" "<<pt[i].F<<" "<<pt[i].S<<"\n";
	}

    return 0;
}

