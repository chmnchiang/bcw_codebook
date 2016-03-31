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

typedef pair<double,double> pdd;
pdd operator + (const pdd a, const pdd b) { return {a.F+b.F,a.S+b.S}; }
pdd operator - (const pdd a, const pdd b) { return {a.F-b.F,a.S-b.S}; }
double operator % (const pdd p1, const pdd p2){
	return p1.F* p2.S - p2.F * p1.S;
}

const int MAXN = 10;
const double INF = 1e20;
const double PI = acos(-1);

int N, M;
pdd pt[MAXN];
int ord[MAXN];

double cross(pdd o, pdd a, pdd b){
	return (a-o) % (b-o);
}
vector<pdd> convex_hull(vector<pdd> AcThPaU){
	sort(AcThPaU.begin(),AcThPaU.end());
	int top=0;
	vector<pdd> stk(2*AcThPaU.size());
	for (int i=0; i<(int)AcThPaU.size(); i++){
		while (top >= 2 && cross(stk[top-2],stk[top-1],AcThPaU[i]) <= 0)
			top--;
		stk[top++] = AcThPaU[i];
	}
	for (int i=AcThPaU.size()-2, t=top+1; i>=0; i--){
		while (top >= t && cross(stk[top-2],stk[top-1],AcThPaU[i]) <= 0)
			top--;
		stk[top++] = AcThPaU[i];
	}
	stk.resize(top);
	return stk;
}

double ch_len(vector<pdd> vec)
{
	if(vec.empty()) return 0;
	vector<pdd> ch = convex_hull(vec);
	double ans = 0;
	for(int i=0; i<(int)ch.size()-1; i++)
	{
		pdd x = ch[i+1] - ch[i];
		ans += sqrt(x.F*x.F+x.S*x.S);
	}
	return ans + 2 * PI * M;
}

double dfs(int lv, int mx)
{
	if(lv == N)
	{
		double len = 0;
		vector<pdd> gr[N];
		for(int i=0; i<N; i++)
			gr[ord[i]].PB(pt[i]);
		for(int i=0; i<N; i++)
			len += ch_len(gr[i]);
//		for(int i=0; i<N; i++) cout<<ord[i]<<" ";
//		cout<<": "<<len<<endl;
		return len;
	}

	double ans = INF;
	for(int i=0; i<=mx+1; i++)
	{
		ord[lv] = i;
		ans = min(ans, dfs(lv+1, max(mx, i)));
	}
	return ans;
}

double calc()
{
	double ans = dfs(0, -1);
	return ans;
}

int main() {
	IOS;
	int t = 0;
	while(cin>>N>>M && N && M)
	{
		t++;
		for(int i=0; i<N; i++)
			cin>>pt[i].F>>pt[i].S;

		double ans = calc();
		cout<<"Case "<<t<<": length = "<<fixed<<setprecision(2)<<ans<<endl;
	}

	return 0;
}


