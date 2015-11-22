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

typedef long long LL;
typedef unsigned long long ULL;
typedef pair<LL, LL> pll;

const long long MOD = 1000000007;
const int MX = 100005;

LL P, N;
pll ip[MX];


int main() {
	int nT;
	IOS;
	cin >> nT;
	for (int t=1; t<=nT; t++) {
		cin >> P;
		N = 0;
		for (int i=0; i<P; i++) {
			cin >> ip[i].F >> ip[i].S;
			N += ip[i].S;
		}
		sort(ip, ip+P);
		ULL point = 0;
		LL nPer = 1;
		ULL sum = 0;
		for (int i=0; i<P; i++) {
			sum = sum + ip[i].S;
			point += sum * ip[i].S;
			if (i != P-1)
				nPer = nPer * (ip[i].S+1) % MOD;
		}
		cout << "Case " << t << ": " << point << " " << nPer << endl;
	}

    return 0;
}

