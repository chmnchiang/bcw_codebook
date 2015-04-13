#include<bits/stdc++.h>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#include<vector>
#ifdef ONLINE_JUDGE
#define FILEIO(name) \
  freopen(name".in", "r", stdin); \
  freopen(name".out", "w", stdout);
#else
#define FILEIO(name)
#endif
using namespace std;
#define FZ(n) memset((n),0,sizeof(n))
#define FMO(n) memset((n),-1,sizeof(n))
#define MC(n,m) memcpy((n),(m),sizeof(n))
#define F first
#define S second
#define MP make_pair
#define PB push_back
#define FOR(x,y) for(__typeof(y.begin())x=y.begin();x!=y.end();x++)
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
// Let's Fight!

typedef unsigned long long i64;

const int MX = 70;


int N;
i64 K;
i64 dpA[MX][MX];
i64 dpH[MX][MX][MX];
bool usA[MX][MX], usH[MX][MX][MX];

i64 eta(int, int, int, i64);

void aozora() {
	FZ(usA);
	FZ(usH);
}

void zz(int a) {
	for(int i=0; i<=N; i++) {
		usA[i][a] = false;
		for(int j=0; j<=N; j++) {
			usH[i][j][a] = false;
		}
	}
}

i64 alpha(int n, int prefLen, i64 pref) {
	if(usA[n][prefLen]) return dpA[n][prefLen];

	usA[n][prefLen] = 1;
	i64 ans = (1ull << (n - prefLen));
	for(int k=1; k<=n/2; k++) {
		ans -= eta(n, k, prefLen, pref);
	}
	//cout << "Alpha " << n << ' ' << prefLen << ' ' << ans << endl;
	return dpA[n][prefLen] = ans;
}

i64 boodetrue(int s, i64 pref, int n, int k) {
	int len = s - n + k;
	i64 mask = (1ull << len) - 1;
	i64 a = pref ^ (pref >> (n - k));
	return (a & mask) == 0;
}


i64 eta(int n, int k, int prefLen, i64 pref) {
	
	if(usH[n][k][prefLen]) return dpH[n][k][prefLen];
	//if(n == 1) return 0;
	
	i64 ans;
	if(prefLen <= k) {
		ans = (1ull << (n - 2 * k)) * alpha(k, prefLen, pref);
	} else if(prefLen <= n-k) {
		ans = alpha(k, k, pref) * (1ull << (n - prefLen - k));
	} else {
		ans = alpha(k, k, pref) * boodetrue(prefLen, pref, n, k);
	}

	//cout << "Eta " << n << ' ' << k << ' ' << prefLen << ' ' << ans << endl;
	return dpH[n][k][prefLen] = ans;
}

int main()
{
	FILEIO("borderless");
	IOS;
	while(cin >> N >> K) {
		if(!N && !K) return 0;
		aozora();
		K--;

		i64 t = 0, msk = 1;
		for(int i=0; i<N; i++) {
			i64 cnt = alpha(N, i+1, t);

			//cout << "RES " << K << ' ' << cnt << endl;
			zz(i+1);

			if(K < cnt) {
			} else {
				t += msk;
				K -= cnt;
				cnt = alpha(N, i+1, t);
			}
			msk <<= 1;
		}

		for(int i=0; i<N; i++) {
			if(t&1ull) cout << 'b';
			else cout << 'a';
			t >>= 1;
		}
		cout << endl;

	}
	
	return 0;
}