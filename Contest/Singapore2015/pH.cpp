#include <bits/stdc++.h>
using namespace std;
#define SZ(x) ((int)(x).size())
#define F first
#define S second
#define PB push_back
#define IOS ios_base::sync_with_stdio(0);cin.tie(0)
#define int long long

typedef long long LL;
typedef pair<int,int> pii;

pii operator - (const pii &a, const pii &b) {
	return {a.F-b.F, a.S-b.S};
}
int operator % (const pii &a, const pii &b) {
	return a.F * b.S - b.F * a.S;
}

vector<pii> vec, pt;

bool cmp(pii a, pii b)
{
	return a.F*b.S<a.S*b.F;
}

LL cross(pii o, pii a, pii b) {
	return (a-o) % (b-o);
}

bool check(int N) {
	sort(pt.begin(), pt.end());
	int top=0;
	vector<pii> stk(2*pt.size());
	for (int i=0; i<SZ(pt); i++) {
		while (top>=2 && cross(stk[top-2], stk[top-1], pt[i]) <= 0)
			top--;
		stk[top++] = pt[i];
	}
	for (int i=SZ(pt)-2, t=top+1; i>=0; i--) {
		while (top>=t && cross(stk[top-2], stk[top-1], pt[i]) <= 0)
			top--;
		stk[top++] = pt[i];
	}
	stk.resize(top-1);
//	cout << stk.size() << " " << N << endl;
//	assert(SZ(stk) == N);
}

int32_t main() {
	LL dx, dy;
	int t = 460;
	//t = 4;
	dx = dy = 0;
	for (int i=1; i<=t; i++) {
		for (int j=1; j<=t; j++) {
			if (i*i + j*j > t*t) break;
			if (__gcd(i,j) == 1) {
				vec.PB({i, j});
				dx += i;
				dy += j;
			}
		}
	}
	
	sort(vec.begin(), vec.end(), cmp);

	int x,y;
	x = 0;
	y = 20000000;
	pt.PB({x,y});
	for (auto it:vec) {
		x += it.F;
		y += it.S;
		pt.PB({x,y});
	}
	for (auto it:vec) {
		y -= it.F;
		x += it.S;
		pt.PB({x,y});
	}
	for (auto it:vec) {
		x -= it.F;
		y -= it.S;
		pt.PB({x,y});
	}
	for (auto it:vec) {
		y += it.F;
		x -= it.S;
		pt.PB({x,y});
	}

	for(auto v: pt)
		assert(v.F>=0 && v.F<=4e7 && v.S>=0 && v.S<=4e7);

//	printf("%lld\n", (int)pt.size());
	int N;
	scanf("%lld", &N);
	pt.resize(N);
//	check(N);
//	return 0;	
	for(int i=0; i<N; i++)
		printf("%lld %lld\n", pt[i].F, pt[i].S);

	return 0;
}

