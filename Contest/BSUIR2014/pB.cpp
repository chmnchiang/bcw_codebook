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
#define IOS ios_base::sync_with_stdio(0); cin.tie(0)
// Let's Fight!

typedef long long ll;

const int MAXN = 101010;

int N, M;
ll a[MAXN], b[MAXN];
int aord[MAXN], bord[MAXN];

bool cmpa(int x, int y) { return a[x] < a[y];}
bool cmpb(int x, int y) { return b[x] < b[y];}

int main() {
	IOS;

	cin>>N>>M;
	for(int i=0; i<N; i++)
		cin>>a[i];
	for(int i=0; i<M; i++)
		cin>>b[i];

	for(int i=0; i<N; i++)
		aord[i] = i;
	for(int i=0; i<M; i++)
		bord[i] = i;

	long long SJ = (ll) M * (M-1) / 2;
	long long SJBJ = 0;
	for(int i=0; i<M; i++)
		SJBJ += i * b[i];
	long long SBJ = 0;
	for(int i=0; i<M; i++)
		SBJ += b[i];

	sort(aord, aord+N, cmpa);
	sort(bord, bord+M, cmpb);

	long long ans = 0;
	int bpos = 0;
	long long m = 0, sj = 0, sbj = 0, sjbj = 0;
	for(int ii=0; ii<N; ii++)
	{
		int i = aord[ii];
		while(bpos < M && b[bord[bpos]] < a[i])
		{
			int j = bord[bpos];
			m++;
			sj += j;
			sbj += b[j];
			sjbj += j * b[j];
			bpos++;
		}
		ans += m * i * a[i] - sj * a[i] - i * sbj + sjbj;
		ans -= (M-m) * i * a[i] - (SJ-sj) * a[i] - i * (SBJ-sbj) + (SJBJ-sjbj);
	}

	cout<<ans<<endl;	

	return 0;
}

