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
#include <sys/resource.h>
void increase_stack_size() {
  const rlim_t ks = 64*1024*1024;
  struct rlimit rl;
  int res=getrlimit(RLIMIT_STACK, &rl);
  if(res==0){
    if(rl.rlim_cur<ks){
      rl.rlim_cur=ks;
      res=setrlimit(RLIMIT_STACK, &rl);
    }
  }
}

typedef long double ld;

const int MAXN = 333;
const ld EPS = 1E-9;

int J, R, N, M, Jf;
ld px[MAXN], py[MAXN], pz[MAXN];
bool fr[MAXN];
int idx[MAXN];
ld arr[MAXN][MAXN];
ld brr[MAXN];

bool isz(ld x)
{
	return abs(x) < EPS;
}

int main() {
	IOS;
	increase_stack_size();

	int t = 0;
	while(cin>>J>>R && !(J==0 && R==0))
	{
		t++;
		Jf = 0;
		M = R;
		for(int i=0; i<J; i++)
		{
			cin>>px[i]>>py[i]>>pz[i];
			fr[i] = isz(pz[i]);
			if(!fr[i])
				idx[i] = Jf++;
		}
		N = Jf * 3;

		for(int i=0; i<N; i++)
			for(int j=0; j<R; j++)
				arr[i][j] = 0;
		for(int i=0; i<N; i++)
			brr[i] = (i%3==2 ? 1 : 0);

		for(int i=0; i<R; i++)
		{
			int a, b;
			cin>>a>>b;
			a--;
			b--;
			ld dx = px[a] - px[b];
			ld dy = py[a] - py[b];
			ld dz = pz[a] - pz[b];
			ld dr = sqrtl(dx*dx + dy*dy + dz*dz);
			dx /= dr;
			dy /= dr;
			dz /= dr;
			if(!fr[a])
			{
				int x = idx[a];
				arr[3*x][i] += dx; 
				arr[3*x+1][i] += dy; 
				arr[3*x+2][i] += dz; 
			}
			if(!fr[b])
			{
				int x = idx[b];
				arr[3*x][i] -= dx; 
				arr[3*x+1][i] -= dy; 
				arr[3*x+2][i] -= dz; 
			}
		}

//		for(int i=0; i<N; i++){for(int j=0; j<R; j++) cout<<arr[i][j]<<" ";cout<<endl;}

		int rank = 0;
		for(int i=0; i<R; i++)
		{
			int piv = -1;
			for(int j=rank; j<N; j++)
			{
				if(!isz(arr[j][i]))
				{
					piv = j;
					break;
				}
			}
			if(piv == -1) continue;
			swap(arr[piv], arr[rank]);
			swap(brr[piv], brr[rank]);

			ld rat = arr[rank][i];
			for(int j=0; j<R; j++)
				arr[rank][j] /= rat;
			brr[rank] /= rat;

			for(int j=0; j<N; j++)
			{
				if(j == rank) continue;
				rat = arr[j][i];
				for(int k=0; k<R; k++)
					arr[j][k] -= rat * arr[rank][k];
				brr[j] -= rat * brr[rank];
			}
			rank++;
		}

//		for(int i=0; i<N; i++) {for(int j=0; j<M; j++) cout<<arr[i][j]<<" "; cout<<" | "<<brr[i]<<endl;}

		bool ok = true;
		for(int i=rank; i<N; i++)
			if(!isz(brr[i]))
				ok = false;

		cout<<"Sculpture "<<t<<": ";
		if(!ok) cout<<"NON-STATIC";
		else if(rank == N) cout<<"STABLE";
		else cout<<"UNSTABLE";
		cout<<endl;
	}

    return 0;
}

