#include<bits/stdc++.h>
#include<unistd.h>
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define MC(n,m) memcpy((n),(m),sizeof(n))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define ALL(x) begin(x),end(x)
#define SZ(x) ((int)(x).size())
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
// Let's Fight!

const int MAXN = 15;
const double PI = acos(-1);

int N, SL, ST;
double A, B;
double arr[MAXN];
double brr[MAXN];

double eval(double* poly, int n, double x)
{
	double ret = 0;
	double cur = 1;
	for(int i=0; i<=n; i++)
	{
		ret += poly[i] * cur;
		cur *= x;
	}
	return ret;
}

double true_vol()
{
	for(int i=0; i<=2*N; i++)
		brr[i] = 0;
	for(int i=0; i<=N; i++)
		for(int j=0; j<=N; j++)
			brr[i+j] += arr[i] * arr[j];
	for(int i=2*N+1; i>0; i--)
		brr[i] = brr[i-1] / i;
	brr[0] = 0;

	double ans = eval(brr, 2*N+1, B) - eval(brr, 2*N+1, A); 
	return PI * ans;
}

double approx_vol()
{
	double ans = 0;
	double prefix = SL / 6. * sin(2*PI/SL) * (B-A) / ST;
	for(int i=0; i<ST; i++)
	{
		double lb = A + i*(B-A)/ST;
		double rb = A + (i+1)*(B-A)/ST;
		double h1 = eval(arr, N, lb), h2 = eval(arr, N, rb);
		ans += h1*h1 + h1*h2 + h2*h2;
	}

	return ans * prefix;
}

int main() {
	int T;
	scanf("%d", &T);
	for(int _t=1; _t<=T; _t++)
	{
		scanf("%d", &N);
		for(int i=0; i<MAXN; i++)
			arr[i] = 0;
		for(int i=N; i>=0; i--)
			scanf("%lf", &arr[i]);
		scanf("%lf%lf%d%d", &A, &B, &SL, &ST);

		double tv = true_vol();
		double av = approx_vol();

		double ans = abs(tv - av) / tv;

		printf("Case %d: %.4f\n", _t, ans * 100);
	}

    return 0;
}

