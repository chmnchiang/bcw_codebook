//bcw0x1bd2 {{{
#include<bits/stdc++.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define MC(n,m) memcpy((n),(m),sizeof(n))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define FOR(x,y) for(__typeof(y.begin())x=y.begin();x!=y.end();x++)
#define IOS ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
  freopen(name".in", "r", stdin); \
  freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif

void RI() {}

template<typename... T>
void RI( int& head, T&... tail ) {
	    scanf("%d",&head);
			    RI(tail...);
}

mt19937 rng(0x5EED);
int randint(int lb, int ub) {
    return uniform_int_distribution<int>(lb, ub)(rng);
}
// Let's Fight! }}}

typedef pair<double, double> pdd;
typedef pair<pdd, pdd> Line;

pdd operator+(pdd a, pdd b){ return MP(a.F+b.F, a.S+b.S);}
pdd operator-(pdd a, pdd b){ return MP(a.F-b.F, a.S-b.S);}
pdd operator*(pdd a, double b){ return MP(a.F*b, a.S*b);}
double cross(pdd a, pdd b){ return a.F*b.S-b.F*a.S;}
double dot(pdd a, pdd b){ return a.F*b.F+a.S*b.S;}
double abs(pdd a){ return sqrt(dot(a, a));}
pdd unit(pdd a){ return a * (1 / abs(a));}

const int MAXN = 222;
const double EPS = 1E-10;

int N;
pdd pt[MAXN];
pdd p1, p2;

bool test(double R)
{
	vector<Line> vline;

	for(int i=0; i<N; i++)
	{
		pdd d = pt[(i+1)%N] - pt[i];
		pdd du = unit(d);
		pdd n = MP(-du.S, du.F);
		pdd q = pt[i] + n * R;
		vline.PB(MP(q, du));
		//cout<<q.F<<","<<q.S<<" Dir "<<du.F<<","<<du.S<<endl;
	}

	vector<pdd> ipts;
	for(int i=0; i<N; i++)
	{
		for(int j=i+1; j<N; j++)
		{
			pdd q1 = vline[i].F, q2 = vline[j].F;
			pdd d1 = vline[i].S, d2 = vline[j].S;
			double crs = cross(d2, d1);
			if(abs(crs) < EPS) continue;
			double s = cross(q1-q2, d1) / crs;
			pdd c = q2 + d2 * s;

			bool ok = true;
			for(int k=0; k<N; k++)
			{
				pdd qq = vline[k].F, dd = vline[k].S;
				if(cross(dd, c - qq) < -EPS)
				{
					ok = false;
					break;
				}
			}

			if(ok)
				ipts.PB(c);
		}
	}

	int P = ipts.size();
	//cout<<"P = "<<P<<endl;
	for(int i=0; i<P; i++)
	{
		for(int j=i+1; j<P; j++)
		{
			if(abs(ipts[i] - ipts[j]) >= 2 * R)
			{
				p1 = ipts[i];
				p2 = ipts[j];
				//cout<<p1.F<<","<<p1.S<<" "<<p2.F<<","<<p2.S<<endl;
				return true;
			}
		}
	}

	return false;
}

int main(){
	FILEIO("kabbalah");

	while(cin>>N && N)
	{
		for(int i=0; i<N; i++)
			cin>>pt[i].F>>pt[i].S;

		double lb = 0, rb = 3E4;
		while(rb - lb > EPS)
		{
			double mb = (lb + rb) / 2;
			if(test(mb))
				lb = mb;
			else
				rb = mb;
		}

		cout << fixed << setprecision(10);
		cout << (lb + rb) / 2 << endl;
		cout << p1.F << " " << p1.S << endl;
		cout << p2.F << " " << p2.S << endl;
	}


	return 0;
}

