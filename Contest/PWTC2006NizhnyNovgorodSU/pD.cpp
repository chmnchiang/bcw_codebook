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

const int MAXN = 105;
const double EPS = 1E-7;

int N, M;

int vec[MAXN][MAXN];

int result[MAXN];
int base[MAXN];
int lb[MAXN], rb[MAXN];
double arr[MAXN][MAXN], brr[MAXN];

void gauss()
{
	for(int i=0; i<N; i++)
		for(int j=0; j<N; j++)
			arr[j][i] = vec[i][j];
	for(int i=0; i<N; i++)
		brr[i] = result[i];

	for(int i=0; i<N; i++)
	{
		int piv = -1;
		for(int j=i; j<N; j++)
		{
			if(abs(arr[j][i]) > EPS)
			{
				piv = j;
				break;
			}
		}
		swap(arr[i], arr[piv]);
		swap(brr[i], brr[piv]);
		double rat = arr[i][i];
		for(int j=0; j<N; j++)
			arr[i][j] /= rat;
		brr[i] /= rat;
		for(int j=0; j<N; j++)
		{
			if(j == i) continue;
			rat = arr[j][i];
			for(int k=0; k<N; k++)
				arr[j][k] -= rat * arr[i][k];
			brr[j] -= rat * brr[i];
		}
	}
}

void query(vector<int> vq)
{
	cout<<"?";
	for(auto v: vq)
		cout<<" "<<v+1;
	cout<<endl;
	for(int i=0; i<N; i++)
		cin>>result[i];
}

void answer(vector<int> vq)
{
	cout<<"A";
	for(auto v: vq)
		cout<<" "<<v+1;
	cout<<endl;
	exit(0);
}

int main() {
	IOS;

	cin>>N>>M;

	vector<int> vq;
	vq.resize(N);

	if(M == 1)
		answer(vq);

	query(vq);
	for(int i=0; i<N; i++)
		base[i] = result[i];

	for(int i=0; i<N; i++)
	{
		vq[i] = 1;
		query(vq);
		for(int j=0; j<N; j++)
			vec[i][j] = result[j] - base[j];
		vq[i] = 0;
	}

	for(int i=0; i<N; i++)
	{
		lb[i] = 0;
		rb[i] = M-1;
	}

	for(int z=0; z<10; z++)
	{
		for(int i=0; i<N; i++)
		{
			vq[i] = (lb[i] + rb[i]) / 2;
		}
		query(vq);
		gauss();
		for(int i=0; i<N; i++)
		{
			if(brr[i] > -EPS)
				rb[i] = vq[i];
			else
				lb[i] = vq[i] + 1;
		}
	}

	for(int i=0; i<N; i++)
		vq[i] = lb[i];
	answer(vq);

	return 0;
}
