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

double W, H, x, xe, ye, mu;

int main() {
	IOS;
	int T;
	scanf("%d", &T);
	while(T--)
	{
		scanf("%lf%lf%lf%lf%lf%lf", &W, &H, &x, &xe, &ye, &mu);
		double dx = xe - W, dy = ye - H;
		double orx = H * dx / dy;
		double K = dx / (mu * sqrt(dx * dx + dy * dy));
		double dim = (dx / dy) - K / sqrt(1 - K * K);
		double ans = (orx - W + x) / dim;
		if(ans < 0) ans = 0;
		if(ans > H)
			puts("Impossible");
		else
			printf("%.4f\n", ans);
	}

    return 0;
}

