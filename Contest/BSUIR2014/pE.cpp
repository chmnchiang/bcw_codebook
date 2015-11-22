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

typedef pair<int, int> pii;

const int MAXN = 20;

int K;
int N[MAXN], X[MAXN];
vector<pii> vans;

void go(vector<int> vdim, vector<int> vl, vector<int> vr, vector<int> vcur, vector<int> vdir)
{
	int D = vdim.size();
	while(1)
	{
		int cd = D-1;
		while(cd >= 0)
		{
			int nxtval = vcur[cd] + vdir[cd];
			if(nxtval > vr[cd] || nxtval < vl[cd])
			{
				vdir[cd] *= -1;
				cd--;
			}
			else
			{
				vans.PB(MP(vdim[cd], vdir[cd]));
				vcur[cd] = nxtval;
				break;
			}
		}
		if(cd < 0) break;
	}
}

int main() {
	IOS;

	cin>>K;
	for(int i=0; i<K; i++)
		cin>>N[i];
	for(int i=0; i<K; i++)
		cin>>X[i];

	int product = 1;
	vector<int> dims;
	for(int i=0; i<K; i++)
	{
		if(N[i] > 1)
		{
			product *= N[i];
			dims.PB(i);
		}
	}

	int D = dims.size();

	if(product == 1)
	{
		cout<<"Yes"<<endl;
		return 0;
	}
	if(product % 2 == 1 || D == 1)
	{
		cout<<"No"<<endl;
		return 0;
	}

	for(int i=0; i<D; i++)
	{
		int d = dims[i];
		if(N[d] % 2 == 0)
		{
			swap(dims[0], dims[i]);
			break;
		}
	}

	vans.PB(MP(dims[1], 1));
	vector<int> vdim, vl, vr, vcur, vdir;
	for(int i=0; i<D; i++)
	{
		vdim.PB(dims[i]);
		vl.PB(1);
		vr.PB(N[dims[i]]);
		vdir.PB(1);
	}
	vl[1] = 2;
	vcur = vl;

	go(vdim, vl, vr, vcur, vdir);

	vans.PB(MP(dims[1], -1));

	vdim.clear();
	vl.clear();
	vr.clear();
	vcur.clear();
	vdir.clear();

	for(int i=0; i<D; i++)
	{
		if(i == 1) continue;
		vdim.PB(dims[i]);
		vl.PB(1);
		vr.PB(N[dims[i]]);
		vdir.PB(1);
	}
	vcur = vl;
	vcur[0] = N[dims[0]];
	vdir[0] = -1;

	go(vdim, vl, vr, vcur, vdir);

	vector<int> pos;
	for(int i=0; i<K; i++)
		pos.PB(1);
	int cutpoint = 0;
	for(int i=0; i<(int)vans.size(); i++)
	{
		bool ok = true;
		for(int j=0; j<K; j++)
			if(pos[j] != X[j])
				ok = false;
		if(ok)
		{
			cutpoint = i;
		}
		pos[vans[i].F] += vans[i].S;
	}

	cout<<"Yes"<<"\n";
	for(int i=cutpoint; i<(int)vans.size(); i++)
		cout<<vans[i].F+1<<" "<<(vans[i].S == 1 ? "+" : "-")<<"\n";
	for(int i=0; i<cutpoint; i++)
		cout<<vans[i].F+1<<" "<<(vans[i].S == 1 ? "+" : "-")<<"\n";

	return 0;
}

